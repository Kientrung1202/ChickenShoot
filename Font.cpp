#include"Font.h"

Font::Font(){
    color = {255, 255, 255 };
    rect_ = {0 ,0 , 0 , 0 };
    p_texture = NULL ;
}
Font::~Font(){
    Free();
}
void Font::Free(){
     if(p_texture!= NULL) {
        SDL_DestroyTexture(p_texture);
        p_texture= NULL;
        rect_.w = 0;
        rect_.h = 0;
    }
    TTF_CloseFont(font);
}

void Font::SetFont(std::string path , int size )
{
    font = TTF_OpenFont(path.c_str(), size);
}

void Font::LoadTexture(const std::string text , SDL_Renderer* screen )
{
    SDL_Surface* SurfaceMessageText = TTF_RenderText_Solid(font, text.c_str(), color);
    p_texture = SDL_CreateTextureFromSurface(screen, SurfaceMessageText);
}

void Font::RenderText(SDL_Renderer* des, const SDL_Rect* clip )
{
    SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w,rect_.h };
    if(clip != NULL ){
        renderquad.w = clip->w ;
        renderquad.h = clip->h ;
    }
    SDL_RenderCopy(des , p_texture, clip, &renderquad);
}
