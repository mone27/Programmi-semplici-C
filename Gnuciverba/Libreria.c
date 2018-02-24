//Includo dipendenze
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "Dizionario.h" //definisce la corretta matrice dizionario
char cruciverba[RIGHE+2][COLONNE+2]; //matrice che rappresenta il cruciverba


//==================================================================
//==================================================================
//Funzione per inizializzare il cruciverba
//==================================================================
//==================================================================

//funzione che pulisce inizializza il cruciverba a spazio
void cruciClean(){
  int a,b;
  //inizializzo matrice a spazio e la riquadro con caratteri di terminazione
  for(a=0;a<RIGHE+2;a++)//per ogni riga
    for(b=0;b<COLONNE+2;b++)//per ogni colonna
      if( 0==a || 0==b || RIGHE+1==a || COLONNE+1==b ) //se sto al bordo
	cruciverba[a][b]='\0';
      else
	cruciverba[a][b]=' ';
}

//==================================================================
//==================================================================
//Funzioni per controllare se esistono le parole nel cruciverba
//==================================================================
//==================================================================

//funzione che determina se s1 e' uguale a s2 (asterischi considerati jolly)
//Esempio: strCompara(stringa,dizionario[lun][x]);
int strCompara(const char * const s1,const char * const s2){
  int a,bene;
  bene=1;//se supero tutti i controlli s1==s2

  if(strlen(s1)!=strlen(s2))//se una e' piu lunga dell'altra
    bene=0;//di che stiamo a parla

  for(a=0;a<strlen(s1);a++)//considero tutte le locazioni
    if(s1[a]!=s2[a])//se ne becco due diverse
      if('*'!=s1[a])//se non e' un jolly
	bene=0;//so diverse le stringhe
  
  return bene;
}


//funzione che determina se una stringa orizzontale del cruciverba
//sia presente nel dizionario o meno
int vediSeEsisteO(const int x,int y){
  char appoggio[LPAROLE+3];//al massimo trattero parole di lunghezza LPAROLE+2 ma parlando di stringhe aggiungo+1 per c.t.
  int c,trovato;

  //torno indietro a inizio parola qualora non ci fossi gia
  while('\0'!=cruciverba[x][y-1])
    y--;
    
  //copio la parola in appoggio
  for(c=0;'\0'!=cruciverba[x][y+c] && ' '!=cruciverba[x][c+y];c++)
    appoggio[c]=cruciverba[x][y+c];
  appoggio[c]='\0';
  
  trovato=0;
    
  if(strlen(appoggio)<3)//se la parola e' lunga 1 o 2 
    trovato=1;//tutto apposto
  
  if(strlen(appoggio)>LPAROLE+2){
    puts("Errore: nel cruciverba ce una parola piu lunga del dizionario");
    trovato=1;//proviamo a limitare i danni...
  }
  
  //cerco se esiste la parola nel dizionario 
  for(c=0;c<NPAROLE && !trovato;c++) 
    if(strCompara(appoggio,dizionario[strlen(appoggio)-3][c]))//comparo tutte le stringhe della stessa lunghezza
      trovato=1;
  
  return trovato;
}

//funzione che determina se una stringa verticale del cruciverba
//sia presente nel dizionario o meno
int vediSeEsisteV(int x, const int y){
  char appoggio[LPAROLE+3];//al massimo trattero parole di lunghezza LPAROLE+2 ma parlando di stringhe aggiungo+1 per c.t.
  int c,trovato;

  //torno indietro a inizio parola qualora non ci fossi gia
  while('\0'!=cruciverba[x-1][y])
    x--;
  
  //copio la parola in appoggio
  for(c=0;'\0'!=cruciverba[x+c][y] && ' '!=cruciverba[x+c][y];c++)
    appoggio[c]=cruciverba[x+c][y];
  appoggio[c]='\0';

  trovato=0;
  
  if(strlen(appoggio)<3)//se la parola e' lunga 1 o 2 
    trovato=1;//tutto apposto

  if(strlen(appoggio)>LPAROLE+2){
    puts("Errore: nel cruciverba ce una parola piu lunga del dizionario");
    trovato=1;//proviamo a limitare i danni...
  }

  //cerco se esiste la parola nel dizionario 
  for(c=0;c<NPAROLE && !trovato;c++) 
    if(strCompara(appoggio,dizionario[strlen(appoggio)-3][c]))//comparo tutte le stringhe della stessa lunghezza
      trovato=1;
  
  return trovato;
}

