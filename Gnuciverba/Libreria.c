//Includo dipendenze
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "Dizionario.h" //definisce la corretta matrice dizionario
char cruciverba[RIGHE+2][COLONNE+2]; //matrice che rappresenta il cruciverba
int tabUtilizzo[LPAROLE][NPAROLE]; //matrice che tiene traccia dell'utilizzo delle parole del dizionario: 0 non usata, 1 gia' usata;


//==================================================================
//==================================================================
//Funzioni per completare le parole iniziate nel cruciverba
//==================================================================
//==================================================================

//funzione che data una posizione nel cruciverba, va a inizio parola orizzontale e se e' iniziata
//cerca nel dizionario un possibile completamento, se lo trova lo scrive subito nel cruciverba
int completaO(const int x, const int y){
  //da cambiare
  return y;
}

//funzione che data una posizione nel cruciverba, va a inizio parola verticale e se e' iniziata
//cerca nel dizionario un possibile completamento, se lo trova lo scrive subito nel cruciverba
int completaV(const int x, const int y){
  //da cambiare
  return y;
}


//==================================================================
//==================================================================
//Funzioni per copiare parole dal dizionario al cruciverba
//==================================================================
//==================================================================

//funzione che copia una stringa del dizionario nel cruciverba in orizzontale
//ATTENZIONE: la funzione deve essere chiamata solo se si e' sicuri che la stringa entri nella tabella
void copiaNelCruciverbaO(const char * const stringa,const int riga, const int colonna){
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
//Funzioni per estrarre parole dal dizionario 
//==================================================================
//==================================================================

//funzione che estrae una parola di lunghezza assegnata dal dizionario
//se dovesse essere gia stata usata la parola estratta a sorte ricerca a seguire la parola
//se dovessero essere tutte gia' usate restituisce NULL
char * sorteggiaParola(const int lunghezza){
  int n;
  char *ptr;

  //controllo che esistano parole non usate
  for(n=0;NPAROLE>n && tabUtilizzo[lunghezza-3][n];n++);

  //se ho finito il ciclo precedente non esistono parole
  if(NPAROLE==n)
    ptr=NULL;

  //se esistono parole 
  else{
    //ne sorteggio una
    n=rand()%NPAROLE;

    //se non va bene scorro fino a trovarne una buona
    while(tabUtilizzo[lunghezza-3][n])
      //se incrementando uscirei dalla matrice
      if(++n>=NPAROLE)
	n=0;//torno dentro
      else
	n++;

    //restituisco la parola trovata
    ptr=dizionario[lunghezza-3][n];

    //aggiorno tabella utilizzi
    tabUtilizzo[lunghezza-3][n]=1;
  }
  
  return ptr;
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

//funzione che estrae una parola casuale dal dizionario di lunghezza massima uguale a max e lunghezza minima uguale a tre
//restituisce null in caso max sia minore di 3
char * parolaO(const int max){
  char *ptr;

  ptr=0; //imposto a null
  
  if(max>=3)
    ptr=sorteggiaParola(sorteggiaLunghezza(max));
    
  return ptr;
}


//==================================================================
//==================================================================
//Funzioni per l'approccio brutale (migliorato)
//==================================================================
//==================================================================

//funzione che riempie il cruciverba scrivendo anche in verticale
int cruciFill2(){
  int a,b,bene;
  char *ptr;
  
  //sempre tutto bene all'inizio
  bene=1;
  
  //per ogni casella del cruciverba significativa
  for(a=1;a<RIGHE+1 && bene;a++)//per ogni riga
    for(b=1;b<COLONNE+1 && bene;b++)//per ogni colonna
      switch(cruciverba[a][b]){
	
	//se e' un blocco nero skippa
      case '\0':
	break;
	
	//se e' una casella vuota
      case ' ':
	//inserisci una parola di almeno tre lettere in orizzontale
	ptr=parolaO(contaOrizzontale(a,b));
	
	if(0!=ptr)//se la parola ha restituito effettivamente una stringa 
	  copiaNelCruciverbaO(ptr,a,b);

	//volutamente eseguo le istruzioni anche del default
	
	//se e' una casella con una lettera
      default :
	//completo la parola in orizzontale e poi in verticale se possibile o necessario
	bene=completaO(a,b);
	if(bene)//se quello di prima va male e quello dopo va bene avrei un falso positivo
	  bene=completaV(a,b);
      }

  return bene;
}


//==================================================================
//==================================================================
//Funzione per inizializzare il cruciverba e la tabUtilizzo
//==================================================================
//==================================================================

//funzione che pulisce inizializza il cruciverba a spazio e la tab utilizzo a 0
void cruciClean(){
  int a,b;
  
  //inizializzo matrice a spazio e la riquadro con caratteri di terminazione
  for(a=0;a<RIGHE+2;a++)//per ogni riga
    for(b=0;b<COLONNE+2;b++)//per ogni colonna
      if( 0==a || 0==b || RIGHE+1==a || COLONNE+1==b ) //se sto al bordo
	cruciverba[a][b]='\0';
      else
	cruciverba[a][b]=' ';
  
  //inizializzo matrice utilizzo a parole non usate
  for(a=0;a<LPAROLE;a++)//per ogni riga
    for(b=0;b<NPAROLE;b++)//per ogni colonna
      tabUtilizzo[a][b]=0;
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
//Funzione per controllare la correttezza del cruciverba
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



//====================VECCHIE=FUNZIONI==================================================================================================================================

/*





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

//funzione che riempie il cruciverba di parole in orizzontale casualmente
void cruciFill(){
  int a,b;
  for(a=1;a<RIGHE+1;a++)//per ogni riga del cruciverba che abbia senso considerare
    for(b=1;b<COLONNE+1;b++)//le colonne 0 e COLONNE+1 contengono caratteri di terminazione
      if(' '==cruciverba[a][b])
	copiaNelCruciverba(parola(contaOrizzontale(a,b)),a,b);
}

*/
