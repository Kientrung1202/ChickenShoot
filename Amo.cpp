#include"Amo.h"

AmoObject::AmoObject()
{
    rect_.x = 0 ;
    rect_.y = 0;
    rect_.w = 0;
    rect_.h = 0;
    x_val = 0;
    y_val = 0;
    is_move = false ;
}

void AmoObject::SetCollidersOfNormalEgg()
{
    Colliders.resize(4);
    Colliders[0].w = 0 ;
    Colliders[0].h = 0 ;
    Colliders[1].w = 8 ;
    Colliders[1].h = 8 ;
    Colliders[2].w = 15;
    Colliders[2].h = 8 ;
    Colliders[3].w = 8 ;
    Colliders[3].h = 4 ;
}

void AmoObject::SetCollidersOfBulletOfCraft()
{
    Colliders.resize(3);
    Colliders[0].w = 0;
    Colliders[0].h = 0 ;
    Colliders[1].w = 12 ;
    Colliders[1].h = 25 ;
    Colliders[2].w = 14 ;
    Colliders[2].h = 27 ;
}

void AmoObject::HandleMoveOfMain( const int& y_border)
{
    rect_.y -= y_val ;
    ShiftColliders(WIDTH_EGG);
    if(rect_.y < y_border) is_move = false ;// gap khung hinh hoac vat can
}

 void AmoObject::Set_widthHeight(int width, int height )
 {
     rect_.w = width;
     rect_.h =height;

 }

void AmoObject::SetY_val( const int &y_val_)
{
    y_val = y_val_ ;
}

void AmoObject::HandleMoveOfThreat(const int& y_border )
{
    rect_.y += y_val;
    ShiftColliders(WIDTH_EGG);
    if(rect_.y + rect_.h > y_border ) is_move = false ;

}
