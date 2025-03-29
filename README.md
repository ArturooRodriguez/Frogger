# FroggerProcess - Gioco Frogger in C con ncurses

FroggerProcess è un progetto sviluppato in linguaggio C utilizzando la libreria **ncurses** per la grafica in terminale. L'obiettivo è realizzare una versione del gioco **Frogger** tramite un'architettura concorrente, sfruttando sia processi che thread.

## Versioni Implementate

1. **Versione a Processi:** Ogni elemento di gioco (rana, tronchi, automobili, proiettili) è gestito come un processo indipendente tramite `fork` ed `exec`, garantendo isolamento tra componenti. La comunicazione avviene tramite segnali e pipe.

2. **Versione a Thread:** Gli elementi di gioco sono gestiti come thread all’interno di un unico processo, condividendo la memoria tramite variabili condivise e sincronizzando l’accesso con mutex.

### Differenze Chiave
- **Processi:** Isolamento completo, maggiore sicurezza, comunicazione tramite segnali.  
- **Thread:** Maggiore efficienza, condivisione della memoria, sincronizzazione tramite mutex.  

## Tecnologie Utilizzate
- **Linguaggio:** C  
- **Libreria Grafica:** ncurses  
- **Gestione Processi:** `fork`, `exec`, `wait`  
- **Gestione Thread:** Libreria `pthread`  
- **Sincronizzazione:** Mutex e segnali  

