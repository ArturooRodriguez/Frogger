#include "header.h"
#include "main.h"
bool menu(){
    clear() ;
    getmaxyx(stdscr, maxy, maxx) ;
    init_pair(8, COLOR_WHITE, COLOR_WHITE) ;
    init_pair(9, COLOR_GREEN, COLOR_GREEN) ;
    init_pair(23, COLOR_WHITE, COLOR_BLUE) ;
    int option = 1 ;
    bkgd(COLOR_PAIR(23)) ;
    box(stdscr, ACS_VLINE, ACS_HLINE) ;
    title_maker(option) ;
    graphic_frog() ;
    refresh() ;
    
    while(true){
        attron(COLOR_PAIR(23)) ;
        mvprintw(21, 24, "PRESS SPACEBAR TO START PLAYING!") ;
        attroff(COLOR_PAIR(23)) ;
        int s =  getch() ;
        switch(s){
            case KEY_LEFT:
                option = 1 ;
                title_maker(option) ;
                break ;          

            case KEY_RIGHT:
                option = 2 ;
                title_maker(option) ;
                break ;
            
            case 32:
                if(option == 1)
                    return TRUE ;
                else
                    return FALSE ;
                break ;
        }
    }
}


void title_maker(int option){
    init_pair(10, COLOR_WHITE, COLOR_WHITE) ;
    init_pair(11, COLOR_GREEN, COLOR_GREEN) ;
    
    if(option == 1)
        attron(COLOR_PAIR(11)) ;
    else
        attron(COLOR_PAIR(10)) ;
    
    mvprintw(3, 13, "      ") ;
    mvprintw(4,13, "  ") ;
    mvprintw(4, 17, "  ") ;
    mvprintw(5, 13, "      ") ;
    mvprintw(6, 13, "  ") ;
    mvprintw(7, 13, "  ") ;

    mvprintw(9, 13, "  ") ;
    mvprintw(10, 13, "  ") ;
    mvprintw(11, 13, "  ") ;
    mvprintw(12, 13, "  ") ;
    mvprintw(13, 13, "      ") ;

    mvprintw(15, 13, "      ") ;
    mvprintw(16, 13, "  ") ;
    mvprintw(16, 17, "  ") ;
    mvprintw(17, 13, "      ") ;
    mvprintw(18, 13, "  ") ;
    mvprintw(18, 17, "  ") ;
    mvprintw(19, 13, "  ") ;
    mvprintw(19, 17, "  ") ;

    mvprintw(21, 13, "  ") ;
    mvprintw(21, 17, "  ") ;    
    mvprintw(22, 13, "      ") ;
    mvprintw(23, 15, "  ") ;
    mvprintw(24, 15, "  ") ;
    mvprintw(25, 15, "  ") ;

    if(option == 1)
        attron(COLOR_PAIR(10)) ;
    else
        attron(COLOR_PAIR(11)) ;
    
    mvprintw(3, 61, "      ") ;
    mvprintw(4, 61, "  ") ;
    mvprintw(5, 61, "      ") ;
    mvprintw(6, 61, "  ") ;
    mvprintw(7, 61, "      ") ;

    mvprintw(9, 61, "  ") ;
    mvprintw(9, 65, "  ") ;
    mvprintw(10, 62, "    ") ;
    mvprintw(11, 63, "  ") ;
    mvprintw(12, 62, "    ") ;
    mvprintw(13, 61, "  ") ;
    mvprintw(13, 65, "  ") ;

    for(int i = 15; i < 20 ; i++)
        mvprintw(i, 63, "  ") ;

    mvprintw(21, 61, "      ") ;
    for(int i = 22; i < 26; i++)
        mvprintw(i, 63, "  ") ;

}

