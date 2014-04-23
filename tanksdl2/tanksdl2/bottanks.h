#pragma once
#include "tanks.h"
class bottanks :
	public tanks
{

protected:

	void randmove(); //тестовая функция движения и ведения огня
public:
	void Draw();
	bottanks(int _he, int _s, int _a,SDL_Texture* _Texture,int _h,int _w, int _x, int _y);
	~bottanks(void);
};

