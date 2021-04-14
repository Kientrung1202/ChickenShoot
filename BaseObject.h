#ifndef BASEOBJECT_H_
#define BASEOBJECT_H_

#include"CommonFunction.h"

class BaseObject{
public:
    BaseObject();
    ~BaseObject();
    void SetRect(const int& x,const int& y);
    SDL_Rect GetRect(){ return rect_; };
    SDL_Texture* GetTexture() { return p_object_;};
    bool LoadImg(const std::string path, SDL_Renderer* screen );
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void Free();
    std::vector<SDL_Rect>& GetColliders(){ return Colliders; };
    void ShiftColliders(const int WIDTH);// init colliders relative to position
protected:
    SDL_Texture* p_object_;
    SDL_Rect rect_;
    std::vector<SDL_Rect> Colliders;// to check collission per pixcel
};

#endif // BASEOBJECT_H_
