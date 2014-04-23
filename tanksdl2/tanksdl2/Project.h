#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h> //хедер, который ссылаетс€ на внешние элементы, предлагаю глобальные const объ€вл€ть здесь, а глобальные не const в майне
#include <iostream>
#include <windows.h>
#include <list>
#include <time.h>
#include <cmath>
#include "SDL_thread.h"
const int tank_H=32;
const int tank_W=32;

const int text_H=tank_H;
const int text_W=tank_H;

const int X_disp=1000;
const int Y_disp=650;
const int bullet_H=12;
const int bullet_W=4;
const int SPEED_BULLETS = 15;
const double rad=57.295779513;

using namespace std;