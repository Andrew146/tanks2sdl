#include "Project.h"
#include "Graphics.h"
#include "tanks.h"
#include "bullets.h"
#include "StaticTextures.h"
#include "hero.h"
#include "bottanks.h"
												//��������� ����    //0-------------------------->x
																	//|
																	//|
SDL_Renderer *ren; //������											//|	
list<tanks*> t; //���� ������ (�����, �����)						//|
list<bullets*> b; //���� ���� ��������								//|
list<StaticTextures*> tex; //���� ���� �������						//v y

// ��� ��� �� �������??
int tfn(void *unused);  

int main(int argc, char* args[])
{
	srand(time(NULL));
	Graphics grafika; //������ ��������� ������, ����������� �� ������������� ���
	grafika.instal_sdl(); //�������������� ���
	 
	hero Hero(10, 5, 90, IMG_LoadTexture(ren, "image/battlecity_playerA1.png"), tank_H, tank_W, 90, 100); //������ ���������, ����������� ����  (health, speed,anlge, texture, heigh, weight, x,y)

	int number = 4; //����� ������ ����������

	//�������������� ��
	SDL_Texture *backgroundT = IMG_LoadTexture(ren, "image/background.png");
	SDL_Rect background;
	background.x = 0;   //�������� ������� �� �
	background.y = 0;   //�������� ������� �� Y
	background.w = X_disp; //������ �������
	background.h = Y_disp; //������ �������
	SDL_RenderClear(ren); //������� �������
	SDL_RenderCopy(ren, backgroundT, NULL, &background); //���������� � ������
	//

	SDL_RenderPresent(ren);

	t.push_back(&Hero); //��������� �����
	
	int j; 
	for (j=0; j<number; j++) //������ � ��������� � ���� ������ �����������, �������� ������ � ���������� ������������, ����������� ����� ��
		t.push_back(new bottanks(10, 20, (rand() % 4)*90, IMG_LoadTexture(ren,"image/battlecity_enemy1.png"), tank_H, tank_W, rand() % 500+100, rand() % 200+100));

	for (j=0; j<5; j++) //������ � ��������� ��������
		tex.push_back(new StaticTextures(13, IMG_LoadTexture(ren,"image/block_9.png"), text_H,text_W, rand() % 500+100, rand() % 200+100));

	//������ ������� ��� ��������� �������
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	bool quit = false;
	//


	while(!quit) //����������� ���� ��������� �������
	{
		SDL_RenderClear(ren); //������� �����
		SDL_RenderCopy(ren, backgroundT, NULL, &background); //���������� ���

		//������ � ����� ������� �������
		SDL_PollEvent(&event); 
		SDL_PumpEvents(); 
		//

		//player 
		if(event.type == SDL_QUIT) 
			exit(-1); 
		//��������� ���������� � ������ ������� ����� ������
		// ������� else, ����� �� ������ �� ��������� 
		if((keyboardState[SDL_SCANCODE_UP]))   
			Hero.moveTo('u');		
		else
			if((keyboardState[SDL_SCANCODE_DOWN]))
				Hero.moveTo('d');
			else
				if((keyboardState[SDL_SCANCODE_LEFT]))
					Hero.moveTo('l');
				else
					if((keyboardState[SDL_SCANCODE_RIGHT]))
						Hero.moveTo('r');

		if((keyboardState[SDL_SCANCODE_SPACE]))
			Hero.moveTo('f');
		//
		///

		//��������� �� ������ ������, ���� ������ � �����. � ������ ������� ���� �������  draw 
		list<tanks*>::iterator k;
		for(list<tanks*>::iterator i=t.begin(); i!=t.end(); i++)
		{
			(*i)->Draw();
			if((*i)->am_i_dead())  // �������� �� ������ �����
			{ 
				k=i;  
				k++;
				t.erase(i);
				i=k;
				i--;
			}
		}
		//��������� �� ���������
		list<StaticTextures*>::iterator m;
		for(list<StaticTextures*>::iterator i=tex.begin(); i!=tex.end(); i++)
		{
			(*i)->Draw();
			if((*i)->am_i_dead())  // �������� �� �������� ��������
			{ 
				m=i;  
				m++;
				tex.erase(i);
				i=m;
				i--;
			}
		}
		//
		//��������� �� ���� �����
		list<bullets*>::iterator j;
		for(list<bullets*>::iterator i=b.begin(); i!=b.end(); i++)
		{

			(*i)->Draw(); //������� ��������� (������� �������� � ����� � �����)
			if((*i)->dead_check() || (*i)->strike())  // �������� �� ����� �� ����� � �� ��������� � ������(���� ��� �����)
			{ 
				j=i;  
				j++;
				b.erase(i);
				i=j;
				i--;
			}			 
		}
		//
		Sleep(100); //����
		SDL_RenderPresent(ren); //����� �� �����
	}
	SDL_RenderClear(ren); //������� �������

	// ���������� ������
	t.clear();
	b.clear();
	tex.clear();
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(grafika.win);
	SDL_Quit();

	return 0;
}



/*int tfn(void *unused)
{
	SDL_Init(SDL_INIT_EVENTS);
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	bool quit = false;

	/*	if(event.type == SDL_QUIT) 
	exit(-1); 
	SDL_WaitEvent(&event);
	SDL_PumpEvents(); 

	if((keyboardState[SDL_SCANCODE_UP]))
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYUP)	KEY='u'; }

	if((keyboardState[SDL_SCANCODE_DOWN]))
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYUP)	KEY='d';}

	if((keyboardState[SDL_SCANCODE_LEFT]))
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYUP)	KEY='l';}

	if((keyboardState[SDL_SCANCODE_RIGHT]))
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYUP)	KEY='r';}

	if((keyboardState[SDL_SCANCODE_SPACE]))
	{
		SDL_WaitEvent(&event);
		if (event.type==SDL_KEYUP)	KEY='f';}


	return 0;}*/