#include"Threat.h"

using namespace std;

Threat::Threat()
{
    y_val_ = 0 ;
    rect_.x = 0;
    rect_.y = 0;
    rect_.w = 0 ;
    rect_.h = 0 ;
    index_broken_egg = 0 ;
    index_chick = 0;
    is_move = true ;
    t_amo = NULL;
    Colliders.resize(5);

    Colliders[0].w = 0 ;
    Colliders[0].h = 5 ;

    Colliders[1].w = 7 ;
    Colliders[1].h = 8 ;

    Colliders[2].w = 45 ;
    Colliders[2].h = 16;

    Colliders[3].w = 70 ;
    Colliders[3].h = 16 ;

    Colliders[4].w = 45 ;
    Colliders[4].h = 8 ;
}

Threat::~Threat()
{
}

void Threat::MoveNormalChick( const int& height)
{
    rect_.x += x_val_;
    if( rect_.x +NORMAL_CHICK_WIDTH > SCREEN_WIDTH ) rect_.x = - NORMAL_CHICK_WIDTH;
    this->ShiftColliders(NORMAL_CHICK_WIDTH);
    rect_.y += y_val_;
    if(rect_.y + NORMAL_CHICK_HEIGHT > height ) is_move = false ;
    this->ShiftColliders(NORMAL_CHICK_WIDTH);
}

void Threat::InitNormalAmo()
{
        t_amo = new AmoObject() ;
        t_amo->SetRect(rect_.x + (NORMAL_CHICK_WIDTH - WIDTH_EGG) / 2, rect_.y + NORMAL_CHICK_HEIGHT);
        t_amo->Set_isMove(true );
        t_amo->SetY_val(5);
        t_amo->SetCollidersOfNormalEgg();
        //std::cout<<t_amo->Get_isMove();
}

void Threat::RenderNormalAmo(SDL_Renderer* screen)
{
    if(t_amo != NULL) {
            if(t_amo->Get_isMove()) {
                t_amo->LoadImg(LINK_NORMAL_EGG, screen);
                t_amo->Render(screen);
                t_amo->HandleMoveOfThreat(SCREEN_HEIGHT);
            } else {
                if( index_broken_egg < 4 && t_amo->GetRect().y + HEIGHT_EGG >= SCREEN_HEIGHT ) {// roi het
                    t_amo->LoadImg(LINK_NORMAL_EGG_BROKEN[index_broken_egg], screen);
                    t_amo->Render(screen);
                    ++index_broken_egg;
                }
                else if(this->GetTexture() != NULL ){
                    this->InitNormalAmo();
                    index_broken_egg = 0;
                }
                else {
                    t_amo->Free();
                }
                }

    }
}
void Threat::RenderNormalChick(SDL_Renderer* screen)
{
    if( is_move ) {
        this->LoadImg(LINK_CHICK_NORMAL[index_chick % 6], screen);
        this->Render( screen );
        this->MoveNormalChick( SCREEN_HEIGHT );
        ++index_chick;
    }
}