//==================================================================
//==================================================================
//Funzioni per estrarre parole dal dizionario al cruciverba
//==================================================================
//==================================================================

//stringhe per restituire carattere jolly
char unchar[2]="*";
char duechar[3]="**";

//funzione che estrae una parola di lunghezza assegnata dal dizionario e la restituisce direttamente
char * sorteggiaParola(const int lunghezza){
  return dizionario[lunghezza-3][rand()%NPAROLE];
  
}

//funzione che restituisce una lunghezza tra 3 e max
int sorteggiaLunghezza(int max){
  int n;
  
  //evito di richiedere parole di una lunghezza non supportata
  if(max>LPAROLE+2)
    max=LPAROLE+2;//(+2 perche salto le parole di una e due lettere nel dizionario)

  if(3==max)
    n=3;//c'e' poco da sorteggiare...
  else{
    max=max-2;// 
    n=rand()%max+3;//non restituisco l'indice ma la lunghezza della parola
  }
  return n;
}

//funzione che estrai una parola casuale di lunghezza massima uguale a max
char * parola(const int max){
  char *ptr;
  
  if(0==max)
    puts("Errore: passato argomento zero a parola(int max)");
  
  //se richiedo una parola di uno o due caratteri metto il carattere jolly
  else if(2==max)
    ptr=duechar;
  else if(1==max)
    ptr=unchar;
  
  else{
    ptr=sorteggiaParola(sorteggiaLunghezza(max));
  
    if(0==ptr)  //utile solo fintanto che il dizionario non e' ancora terminato
      ptr=parola(max);
  }
  
  return ptr;
}


//==================================================================
//==================================================================
//Funzione per copiare parole dal dizionario al cruciverba
//==================================================================
//==================================================================

//funzione che copia una stringa del dizionario nel cruciverba in orizzontale
//ATTENZIONE: la funzione deve essere chiamata solo se si e' sicuri che la stringa entri nella tabella
void copiaNelCruciverba(const char * const stringa,const int riga, const int colonna){
  int a;
  
  //per ogni locazione della stringa
  for(a=0;'\0'!=stringa[a];a++)
    //se non scrivo su un carattere di terminazione
    if('\0'==cruciverba[riga][colonna+a])
      printf("Errore: tentata scrittura su carattere di terminazione");
    else
      cruciverba[riga][colonna+a]=stringa[a];  //copio normalmente

  //copio anche carattere di terminazione (quadratino nero nel cruciverba finito)
  cruciverba[riga][colonna+a]='\0'; 
  
  return;
}


//==================================================================
//==================================================================
//Funzioni per contare le caselle del cruciverba
//==================================================================
//==================================================================

//funzione che conta quante caselle ci sono tra la casella attuale (compresa) e il primo carattere di terminazione 
int contaVerticale(const int riga,const int colonna){
  int a;

  //scorro in verticale finche non trovo il carattere di terminazione
  for(a=riga;'\0'!=cruciverba[a][colonna];a++);
  
  return a-riga;
}


//funzione che conta quante caselle ci sono tra la casella attuale (compresa) e il primo carattere di terminazione 
int contaOrizzontale(const int riga,const int colonna){
  int a;

  //scorro in verticale finche non trovo il carattere di terminazione
  for(a=colonna;'\0'!=cruciverba[riga][a];a++);
  
  return a-colonna;
}


//==================================================================
//==================================================================
//Funzioni per stampare le caselle del cruciverba
//==================================================================
//==================================================================


