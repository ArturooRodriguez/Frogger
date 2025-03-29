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
void stampa_nemico(obj nemico, obj proiettile);
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
