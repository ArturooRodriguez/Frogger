#include "header.h"
void initialize_road_river(){
    srand(time(NULL)) ;
    //corsie autostrada
    c1.y = 31 ;
    c2.y = 28 ;
    c3.y = 25 ;
    c4.y = 22 ;
     
    //corsie fiume
    f1.y = 16 ;
    f2.y = 13 ;
    f3.y = 10 ;
    f4.y = 7 ;

    switch(rand()%2){
        case 0:
            c1.senso = 1 ;
            break ;
        case 1:
            c1.senso = -1 ;
            break ;
    }

    switch(rand()%2){
        case 0:
            f1.senso = 1 ;
            break ;
        case 1:
            f1.senso = -1 ;
            break ;
    }

    c2.senso = c1.senso * -1 ;
    c3.senso = c2.senso * -1 ;
    c4.senso = c3.senso * -1 ;

    f2.senso = f1.senso * -1 ;
    f3.senso = f2.senso * -1 ;
    f4.senso = f3.senso * -1 ;
}