#include "bottanks.h"
#include "tanks.h"
extern SDL_Renderer *ren;
extern list<bullets*> b;
extern list<tanks*> t;
extern list<StaticTextures*> tex;

bottanks::bottanks(int _he, int _s, int _a,SDL_Texture* _Texture,int _h,int _w, int _x, int _y)
	:	tanks(_he, _s, _a,_Texture,_h,_w, _x, _y,'B')
{}


bottanks::~bottanks(void)
{
}
void bottanks::Draw()
{
	randmove();
	SDL_Point p;
	p.x=tank_W/2;
	p.y=tank_H/2;
	SDL_RenderCopyEx(ren, Texture, NULL,&Rect,double(angle), NULL, SDL_FLIP_NONE);

}



void bottanks::randmove()
{
	if(rand() % 10==5) fire();

}