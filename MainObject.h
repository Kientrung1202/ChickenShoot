#ifndef MAINOBJECT_H_
#define MAINOBJECT_H_

#include"BaseObject.h"
#include"Amo.h"
#include"CommonFunction.h"
#include<vector>// can xuat hien nhieu anh dan tren man hinh

#define SPEED 8
#define MAX_SPEED 20
#define MAIN_WIDTH  60
#define MAIN_HEIGHT 101
#define VAL_AMO_OF_MAIN 20
#define NUM_OF_FRAME_FLY 5

const std:: string LINK_MAIN_OBJ[3] ={ "./img/craft/craftLeft.png", "./img/craft/craftCenter.png", "./img/craft/craftRight.png" };
const int max_died_of_main = 5 ;

class MainObject: public BaseObject
{
public:
    MainObject();
    ~MainObject();
    //bool CheckPostionMouse( SDL_Event event );
    void HandleInputAction( SDL_Event e_vent, Mix_Chunk* Fire_Sound);
    void HandleMove();// di chuyen nhan vat
    void RenderMain(SDL_Renderer* screen);
    void SetAmo();
    std::vector<AmoObject*> GetAmo(){return p_amo_list; };
    void RenderAmo(SDL_Renderer* screen);
    void ClearAmo(int idx ){ p_amo_list.erase(p_amo_list.begin()+idx) ;};
    void Set_isMove(bool is_move_){ is_move = is_move_ ;};
    bool Get_isMove(){return is_move; };
private:
    int x_val;
    int y_val;
    std:: vector<AmoObject*> p_amo_list;
    int frame;
    bool is_move ;
};

#endif // MAINOBJECT_H_
