#ifndef EXPLOSIVE_H_
#define EXPLOSIVE_H_

#include"CommonFunction.h"
#include"BaseObject.h"

const int EXP_CRAFT_EDGE = 80 ;
const std::string LINK_EXPLOSIVE_CRAFT[] = {"./img/explosive/craft/explosive0.png", "./img/explosive/craft/explosive1.png",
                                                "./img/explosive/craft/explosive2.png", "./img/explosive/craft/explosive3.png",
                                                "./img/explosive/craft/explosive4.png", "./img/explosive/craft/explosive5.png",
                                                "./img/explosive/craft/explosive6.png", "./img/explosive/craft/explosive7.png",
                                                "./img/explosive/craft/explosive8.png", "./img/explosive/craft/explosive9.png",
                                                "./img/explosive/craft/explosive10.png"};

const int EXP_NORMAL_CHICK_EDGE = 64 ;
const std::string LINK_EXPLOSIVE_NORMAL_CHICK[] = { "./img/explosive/normalChick/explosive0.png", "./img/explosive/normalChick/explosive1.png",
                                            "./img/explosive/normalChick/explosive2.png", "./img/explosive/normalChick/explosive3.png" ,
                                            "./img/explosive/normalChick/explosive4.png", "./img/explosive/normalChick/explosive5.png",
                                            "./img/explosive/normalChick/explosive6.png", "./img/explosive/normalChick/explosive7.png",
                                            "./img/explosive/normalChick/explosive8.png"};



class Explosive : public BaseObject
{
private :
    int frame;
public:
    Explosive(){ frame =0; };
    ~Explosive(){;};
    void SetFrame(int x){ frame = x;};
    int GetFrame(){return frame; } ;
    void RenderExplosive(const std::string LINK[], int size , SDL_Renderer* screen );

};

#endif // EXPLOSIVE_H_
