#pragma once
#include "tanks.h"
class hero :
	public tanks
{
	friend class bottanks;
protected: 
	double t0;

public:
	void Draw(); //отрисовка
	void moveTo(char dir); // отвечает за движение (получает из главного цикла команды и осуществляет движение)
	hero(int _he, int _s, int _a,SDL_Texture* _Texture,int _h,int _w, int _x, int _y);
	~hero(void);
};

