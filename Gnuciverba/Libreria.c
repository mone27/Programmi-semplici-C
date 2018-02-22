//Includo dipendenze
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>



//==================================================================
//==================================================================
//Funzioni per estrarre parole dal dizionario al cruciverba
//==================================================================
//==================================================================

//funzione che estrae una parola di lunghezza assegnata dal dizionario e la restituisce direttamente
char * sorteggiaParola(const int lunghezza){
  srand(time(NULL));
  return dizionario[lunghezza-3][rand()%NPAROLE];
  
}

//funzione che restituisce una lunghezza tra 3 e max
int sorteggiaLunghezza(int max){
  srand(time(NULL));
  
  max-=3;
  return rand()%max+3;
}

//funzione che estrai una parola casuale di lunghezza massima uguale a max
char * parola(const int max){
  return sorteggiaParola(sorteggiaLunghezza(max));
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
//Funzione per stampare le caselle del cruciverba
//==================================================================
//==================================================================

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

