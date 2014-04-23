#pragma once
#include "Project.h" //инициализирует СДЛ
class Graphics
{
public:
	SDL_Window *win;
	//SDL_Renderer *ren;
	SDL_DisplayMode displayMode;
	void instal_sdl();
	Graphics(void);
	~Graphics(void);
};

