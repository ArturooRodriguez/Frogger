#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ncurses.h>
#include <time.h>
#include <fcntl.h>

#define NUM_V 20
#define NUM_T 4
#define MAXLIM 180

bool b1_flag = TRUE ;
bool b2_flag = TRUE ;
bool b3_flag = TRUE ;
bool b4_flag = TRUE ;
bool b5_flag = TRUE ;

int maxx = 0 ;
int maxy = 0 ;

typedef struct{
    int y ;
    int x ;
    char c ;
    char type ;
    int id ; 
    bool flag ;
    bool t_flag ;
    bool sparato ;
    bool bullet ;  ;
    bool frequenza;
    bool tronco;
} obj;

typedef struct{
    int y ;
    int senso ;
} corsia ;

char car_sprite_h[6] = {" ____ "} ;
char car_sprite_m[6] = {"_|xx|_"} ;
char car_sprite_l[6] = {":o--o:"} ;

char cam_sprite_h[10] = {"__________"} ;
char cam_sprite_m[10] = {"| x xx x |"} ;
char cam_sprite_l[10] = {":-0----0-:"} ;

corsia c1, c2, c3, c4 ;
corsia f1, f2, f3, f4 ;

void rana(int p[2], int p_frog[2], int p_frogtobullet[2], int p_bullettofrog[2], int p_log[2], int p_proiettilerana[2]) ;
void dati_veicolo(int p_car[2], int p_coda[2]) ;
void generatrice(int p[2], int p_car[2], int p_coda[2]) ;
void controllo(int p[2], int p_frog[2], int p_log[2], int p_time[2], int p_proiettilerana[2], int p_enemybullet[2]) ;
void tronco(int p[2], int p_enemybullet[2], int id, int x, corsia fiume) ;
void proiettile(int p[2], int p_frogtobullet[2], int p_proiettilerana[2]) ;
void proiettile_nemico(obj tronco, int p[2], int p_enemybullet[2]);
void drawmap() ;
bool menu() ;
void title_maker(int option) ;
void graphic_frog() ;
void gameover() ;
void win() ;
void initialize_road_river() ;
void timer(int p_time[2]) ;

