
void drawmap(){
    getmaxyx(stdscr, maxy, maxx) ;

    init_pair(1, COLOR_WHITE, COLOR_BLUE) ;
    init_pair(2, 8, COLOR_WHITE) ;
    init_pair(3, COLOR_WHITE, COLOR_BLACK) ;
    init_pair(4, COLOR_WHITE, COLOR_CYAN) ;
    init_pair(5, COLOR_WHITE, COLOR_YELLOW) ;
    init_pair(6, COLOR_WHITE, COLOR_GREEN) ;
    init_pair(7, COLOR_WHITE, COLOR_RED) ;

    //COLORE BASE
    attron(COLOR_PAIR(5)) ;
    for(int i = 0; i < 5 ; i++)
        mvhline(i, 0, ' ', 80) ;

    //COLORE FIUME
    attron(COLOR_PAIR(4)) ;
    for(int i = 5; i < 17 ; i++)
        mvhline(i, 0, ' ', 80) ;
    
    //COLORE ERBA
    attron(COLOR_PAIR(2)) ;
    for(int i = 17; i < 20; i++) 
        mvhline(i, 0, '-', 80) ;

    //COLORE STRADA
    attron(COLOR_PAIR(3)) ;
    for(int i = 20; i < 32; i++)
        mvhline(i, 0, ' ', 80) ;

    //COLORE MARCIAPIEDE
    attron(COLOR_PAIR(2)) ;
    for(int i = 32; i < 35; i++)
        mvhline(i, 0, '-', 80) ;

    //COLORE STATISTICHE
    attron(COLOR_PAIR(1)) ;
    mvhline(35, 0, ' ', 80) ;
    
    
    //COLORE BASE 1
    attron(COLOR_PAIR(4)) ;
    for(int i = 1; i < 11; i++){
        if(b1_flag){
            attron(COLOR_PAIR(4)) ;
            mvvline(2, i, ' ', 3) ;
        }
        else{
            attron(COLOR_PAIR(5)) ;
            mvvline(2, i, '=', 3) ;
        }
    }
    
    
    //COLORE BASE 2
    for(int i=18; i < 28; i++){
        if(b2_flag){
            attron(COLOR_PAIR(4)) ;
            mvvline(2, i, ' ', 3) ;
        }
        else{
            attron(COLOR_PAIR(5)) ;
            mvvline(2, i, '=', 3) ;
        }
    }

    //COLORE BASE 3
    for(int i=35; i < 45; i++){
        if(b3_flag){
            attron(COLOR_PAIR(4)) ;
            mvvline(2, i, ' ', 3) ;
        }
        else{
            attron(COLOR_PAIR(5)) ;
            mvvline(2, i, '=', 3) ;
        }
    }

    //COLORE BASE 4
    for(int i=52; i < 62; i++){
        if(b4_flag){
            attron(COLOR_PAIR(4)) ;
            mvvline(2, i, ' ', 3) ;
        }
        else{
            attron(COLOR_PAIR(5)) ;
            mvvline(2, i, '=', 3) ;
        }
    }
    
    //COLORE BASE 5
    for(int i=69; i < 79; i++){
        if(b5_flag){
            attron(COLOR_PAIR(4)) ;
            mvvline(2, i, ' ', 3) ;
        }
        else{
            attron(COLOR_PAIR(5)) ;
            mvvline(2, i, '=', 3) ;
        }
    }

    attroff(COLOR_PAIR(4)) ;
}
