//==============
//Configurazioni
//==============
#define GENERICO 1 //attiva dizionario LINUX
#define COLONNE 7  //scegli numero di caselle di lunghezza del cruciverba7
#define RIGHE 5 //scegli numero di caselle di altezza del cruciverba 5 
//--------------------------------------------------------------------

#include "Libreria.c" //include: stdio.h, string.h, ctype.h, time.h, stdlib.h

//funzione che inizializza la matrice a tutte A
void cruciInit(){
  int a,b;
  
  //inizializzo matrice ad A e la riquadro con caratteri di terminazione
  for(a=0;a<RIGHE+2;a++)//per ogni riga
    for(b=0;b<COLONNE+2;b++)//per ogni colonna
      if( 0==a || 0==b || RIGHE+1==a || COLONNE+1==b ) //se sto al bordo
	cruciverba[a][b]='\0';
      else
	cruciverba[a][b]='A';
}

//funzione che controlla se tutti i caratteri della matrice sono uguali al carattere dato
int allZ(const char carattere){
  int a,b,daje;
  daje=1;
  
  for(a=1; a<RIGHE+1 && daje ;a++)//per ogni riga utile
    for(b=1; b<COLONNE+1 && daje ;b++)//per ogni colonna utile
      if(cruciverba[a][b]!=carattere)
	daje=0;
	 
  return daje;
}

//funzione che stampa il cruciverba prima pieno e poi vuoto
void cruciPrint(){
  puts("\nCruciverba trovato vuoto:");
  stampaCruciverbaVuoto();
  puts("\nCruciverba trovato:");
  stampaCruciverba();
}

void cruciPlusPlus(const int a, const int b){
  
  //se ho una Z incremento sul carattere di terminazione
  if(cruciverba[a][b]=='Z')
    cruciverba[a][b]='\0';
  
  //se ho il carattere di terminazione ritorno a A e incremento la casella successiva
  else if(cruciverba[a][b]=='\0'){
    cruciverba[a][b]='A';
    //se la casella successiva sta sulla stessa riga
    if(b+1<COLONNE+1)
      cruciPlusPlus(a,b+1);
    //altrimenti vado a capo
    else
      cruciPlusPlus(a+1,1);
  }
  
  //se ho una lettera qualsiasi: cruciPlusPlus!!!
  else
    cruciverba[a][b]++;
}

int main(){
  time_t inizio;
  double secondi;
  int ore,minuti;
  
  //prendo il tempo ad inizio esecuzione
  inizio= clock();
  
  //stampo ora di inizio esecuzione
  printf("Esecuzione lanciata\n");
//Inizio generazione--------------------------------------------------------

  tabInit();
  cruciInit();
  while(!allZ('\0')){
    cruciPlusPlus(1,1);
    if(cruciCheck())
      cruciPrint();
  }

//Fine generazione----------------------------------------------------------

  //ricavo e raffino tempo di esecuzione del programma
  secondi=(double)(clock()-inizio)/CLOCKS_PER_SEC;
  minuti=secondi/60;
  secondi-=(double)minuti*60;
  ore=minuti/60;
  minuti-=ore*60;
  printf("\nProgramma terminato con successo\nTempo di esecuzione: %d Ore %d Minuti %.3f Secondi\n\a",ore,minuti,secondi);
  return 0;
}
