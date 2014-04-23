#include "Project.h"
#include "Graphics.h"
#include "tanks.h"
#include "bullets.h"
#include "StaticTextures.h"
#include "hero.h"
#include "bottanks.h"
												//кординаты окна    //0-------------------------->x
																	//|
																	//|
SDL_Renderer *ren; //рендер											//|	
list<tanks*> t; //лист танков (враги, герои)						//|
list<bullets*> b; //лист всех снарядов								//|
list<StaticTextures*> tex; //лист всех текстур						//v y

// что это за функция??
int tfn(void *unused);  

int main(int argc, char* args[])
{
	srand(time(NULL));
	Graphics grafika; //создаём экземпляр класса, отвечающего за инициализацию СДЛ
	grafika.instal_sdl(); //инициализируем СДЛ
	 
	hero Hero(10, 5, 90, IMG_LoadTexture(ren, "image/battlecity_playerA1.png"), tank_H, tank_W, 90, 100); //создаём персонажа, конструктор вида  (health, speed,anlge, texture, heigh, weight, x,y)

	int number = 4; //число танков противника

	//инициализируем БГ
	SDL_Texture *backgroundT = IMG_LoadTexture(ren, "image/background.png");
	SDL_Rect background;
	background.x = 0;   //Смещение полотна по Х
	background.y = 0;   //Смещение полотна по Y
	background.w = X_disp; //Ширина полотна
	background.h = Y_disp; //Высота полотна
	SDL_RenderClear(ren); //Очистка рендера
	SDL_RenderCopy(ren, backgroundT, NULL, &background); //отправляем в буффер
	//

	SDL_RenderPresent(ren);

	t.push_back(&Hero); //добавляем героя
	
	int j; 
	for (j=0; j<number; j++) //создаём и добавляем в лист танков противников, тестовая версия с рандомными координатами, конструктор такой же
		t.push_back(new bottanks(10, 20, (rand() % 4)*90, IMG_LoadTexture(ren,"image/battlecity_enemy1.png"), tank_H, tank_W, rand() % 500+100, rand() % 200+100));

	for (j=0; j<5; j++) //создаём и добавляем текстуры
		tex.push_back(new StaticTextures(13, IMG_LoadTexture(ren,"image/block_9.png"), text_H,text_W, rand() % 500+100, rand() % 200+100));

	//создаём объекты для обработки событий
	const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
	SDL_Event event;
	bool quit = false;
	//


	while(!quit) //бесконечный цикл обработки событий
	{
		SDL_RenderClear(ren); //очищаем буфер
		SDL_RenderCopy(ren, backgroundT, NULL, &background); //отправляем фон

		//захват и сдвиг очериди событий
		SDL_PollEvent(&event); 
		SDL_PumpEvents(); 
		//

		//player 
		if(event.type == SDL_QUIT) 
			exit(-1); 
		//считываем клавиатуру и подаем команду танку игрока
		// добавил else, чтобы не ездили по диагонале 
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

		//пробегаем по списку танков, куда входит и герой. У разных классов своя функция  draw 
		list<tanks*>::iterator k;
		for(list<tanks*>::iterator i=t.begin(); i!=t.end(); i++)
		{
			(*i)->Draw();
			if((*i)->am_i_dead())  // проверка на смерть танка
			{ 
				k=i;  
				k++;
				t.erase(i);
				i=k;
				i--;
			}
		}
		//пробегаем по текстурам
		list<StaticTextures*>::iterator m;
		for(list<StaticTextures*>::iterator i=tex.begin(); i!=tex.end(); i++)
		{
			(*i)->Draw();
			if((*i)->am_i_dead())  // проверка на удаление текстуры
			{ 
				m=i;  
				m++;
				tex.erase(i);
				i=m;
				i--;
			}
		}
		//
		//пробегаем по всем пулям
		list<bullets*>::iterator j;
		for(list<bullets*>::iterator i=b.begin(); i!=b.end(); i++)
		{

			(*i)->Draw(); //функция отрисовки (сичтает смещение и подаёт в буфер)
			if((*i)->dead_check() || (*i)->strike())  // проверка на вылет за экран и на попадание в объект(пока что танки)
			{ 
				j=i;  
				j++;
				b.erase(i);
				i=j;
				i--;
			}			 
		}
		//
		Sleep(100); //спим
		SDL_RenderPresent(ren); //вывод на экран
	}
	SDL_RenderClear(ren); //Очистка рендера

	// завершение работы
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