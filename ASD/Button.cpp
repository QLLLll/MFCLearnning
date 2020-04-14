#include "Button.h"

Button::Button(){
	kind=none;
	move=false;
	play_y=score_y=0;
}
void Button::click(CPoint &point){
	if(point.x>=25 && point.x<=25+116 && point.y>=340 && point.y<=340+70){
		kind=play;
		move=true;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE_PANEL),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
	}else if(point.x>=155 && point.x<=155+116 && point.y>=340 && point.y<=340+70){
		kind=score;
		move=true;
		LoadFromResource(IDR_HTML1);
	}else kind=none;
}
void Button::logic(int &game_state){
	if(kind==play){//颤动控制
		if(move==true){
			play_y=2;
			move=false;
		}else{
			play_y=0;
			kind=none;
			game_state=4;
		}
	}else if(kind==score){
		if(move==true){
			score_y=2;
			move=false;
		}else{
			score_y=0;
			kind=none;
		}
	}
}
void Button::draw(Pic &All,CDC* To,CDC* From){
	All.button_play.TBlt(25,340+play_y,To,From);
	All.button_score.TBlt(155,340+score_y,To,From);
}
BOOL Button::LoadFromResource(UINT nRes){//打开网页加载自己写的html文件

	HINSTANCE hInstance = AfxGetResourceHandle();
	ASSERT(hInstance != NULL);//确定有资源

	CString strResourceURL;
	BOOL bRetVal = TRUE;
	LPTSTR lpszModule = new TCHAR[_MAX_PATH];

	if (GetModuleFileName(hInstance, lpszModule, _MAX_PATH)){
		strResourceURL.Format(_T("res://%s/%d"),lpszModule, nRes);
		//Navigate(strResourceURL, 0, 0, 0);
		ShellExecute(NULL,_T("open"),strResourceURL,NULL,NULL,SW_SHOWNORMAL);
	}
	else bRetVal = FALSE;

	delete [] lpszModule;
	return bRetVal;
}
