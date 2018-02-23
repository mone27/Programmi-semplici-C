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
*/


/*
1  Data una matrice char n+1 x m+1 OK
2  inizializzata a spazio e con caratteri di terminazione a riquadrare il tutto OK
3  fintanto che non sono arrivato alla riga con tutti caratteri di terminazione
4    fintanto che non ho scritto tutte le caselle fino a fine riga
5      sorteggio una parola dal dizionario di una lunghezza che entra nello spazio disponibile
6      se in verticale ho possibilita' di creare una parola di quattro lettere o piu (nel dizionario)
7        scrivo la parola sorteggiata nella matrice con tutto il carattere di terminazione
8        rimuovo dal dizionario la parola sorteggiata (pongo un flag in caso di backtrack) 
9      altrimenti
10       sorteggio un altra parola
11   vado a capo e inizio a scrivere una nuova riga
*/



int main() {
  int a,b,bene;
  srand(time(NULL));

  //Approccio brutale per cruciverba max 7x5
  while(!bene){
    //inizializzo matrice a spazio e la riquadro con caratteri di terminazione
    for(a=0;a<RIGHE+2;a++)//per ogni riga
      for(b=0;b<COLONNE+2;b++)//per ogni colonna
	if( 0==a || 0==b || RIGHE+1==a || COLONNE+1==b ) //se sto al bordo
	  cruciverba[a][b]='\0';
	else
	  cruciverba[a][b]=' ';
  
    //riempio cruciverba a cazzo
    bene=1;//PER ORA NON LO USO PERCHE NON CHO TEMPO
    for(a=1;a<RIGHE+1 && bene;a++)//per ogni riga del cruciverba che abbia senso considerare
      for(b=1;b<COLONNE+1 && bene;b++)//le colonne 0 e COLONNE+1 contengono caratteri di terminazione
	if(' '==cruciverba[a][b])
	  copiaNelCruciverba(parola(contaOrizzontale(a,b)),a,b);

    //se non va bene il cruciverba fanne un altro 
    bene=0;
    for(a=1;a<RIGHE+1 && !bene;a++)//per ogni riga utile
      for(b=1;b<COLONNE+1 && !bene;b++)//per ogni colonna utile
	if(!(vediSeEsisteV(a,b) && vediSeEsisteO(a,b)))
	  bene=1;
  }

  il ciclo brutale non funziona; strcmp va riscritta perche non considera gli asterischi come jolly
  
  
//Fine Programma----------------------------------------------------------
  stampaCruciverbaVuoto();
  stampaCruciverba();
  return 0;
}

