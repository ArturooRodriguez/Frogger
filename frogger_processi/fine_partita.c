#include "header.h"
#include "controllo.h"
#include "main.h"
void gameover(){
    clear() ;
    start_color() ;
    init_pair(12, COLOR_BLACK, COLOR_RED) ;
    bkgd(COLOR_PAIR(12)) ;
    mvprintw(maxy/2,maxx/2-4,"GAME OVER") ;
    refresh() ;
    sleep(3) ;
    return ;
}

void win(){
    clear() ;
    start_color() ;
    init_pair(13, COLOR_BLACK, COLOR_GREEN) ;
    bkgd(COLOR_PAIR(13)) ;
    mvprintw(maxy/2,maxx/2-3,"YOU WON!") ;
    refresh() ;
    sleep(3) ;
    return ;
}