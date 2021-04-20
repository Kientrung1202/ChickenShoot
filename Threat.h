#ifndef THREAT_H_
#define THREAT_H_

#include"CommonFunction.h"
#include"BaseObject.h"
#include"Amo.h"
#include<stdio.h>
#include<time.h>
#include<vector>

const int Val_Of_Normal_Chick = 10;
const int Val_Of_Big_Chick = 20 ;
const std::string LINK_CHICK_NORMAL[] = {"./img/chick/ga0.png","./img/chick/ga1.png", "./img/chick/ga2.png",
                                                    "./img/chick/ga3.png", "./img/chick/ga4.png", "./img/chick/ga5.png"};
const std :: string LINK_NORMAL_EGG_BROKEN[] = {"./img/trungvo/trungvo0.png", "./img/trungvo/trungvo1.png",
                                                            "./img/trungvo/trungvo2.png", "./img/trungvo/trungvo3.png"};
const std::string LINK_NORMAL_EGG = "./img/trung.png";

#define NORMAL_CHICK_WIDTH 85
#define NORMAL_CHICK_HEIGHT 64

const int max_died_of_boss = 15 ;
const int max_died_of_normal_chick = 2;

class Threat : public BaseObject
{
private :
    int y_val_;
    int x_val_;
    AmoObject* t_amo;
    int index_broken_egg ;// tao hoat hinh
    int index_chick;// tao hoat hinh
    bool is_move ;
public:
    Threat();
    ~Threat();
    int GetY_val(){return y_val_ ; };
    int GetX_val(){return x_val_ ; };
    void Set_index_chick(int _index ){index_chick = _index ;}
    AmoObject* GetAmo() {return t_amo; };
    bool Get_isMove(){return is_move ;};
    void Set_isMove(bool _move ){ is_move = _move ;}
    void Set_Amo(AmoObject* t_amo_ ){ t_amo = t_amo_ ;};
    void SetX_Y_val(const int& x, const int& y){
        y_val_ = y ;
        x_val_ = x ;
        };
    void MoveNormalChick(const int& height );
    void RenderNormalChick(SDL_Renderer* screen);
    void InitNormalAmo();
    void RenderNormalAmo(SDL_Renderer* screen);
};

#endif // THREAT_H_
