#ifndef AMO_H_
#define AMO_H_


#include "CommonFunction.h"
#include "BaseObject.h"
#include<vector>

const int NORMAL_BULLET_WIDTH = 16 ;
const int NORMAL_BULLET_HEIGHT = 53 ;

const int WIDTH_EGG = 18 ;
const int HEIGHT_EGG = 23 ;

class AmoObject : public BaseObject
{
public:// hien tai chi khoi tao cho craft, can bo sung cho chicken
    AmoObject();
    ~AmoObject(){;};
    void HandleMoveOfMain ( const int& y_border );
    void SetY_val( const int &y_val_);
    void Set_isMove(bool is_move_){is_move = is_move_; };
    void Set_widthHeight(int width, int height );
    void SetCollidersOfNormalEgg();
    void SetCollidersOfBulletOfCraft();
    int GetY_val() {return y_val;};
    bool Get_isMove() {return is_move; };
    void HandleMoveOfThreat(const int& y );
    // xu ly va cham
private:
    bool is_move;
    int x_val;
    int y_val;
};

#endif // AMO_H_
