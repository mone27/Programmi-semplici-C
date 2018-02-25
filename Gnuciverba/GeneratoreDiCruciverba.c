//==============
//Configurazioni
//==============
#define LINUX 1 //attiva dizionario LINUX
#define COLONNE 7 //scegli numero di caselle di lunghezza del cruciverba
#define RIGHE 5 //scegli numero di caselle di altezza del cruciverba
//--------------------------------------------------------------------

#include "Libreria.c" //include: stdio.h, string.h, ctype.h, time.h, stdlib.h
/* Funzioni incluse in Libreria.c
   void stampaCruciverba(); (funzionante)
   void stampaCruciverbaVuoto(); (funzionante)
   void ordina_stringhe( char ** stringa, const int nStringhe); (funzionante)
   int contaVerticale(const int riga,const int colonna); (funzionante)
   int contaOrizzontale(const int riga,const int colonna); (funzionante)
   void copiaNelCruciverba(const char * const stringa,const int riga, const int colonna); (funzionante)
   char parola(int max); (funzionante)
   int vediSeEsisteV(int x, const int y); (funzionante)
   int vediSeEsisteO(const int x,int y); (funzionante)
   void cruciClean(); (funzionante)
   void cruciFill(); (funzionante)
   int cruciCheck();
*/

int main() {
  time_t inizio;
  double secondi;
  int ore,minuti;
  
  //prendo il tempo ad inizio esecuzione
  inizio= clock();
  
  //insemino funzione rand()
  srand(time(NULL));
  
  //stampo ora di inizio esecuzione
  printf("Esecuzione lanciata\n");
//Inizio generazione--------------------------------------------------------
  
  //Approccio brutale per cruciverba
  do{
  cruciClean();
  cruciFill();
  }while(!cruciCheck());
  
  
//Fine generazione----------------------------------------------------------
  stampaCruciverbaVuoto();
  stampaCruciverba();
  
  //ricavo e raffino tempo di esecuzione del programma
  secondi=(double)(clock()-inizio)/CLOCKS_PER_SEC;
  minuti=secondi/60;
  secondi-=(double)minuti*60;
  ore=minuti/60;
  minuti-=ore*60;
  printf("Programma terminato con successo\nTempo di esecuzione: %d Ore %d Minuti %.3f Secondi\n",ore,minuti,secondi);
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

