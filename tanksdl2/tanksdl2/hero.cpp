#include "hero.h"
#include "tanks.h"
#include "Project.h"
extern SDL_Renderer *ren;
extern list<bullets*> b;
extern list<tanks*> t;
extern list<StaticTextures*> tex;


hero::hero(int _he, int _s, int _a, SDL_Texture* _Texture, int _h, int _w, int _x, int _y)
	:tanks(_he, _s, _a, _Texture, _h, _w,  _x, _y, 'H')
{
	t0 = clock()/double(CLOCKS_PER_SEC); // время после последнего выстрела 
}


hero::~hero(void) {}

void hero::moveTo(char dir)
{

	double current_t;
	//if (current_t-t0<0.2)	Sleep((0.2-(current_t-t0))*1000);
	if (dir == 'u') 
	{
		Rect.y -= speed;
		angle = 0;		
	}
	if (dir == 'd') 
	{
		Rect.y += speed;
		angle = 180;	
	}
	if (dir == 'l') 
	{
		Rect.x -= speed;
		angle = 270;		
	}

	if (dir == 'r') 
	{
		Rect.x += speed;
		angle = 90;
	}
	if (dir == 'f') 
	{
		current_t = clock()/double(CLOCKS_PER_SEC);
		if(current_t-t0 > 0.5)
		{
			fire();
			t0 = clock()/double(CLOCKS_PER_SEC);
		}
	}
	//angle = angle % 360;
	//t0=clock()/double(CLOCKS_PER_SEC);
}

void hero::Draw(void)
{
	//SDL_Point p;
	//p.x = tank_W / 2;   // зачем перменная p, если она не используется ??
	//p.y = tank_H / 2;
	SDL_RenderCopyEx(ren, Texture, NULL, &Rect, double(angle), NULL, SDL_FLIP_NONE);	
}
