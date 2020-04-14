#include "Bird.h"

Bird::Bird(){
	srand((unsigned)time(NULL));
	if(rand()%10==9)bird_state=2;
	else if(rand()%5==1)bird_state=1;
	else bird_state=0;
	fly_state=0;
	dis_state=2;
	y=0;//鸟
	Time=0;
	delay=0;
	v=bird_v0;
	a=bird_a0;

	bird[0][0].LoadBitmap(IDB_BITMAP2);
	bird[0][1].LoadBitmap(IDB_BITMAP3);
	bird[0][2].LoadBitmap(IDB_BITMAP4);
	bird[1][0].LoadBitmap(IDB_BITMAP5);
	bird[1][1].LoadBitmap(IDB_BITMAP6);
	bird[1][2].LoadBitmap(IDB_BITMAP7);
	bird[2][0].LoadBitmap(IDB_BITMAP8);
	bird[2][1].LoadBitmap(IDB_BITMAP9);
	bird[2][2].LoadBitmap(IDB_BITMAP10);
}
void Bird::recover(){
	srand((unsigned)time(NULL));
	if(rand()%10==9)bird_state=2;
	else if(rand()%5==1)bird_state=1;
	else bird_state=0;
	fly_state=0;
	dis_state=2;
	y=0;//鸟
	Time=0;
	delay=0;
	v=bird_v0;
	a=bird_a0;
}
void Bird::jump(){
	v=bird_v0;
	a=bird_a0;
	dis_state=2;
	state=state_up;
	PlaySound(MAKEINTRESOURCE(IDR_WAVE_FLY),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
}
void Bird::stop(){
	v=a=0;
}
void Bird::logic(int ID,int &game_state){
	if(ID==0){//开始前
		y=4*sin(Time*PI);
		Time+=0.25;
		fly_state=(fly_state+1)%3;
	}
	else if(ID==1){//正常
		switch(state){
		case state_up:
			v+=a;
			y+=v;
			dis_state--;
			if(dis_state==0){
				state=state_turn;
				Time=0;
			}
			break;
		case state_turn:
			v+=a;
			y+=v;
			if(230+y+48-$d>=400){
				y=400-230-48+$d;
				stop();
				game_state=3;
			}
			dis_state++;
			if(dis_state==1 && Time<=0.4){
				Time+=0.1;
				dis_state=0;
			}
			if(dis_state==6){
				state=state_down;
			}
			break;
		case state_down:
			v+=a;
			y+=v;
			if(delay==0 && 230+y+48-$d>=400){
				y=400-230-48+$d;
				stop();
				PlaySound(MAKEINTRESOURCE(IDR_WAVE_HIT),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
				state=state_delay;
			}
			break;
		case state_delay:
			delay++;
			if(delay==8){game_state=3;}
			break;
		default:break;
		}
		if(dis_state!=6)fly_state=(fly_state+1)%3;
	}
	else if(ID==2){//下落
		delay++;
		if(delay==8){//撞击声延时
			PlaySound(MAKEINTRESOURCE(IDR_WAVE_DIE),AfxGetResourceHandle(),SND_RESOURCE|SND_ASYNC);
		}
		if(delay<60){//下落运算
			y+=v;
			v+=a;
			if(dis_state!=6)dis_state++;
			if(230+y+48-$d>=400){//撞地检测
				y=400-230-48+$d;
				stop();
				if(dis_state==6){delay=60;}
			}
		}else if(delay==66){//坠地后延时
			game_state=3;
		}
	}
}
void Bird::paint(CDC* To,CDC* From){
	//游戏开始前，鸟上下动
	From->SelectObject(&bird[bird_state][fly_state]);
	To->TransparentBlt(65,230+y,48,48,From,9.936,9.936+dis_state*48,48,48,RGB(0,0,0));	
}

