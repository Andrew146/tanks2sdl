#include "tanks.h"
extern SDL_Renderer *ren;
extern list<bullets*> b;
extern list<tanks*> t;
extern list<StaticTextures*> tex;


tanks::tanks(int _he, int _s, int _a,SDL_Texture* _Texture,int _h,int _w, int _x, int _y, char _whos)
	:	Objects(_Texture,_h, _w, _x,_y, _whos),	health(_he),	speed(_s),angle(_a)
{
}

tanks::~tanks(void)
{
}


void tanks::explosion()
{
	SDL_Rect exp;
	exp = Rect;
	exp.w = exp.h;	
	SDL_RenderCopy(ren, IMG_LoadTexture(ren, "explosion.png"), NULL, &exp); // 
}


void tanks::moveTo(char dir)
{
}

void tanks::Draw() {}

void tanks::fire()
{
	//int xb = Rect.x + ((angle/90) % 2==0)*tank_W/2+(angle==90)*0.7*tank_H-(angle==270)*(tank_W/2+5);//+((angle/90) % 2==1)*tank_H/2-(angle==180)*tank_H/2;
	//int yb = Rect.y + (angle==180)*(tank_H-3)-12*(angle==0)+(angle==90)*(tank_W/2+5)+(angle==270)*0.698*tank_W;//+((angle/90) % 2==1)*tank_W/2+((angle/90) % 2==0)*tank_H/2-(angle==270)*tank_H/2;
	int xb, yb;
	switch (angle) {
	case 0:
		{
			xb = Rect.x + (double(tank_W) / 2.0) - (double(bullet_W) / 2.0);
			yb = Rect.y;
		} break;
	case 90:
		{
			xb = Rect.x + double(tank_W);
			yb = Rect.y + (double(tank_W) / 2.0) - (double(bullet_H) / 2.0);
		} break;
	case 180:
		{
			xb = Rect.x + (double(tank_W) / 2.0) - (double(bullet_W) / 2.0);
			yb = Rect.y + double(tank_W);
		} break;
	case 270:
		{
			xb = Rect.x;
			yb = Rect.y + (double(tank_W) / 2.0) - (double(bullet_H) / 2.0);
		} break;
	}
	b.push_back(new bullets(SPEED_BULLETS, angle, IMG_LoadTexture(ren,"image/fire.png"), bullet_H, bullet_W, xb, yb, whos));
}

bool tanks::am_i_dead()
{
	if (health > 0) return false;
	explosion();
	return true;
}

