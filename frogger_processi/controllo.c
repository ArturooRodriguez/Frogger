#include "header.h"
#include "main.h"
#include "f_frog.h"
#include "timer.h"
#include "proiettili.h"
#include "veicoli.h"
#include "tronco.h"
#include "menu_grafica.h"
#include "fine_partita"
#include "drawmap.h"
void controllo(int p[2], int p_frog[2], int p_log[2], int p_time[2], int p_proiettilerana[2], int p_enemybullet[2]){

    //dichiarazione oggetti
    obj letto ;
    obj rana ;
    obj oldfrog ;
    obj nemico[NUM_T] ;
    obj enemy_bullet[NUM_T] ;
    obj bullet ;
    obj veicolo[NUM_V] ;
    obj t[NUM_T] ;
    obj old_t[NUM_T] ;

    //posizioni iniziali 
    rana.y = maxy-2 ;
    rana.x = maxx/2 ;
    rana.id = 300 ;
    bullet.x = -1 ;
    bullet.y = -1 ;
    bullet.id = 500 ;

    //dichiarazioni variabili 
    int vite = 3 ;
    int basi = 5 ;
    int punteggio = 0;
    int time_left = 120 ;
    int counter = 0;
    int pos[4];
    bool collision = FALSE ;
    bool control[4];
    bool shoot[4];


    getmaxyx(stdscr, maxy, maxx) ;
    

    for (int i = 0; i < 4; i++)
    {
        nemico[i].sparato = false;
        enemy_bullet[i].sparato = false;
    }


    while(true){
        erase() ;
        drawmap() ;

        read(p[0], &letto, sizeof(obj)) ;
        read(p_time[0], &time_left, sizeof(int)) ;

        //riconoscimento e assegnazione del contenuto della pipe
        if(letto.type == 'r')
            rana = letto ;
        for(int i = 0 ; i < NUM_V ; i++){
            if(letto.id == i){
                veicolo[i] = letto ;
            }
        }
        if(letto.type == 'b'){
            bullet = letto ;
        }
        for(int i = 20; i < 24 ; i++){
            if(letto.id == i && letto.type == 't')
                t[i-20] = letto ;
        }

        for (int i = 30; i < 34; i++)
        {
            if(letto.id == i && letto.type == 'p')
                enemy_bullet[i-30] = letto;
        }



        //stampa del tronco 
        for(int i = 0 ; i < 4 ; i++){

            attron(COLOR_PAIR(3)) ;
            mvprintw(t[i].y-2, t[i].x, "|==============|") ;
            mvprintw(t[i].y-1, t[i].x, "|==============|") ;
            mvprintw(t[i].y, t[i].x,   "|==============|") ;
            attroff(COLOR_PAIR(3)) ;                

        }   


    
        //se la rana è in posizione di spawn vuol dire che è respawnata e possiamo risettare la collisione a false
        if(rana.x == maxx/2 && rana.y == maxy-2){
            collision = FALSE ;
        }

        //*****************************RANA SUI TRONCHI************************************************************************
        if(oldfrog.y==t[0].y && rana.y==t[0].y+3){
            rana.t_flag = TRUE ;
            write(p_log[1], &rana, sizeof(obj)) ;
            rana.t_flag = FALSE ;
            oldfrog.y = -1 ; 
        }

        if(rana.y<=t[0].y && rana.y>=t[3].y){
            rana.t_flag =  TRUE ;
            for(int i = 0; i<4; i++){
                if(old_t[i].x != t[i].x && rana.y == t[i].y){
                    rana.x=rana.x+(t[i].x-old_t[i].x) ;
                    if(rana.y == t[i].y && (rana.x < t[i].x || rana.x+5 > t[i].x+17)){
                        rana.y = maxy-2 ;
                        rana.x = maxx/2 ;
                        vite-- ;
                    }
                    write(p_log[1], &rana, sizeof(obj)) ;
                }
            }
            oldfrog = rana ;
        }
        
        for(int i = 0 ; i<4 ; i++)
            old_t[i] = t[i] ;
        //*****************************FINE RANA SUI TRONCHI************************************************************************

        attron(COLOR_PAIR(1)) ;
        mvprintw(35, 1, "VITE: %d", vite) ;
        mvprintw(35, 10, "BASI RIMANENTI: %d", basi) ;
        mvprintw(35, 30, "TEMPO RIMANENTE: %d", time_left) ;

        /*attron(COLOR_PAIR(5)) ;
        mvprintw(0,1, "RANA X: %d", rana.x) ;
        mvprintw(1,1, "RANA Y: %d", rana.y) ;
        mvprintw(0, 15, "TRONCO FLAG: %s", t[0].flag ? "TRUE":"FALSE") ;
        mvprintw(1, 15, "TRONCO X: %d", t[0].x+3) ;
        mvprintw(1, 40, "PROJ Y:  %d", bullet.y) ;*/

        attron(COLOR_PAIR(1)) ;
        mvprintw(35, 1, "VITE: %d", vite) ;
        mvprintw(35, 10, "BASI RIMANENTI: %d", basi) ;
        mvprintw(35, 30, "TEMPO RIMANENTE: %d", time_left) ;   
        mvprintw(35, 55, "PUNTEGGIO: %d", punteggio) ; 

        attron(COLOR_PAIR(5)) ;
        mvprintw(0,1, "RANA X: %d", rana.x) ;
        mvprintw(1,1, "RANA Y: %d", rana.y) ;
        mvprintw(0, 15, "TRONCO FLAG: %s", t[0].flag ? "TRUE":"FALSE") ;
        mvprintw(0, 35, "pro_nemi FLAG: %s", enemy_bullet[3].sparato ? "TRUE":"FALSE") ;

        mvprintw(1, 15, "TRONCO1 X: %d", t[0].x) ;
        mvprintw(1, 30, "TRONCO2 X: %d", t[1].x) ;
        mvprintw(1, 45, "TRONCO3 X: %d", t[2].x) ;
        mvprintw(1, 60, "TRONCO4 X: %d", t[3].x) ;

        mvprintw(2, 15, "nemico1 X: %d", nemico[0].x) ;
        mvprintw(2, 30, "nemico2 X: %d", nemico[1].x) ;
        mvprintw(2, 45, "nemico3 X: %d", nemico[2].x) ;
        mvprintw(2, 60, "nemico4 X: %d", nemico[3].x) ;

        mvprintw(0, 60, "proiettile X: %d", enemy_bullet[3].x) ;

        for(int i = 0 ; i < NUM_V ; i++){
            attron(COLOR_PAIR(21)) ;
            //MACCHINA
            if(veicolo[i].type == 'm'){
                //STA USCENDO A DESTRA
                if(veicolo[i].x+6 >= maxx){
                    for(int j = 0 ; j < 6; j++){
                        if(veicolo[i].x+j <= maxx){
                            mvaddch(veicolo[i].y-2, veicolo[i].x+j, car_sprite_h[j]) ;
                            mvaddch(veicolo[i].y-1, veicolo[i].x+j, car_sprite_m[j]) ;
                            mvaddch(veicolo[i].y, veicolo[i].x+j, car_sprite_l[j]) ;
                        }
                    }
                }
                //STA USCENDO A SINISTRA
                if(veicolo[i].x < 0){
                    for(int j = 0 ; j < 6 ; j++){
                        if(veicolo[i].x+j >= 0){
                            mvaddch(veicolo[i].y-2, veicolo[i].x+j, car_sprite_h[j]) ;
                            mvaddch(veicolo[i].y-1, veicolo[i].x+j, car_sprite_m[j]) ;
                            mvaddch(veicolo[i].y, veicolo[i].x+j, car_sprite_l[j]) ;
                        }
                    }
                }
                //E' COMPRESO
                else if(veicolo[i].x >= 0 && veicolo[i].x+6 <= maxx-1){
                    mvprintw(veicolo[i].y-2, veicolo[i].x, " ____ ") ;
                    mvprintw(veicolo[i].y-1, veicolo[i].x, "_|xx|_") ;
                    mvprintw(veicolo[i].y, veicolo[i].x, ":o--o:") ;
                }
            }
            //CAMION
            else if(veicolo[i].type == 'c'){
                //STA USCENDO A DESTRA
                if(veicolo[i].x+10 >= maxx){
                    for(int j = 0 ; j < 10; j++){
                        if(veicolo[i].x+j <= maxx){
                            mvaddch(veicolo[i].y-2, veicolo[i].x+j, cam_sprite_h[j]) ;
                            mvaddch(veicolo[i].y-1, veicolo[i].x+j, cam_sprite_m[j]) ;
                            mvaddch(veicolo[i].y, veicolo[i].x+j, cam_sprite_l[j]) ;
                        }
                    }
                }
                //STA USCENDO A SINISTRA
                if(veicolo[i].x < 0){
                    for(int j = 0 ; j < 10 ; j++){
                        if(veicolo[i].x+j >= 0){
                            mvaddch(veicolo[i].y-2, veicolo[i].x+j, cam_sprite_h[j]) ;
                            mvaddch(veicolo[i].y-1, veicolo[i].x+j, cam_sprite_m[j]) ;
                            mvaddch(veicolo[i].y, veicolo[i].x+j, cam_sprite_l[j]) ;
                        }
                    }
                }
                //E' COMPRESO
                else if(veicolo[i].x >= 0 && veicolo[i].x+10 <=maxx-1){
                    mvprintw(veicolo[i].y-2, veicolo[i].x, "__________") ;
                    mvprintw(veicolo[i].y-1, veicolo[i].x, "| x xx x |") ;
                    mvprintw(veicolo[i].y, veicolo[i].x, ":-0----0-:") ;
                }
            }
            attroff(COLOR_PAIR(21)) ;
        }

        if(bullet.y >= 0){
            attron(COLOR_PAIR(7)) ;
            mvaddch(bullet.y, bullet.x, 'o') ;
            attroff(COLOR_PAIR(7)) ;
        }
        else{
            bullet.x = -1 ;
            bullet.y = -1 ;
        }

        //stampa della rana 
        attron(COLOR_PAIR(6)) ;
        mvprintw(rana.y-2, rana.x, "|@ @|") ;
        mvprintw(rana.y-1, rana.x, "(---)") ;
        mvprintw(rana.y, rana.x, "<(X)>") ;
        attroff(COLOR_PAIR(6)) ;

        //************inizio spazio nemici*********************+
        int counter2= 0;   // variabile che si azzera ad ogni ciclo e serve per lo spawn dei nemici 


        for (int i = 0; i < 4; i++)
        {  
    
            if (t[i].frequenza == true)
            {
            
            srand(time(NULL));

            //frequenza per lo spawn dei nemici 
            if (counter2 == pos[i])
            {
                //controlla se il nemico è stato sparato
                if (nemico[i].sparato == true)
                {
                nemico[i].y = -10;
                nemico[i].x = -10;              
                }
                //se non è stato sparato viene spawnato al centro del tronco 
                else    
                 {
                nemico[i].x = t[i].x+4;
                nemico[i].y = t[i].y-1;
                shoot[i] = true;  // il proiettile può essere sparato 
                   
                }

            }
            else 
            {
                pos[i] = rand() % 20;
                counter2++;
            }
            //spawn del nemico in base alla frequenza e se la rana non è sul tronco  
            if (rana.y != t[i].y && nemico[i].sparato == false)
                attron(COLOR_PAIR(7));
                mvprintw (nemico[i].y-1, nemico[i].x, "X-^-X");
                mvprintw (nemico[i].y, nemico[i].x,  "(\\o/)");
                attroff(COLOR_PAIR(7));
                
            }


            //collisione tra proiettile della rana e i nemici 
            if (bullet.y == nemico[i].y && bullet.x >= nemico[i].x && bullet.x <= nemico[i].x + 7)
            {   

                nemico[i].sparato = true;
                bullet.y = -10;
                bullet.x = -10;
                bullet.sparato = true;

                if (enemy_bullet[i].y > 0 && enemy_bullet[i].y <= maxy) //se il proiettile e' ancora nello schermo 
                {
                    control[i] = false;
                    shoot[i] = true; //il proiettile non deve sparire  
                }
                else //se esce fuori dallo schermo non puo' piu' essere risparato 
                {
                    control[i] = true;
                    shoot[i] = false;                   
                } 

                write(p_enemybullet[1], &control[i], sizeof(bool));
                write(p_proiettilerana[1], &bullet, sizeof(bullet)); 
                  
                punteggio += 50;             
            }

        }
 
        //***************fine spazio dei nemici*********************
    

        
        //****************COLLISIONI********************

        //collisioni con le basi 
        if(rana.x >= 1 && rana.x+5 <= 11 && rana.y == 4){
            if(!b1_flag)
                vite-- ;
            else{
                b1_flag = FALSE ;
                basi-- ;
                punteggio += 200;
            }
        }

        if(rana.x >= 18 && rana.x+5 <= 28 && rana.y == 4){
            if(!b2_flag)
                vite-- ;
            else{
                b2_flag = FALSE ;
                basi-- ;
                punteggio += 200;
            }
        }

        if(rana.x >= 35 && rana.x+5 <= 45 && rana.y == 4){
            if(!b3_flag)
                vite-- ;
            else{
                b3_flag = FALSE ;
                basi-- ;
                punteggio += 200;
            }
        }

        if(rana.x >= 52 && rana.x+5 <= 62 && rana.y == 4){
            if(!b4_flag)
                vite-- ;
            else{
                b4_flag = FALSE ;
                basi-- ;
                punteggio += 200;
            }
        }

        if(rana.x >= 69 && rana.x+5 <= 79 && rana.y == 4){
            if(!b5_flag)
                vite-- ;
            else{
                b5_flag = FALSE ;
                basi-- ;
                punteggio += 200;
            }
        }


        if(collision == FALSE){
            //collisioni tra RANA e VEICOLO
            for(int i = 0 ; i < NUM_V ; i++){
                if( (veicolo[i].type == 'm' && veicolo[i].y == rana.y && ( (rana.x >= veicolo[i].x && rana.x <= veicolo[i].x+6) || (rana.x+5 >= veicolo[i].x && rana.x+5 <= veicolo[i].x+6)) || (veicolo[i].type == 'c' && veicolo[i].y == rana.y && ( (rana.x >= veicolo[i].x && rana.x <= veicolo[i].x+10) || (rana.x+5 >= veicolo[i].x && rana.x+5 <= veicolo[i].x+10)) ) )){
                    collision = TRUE ;
                    vite-- ;
                    write(p_frog[1], &collision, sizeof(collision)) ;
                }

            }
            //collisioni tra PROIETTILE NEMICO e RANA 
            for (int i = 0; i < 4; i++)
            {
                //in caso di collisione il proiettile sparisce e la rana torna alla posizione di partenza 
                if (enemy_bullet[i].y >= rana.y-2 && enemy_bullet[i].y <= rana.y)
                {
                    if (enemy_bullet[i].x >= rana.x && enemy_bullet[i].x <= rana.x+6 && control[i] == false)
                    {
                        collision = true;
                        control[i] = true;
                        shoot[i] = false;
                        write(p_frog[1], &collision, sizeof(collision)) ;
                        write(p_enemybullet[i], &control[i], sizeof(bool));
                    }
                }

                if (enemy_bullet[i].y < 0 || enemy_bullet[i].y >= maxy)
                {
                    control[i] = false;
                    //shoot[i] = false;                
                }

                //collisione tra NEMICO e RANA - la rana torna in posizione di partenza 
                if (rana.y-1 == nemico[i].y)
                {
                    collision = TRUE;
                    nemico[i].y = -10;
                    vite--;
                    write(p_frog[1], &collision, sizeof(collision)) ;
                }

                //collisione tra PROIETTILE NEMICO e PROIETTILE DELLA RANA 
                //entrambi spariscono 
                if (bullet.y == enemy_bullet[i].y && bullet.x == enemy_bullet[i].x)
                {
                    bullet.y = -10;
                    bullet.x = -10;
                    bullet.sparato = true;
                    control[i] = true;
                    write(p_enemybullet[1], &control[i], sizeof(bool));   
                    write(p_proiettilerana[1], &bullet, sizeof(bullet));                     
                }

                //collisione tra PROIETTILE NEMICO e VEICOLI 
                //il proiettile sparisce 
                if (enemy_bullet[i].y >= veicolo[i].y-2 && enemy_bullet[i].y <= veicolo[i].y)
                {
                    if (enemy_bullet[i].x >= veicolo[i].x && enemy_bullet[i].x <= veicolo[i].x+10)
                    {
                        shoot[i] = false;
                        control[i] = true;
                        write(p_enemybullet[1], &control[i], sizeof(bool));                        
                    } 
                        
                }

                //stampa del proiettile in base alle condizioni 
                if (control[i] == false && shoot[i] == true)
                {
                    attron(COLOR_PAIR(7));
                    mvprintw(enemy_bullet[i].y , enemy_bullet[i].x, "V");
                    attroff(COLOR_PAIR(7));                  
                }
            }
        }

        //****************fine partita***********
        //se scade il tempo - sconfitta
        if(time_left == 0){
            gameover() ;
            break ;
        }
        //se finiscono le vite - sconfitta 
        if(vite == 0){
            flash() ;
            gameover() ;
            break ;
        }

        //se finiscono le basi - vittoria 
        if(basi == 0){
            flash() ;
            win() ;
            break ;
        }
        refresh() ;
    }
}