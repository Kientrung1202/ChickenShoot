#include"MainObject.h"

MainObject:: MainObject()
{
    x_val = 0;
    y_val = 0;
    rect_.h = MAIN_HEIGHT;
    rect_.w = MAIN_WIDTH;
    rect_.x = (SCREEN_WIDTH - MAIN_WIDTH)/2  ;
    rect_.y = SCREEN_HEIGHT - MAIN_HEIGHT ;
    frame = 1 ;
    is_move = true;
    this->Colliders.resize(6);
    Colliders[0].w = 10 ;
    Colliders[0].h = 12 ;

    Colliders[1].w = 12 ;
    Colliders[1].h = 14 ;

    Colliders[2].w = 15 ;
    Colliders[2].h = 14 ;

    Colliders[3].w = 30 ;
    Colliders[3].h = 14 ;

    Colliders[4].w = 45 ;
    Colliders[4].h = 14 ;

    Colliders[5].w = 30 ;
    Colliders[5].h = 8  ;
}

MainObject::~MainObject()
{
    if(p_amo_list.size() > 0)
        p_amo_list.clear();
}
/*bool MainObject:: CheckPostionMouse( SDL_Event event )
{
    bool in = true ;
    int x,y;
    SDL_GetMouseState( &x, &y);
    if(x < rect_.x || x > rect_.x + MAIN_WIDTH || y < rect_.y || y > rect_.y + MAIN_HEIGHT ) in = false ;
    return in ;
}*/

void MainObject:: HandleInputAction( SDL_Event event, Mix_Chunk* Fire_Sound)
{
    if( event.type == SDL_KEYDOWN ) {
        switch(event.key.keysym.sym) {
        case SDLK_UP :
            y_val -= SPEED ;
            if(y_val < MAX_SPEED * -1 ) y_val = -1 * MAX_SPEED;
            break;
        case SDLK_DOWN:
            y_val += SPEED;
            if(y_val > MAX_SPEED ) y_val = MAX_SPEED ;
            break;
        case SDLK_RIGHT:
            x_val += SPEED ;
            frame = 2;
            if(x_val > MAX_SPEED ) x_val = MAX_SPEED ;
            break;
        case SDLK_LEFT :
            x_val -= SPEED ;
            frame = 0 ;
            if(x_val <-1* MAX_SPEED ) x_val = -1*MAX_SPEED ;
            break;
        default :
            break;
        }
    } else if (event.type == SDL_KEYUP ) {
        switch (event.key.keysym.sym ) {
        case SDLK_UP :
            y_val = 0 ;
            frame = 1;
            break;
        case SDLK_DOWN :
            y_val  = 0 ;
            frame = 1;
            break ;
        case SDLK_LEFT:
            x_val = 0 ;
            frame = 1;
            break;
        case SDLK_RIGHT :
            x_val = 0 ;
            frame = 1;
            break;
        default :
            break;
        }
    } else if(event.type == SDL_MOUSEBUTTONDOWN ) {
        if(is_move){
        AmoObject *p_amo = new AmoObject();
        if (event.button.button == SDL_BUTTON_LEFT) {
            p_amo->Set_isMove(true);
            p_amo->SetY_val(VAL_AMO_OF_MAIN);
            int x = rect_.x + ( MAIN_WIDTH - NORMAL_BULLET_WIDTH) / 2;
            int y = rect_.y - NORMAL_BULLET_HEIGHT;
            p_amo->Set_widthHeight( NORMAL_BULLET_WIDTH, NORMAL_BULLET_HEIGHT);
            p_amo->SetRect( x,y );
            p_amo->SetCollidersOfBulletOfCraft();
            p_amo_list.push_back( p_amo );
            Mix_PlayChannel(-1, Fire_Sound, 0);
        }
        }
        /* int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
            else if ( event.type == SDL_MOUSEMOTION ) {
                SDL_GetMouseState(&x2, &y2);
                x_val = x2 - x1 ;
                y_val = y2 - y1 ;
                x1 = x2 ;
                y1 = y2 ;
            }*/
    }
}

void MainObject:: HandleMove()//  di chuyen nhan vat
{
    rect_.x += x_val;
    if( rect_.x + MAIN_WIDTH > SCREEN_WIDTH || rect_.x < 0 ) {
        rect_.x -= x_val;
    }
    this->ShiftColliders(MAIN_WIDTH );

    rect_.y += y_val ;
    if( rect_.y + MAIN_HEIGHT > SCREEN_HEIGHT || rect_.y < 0 ) {
        rect_.y -= y_val;
    }
    this->ShiftColliders(MAIN_WIDTH );
    //std::cout<<this->x_val << " " << this->y_val << std::endl;
    //std::cout<< rect_.x <<" "<<rect_.y<<std::endl;
}

void MainObject::RenderMain(SDL_Renderer* screen)
{
    if(is_move ) {
        this->LoadImg(LINK_MAIN_OBJ[frame],screen);
        this->Render(screen, NULL);
        this->HandleMove();
    }
}
void MainObject::RenderAmo(SDL_Renderer* screen)
{
    for (unsigned int i = 0 ; i < p_amo_list.size() ; i++ ) {
        if(p_amo_list[i]->Get_isMove()) {
            p_amo_list[i]->LoadImg("./img/dan_1.png",screen);
            p_amo_list[i]->Render(screen,NULL);
            p_amo_list[i]->HandleMoveOfMain(0);
        } else {
            p_amo_list.erase(p_amo_list.begin()+ i);
        }
    }
}





