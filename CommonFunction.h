#ifndef COMMONFUNCTION_H_
#define COMMONFUNCTION_H_

#include<SDL.h>
#include<SDL_image.h>
#include<windows.h>
#include<iostream>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<vector>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 675 ;
const int SCREEN_BPP = 32;

const std::string SCREEN_TITLE = "NGUYEN KIEN TRUNG - 20020489 ";
const int COLOR_RENDER = 255;

const std::string LINK_BACK_GROUND = "./img/background.jpg" ;

static SDL_Renderer* g_screen = NULL;
static SDL_Window* g_window = NULL;
static SDL_Event g_event;

static Mix_Music* g_music ;
static Mix_Chunk* g_normalBullet;
static Mix_Chunk* g_normalChickenDied ;
static Mix_Chunk* g_normalChickHitted;
static Mix_Chunk* g_craftBroken ;
static Mix_Chunk* g_gameOver ;

const int COLOR_KEY_R = 255 ;
const int COLOR_KEY_B = 255 ;
const int COLOR_KEY_G = 255 ;

//
namespace SDLCommonFunc
{
    bool CheckCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b );
}

#endif // COMMONFUNCTION_H_
