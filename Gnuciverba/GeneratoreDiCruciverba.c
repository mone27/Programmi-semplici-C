//==============
//Configurazioni
//==============
#define LINUX 1 //attiva dizionario LINUX
#define COLONNE 7 //scegli numero di caselle di lunghezza del cruciverba
#define RIGHE 5 //scegli numero di caselle di altezza del cruciverba
//--------------------------------------------------------------------

char cruciverba[RIGHE+2][COLONNE+2]; //matrice che rappresenta il cruciverba
#include "Dizionario.h" //definisce la corretta matrice dizionario
#include "Libreria.c" //include: stdio.h, string.h, ctype.h, time.h, stdlib.h
/* Funzioni incluse in Libreria.c
   void stampaCruciverba(); (funzionante)
   void ordina_stringhe( char ** stringa, const int nStringhe); (funzionante)
   int contaVerticale(const int riga,const int colonna); (funzionante)
   int contaOrizzontale(const int riga,const int colonna); (funzionante)
   void copiaNelCruciverba(const char * const stringa,const int riga, const int colonna); (funzionante)
   char parola(int max); (funzionante)
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
  int a,b;
  
  //inizializzo matrice a spazio e la riquadro con caratteri di terminazione
  for(a=0;a<RIGHE+2;a++)//per ogni riga
    for(b=0;b<COLONNE+2;b++)//per ogni colonna
      if( 0==a || 0==b || RIGHE+1==a || COLONNE+1==b ) //se sto al bordo
	cruciverba[a][b]='\0';
      else
	cruciverba[a][b]=' ';
  
//Programma effettivo fino a qui-------------------------------------------

  
  puts(parola(7));




  
//Fine Programma----------------------------------------------------------  
  stampaCruciverba();
  return 0;
}

