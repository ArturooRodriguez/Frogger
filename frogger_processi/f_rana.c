#include "header.h"

void rana(int p[2], int p_frog[2], int p_frogtobullet[2], int p_bullettofrog[2], int p_log[2], int p_proiettilerana[2]){

    //dichiarazione oggetti
    getmaxyx(stdscr, maxy, maxx) ;
    obj r = {maxy-2, maxx/2, '#', 'r', 300, FALSE, FALSE} ;
    obj oldpos ;
    oldpos = r ;
    obj letto ;
    letto.t_flag = FALSE ;
    bool collision = FALSE ;

    pid_t pid_bullet ;  //pid che serve per la generazione del proiettile
    write(p[1], &r, sizeof(obj)) ;

    while(true){
        getmaxyx(stdscr, maxy, maxx) ;  

        read(p_frog[0], &collision, sizeof(collision)) ;  
        read(p_bullettofrog[0], &r.flag, sizeof(bool)) ;
        read(p_log[0], &letto, sizeof(obj)) ;


        //lettura della variabile collisione dalla funzione controllo 
        //se si hanno collisioni la rana torna nella collisione di partenza
        if(collision == TRUE){
            collision = FALSE ;
            r.y = maxy-2 ;
            r.x = maxx/2 ;
            write(p[1], &r, sizeof(obj)) ;
        }

        //se la rana è sul tronco 
        if(letto.t_flag == TRUE){
            r.x = letto.x ;
            r.y = letto.y ;
            letto.t_flag = FALSE ;
        }
        
        //se la rana raggiunge le basi 
        if(r.y == 4 && ((r.x >= 1 && r.x+5 <= 11) || (r.x >= 18 && r.x+5<=28) || (r.x >= 35 && r.x+5 <= 45) || (r.x >= 52 && r.x+5 <= 62) || (r.x >= 69 && r.x+5 <= 79))){
            r.y = maxy-2 ;
            r.x = maxx/2 ;
            write(p[1], &r, sizeof(obj)) ;
        }
        
        timeout(1) ;

        //movimento della rana 
        int s = getch() ;
        switch(s){
            case KEY_UP:
                if(r.y > 5)
                    r.y -= 3;
                break;
            case KEY_DOWN:
                if(r.y < maxy-2)
                    r.y += 3;
                break;
            case KEY_LEFT:
                if(r.x > 0){
                    r.x -= 1;
                }
                break;
            case KEY_RIGHT:
                if(r.x < maxx-7){
                    r.x += 1;
                }
                break;
            case 32:
            //se viene premuto lo spazio viene generato il processo 'proiettile' 
            if(waitpid(-1, NULL, WNOHANG) != 0){
                write(p_frogtobullet[1], &r, sizeof(obj)) ;
                pid_bullet = fork() ;
                if(pid_bullet == 0)
                    proiettile(p, p_frogtobullet, p_proiettilerana) ;
                break ;
            }
        }
    
        if(r.x != oldpos.x || r.y != oldpos.y)
            write(p[1], &r, sizeof(obj)) ;
        oldpos = r ;
    }
}
