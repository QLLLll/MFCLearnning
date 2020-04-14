#pragma once
class Land
{
public:
	int x,speed;
public:
	Land(){x=0;speed=4;}
	void recover(){speed=4;}
	void logic(){x=(x+speed)%51;}
	void start(){speed=4;}
	void stop(){speed=0;}
	void draw(Pic &All,CDC* To,CDC* From){//»æÖÆº¯Êý
		To->TransparentBlt(0,400,288,All.land.y,From,All.land.pos_x*1024+x,All.land.pos_y*1024,288,All.land.y,RGB(0,0,0));
	}
};

