#pragma once
#include "tanks.h"
class hero :
	public tanks
{friend class bottanks;
	protected: 
		double t0;
		
public:
	void Draw(); //���������
	void moveTo(char dir); // �������� �� �������� (�������� �� �������� ����� ������� � ������������ ��������)
	hero(int _he, int _s, int _a,SDL_Texture* _Texture,int _h,int _w, int _x, int _y);
	~hero(void);
};

