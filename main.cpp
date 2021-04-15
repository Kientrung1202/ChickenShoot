#include"BaseObject.h"
#include"CommonFunction.h"
#include"MainObject.h"
#include"Threat.h"
#include"Explosive.h"
#include"Font.h"
#include"Menu.h"
#include<stdio.h>
#include<ctime>
#include<vector>
#include<sstream>

using namespace SDLCommonFunc;

bool initData();
bool loadBackground();
void close();
int game();// use play again

const int NUM_OF_NORMAL_Threat = 20 ;

int main(int argc, char* args[])
{
    return game() ;
}

bool initData()
{
    if( SDL_Init(SDL_INIT_VIDEO| SDL_INIT_AUDIO) < 0 ) {
        std::cout<<SDL_GetError();
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1" );
    g_window = SDL_CreateWindow(SCREEN_TITLE.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    if(g_window == NULL ) {
        std::cout<<IMG_GetError();
        return false;
    } else {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL) {
            std:: cout<< SDL_GetError();
            return false;
        } else {
            SDL_SetRenderDrawColor(g_screen, COLOR_RENDER, COLOR_RENDER, COLOR_RENDER, COLOR_RENDER);
            int imgFlags = IMG_INIT_PNG;
            if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
                std::cout<< "SDL_image could not initialize! SDL_image Error: "<< IMG_GetError()<<std::endl ;
                return false ;
            }
        }
    }
    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        std::cout<< "SDL_mixer could not initialize! SDL_mixer Error: "<< Mix_GetError() <<std::endl;
        return false ;
    }
    //init music in game
    g_music = Mix_LoadMUS( "./sound/mainMusic.wav" );
    if( g_music == NULL ) {
        std::cout<< "Failed to load beat music! SDL_mixer Error: "<< Mix_GetError() <<std::endl ;
        return false;
    }
    //init sound effect
    g_normalBullet = Mix_LoadWAV("./sound/normalBullet1.wav");
    if(g_normalBullet == NULL ) std::cout<<"Can't open the g_normalBullet sound"<<std::endl;

    g_normalChickHitted = Mix_LoadWAV("./sound/normalChickHitted.wav");
    if(g_normalChickHitted == NULL ) std::cout<<"Can't open the g_normalChickHitted sound"<<std::endl;

    g_normalChickenDied = Mix_LoadWAV("./sound/normalChickDied.wav");
    if(g_normalChickenDied == NULL ) std::cout<<"Can't open the g_normalChickDied sound"<<std::endl ;

    g_craftBroken = Mix_LoadWAV("./sound/craftBroken.wav");
    if(g_craftBroken == NULL ) std::cout<< "Can't open the g_craftBroken sound "<<std::endl;

    g_gameOver = Mix_LoadWAV("./sound/gameOver.wav");
    if(g_gameOver == NULL ) std::cout<< "Can't open the g_gameOver sound "<<std::endl;

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ) {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
        return false;
    }
    return true;
}

void close()
{
    SDL_DestroyRenderer(g_screen);
    SDL_DestroyWindow(g_window);

    Mix_FreeChunk(g_craftBroken );
    Mix_FreeChunk(g_gameOver);
    Mix_FreeChunk(g_normalChickHitted);
    Mix_FreeChunk(g_normalChickenDied);
    Mix_FreeChunk(g_normalBullet);
    Mix_FreeMusic(g_music);
    g_gameOver = NULL;
    g_normalBullet = NULL;
    g_normalChickenDied = NULL;
    g_normalChickHitted  = NULL;
    g_music = NULL ;
    g_craftBroken = NULL ;
    Mix_Quit();

    TTF_CloseFont(g_font);
    TTF_Quit();

    IMG_Quit();

    SDL_Quit();
    SDL_Delay(2000);
}

