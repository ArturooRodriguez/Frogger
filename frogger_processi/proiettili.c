
#include "header.h"
#include "main.h"
#include "f_rana.h"
#include "tronco.h"
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