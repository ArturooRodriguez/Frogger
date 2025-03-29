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

    //randomizzazione posizione di partenza 
    int x_tronco[4];

    for (int i = 0; i < 4; i++)
    {
        x_tronco[i] =  rand() % 60;
    }

    //dichiarazione pid (r=rana, v=veicolo, c=controllo)
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
        tronco(p, p_enemybullet, 20, x_tronco[0], f1) ;
    }

    else if(pid8p > 0){
        pid10t = fork() ;
    }

    if(pid10t == 0){
        tronco(p, p_enemybullet, 21, x_tronco[1], f2) ;
    }

    else if(pid10t > 0){
        pid11t = fork() ;
    }

    if(pid11t == 0){
        tronco(p, p_enemybullet, 22, x_tronco[2], f3) ; 
    }

    else if(pid11t > 0){
        pid12t = fork() ;
    }

    if(pid12t == 0){
        tronco(p, p_enemybullet, 23, x_tronco[3], f4) ;
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