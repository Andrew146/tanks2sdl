#include "Objects.h"


Objects::Objects(SDL_Texture* _Texture,int _h,int _w, int _x, int _y, char _whos)
	:Texture(_Texture), whos(_whos)
{
	Rect.h=_h;
	Rect.w=_w;
	Rect.x=_x;
	Rect.y=_y;
}
void Objects::Draw()
{

}


Objects::~Objects(void)
{
}

bool Objects::am_i_dead()
{

	return true;
}