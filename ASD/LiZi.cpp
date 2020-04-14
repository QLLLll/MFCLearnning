#include "LiZi.h"
#define bird_time 0
#define land_time 1

#define before_game 0
#define during_game 1
#define dying_game  2
#define end_game    3
#define start_game  4
#define bird_delay  4

CMyApp myapp;


BOOL CMyApp::InitInstance(){
	m_pMainWnd=new CMainWindow;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainWindow,CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_CLOSE ()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

//CMainWindow的构造函数----------------------------------------------
CMainWindow::CMainWindow(){
	CString strWndClass = AfxRegisterWndClass (
        CS_HREDRAW | CS_VREDRAW,
        myapp.LoadStandardCursor (IDC_ARROW),
        (HBRUSH) (COLOR_3DFACE + 1),
        myapp.LoadIcon (IDIGNORE)
    );

    Create (strWndClass,_T("@-@"),WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION | WS_MINIMIZEBOX);
	//处理窗口位置和尺寸
    CRect rect (0,0,286,512);       //理想客户区窗口矩形形状
    CalcWindowRect (&rect);            //根据分辨率、菜单...计算窗口矩形大小（必须在窗口创建后调用）

    SetWindowPos (NULL, 0, 0, rect.Width (), rect.Height (),
        SWP_NOZORDER | SWP_NOMOVE | SWP_NOREDRAW);

	HICON a = AfxGetApp()->LoadIcon(IDI_ICON1);
	SetIcon(a,true);//设置图标

	CDC *cDC=this->GetDC();
	GetClientRect(&m_client);   //获得窗口的尺寸
	m_cacheDC.CreateCompatibleDC(cDC);
	m_bgcDC.CreateCompatibleDC(cDC);
	m_tempcDC.CreateCompatibleDC(cDC);
	m_tempBitmap.CreateCompatibleBitmap(cDC,m_client.Width(),m_client.Height());
	m_bgBitmap.LoadBitmap(IDB_BITMAP1);
	m_cacheDC.SelectObject(&m_tempBitmap);
	ReleaseDC(cDC); 

	srand((unsigned)time(NULL));
	bg_state=rand()%2;game_state=0;last_state=0;
	goals=best_goals=0;
}//-----------------------------------------------------------------

//消息--------------------------------------------------------------
int CMainWindow::OnCreate(LPCREATESTRUCT lpcs){
	if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

    if (!SetTimer (bird_time,100, NULL)) {
        MessageBox (_T ("Error: SetTimer failed"));
        return -1;
    }
    if (!SetTimer (land_time,60, NULL)) {
        MessageBox (_T ("Error: SetTimer failed"));
        return -1;
    }
    return 0;
}
void CMainWindow::OnTimer(UINT nTimerID){
	switch(nTimerID){
	case bird_time:
		if(game_state==before_game)bird.logic(before_game,game_state);//开始前
		break;
	case land_time:
		if(game_state==before_game){//开始前
			land.logic();//路
		}
		else if(game_state==during_game){//游戏中
			if(bird.state!=bird_delay)land.logic();//路
			bird.logic(1,game_state);//鸟正常运动
			if(bird.state!=bird_delay)pipe.logic(goals,bird,game_state);//管道
		}
		else if(game_state==dying_game){//失败中
			bird.logic(2,game_state);//垂直下落
		}
		else if(game_state==end_game){//显示game-over+计分板+2个按钮
			if(panel.state==finish)button.logic(game_state);
			if(last_state>=10)panel.logic(goals,best_goals);
		}
		else if(game_state==start_game){//重新开始
			restart();
			game_state=before_game;
		}
		break;
	default:break;
	}
	draw();
}
void CMainWindow::OnClose(){
    KillTimer(0);
	KillTimer(1);
    CFrameWnd::OnClose ();
}
void CMainWindow::OnLButtonDown(UINT nFlags, CPoint point){
	if(game_state==0){
		game_state=1;
		pipe.add();
		bird.jump();
	}else if(game_state==1){
		bird.jump();
	}else if(game_state==3){
		button.click(point);
	}
}
void CMainWindow::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags){
	if(game_state==end_game && (::GetKeyState (VK_CONTROL) < 0)){
		screenShot(CRect(0,0,280,508),0,0,"ABCDEFG.bmp");
	}
	if(game_state==during_game && (::GetKeyState (VK_SHIFT) < 0)){
		goals+=10;
	}
}//-----------------------------------------------------------------
//其他辅助函数
void CMainWindow::draw(){
	
	//为什么不直接画到cdc上面，而是要通过cacheDc这个中间变量来画？	
	//为了一次性画完一个过程
	CDC *cDC=this->GetDC();//获得当前窗口的DC   

	m_bgcDC.SelectObject(&m_bgBitmap); 
	pic.bg[bg_state].TBlt(0,0,&m_cacheDC,&m_bgcDC);//背景
	pipe.draw(pic,&m_cacheDC,&m_bgcDC);//所有柱子，开始时柱子数为0，就没画柱子
	land.draw(pic,&m_cacheDC,&m_bgcDC);//道路
	bird.paint(&m_cacheDC,&m_tempcDC);

	if(game_state==before_game ||game_state==during_game ||game_state==dying_game){
		int copy=goals,wei=1;//显示分数
		while(copy/10){wei++;copy/=10;}copy=goals;
		int this_wei,first_pos=142-12*wei-wei/2;
		while(wei--){
			this_wei=copy%10;
			copy/=10;
			pic.font[this_wei].TBlt(first_pos+wei*25,60,&m_cacheDC,&m_bgcDC);//分数
		}
		
		if(game_state==before_game){
			pic.text_ready.TBlt(50,140,&m_cacheDC,&m_bgcDC);//ready图标
			pic.tutorial.TBlt(85,220,&m_cacheDC,&m_bgcDC);//指示
		}
	}
	else if(game_state==end_game || game_state==start_game){
		if(last_state==0){
			pic.text_game_over.TBlt(50,105,&m_cacheDC,&m_bgcDC);//game_over图标
			last_state=1;
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_PANEL),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
		}
		else if(last_state>=1){
			pic.text_game_over.TBlt(50,115,&m_cacheDC,&m_bgcDC);//game_over图标(0->1实现动画效果）
			if(last_state==10){
				panel.draw(pic,&m_cacheDC,&m_bgcDC);//贴上计分板
				if(panel.state==2){
					button.draw(pic,&m_cacheDC,&m_bgcDC);
				}
			}else last_state++;
		}
	}

	m_cacheDC.SelectObject(&m_tempBitmap);
	//把缓存DC上的所有图片绘制上去
	cDC->BitBlt(0,0,m_client.Width(),m_client.Height(),&m_cacheDC,0,0,SRCCOPY); 

	ReleaseDC(cDC);
}
void CMainWindow::restart(){
	bg_state=rand()%2;
	game_state=0;
	last_state=0;
	goals=0;

	pipe.recover();//柱子
	land.recover();
	bird.recover();//鸟
	panel.recover();//计分板
}
void CMainWindow::screenShot(CRect rect,int left,int top,char *name){//截取窗口的大小，位置，名字（保存在默认路径下)
    CBitmap*  m_pBitmap; 	                                                 // 加入类成员
	CFrameWnd* pMainFrame = (CFrameWnd*)AfxGetMainWnd();                     // 获得截图窗口的指针，默认为主窗口，可以更改为其他的窗口。
   	CPaintDC   dc(pMainFrame); 
	
	m_pBitmap=new   CBitmap;   
	m_pBitmap->CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());   

	CDC   memDC;  
	memDC.CreateCompatibleDC(&dc); 
	CBitmap memBitmap, *oldmemBitmap;                                        // 建立和屏幕兼容的bitmap
    memBitmap.CreateCompatibleBitmap(&dc, rect.Width(),rect.Height());
	
    oldmemBitmap = memDC.SelectObject(&memBitmap);//将memBitmap选入内存DC
    memDC.BitBlt(0, 0, rect.Width(),rect.Height(), &dc,left, top, SRCCOPY);  // 调解高度宽度
	BITMAP bmp;
    memBitmap.GetBitmap(&bmp);                                               // 获得位图信息 
    
    FILE *fp = fopen(name, "w+b");
	
    BITMAPINFOHEADER bih = {0};                                              // 位图信息头
    bih.biBitCount = bmp.bmBitsPixel;                                        // 每个像素字节大小
    bih.biCompression = BI_RGB;
    bih.biHeight = bmp.bmHeight;                                             // 高度
    bih.biPlanes = 1;
    bih.biSize = sizeof(BITMAPINFOHEADER);
    bih.biSizeImage = bmp.bmWidthBytes * bmp.bmHeight;                       // 图像数据大小
    bih.biWidth = bmp.bmWidth;                                               // 宽度
    
    BITMAPFILEHEADER bfh = {0};                                              // 位图文件头
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);     // 到位图数据的偏移量
    bfh.bfSize = bfh.bfOffBits + bmp.bmWidthBytes * bmp.bmHeight;            // 文件总的大小
    bfh.bfType = (WORD)0x4d42;
    
    fwrite(&bfh, 1, sizeof(BITMAPFILEHEADER), fp);                           //写入位图文件头
    
    fwrite(&bih, 1, sizeof(BITMAPINFOHEADER), fp);                           //写入位图信息头
    
    byte * p = new byte[bmp.bmWidthBytes * bmp.bmHeight];                    //申请内存保存位图数据
	
    GetDIBits(memDC.m_hDC, (HBITMAP) memBitmap.m_hObject, 0, rect.Height(), p, 
    (LPBITMAPINFO) &bih, DIB_RGB_COLORS);                                    //获取位图数据
	
    fwrite(p, 1, bmp.bmWidthBytes * bmp.bmHeight, fp);                       //写入位图数据
    delete [] p;	
    fclose(fp);
	memDC.SelectObject(oldmemBitmap);
	memDC.DeleteDC();
}





	