//funzione che prende in input la tabella cruciverba e stampa solo i caratteri di terminazione
void stampaCruciverbaVuoto(){
  int a,b;

  //stampo caratteri tabella
  for(a=0;a<RIGHE+2;a++){
    for(b=0;b<COLONNE+2;b++)
      if('\0'==cruciverba[a][b])  //se e' un carattere di terminazione 
	putchar('#');  //lo sostituisco con #
      else
	putchar(' ');
    putchar('\n');
  }
  
  return;
}


//funzione che prende in input la tabella cruciverba e la stampa
void stampaCruciverba(){
  int a,b;

  //stampo caratteri tabella
  for(a=0;a<RIGHE+2;a++){
    for(b=0;b<COLONNE+2;b++)
      if('\0'==cruciverba[a][b])  //se e' un carattere di terminazione 
	putchar('#');  //lo sostituisco con #
      else
	putchar(cruciverba[a][b]);
    putchar('\n');
  }
  
  return;
}


//==================================================================
//==================================================================
//Funzione per ordinare in ordine alfabetico un vettore di stringhe
//==================================================================
//==================================================================

//funzione che prendendo in input un vettore di stringhe lo ordina
//in ordine alfabetico con metodo bubble sort ottimizzato
void ordina_stringhe( char ** stringa, const int nStringhe){
  void sscambia( char ** stringa1, char ** stringa2);
  void rendi_maiuscola(const char * const stringa, char * const maiuscola);
  int i,j;

  for(i=0; i < nStringhe-1 ;i++)//per ogni passaggio
    for(j=0; j< nStringhe-1-i; j++){//per ogni stringa della matrice di stringhe
      char appoggio1[20],appoggio2[20];
      
      rendi_maiuscola(stringa[j],appoggio1);
      rendi_maiuscola(stringa[j+1],appoggio2);
      
      if(strcmp(appoggio1,appoggio2)>0)//se strcmp della maiuscola e' positiva
        sscambia(&stringa[j],&stringa[j+1]);// inverto le stringhe
    }
  
  return;
}


//funzione che copia una stringa in un altra rendendo maiuscole tutte le lettere
void rendi_maiuscola(const char * const stringa, char * const maiuscola){  //testata e funzionante
  int l,i;
  l=strlen(stringa);

  //per ogni locazione
  for(i=0;i<l;i++){
    //se ho un carattere
    if(isalpha(stringa[i]))
      //lo rendo maiuscolo
      maiuscola[i]=toupper(stringa[i]);
    else
      maiuscola[i]=stringa[i];
  }

  return;
}


//funzione che scambia due puntatori a stringa in un vettore di stringhe
//esempio chiamata: sscambia(&vettoreDiStringhe[1],&vettoreDiStringhe[2]);
void sscambia( char ** stringa1, char ** stringa2){  //testata e funzionante
   char *appoggio;
   appoggio=*stringa1;
   *stringa1=*stringa2;
   *stringa2=appoggio;
   return;
}


//==================================================================
//==================================================================
//Funzioni per l'approccio brutale (limitato e non ottimizzato)
//==================================================================
//==================================================================

//funzione che controlla che il cruciverba sia corretto
int cruciCheck(){
  int bene,a,b;
  bene=1;
  
  for(a=1;a<RIGHE+1 && bene;a++)//per ogni riga utile
    for(b=1;b<COLONNE+1 && bene;b++)//per ogni colonna utile
      if(!(vediSeEsisteV(a,b) && vediSeEsisteO(a,b)))
	bene=0;
  
  return bene;
}


//funzione che riempie il cruciverba di parole in orizzontale casualmente
void cruciFill(){
  int a,b;
  for(a=1;a<RIGHE+1;a++)//per ogni riga del cruciverba che abbia senso considerare
    for(b=1;b<COLONNE+1;b++)//le colonne 0 e COLONNE+1 contengono caratteri di terminazione
      if(' '==cruciverba[a][b])
	copiaNelCruciverba(parola(contaOrizzontale(a,b)),a,b);
}

