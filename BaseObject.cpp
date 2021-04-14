
#include"BaseObject.h"

BaseObject :: BaseObject()
{
    p_object_ = NULL;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
}

BaseObject:: ~BaseObject()
{
    Free();
}

void BaseObject::SetRect(const int& x, const int& y)
{
    rect_.x = x;
    rect_.y = y;
}

bool BaseObject::LoadImg(const std::string path,SDL_Renderer* screen )
{
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load( path.c_str());
    if( loadSurface != NULL ) {
        // k can khi dung anh k nen
        //SDL_SetColorKey( loadSurface,SDL_TRUE,SDL_MapRGB(loadSurface->format, COLOR_KEY_R, COLOR_KEY_G, COLOR_KEY_B));
        newTexture = SDL_CreateTextureFromSurface(screen, loadSurface );
        if(newTexture != NULL) {
            rect_.w = loadSurface->w;
            rect_.h = loadSurface->h;
        }
        SDL_FreeSurface(loadSurface);
    } else {
        std:: cout<<SDL_GetError();
    }
    p_object_ = newTexture;
    return p_object_!= NULL;
}

void BaseObject::Render( SDL_Renderer* des, const SDL_Rect* clip )
{
    SDL_Rect renderquad = { rect_.x, rect_.y, rect_.w,rect_.h };
    if(clip != NULL ){
        renderquad.w = clip->w ;
        renderquad.h = clip->h ;
    }
    SDL_RenderCopy(des , p_object_, clip, &renderquad);
}

void BaseObject::Free()
{
    if(p_object_!= NULL) {
        SDL_DestroyTexture(p_object_);
        p_object_= NULL;
        rect_.w=0;
        rect_.h = 0;
    }
    // clear element in vector Colliders
    Colliders.resize(0);
}

void BaseObject::ShiftColliders(const int WIDTH )
{
    // the row offset
    int r = 0 ;
    for (int set_ = 0 ; set_ < Colliders.size() ; set_ ++)
    {
        // set x, y for Collider relative
        // x = center , y += multiple colliders[i].h
        Colliders[set_].x = rect_.x + ( WIDTH - Colliders[set_].w) / 2;
        Colliders[set_].y = rect_.y + r ;
        r += Colliders[set_].h ;
    }
}

