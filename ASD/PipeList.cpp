#include "PipeList.h"


void PipeList::recover(){
	int count=pipe.GetCount();
	for(int i=0;i<count;i++){
		pipe.RemoveHead();
	}
}
void PipeList::add(){
	Pipe temp;
	pipe.AddTail(temp);
}
void PipeList::logic(int &goals,Bird &bird,int &game_state){//逻辑函数
	int count=pipe.GetCount();
	for(int i=0;i<count;i++){
		Pipe temp=pipe.GetHead();
		pipe.RemoveHead();
		temp.logic();
		//管道移动到64位置
		if(temp.pos_x==64){
			goals+=1;
			mciSendString(_T("close mymusic"), NULL, 0, NULL);//先关再开，注意顺序！！！
			mciSendString(mcicmd, NULL,0, NULL);
			mciSendString(_T("play mymusic"),NULL,0, NULL);	
		}
		if(temp.pos_x>=-70)pipe.AddTail(temp);

		//碰撞检测
		if(23+bird.y+48-$d>400){//与地面
			bird.y=400-230-48+$d;//让鸟处于地面
			bird.stop();
			game_state=2;
		}else if(!(65+48-$d < temp.pos_x || temp.pos_x+52<65+$d)){//与柱子
			if(!(230+bird.y+$d > temp.pos_y+320 && temp.pos_y+420 > 230+bird.y+48-$d)){
				game_state=2;//表示碰撞,游戏结束;
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_HIT),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
			}
		}
	}
	if((pipe.GetTail()).pos_x<=140){
		Pipe temp;
		pipe.AddTail(temp);
	}
}
void PipeList::draw(Pic &All,CDC* To,CDC* From){//绘制函数
	int count=pipe.GetCount();
	for(int i=0;i<count;i++){
		Pipe temp=pipe.GetHead();
		pipe.RemoveHead();
		pipe.AddTail(temp);
		All.pipe_down.TBlt(temp.pos_x,temp.pos_y,To,From);//上柱子
		All.pipe_up.TBlt(temp.pos_x,temp.pos_y+420,To,From);//下柱子
	}
}
//---------------------------------------------------------------
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC	hRes	= ::FindResource(NULL, strResName, strResType);
	HGLOBAL	hMem	= ::LoadResource(NULL, hRes);
	DWORD	dwSize	= ::SizeofResource(NULL, hRes);
	
	// 写入文件
	DWORD dwWrite = 0;  	// 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}
//--------------------------------------------------------------
PipeList::PipeList(){
	// 产生临时文件的文件名
	TCHAR tmpwav[_MAX_PATH];
	::GetTempPath(_MAX_PATH,tmpwav);
	_tcscat_s(tmpwav, _T("testapp_background.wav"));		// VC2008、VC2010 请用 _tcscat_s 函数
	// 将wav 资源提取为临时文件
	//ExtractResource(tmpwav,_T("WAVE"), "background.mp3");
	// 注：如果wave资源的 ID 为宏 IDR_BACKGROUND，这样做：
	ExtractResource(tmpwav, _T("WAVE"), MAKEINTRESOURCE(IDR_WAVE_POINT));
	// 打开音乐
	//TCHAR mcicmd[300];
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"),tmpwav);		// VC2008、VC2010 请用 _stprintf_s 函数
	//mciSendString(mcicmd, NULL,0, NULL);
	// 播放音乐
	//mciSendString(_T("play mymusic"), NULL, 0, NULL);
	// 停止播放并关闭音乐
	//mciSendString(("stop mymusic"), NULL, 0, NULL);
	//mciSendString(("close mymusic"), NULL, 0, NULL);
	// 删除临时文件
	//DeleteFile(tmpmp3);
}