int game()
{
    initData() ;
    // background
    BaseObject background ;
    BaseObject background1 ;
    int scrollingOffset = 0;
    background.LoadImg("./img/background.jpg",g_screen);
    background1.LoadImg("./img/background.jpg",g_screen);
    //backgroundMenu
    BaseObject Bkgmenu;
    Bkgmenu.SetRect( (SCREEN_WIDTH - WIDTH_BG_MENU) / 2, (SCREEN_HEIGHT - HEIGHT_BG_MENU ) / 2);
    BaseObject optionPlay, optionQuit ;
    // option


    bool is_quit = false ;
    bool is_play = false ;
    int play_ = 1, quit_ = 1 ;
    bool win = true ;
    Mix_PlayMusic(g_music, -1 );
    // Menu
    while( !is_quit ) {
        while(SDL_PollEvent(&g_event) != 0) {
            if(g_event.type == SDL_QUIT) {
                is_quit = true;
            }
            int x, y ;
            SDL_GetMouseState(&x, & y );
            // option 1
            optionPlay.SetRect( Bkgmenu.GetRect().x + (WIDTH_BG_MENU - WIDTH_CHOSE) / 2 - 20,
                                Bkgmenu.GetRect().y + (HEIGHT_BG_MENU /2  - HEIGHT_CHOSE ) / 2  + 60 );
            optionQuit.SetRect( Bkgmenu.GetRect().x  + (WIDTH_BG_MENU - WIDTH_CHOSE) / 2 -20,
                                Bkgmenu.GetRect().y + (HEIGHT_BG_MENU   + HEIGHT_CHOSE ) / 2   ) ;
            if(x >= optionPlay.GetRect().x && x <= optionPlay.GetRect().x + WIDTH_CHOSE &&
                    y >= optionPlay.GetRect().y && y <= optionPlay.GetRect().y + HEIGHT_CHOSE) {
                play_ = 2 ;
                if(g_event.type == SDL_MOUSEBUTTONDOWN ) {
                    if(g_event.button.button == SDL_BUTTON_LEFT) {
                        is_play = true;
                        is_quit = true;
                    }
                }
            }
            // option 2
            else if(x >= optionQuit.GetRect().x && x <= optionQuit.GetRect().x + WIDTH_CHOSE &&
                    y >= optionQuit.GetRect().y && y <= optionQuit.GetRect().y + HEIGHT_CHOSE ) {
                quit_ = 2 ;
                if(g_event.type == SDL_MOUSEBUTTONDOWN ) {
                    if( g_event.button.button == SDL_BUTTON_LEFT ) {
                        is_quit = true;
                    }
                }
            } else {
                play_ = 1 ;
                quit_ = 1 ;
            }
        }
        // render background
        SDL_RenderClear(g_screen);
        --scrollingOffset;
        if(scrollingOffset < -SCREEN_HEIGHT ) scrollingOffset = 0 ;
        background.SetRect(0, scrollingOffset );
        background1.SetRect(0, scrollingOffset + SCREEN_HEIGHT );
        background.Render( g_screen );
        background1.Render( g_screen );
        // bkg menu
        Bkgmenu.LoadImg(LINK_BG_MENU, g_screen);
        Bkgmenu.Render(g_screen);
        // option
        if(play_ == 1 )
            optionPlay.LoadImg( "./img/play/batdau1.jpg", g_screen ) ;
        else optionPlay.LoadImg("./img/play/batdau2.jpg", g_screen) ;
        optionPlay.Render( g_screen ) ;

        if(quit_ == 1 )
            optionQuit.LoadImg( "./img/play/btnthoat1.jpg", g_screen );
        else optionQuit.LoadImg("./img/play/btnthoat2.jpg", g_screen) ;
        optionQuit.Render( g_screen ) ;
        //std::cout<<quit_<<std::endl ;
        SDL_RenderPresent(g_screen);
        SDL_Delay(20);
    }
    bool playAgain = true ;
    if( is_play == true ) {
        while(playAgain) {
            // inittialize craft
            MainObject craft;
            // inittialize explosive
            Explosive ExpCraft ;
            Explosive ExpNormalChick ;
            // init normal chicken
            std::vector<Threat> normal_chicks ;
            srand(time(0));
            for(int i = 0; i< NUM_OF_NORMAL_Threat; i++ ) {
                Threat copied;
                int rand_x = rand() % (SCREEN_WIDTH - NORMAL_CHICK_WIDTH);
                int rand_y = rand() % (SCREEN_HEIGHT / 3 - NORMAL_CHICK_HEIGHT);
                copied.SetRect(rand_x, rand_y);
                copied.SetX_Y_val( rand() % 2, 1);
                copied.InitNormalAmo();
                normal_chicks.push_back(copied);
            }
            // BaseObject
            BaseObject heartOfMain[3] ;
            const int widthHeart = 25 ;
            for(int i = 0 ; i < 3; i++) {
                heartOfMain[i].SetRect( i* widthHeart, 0);
                heartOfMain[i].LoadImg("./img/craft/mang.png", g_screen) ;
            }

            // initialize number of heart
            int heart = 3 ;
            int score = 0;
            int died_of_boss = 0;
            int died_of_normal_chick[NUM_OF_NORMAL_Threat] = {0};

            // font
            Font g_font ;
            g_font.SetRect(SCREEN_WIDTH - 75 * 2,0, 75, 75 );
            g_font.SetColor(255, 0,255);
            g_font.SetFont("./font/font1.otf", 20 );
            g_font.LoadTexture("Score: ", g_screen);

            Font g_font2 ;
            g_font2.SetRect( SCREEN_WIDTH - 75, 0, 75, 75 );
            g_font2.SetColor(255, 0,255);
            g_font2.SetFont("./font/font1.otf", 20);
            //
            bool isQuit = false ;
            bool exitFinalLoop = false ;
            int star = 0 ;// represent of result

            while( !isQuit ) {
                while (SDL_PollEvent(&g_event) != 0) {
                    if(g_event.type == SDL_QUIT) {
                        isQuit = true;
                        playAgain = false ;
                        exitFinalLoop = true ;
                    }
                    craft.HandleInputAction(g_event, g_normalBullet );
                }
                // render background
                SDL_RenderClear(g_screen);
                --scrollingOffset;
                if(scrollingOffset < -SCREEN_HEIGHT ) scrollingOffset = 0 ;
                background.SetRect(0, scrollingOffset );
                background1.SetRect(0, scrollingOffset + SCREEN_HEIGHT );
                background.Render(g_screen );
                background1.Render(g_screen );

                //render main and amo of main
                craft.RenderMain(g_screen);
                craft.RenderAmo(g_screen);

                //render the hearts
                for(int i = 0 ; i< heart ; i++ ) {
                    heartOfMain[i].Render(g_screen);
                }

                //render text score
                std::stringstream ss;
                ss << score ;
                g_font2.LoadTexture(ss.str().c_str(), g_screen);
                g_font.RenderText(g_screen);
                g_font2.RenderText(g_screen);
                //render normal chick and check colision
                for(int i = 0; i < NUM_OF_NORMAL_Threat ; i++) {

                    Threat* p_copy = &normal_chicks[i] ;
                    //check amo of chick and craft
                    if(p_copy != NULL) {
                        p_copy->RenderNormalChick(g_screen);
                        p_copy->RenderNormalAmo(g_screen);
                        // check amo of normal chick and craft
                        if( p_copy->GetAmo()->GetRect().y + HEIGHT_EGG < SCREEN_HEIGHT ) {
                            if(p_copy->GetAmo()->GetTexture()!= NULL ) {
                                bool  ret = CheckCollision( p_copy->GetAmo()->GetColliders(), craft.GetColliders());
                                if(ret == true ) {
                                    heart-- ;
                                    p_copy->GetAmo()->Set_isMove(false);
                                    p_copy->GetAmo()->Free();
                                    ExpCraft.SetRect(craft.GetRect().x + (MAIN_WIDTH - EXP_CRAFT_EDGE) / 2, craft.GetRect().y + (MAIN_HEIGHT - EXP_CRAFT_EDGE) /2) ;
                                    ExpCraft.RenderExplosive(LINK_EXPLOSIVE_CRAFT,11, g_screen);
                                    Mix_PlayChannel( -1,g_craftBroken, 0 );
                                    if( heart > 0 ) {
                                        SDL_Delay(225);
                                        craft.SetRect((SCREEN_WIDTH - MAIN_WIDTH)/2, SCREEN_HEIGHT - MAIN_HEIGHT) ;
                                    }
                                }
                            }
                        }
                        // check craft and normal chick
                        bool ret2 = CheckCollision(p_copy->GetColliders(), craft.GetColliders() );
                        if( ret2 ) {
                            heart-- ;
                            p_copy->Set_isMove(false);
                            p_copy->Free();
                            ExpCraft.SetRect(craft.GetRect().x + (MAIN_WIDTH - EXP_CRAFT_EDGE) / 2, craft.GetRect().y + (MAIN_HEIGHT - EXP_CRAFT_EDGE) /2) ;
                            ExpCraft.RenderExplosive(LINK_EXPLOSIVE_CRAFT,11, g_screen);
                            Mix_PlayChannel(-1,g_craftBroken, 0 );
                            Mix_PlayChannel(-1, g_normalChickenDied, 0);
                            if( heart > 0 ) {
                                SDL_Delay(225);
                                craft.SetRect((SCREEN_WIDTH - MAIN_WIDTH)/2, SCREEN_HEIGHT - MAIN_HEIGHT) ;
                            }
                        }
                        // check amo of craft and normal chick
                        std::vector<AmoObject*> amoOfCraft = craft.GetAmo();
                        for(int j = 0; j < amoOfCraft.size() ; j++ ) {
                            bool ret3 = CheckCollision(p_copy->GetColliders(), amoOfCraft[j]->GetColliders() );
                            if(ret3) {
                                amoOfCraft[j]->Free();
                                craft.ClearAmo(j);
                                died_of_normal_chick [i]++;
                                Mix_PlayChannel(1, g_normalChickHitted, 0);
                                if(died_of_normal_chick[i] == max_died_of_normal_chick ) {
                                    score += 20;
                                    p_copy->Set_isMove(false);
                                    p_copy->Free();
                                    Mix_PlayChannel(1, g_normalChickenDied, 0);
                                    ExpNormalChick.SetRect(p_copy->GetRect().x + (NORMAL_CHICK_WIDTH - EXP_NORMAL_CHICK_EDGE )/2,
                                                           p_copy->GetRect().y + (NORMAL_CHICK_HEIGHT - EXP_CRAFT_EDGE ) / 2 );
                                    ExpNormalChick.RenderExplosive(LINK_EXPLOSIVE_NORMAL_CHICK, 9, g_screen);
                                }
                            }
                        }
                        if( p_copy->Get_isMove() == false ) {
                            normal_chicks[i].Free() ;
                            p_copy = NULL ;// clear pointer to decrease
                        }
                    }
                }
                SDL_RenderPresent(g_screen);
                SDL_Delay(20);// xu ly FPS

                if( score < 200 ) star = 1 ;
                else if( score <= 360 ) star = 2 ;
                else star = 3  ;

                win = true ; // assigned again to check
                if(heart > 0 ) {
                    for(int i = 0 ; i < NUM_OF_NORMAL_Threat ; i++) {
                        if(normal_chicks[i].GetTexture() != NULL ) {
                            win = false ;
                            break ;
                        }
                    }
                } else {
                    win = false ;
                    craft.Set_isMove(false );
                    Mix_PlayChannel(1, g_gameOver, 0);
                    SDL_Delay(200);
                    isQuit = true ;
                }
                if( win ) {
                    isQuit = true ;
                    SDL_Delay(200 ) ;
                }
            }
            std::cout<<win<<std::endl ;
            int playAgain_ = 1, exit_ = 1 ;

            // render result: win or lose
            BaseObject result ;
            result.SetRect( (SCREEN_WIDTH - EDGE_RESULT ) /2, (SCREEN_HEIGHT - EDGE_RESULT ) / 2 ) ;
            if( win ) result.LoadImg("./img/play/bgthangcuoc.png", g_screen );
            else result.LoadImg("./img/play/bgthuacuoc.png", g_screen) ;

            // render star
            const int EDGE_STAR = 50 ;
            BaseObject star_[3] ;
            if(win ) {
                for(int i = 0 ; i < star ; i++ ) {
                    star_[i].SetRect(result.GetRect().x + i * EDGE_STAR + EDGE_RESULT/ 4, result.GetRect().y - EDGE_STAR ) ;
                    star_[i].LoadImg("./img/play/goldStar.png", g_screen) ;
                }
                for(int i = 2 ; i > star - 1 ; i-- ) {
                    star_[i].SetRect(result.GetRect().x + i * EDGE_STAR + EDGE_RESULT/ 4, result.GetRect().y - EDGE_STAR ) ;
                    star_[i].LoadImg("./img/play/emptyStar.png", g_screen) ;
                }
            } else {
                for(int i = 0 ; i < 3 ; i++ ) {
                    star_[i].SetRect(result.GetRect().x + EDGE_RESULT/4 + i * EDGE_STAR, result.GetRect().y - EDGE_STAR );
                    star_[i].LoadImg("./img/play/emptyStar.png", g_screen) ;
                }
            }

            // loop
            while( !exitFinalLoop ) {
                while(SDL_PollEvent(&g_event) != 0 ) {
                    if(g_event.type == SDL_QUIT) {
                        exitFinalLoop = true;
                        playAgain = false ;
                    }
                    int x, y ;
                    SDL_GetMouseState(&x, & y );

                    optionPlay.SetRect(result.GetRect().x + 55 , result.GetRect().y + 125 );
                    optionQuit.SetRect(result.GetRect().x + 55 , result.GetRect().y + 180 );
                    // option 1
                    if(x >= optionPlay.GetRect().x && x <= optionPlay.GetRect().x + WIDTH_CHOSE &&
                            y >= optionPlay.GetRect().y && y <= optionPlay.GetRect().y + HEIGHT_CHOSE) {
                        playAgain_ = 2 ;
                        if(g_event.type == SDL_MOUSEBUTTONDOWN ) {
                            if(g_event.button.button == SDL_BUTTON_LEFT) {
                                exitFinalLoop = true ;
                            }
                        }
                    }
                    // option 2
                    else if(x >= optionQuit.GetRect().x && x <= optionQuit.GetRect().x + WIDTH_CHOSE &&
                            y >= optionQuit.GetRect().y && y <= optionQuit.GetRect().y + HEIGHT_CHOSE ) {
                        exit_ = 2 ;
                        if(g_event.type == SDL_MOUSEBUTTONDOWN ) {
                            if( g_event.button.button == SDL_BUTTON_LEFT ) {
                                playAgain = false ;
                                exitFinalLoop = true ;
                            }
                        }
                    } else {
                        exit_ = 1;
                        playAgain_  = 1 ;
                    }
                }
                // render background
                SDL_RenderClear(g_screen);
                --scrollingOffset;
                if(scrollingOffset < -SCREEN_HEIGHT ) scrollingOffset = 0 ;
                background.SetRect(0, scrollingOffset );
                background1.SetRect(0, scrollingOffset + SCREEN_HEIGHT );
                background.Render(g_screen );
                background1.Render(g_screen );
                // bkgenu
                result.Render(g_screen) ;
                // option
                if(playAgain_ == 1 )
                    optionPlay.LoadImg("./img/play/Again1.png", g_screen);
                else optionPlay.LoadImg("./img/play/Again2.png", g_screen) ;
                optionPlay.Render(g_screen) ;

                if(exit_ == 1 ) optionQuit.LoadImg("./img/play/btnthoat1.jpg", g_screen);
                else optionQuit.LoadImg("./img/play/btnthoat2.jpg", g_screen) ;
                optionQuit.Render(g_screen) ;

                // star
                for(int i = 0 ; i < 3 ; i ++ ) {
                    star_[i].Render(g_screen) ;
                }

                SDL_RenderPresent(g_screen) ;
                SDL_Delay(40) ;
            }
        }
    }
    close();
}