int main(){
    srand(time(NULL)) ;

    int p[2] ;
    int p_frog[2] ;
    int p_car[2] ;
    int p_coda[2] ;
    int p_frogtobullet[2] ;
    int p_bullettofrog[2] ;
    int p_log[2] ;
    int p_time[2] ;
    int p_proiettilerana[2];
    int p_enemybullet[2];
    
    pipe(p) ;
    pipe(p_frog) ;
    pipe(p_car) ;
    pipe(p_coda) ;
    pipe(p_frogtobullet) ;
    pipe(p_bullettofrog) ;
    pipe(p_log) ;
    pipe(p_time) ;
    pipe(p_proiettilerana) ;
    pipe(p_enemybullet);
    fcntl(p_frog[0], F_SETFL, fcntl(p_frog[0], F_GETFL) | O_NONBLOCK) ;
    fcntl(p_frogtobullet[0], F_SETFL, fcntl(p_frogtobullet[0], F_GETFL) | O_NONBLOCK) ;
    fcntl(p_bullettofrog[0], F_SETFL, fcntl(p_bullettofrog[0], F_GETFL) | O_NONBLOCK) ;
    fcntl(p_time[0], F_SETFL, fcntl(p_time[0], F_GETFL) | O_NONBLOCK) ;
    fcntl(p_log[0], F_SETFL, fcntl(p_log[0], F_GETFL) | O_NONBLOCK) ;
    fcntl(p_proiettilerana[0], F_SETFL, fcntl(p_proiettilerana[0], F_GETFL) | O_NONBLOCK) ;
    fcntl(p_enemybullet[0], F_SETFL, fcntl(p_enemybullet[0], F_GETFL) | O_NONBLOCK) ;

    initscr() ;  
    noecho() ;     
    keypad(stdscr, 1) ; 
    curs_set(0) ;
    resize_term(36, 80) ;
    getmaxyx(stdscr, maxy, maxx) ;
    start_color() ;

    if(menu()==FALSE){
        endwin() ;
        exit(0) ;
        return 0 ;
    }

    initialize_road_river() ;

    //randomizzazione posizione di partenza del tronco
    int x_tronco[4];

    for (int i = 0; i < 4; i++)
    {
        x_tronco[i] =  rand() % 60;
    }

    //dichiarazione pid (r=rana, v=veicolo, c=controllo, p=proiettile)
    pid_t pid1r, pid2v, pid3v, pid8p, pid9t, pid10t, pid11t, pid12t, pid13time ;
    
    pid1r = fork() ;

    if(pid1r == 0) //rana
        rana(p, p_frog, p_frogtobullet, p_bullettofrog, p_log, p_proiettilerana) ;
    
    else if(pid1r > 0)
        pid2v = fork() ;

    if(pid2v == 0){ //veicolo 1
        generatrice(p, p_car, p_coda) ;
    }

    else if(pid2v > 0){
        pid3v = fork() ;
    }
    
    if(pid3v == 0){ //veicolo 2
        dati_veicolo(p_car, p_coda) ;
    }
    
    else if(pid3v > 0){
        pid8p = fork() ;
    }

    if(pid8p == 0){
        tronco(p, p_enemybullet, 20, x_tronco[0], f1) ; //tronco 1
    }

    else if(pid8p > 0){
        pid10t = fork() ;
    }

    if(pid10t == 0){
        tronco(p, p_enemybullet, 21, x_tronco[1], f2) ; //tronco 2
    }

    else if(pid10t > 0){
        pid11t = fork() ;
    }

    if(pid11t == 0){
        tronco(p, p_enemybullet, 22, x_tronco[2], f3) ; //tronco 3
    }

    else if(pid11t > 0){
        pid12t = fork() ;
    }

    if(pid12t == 0){
        tronco(p, p_enemybullet, 23, x_tronco[3], f4) ; //tronco 4 
    }

    else if(pid12t > 0){
        pid13time = fork() ;
    }
    
    if(pid13time == 0){
        timer(p_time) ;
    }
    
    else if(pid13time > 0){
        controllo(p, p_frog, p_log, p_time, p_proiettilerana, p_enemybullet) ;
    }
    
   
    //blocco di uscita
    endwin() ;
    exit(1) ;
    return 0 ;
}

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
            mvprintw(t[i].y-2, t[i].x, "|========|") ;
            mvprintw(t[i].y-1, t[i].x, "|========|") ;
            mvprintw(t[i].y, t[i].x,   "|========|") ;
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

        mvprintw(1, 15, "TRONCO1 y: %d", t[0].y) ;
        mvprintw(1, 30, "TRONCO2 X: %d", t[1].x) ;
        mvprintw(1, 45, "TRONCO3 X: %d", t[2].x) ;
        mvprintw(1, 60, "TRONCO4 x: %d", t[3].x) ;

        mvprintw(2, 15, "nemico1 X: %d", nemico[0].x) ;
        mvprintw(2, 30, "nemico2 X: %d", nemico[1].x) ;
        mvprintw(2, 45, "nemico3 X: %d", nemico[2].x) ;
        mvprintw(2, 60, "nemico4 X: %d", nemico[3].x) ;
        mvprintw(2, 60, "nemico4 X: %d", nemico[3].x) ;
        mvprintw(2, 60, "rana Y: %d", rana.y) ;

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
    
            if (t[i].frequenza == true && rana.y != t[i].y)
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
                    if (!(rana.y == t[i].y))
                    {
                        nemico[i].x = t[i].x+4;
                        nemico[i].y = t[i].y-1;
                        shoot[i] = true;  // il proiettile può essere sparato                         
                    }
                }

            }
            else 
            {
                pos[i] = rand() % 20;
                counter2++;
            }
            //spawn del nemico in base alla frequenza e se la rana non è sul tronco  
            if (!(rana.y == t[i].y) && nemico[i].sparato == false)
            {
                attron(COLOR_PAIR(7));
                mvprintw (nemico[i].y-1, nemico[i].x, "X-^-X");
                mvprintw (nemico[i].y, nemico[i].x,  "(\\o/)");
                attroff(COLOR_PAIR(7));
                
            }
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

        

        if (nemico[i].x < 0 && enemy_bullet[i].y < 0)
        {
            control[i] = true;
            write(p_enemybullet[1], &control[i], sizeof(bool));  
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
                        //vite--;
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

                //collisione tra proiettile sparato dalla rana e i veicoli 
                //il proiettile scompare
                for (int j = 0; j < NUM_V; j++)
                {
                    if (bullet.x >= veicolo[j].x && ((veicolo[j].type == 'm' && bullet.x <= veicolo[j].x+6) || (veicolo[j].type == 'c' && bullet.x <= veicolo[j].x+9)) && bullet.y >= veicolo[j].y-2 && bullet.y <= veicolo[j].y)
                    {
                        bullet.y = -10;
                        bullet.x = -10;
                        bullet.sparato = true;  
                        write(p_proiettilerana[1], &bullet, sizeof(bullet));                     
                    }
                }



                //collisione tra PROIETTILE NEMICO e VEICOLI 
                //il proiettile sparisce 
                for(int j = 0; j < NUM_V; j++)
                {
                    if (enemy_bullet[i].x >= veicolo[j].x && ((veicolo[j].type == 'm' && enemy_bullet[i].x <= veicolo[j].x+6) || (veicolo[j].type == 'c' && enemy_bullet[i].x <= veicolo[j].x+9)) && enemy_bullet[i].y >= veicolo[j].y-2 && enemy_bullet[i].y <= veicolo[j].y)
                    {
                        shoot[i] = false;
                        control[i] = true;
                        
                        //write(p_enemybullet[1], &control[i], sizeof(bool));                        
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



void proiettile(int p[2], int p_frogtobullet[2], int p_proiettilerana[2]){

    //dichiarazione degli oggetti 
    obj bullet ;
    obj r ;
    obj letto;
    bullet.sparato = false;

    read(p_frogtobullet[0], &r, sizeof(obj)) ;
    
    //posizione iniziale = posizione della rana 
    bullet.x = r.x+2 ;
    bullet.y = r.y-3 ;
    bullet.type = 'b' ;
    bullet.id = 500 ;

    write(p[1], &bullet, sizeof(obj)) ;


    while(bullet.y >= 0){

        read(p_proiettilerana[0], &letto, sizeof(letto));

        //se il proiettile subisce una collisione sparisce dalla schermata 
        if (letto.sparato == true)
        {
            bullet.x = letto.x;
            bullet.y = letto.y;
            letto.sparato = false;
        }
        bullet.y-- ;
        
        write(p[1], &bullet, sizeof(obj)) ;
        usleep(30000) ;
    }
    _exit(0) ; //termine del processo 
}

void proiettile_nemico(obj tronco, int p[2], int p_enemybullet[2])
{
    //dichiarazione dell'oggetto proiettile e
    //assegnazione delle coordinate di partenza
    obj proiettile;
    proiettile.x = tronco.x+8;
    proiettile.y = tronco.y;
    proiettile.id = tronco.id+10;
    proiettile.type = 'p';
    bool killed = false;;

    write(p[1], &proiettile, sizeof(obj));

    while(proiettile.y <= maxy)
    {
        read(p_enemybullet[0], &killed, sizeof(killed));
        
        //se il proiettile subisce collisioni sparisce dalla schermata 
        if (killed == true)
        {
            proiettile.x = -10;
            proiettile.y = -10;            
        }

        proiettile.y++;
        write(p[1], &proiettile, sizeof(proiettile));
        usleep(80000);
    }

    _exit(0); //termine del processo 
        
}

void dati_veicolo(int p_car[2], int p_coda[2]){
    srand(time(NULL)) ;
    close(p_car[0]) ;
    obj coda_veicoli[NUM_V] ;
    int traffico[4] ;
    int i = 0 ;
    int corsie ;
    
    for(int j = 0 ; j < 4 ; j++)
        traffico[j] = 0 ;

    for(i = 0; i < NUM_V; i++){
        switch(rand()%2){
            case 0:
                coda_veicoli[i].type = 'm' ;
                break;
            case 1:
                coda_veicoli[i].type = 'c' ;
                break ;
        }
    }

    i = 0 ;

    while(true){
        if(coda_veicoli[i%NUM_V].type != 'v'){
            do{
                corsie = rand()%4 ;
                switch(corsie){
                    case 0:
                        coda_veicoli[i%NUM_V].y = c1.y;
                        break;
                    case 1:
                        coda_veicoli[i%NUM_V].y = c2.y;
                        break;
                    case 2:
                        coda_veicoli[i%NUM_V].y = c3.y;
                        break;
                    case 3:
                        coda_veicoli[i%NUM_V].y = c4.y;
                        break;
                    }
            }while(traffico[corsie] >= 5) ;
            write(p_car[1], &coda_veicoli[i%NUM_V], sizeof(obj)) ;
        }
        traffico[corsie]++ ;
        coda_veicoli[i%NUM_V].type = 'v' ;
        usleep(500000 + rand()%500000) ;
        i++ ;

        if(coda_veicoli[i%NUM_V].type == 'v'){
            read(p_coda[0], &coda_veicoli[i%NUM_V], sizeof(obj)) ;
            switch(coda_veicoli[i%NUM_V].y){
                case 31:
                    traffico[0]-- ;
                    break ;
                case 28:
                    traffico[1]-- ;
                    break ;
                case 25:
                    traffico[2]-- ;
                    break ;
                case 22:
                    traffico[3]-- ;
                    break ;
            }
        }
    }
}


void generatrice(int p[2], int p_car[2], int p_coda[2]){
    close(p_car[1]) ;
    obj veicolo ;
    obj oldpos ;
    int direzione ;
    pid_t pid_array[NUM_V] ;
    int i = 0 ;

    while(true){
        read(p_car[0], &veicolo, sizeof(obj)) ;
        
        switch(veicolo.y){
            case 31:
                direzione = c1.senso;
                break ;
            case 28:
                direzione = c2.senso;
                break ;
            case 25:
                direzione = c3.senso;
                break ;
            case 22:
                direzione = c4.senso;
                break ;
        }

        if(direzione == 1)
            veicolo.x = 0 ;
        else if(direzione == -1){
            if(veicolo.type == 'm')
                veicolo.x = maxx-6 ;
            else if(veicolo.type == 'c')
                veicolo.x = maxx-10 ;
        }
            
        pid_array[i%NUM_V] = fork() ;

        veicolo.id = i%NUM_V ;
        
        if(pid_array[i%NUM_V] == 0){
            while( ((veicolo.type == 'm' && veicolo.x+6 > -2) || (veicolo.type == 'c' && veicolo.x+10 > -2)) && veicolo.x < maxx+1){
                veicolo.x += direzione ;
                if(oldpos.x != veicolo.x)
                    write(p[1], &veicolo, sizeof(obj)) ;
                oldpos = veicolo ;
                usleep(40000) ;
            }
            write(p_coda[1], &veicolo, sizeof(obj)) ;
            _exit(0) ;
        }

        i++ ;
    }
}

void timer(int p_time[2]){
    int time_left = 120 ;
    while(true){
        write(p_time[1], &time_left, sizeof(int)) ;
        time_left-- ;
        sleep(1) ;
    }
}

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