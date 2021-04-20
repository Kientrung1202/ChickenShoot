#ifndef BACKGROUNDMENU_H_
#define BACKGROUNDMENU_H_

#include"CommonFunction.h"
#include"BaseObject.h"

const int WIDTH_BG_MENU = 800;
const int HEIGHT_BG_MENU = 480;
const int WIDTH_CHOSE = 210;
const int HEIGHT_CHOSE = 50 ;
const int EDGE_RESULT = 324 ;

const std::string LINK_BG_MENU = "./img/play/option_menu.jpg" ;
const std::string LINK_CHOSE_PLAY_AGAIN[] = {"./img/play/Again1.png","./img/play/Again2.png" }  ;
const std::string LINK_CHOSE_PLAY[2] = { "./img/play/batdau1.jpg", "./img/play/batdau2.jpg" };
const std::string LINK_CHOSE_QUIT[2] = {"./img/play/btnthoat1.jpg", "./img/play/btnthoat2.jpg"};

const std::string LINK_GOLD_STAR = "./img/play/goldStar.png" ;
const std::string LINK_EMPTY_STAR = "./img/play/emptyStar.png" ;

const std::string LINK_WIN_GAME = "./img/play/bgthangcuoc.png" ;
const std::string LINK_LOSE_GAME = "./img/play/bgthuacuoc.png" ;

#endif // BACKGROUNDMENU_H_
