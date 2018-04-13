//==============
//Configurazioni
//==============
#define GENERICO 1 //attiva dizionario LINUX
#define COLONNE 7 //scegli numero di caselle di lunghezza del cruciverba7
#define RIGHE 5 //scegli numero di caselle di altezza del cruciverba 5 
#define RANDOM_SEED 3 // defines a seed for reproduce test crossword
//--------------------------------------------------------------------

#include "Libreria.c" //include: stdio.h, string.h, ctype.h, time.h, stdlib.h
/* Funzioni incluse in Libreria.c
   void cruciFill4();
   void stampaCruciverba();                                            (funzionante)
   void stampaCruciverbaVuoto();                                       (funzionante)
   char parola(int max);                                               (funzionante)
   char * sorteggiaParola(const int lunghezza);                        (funzionante)
   int sorteggiaLunghezza(int max);                                    (funzionante)
   int cruciFill4();                                                   (da controllare)
   void cruciClean();                                                  (funzionante)
   int contaOrizzontale(const int riga,const int colonna);             (funzionante)
   int contaVerticale(const int riga,const int colonna);               (funzionante)
   void copiaAsteriscoNelCruciverbaO(stringa, riga, colonna) <-abbr    (funzionante)
   void copiaAsteriscoNelCruciverbaV(stringa, riga, colonna) <-abbr    (funzionante)
   void copiaNelCruciverbaO(stringa, riga, colonna)    <-abbreviata    (funzionante)
   void copiaNelCruciverbaV(stringa, riga, colonna)    <-abbreviata    (funzionante)
   int cruciCheck();                                                   (funzionante)
   int vediSeEsisteV(int x, const int y);                              (funzionante)
   int vediSeEsisteO(const int x,int y);                               (funzionante)
   int strCompara(const char * const s1,const char * const s2);        (funzionante)
   int strnCompara(const char * const s1,const char * const s2);       (funzionante)
   int completaO(const int x, const int y);                            (funzionante)
   int completaV(const int x, const int y);                            (funzionante)
  */



//going to to a adsurd thing please forgive me
time_t start_time; //global variable for storing starting time
void time_start(){
    start_time = clock(); //record start time
}
void time_end(){
    double secondi;
    int ore,minuti,a;
    //ricavo e raffino tempo di esecuzione del programma
    secondi=(double)(clock()-start_time)/CLOCKS_PER_SEC;
    minuti=secondi/60;
    secondi-=(double)minuti*60;
    ore=minuti/60;
    minuti-=ore*60;
    printf("Programma terminato con successo\nTempo di esecuzione: %d Ore %d Minuti %.3f Secondi\n\a",ore,minuti,secondi);
}


int main() {
  //record strat time
  time_start();
  
  //insemino funzione rand()
  srand(RANDOM_SEED);
  
  //stampo ora di inizio esecuzione

   printf("Esecuzione lanciata\n");
   //Inizio generazione--------------------------------------------------------

  do{
    cruciClean();
    a=cruciFill4();
    if(cruciverba[4][4]=='R'){
      puts("Cruciverba parziale:");
      stampaCruciverba();
    }      
  }while(!a && !cruciCheck());
  
//Fine generazione----------------------------------------------------------
  stampaCruciverbaVuoto();
  stampaCruciverba();
  time_end();

  return 0;
}





  /*
  //cruciverba funzionante
  copiaNelCruciverba("LINUX",1,1); 
  copiaNelCruciverba("INIT",2,1); 
  copiaNelCruciverba("NOX",3,1); 
  copiaNelCruciverba("UDOO",4,1);
  copiaNelCruciverba("SENX",5,1);
  copiaNelCruciverba("*",1,7); 
  copiaNelCruciverba("**",2,6);
  copiaNelCruciverba("UNI",3,5);
  copiaNelCruciverba("**",4,6); 
  copiaNelCruciverba("**",5,6); 
  */
