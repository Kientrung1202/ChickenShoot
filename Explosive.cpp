
#include"Explosive.h"

void Explosive::RenderExplosive(const std::string LINK[], int size , SDL_Renderer* screen )
{
    // size of LINK[]
    for(int i = 0; i< size ; ++i ){
        this->LoadImg( LINK[i] , screen );
        this->Render(screen, NULL);
        SDL_Delay(5); //test statshss
        SDL_RenderPresent(screen);
    }
}


