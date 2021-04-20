#ifndef FONT_H_
#define FONT_H_

#include"CommonFunction.h"
#include"BaseObject.h"

const std::string LINK_FONT_1 = "./font/font4.otf";

class Font
{
public :
    Font();
    ~Font();
    void SetRect(int x_ , int y_, int w_, int h_){ rect_ = {x_, y_, w_, h_};};
    void SetFont( std::string path, int size );
    void SetColor(unsigned char r , unsigned char b , unsigned char g ){color = {r,b,g};};
    void LoadTexture(const std::string text, SDL_Renderer* screen);
    void RenderText(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
private:
    SDL_Texture* p_texture ;
    SDL_Rect rect_;
    SDL_Color color ;
    TTF_Font* font;
};

#endif // FONT_H_
