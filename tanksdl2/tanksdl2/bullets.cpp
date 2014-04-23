#include "bullets.h"
#include "tanks.h"
#include "StaticTextures.h"
extern SDL_Renderer *ren;
extern list<bullets*> b;
extern list<tanks*> t;
extern list<StaticTextures*> tex;


bullets::bullets(int _s, int _a, SDL_Texture* _Texture, int _h, int _w, int _x, int _y, char _whos)
	: Objects(_Texture, _h, _w, _x, _y, _whos), speed(_s), angle(_a)
{
}


bullets::~bullets(void) {}

void bullets::fly()
{
	Rect.x += speed*((angle==90) - (angle==270));
	Rect.y += speed*(-(angle==0) + (angle==180));
}
void bullets::Draw()
{
	fly();
	SDL_Point p;
	p.x=tank_W/2;
	p.y=tank_H/2;
	SDL_RenderCopyEx(ren, Texture, NULL,&Rect,double(angle), NULL, SDL_FLIP_NONE);

}
bool bullets::dead_check()
{
	if((Rect.x<0) || (Rect.x>1000) || (Rect.y<0) || (Rect.y>800)) return true;

	return false;}

bool bullets::strike() //проверяет попадание в объект
{
	int cx,cy; //задание левого угла для положения на боку(особенность отрисовки: тестура поварачивается, а коорд. верхнего угла прежние)

	for (list<tanks*>::iterator i=t.begin(); i!=t.end(); i++)
	{
		//проверяем танки
		if ( ((Rect.x>(*i)->Rect.x) && (Rect.x<(*i)->Rect.x+tank_W)) && ((Rect.y>(*i)->Rect.y-((*i)->angle==180)*10) && (Rect.y<(*i)->Rect.y+tank_H)) && (((*i)->angle==0) || ((*i)->angle==180)))
		{
			if  ((*i)->whos!=whos) //чужак получит урон, но снаряд об своего тоже ичезнет
				(*i)->health-=4; 
			return true;
		}
		cx=(*i)->Rect.x-tank_H/2+tank_W/2;
		cy=(*i)->Rect.y+tank_H/2-tank_W/2;
		if ( ((Rect.x>cx) && (Rect.x<cx+tank_H) && (Rect.y+bullet_H-2>cy) && (Rect.y+bullet_H-2<cy+tank_W)) && (((*i)->angle==90) || ((*i)->angle==270)) )
		{
			if  ((*i)->whos!=whos) //чужак получит урон, но снаряд об своего тоже ичезнет
				(*i)->health-=4; 
			return true;
		}
		//

		//проверяем текстуры
		for (list<StaticTextures*>::iterator i=tex.begin(); i!=tex.end(); i++)
		{


			if ( ((Rect.x>(*i)->Rect.x-2) && (Rect.x<(*i)->Rect.x+text_W+2)) && ((Rect.y+bullet_H-2>(*i)->Rect.y-2) && (Rect.y+bullet_H-2<(*i)->Rect.y+text_H+2)) )
			{
				(*i)->health-=4;
				if ((*i)->health<10) (*i)->Texture=IMG_LoadTexture(ren,"textura1.jpg");
				if ((*i)->health<7) (*i)->Texture=IMG_LoadTexture(ren,"textura2.jpg");
				return true;
			}

		}
	}

	return false;
}

