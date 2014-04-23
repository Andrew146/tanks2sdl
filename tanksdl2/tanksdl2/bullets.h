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
	void fly(); //���������� ��������
public:
	bool dead_check(); //�������� �������� �� �� ����, ���������� true ���� �������
	bool strike(); //�������� ��������� � ����� ���� ���� ��� ������
	void Draw(); // ���������
	bullets(int _s, int _a, SDL_Texture* _Texture, int _h, int _w, int _x, int _y, char _whos);
	~bullets(void);

};

