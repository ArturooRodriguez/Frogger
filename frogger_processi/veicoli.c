#include "header.h"
#include "main.h"
#include "controllo.h"
void dati_veicolo(int p_ car[2], int p_coda[2]){
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