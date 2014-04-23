#pragma once
#include "objects.h"
#include "tanks.h"
#include "StaticTextures.h"

class bullets :
	public Objects
{
private:
	int speed;
	int angle;
	void fly(); //определяет смещение
public:
	bool dead_check(); //проверка вылетела ли за зону, возвращает true если улетела
	bool strike(); //проверка попадания в какой либо танк или мишень
	void Draw(); // отрисовка
	bullets(int _s, int _a, SDL_Texture* _Texture, int _h, int _w, int _x, int _y, char _whos);
	~bullets(void);

};