void graphic_frog(){
    init_pair(20, COLOR_WHITE, COLOR_WHITE) ;
    init_pair(21, COLOR_WHITE, COLOR_BLACK) ;
    init_pair(22, COLOR_GREEN, COLOR_GREEN) ;

    attron(COLOR_PAIR(21)) ;
    mvprintw(4, 28, "      ") ;
    mvprintw(4, 46, "      ") ;
    mvprintw(5, 26, "  ") ;
    mvprintw(5, 34, "  ") ;
    mvprintw(5, 44, "  ") ;
    mvprintw(5, 52, "  ") ;
    mvaddch(6, 25, ' ') ;
    mvprintw(6, 28, "    ") ;
    mvprintw(6, 36, "        ") ;
    mvprintw(6, 48, "    ") ;
    mvaddch(6, 54, ' ') ;
    mvaddch(7, 25, ' ') ;
    mvprintw(7, 28, "    ") ;
    mvprintw(7, 48, "    ") ;
    mvaddch(7, 54, ' ') ;   
    mvaddch(8, 25, ' ') ;
    mvaddch(8, 54, ' ') ;   
    mvprintw(9, 26, "  ") ;
    mvprintw(9, 52, "  ") ;   
    mvprintw(10, 24, "  ") ;
    mvprintw(10, 54, "  ") ;
    mvaddch(11, 23, ' ') ;
    mvaddch(11, 29, ' ') ;
    mvaddch(11, 50, ' ') ;
    mvaddch(11, 56, ' ') ;
    mvaddch(12, 23, ' ') ;
    mvprintw(12, 30, "                    ") ;
    mvaddch(12, 56, ' ') ;
    mvprintw(13, 24, "  ") ;
    mvprintw(13, 54, "  ") ;
    mvprintw(14, 26, "      ") ;
    mvprintw(14, 48, "      ") ;
    mvaddch(15, 28, ' ') ;
    mvaddch(15, 51, ' ') ;
    mvprintw(16, 24, "    ") ;
    mvprintw(16, 52, "    ") ;
    mvaddch(17, 23, ' ') ;
    mvaddch(17, 27, ' ') ;
    mvaddch(17, 52, ' ') ;
    mvaddch(17, 56, ' ') ;
    mvaddch(18, 23, ' ') ;
    mvprintw(18, 30, "  ") ;
    mvprintw(18, 34, "  ") ;
    mvprintw(18, 44, "  ") ;
    mvprintw(18, 48, "  ") ;
    mvaddch(18, 56, ' ') ;
    mvprintw(19, 24, "      ") ;
    mvprintw(19, 32, "  ") ;
    mvprintw(19, 36, "        ") ;
    mvprintw(19, 46, "  ") ;
    mvprintw(19, 50, "      ") ;
    attroff(COLOR_PAIR(21)) ;

    attron(COLOR_PAIR(20)) ;
    mvprintw(5, 28, "      ") ;
    mvprintw(5, 46, "      ") ;
    mvprintw(6, 26, "  ") ;
    mvprintw(6, 32, "    ") ;
    mvprintw(6, 44, "    ") ;
    mvprintw(6, 52, "  ") ;
    mvprintw(7, 26, "  ") ;
    mvprintw(7, 32, "    ") ;
    mvprintw(7, 44, "    ") ;
    mvprintw(7, 52, "  ") ;
    mvprintw(8, 26, "          ") ;
    mvprintw(8, 44, "          ") ;
    mvprintw(9, 28, "      ") ;
    mvprintw(9, 46, "      ") ;
    mvprintw(16, 38, "    ") ;
    mvprintw(17, 37, "      ") ;
    mvprintw(18, 36, "        ") ;
    attroff(COLOR_PAIR(20)) ;

    attron(COLOR_PAIR(22)) ;
    mvprintw(7, 36, "        ") ;
    mvprintw(8, 36, "        ") ;
    mvprintw(9, 34, "            ") ;
    mvprintw(10, 26, "                            ") ;
    mvprintw(11, 24, "     ") ;
    mvprintw(11, 30, "                    ") ;
    mvprintw(11, 51, "     ") ;
    mvprintw(12, 24, "      ") ;
    mvprintw(12, 50, "      ") ;
    mvprintw(13, 26, "                            ") ;
    mvprintw(14, 32, "                ") ;
    mvprintw(15, 29, "                      ") ;
    mvprintw(16, 28, "          ") ;
    mvprintw(16, 42, "          ") ;
    mvprintw(17, 24, "   ") ;
    mvprintw(17, 28, "         ") ;
    mvprintw(17, 43, "         ") ;
    mvprintw(17, 53, "   ") ;
    mvprintw(18, 24, "      ") ;
    mvprintw(18, 32, "  ") ;
    mvprintw(18, 46, "  ") ;
    mvprintw(18, 50, "      ") ;
    attroff(COLOR_PAIR(22)) ;
}