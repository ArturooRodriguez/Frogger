#include "header.h"
#include "controllo.h"
#include "main.h"
#include "proiettili.h"
void tronco(int p[2], int p_enemybullet[2], int id, int x, corsia fiume){
    srand(getpid()) ;
    getmaxyx(stdscr, maxy, maxx) ;

    //dichiarazione oggetti
    obj t ;
    obj oldpos ;

    //assegnazione posizioni di partenza 
    t.y = fiume.y ;
    t.id = id ;
    t.x = x;
    t.frequenza = false; 
    t.flag = FALSE ;
    t.type = 't' ;
    oldpos = t ;

    int lim;
    int counter1 = 0;
    bool shoot;
    pid_t proiettile; //pid per la creazione del processo 'proiettile'

    srand(time(NULL));
    lim = rand() % MAXLIM;    
    write(p[1], &t, sizeof(obj)) ;


    while(true){
        getmaxyx(stdscr, maxy, maxx) ;


        if(t.x != oldpos.x)
            write(p[1], &t, sizeof(obj)) ;
    
        oldpos = t ;

        //frequenza di spawn dei nemici 
        if (counter1 >= lim && t.frequenza == false)
            t.frequenza = true;

        //spawn dei nemici 
        if (t.frequenza == true)
        {
            //creazione del processo 'proiettile_nemico'
            if (waitpid(-1,NULL,WNOHANG))
            {
                proiettile = fork(); 
                if (proiettile == 0)
                    proiettile_nemico(t, p, p_enemybullet);
            }
                counter1 = 0;
        }

        //collisioni dei tronchi con i bordi 
        if(t.x == 0 || t.x+17 == maxx-1)
            fiume.senso *= -1 ;

        t.x += fiume.senso ;

        //switch di usleep per avere velocità diverse 
        switch(t.y){
            case 16:
                usleep(70000) ;
                break ;
            case 13:
                usleep(130000) ;
                break ;
            case 10:
                usleep(100000) ;
                break ;
            case 7:
                usleep(60000) ;
                break ;
        }
        
        //aumento del counter per determinare la frequenza 
        counter1++;
}
}