//==============
//Configurazioni
//==============
#define LINUX 1 //attiva dizionario LINUX
#define COLONNE 7 //scegli numero di caselle di lunghezza del cruciverba
#define RIGHE 5 //scegli numero di caselle di altezza del cruciverba
//--------------------------------------------------------------------



#include "Dizionario.h" //definisce la corretta matrice dizionario
#include "Libreria.c" //include stdio.h, string.h e ctype.h
/* Funzioni incluse in Libreria.c
   void stampaCruciverba(const char tab[RIGHE+2][COLONNE+2]); (funzionante)
   void ordina_stringhe( char ** stringa, const int nStringhe); (funzionante)
*/


int main() {
  char cruciverba[RIGHE+2][COLONNE+2]; //matrice che rappresenta il cruciverba
  int a,b;
  
  //inizializzo matrice a spazio e la riquadro con caratteri di terminazione
  for(a=0;a<RIGHE+2;a++)//per ogni riga
    for(b=0;b<COLONNE+2;b++)//per ogni colonna
      if( 0==a || 0==b || RIGHE+1==a || COLONNE+1==b ) //se sto al bordo
	cruciverba[a][b]='\0';
      else
	cruciverba[a][b]=' ';

  stampaCruciverba(cruciverba);
  
  return 0;
}

