//Includo dipendenze
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include "Dizionario.c" //definisce la corretta matrice dizionario
char cruciverba[RIGHE+2][COLONNE+2]; //matrice che rappresenta il cruciverba
int tabUtilizzo[LPAROLE][NPAROLE]; //matrice che tiene traccia dell'utilizzo delle parole del dizionario: 0 non usata, 1 gia' usata;


//==================================================================
//==================================================================
//Funzioni per copiare parole dal dizionario al cruciverba
//==================================================================
//==================================================================

//funzione che copia una stringa del dizionario nel cruciverba in orizzontale
//ATTENZIONE: la funzione deve essere chiamata solo se si e' sicuri che la stringa entri nella tabella
int cruciFill4(){
  int a,b,bene,n,lunO,lunV;
  //per riempimento quadrato trovo lato minore
  n= RIGHE>COLONNE ? COLONNE+1 : RIGHE+1;

  //sempre tutto bene all'inizio
  bene=1;
  //  puts("INIZIO COSTRUZIONE NUOVO CRUCIVERBA---------------------------------");
  //per ogni casella del cruciverba significativa
  for(a=1;a<n && bene;a++)//per ogni riga
    for(b=1;b<n && bene;b++){//per ogni colonna

      //se la casella e' vuota
      if(' '==cruciverba[a][b]){
    //	printf("Casella %d,%d vuota\t",a,b);//debug
    lunO=contaOrizzontale(a,b);
    lunV=contaVerticale(a,b);
    if(lunO>=lunV){//se ho piu' spazio libero in orizzontale
      //       printf("Ho piu spazio in orizzontale\t");//debug
      if(lunO<3)//se ho una o due caselle metto un asterisco (magari in quello dopo lunV>lunO)
        cruciverba[a][b]='*';
      else
        copiaNelCruciverbaO(parola(lunO),a,b);//immetto nuova parola
      bene=completaV(a,b);// vedo se posso dare un senso anche nell'altra dimenzione
    }
    else{ //se invece ho piu spazio in verticale
      //	  printf("Ho piu spazio in verticale\t");//debug
      if(lunV<3){//se ho solo uno o due caselle metto asterischi
        if(1==lunV)
          copiaAsteriscoNelCruciverbaV("*",a,b);
        else//se invece ci sono due spazi
          copiaAsteriscoNelCruciverbaV("**",a,b);
      }
      copiaNelCruciverbaV(parola(lunV),a,b);//immetto nuova parola
      bene=completaO(a,b);// vedo se posso dare un senso anche nell'altra dimenzione
    }
    //       	putchar('\n');//debug
      }

      //se la casella ha una lettera
      else if(isalpha(cruciverba[a][b])){
    bene+=completaO(a,b);
        printf("completaO(%d,%d)=%d\n",a,b,bene);
    stampaCruciverba();
    bene+=completaV(a,b);
    printf("completaV(%d,%d)=%d\n",a,b,bene);
    stampaCruciverba();
    if(1==a){//questo sistema lo utilizzo solo per gli spigoli
      bene+=completaO(b,a);
      printf("completaO(%d,%d)=%d\n",b,a,bene);
      stampaCruciverba();
      bene+=completaV(b,a);
      printf("completaV(%d,%d)=%d\n",b,a,bene);
      stampaCruciverba();
    }
    if(5==bene)//bene stava gia a 1 e ci sommo i quattro positivi delle funzioni completaX
      bene=1;
    else
      bene=0;
      }

      //se e' un carattere di terminazione skippo
    }
  //  puts("FINE GENERAZIONE.");
  return bene;
}
void copiaNelCruciverbaO(const char * const stringa,const int riga, const int colonna){
  int a;
  
  //per ogni locazione della stringa
  for(a=0;'\0'!=stringa[a];a++)
    //se non scrivo su un carattere di terminazione
    if('\0'==cruciverba[riga][colonna+a])
      printf("Errore copiaNelCruciverbaO: tentata scrittura di \'%c\' su carattere di terminazione [%d,%d]\n",stringa[a],riga,colonna+a);
    else
      cruciverba[riga][colonna+a]=stringa[a];  //copio normalmente

  //copio anche carattere di terminazione (quadratino nero nel cruciverba finito)
  cruciverba[riga][colonna+a]='\0'; 
  
  return;
}

//non sovrascrive caratteri preesistenti
void copiaAsteriscoNelCruciverbaO(const char * const stringa,const int riga, const int colonna){
  int a;
  
  //per ogni locazione della stringa
  for(a=0;'\0'!=stringa[a];a++)
    //se non scrivo su un carattere di terminazione
    if('\0'==cruciverba[riga][colonna+a])
      printf("Errore copiaAsteriscoO: tentata scrittura di \'%c\' su carattere di terminazione [%d,%d]\n",stringa[a],riga,colonna+a);
    else if(!isalpha(cruciverba[riga][colonna+a])) //se non scrivo su una lettera
      cruciverba[riga][colonna+a]=stringa[a];  //copio normalmente

  //copio anche carattere di terminazione (quadratino nero nel cruciverba finito)
  cruciverba[riga][colonna+a]='\0'; 
  
  return;
}


//funzione che copia una stringa del dizionario nel cruciverba in verticalmente
//ATTENZIONE: la funzione deve essere chiamata solo se si e' sicuri che la stringa entri nella tabella
void copiaNelCruciverbaV(const char * const stringa,const int riga, const int colonna){
  int a;
  
  //per ogni locazione della stringa
  for(a=0;'\0'!=stringa[a];a++)
    //se non scrivo su un carattere di terminazione
    if('\0'==cruciverba[riga+a][colonna])
      printf("Errore copiaNelCruciverbaV: tentata scrittura di \'%c\' su carattere di terminazione [%d,%d]\n",stringa[a],riga+a,colonna);
    else
      cruciverba[riga+a][colonna]=stringa[a];  //copio normalmente

  //copio anche carattere di terminazione (quadratino nero nel cruciverba finito)
  cruciverba[riga+a][colonna]='\0'; 
  
  return;
}

//non sovrascrivo su caratteri preesistenti
void copiaAsteriscoNelCruciverbaV(const char * const stringa,const int riga, const int colonna){
  int a;
  
  //per ogni locazione della stringa
  for(a=0;'\0'!=stringa[a];a++)
    //se non scrivo su un carattere di terminazione
    if('\0'==cruciverba[riga+a][colonna])
      printf("Errore copiaAsteriscoV: tentata scrittura di \'%c\' su carattere di terminazione [%d,%d]\n",stringa[a],riga+a,colonna);
 
    else if(!isalpha(cruciverba[riga+a][colonna])) //se non scrivo su una lettera
      cruciverba[riga+a][colonna]=stringa[a];  //copio normalmente

  //copio anche carattere di terminazione (quadratino nero nel cruciverba finito)
  cruciverba[riga+a][colonna]='\0'; 
  
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
char * parola(const int max){
  return sorteggiaParola(sorteggiaLunghezza(max));
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
      if('\0'==cruciverba[a][b]){  //se e' un carattere di terminazione
	if(0==a || RIGHE+1==a)//se prima riga o ultima
	  putchar('-');
        else if(0==b || COLONNE+1==b)//se prima o ultima colonna
	  putchar('|');
	else //se carattere di terminazione nel cruciverba
	  putchar('#');  //lo sostituisco con #
      }
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
//Funzioni standard C modificate per leggere asterischi come jolly
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


//funzione che determina se i primi n caratteri di s1 sono uguali a quelli di s2 (asterischi considerati jolly)
//Esempio: strnCompara(stringa,dizionario[lun][x]);
int strnCompara(const char * const s1,const char * const s2,const int n){
  int a,bene;
  bene=1;//se supero tutti i controlli tutto apposto

  for(a=0;a<n;a++)//considero tutte le locazioni
    if(s1[a]!=s2[a])//se ne becco due diverse
      if('*'!=s1[a])//se non e' un jolly
	bene=0;//so diverse le stringhe
  
  return bene;
}


//==================================================================
//==================================================================
//Funzioni per verificare l'esistenza di parole nel dizionario
//==================================================================
//==================================================================

//funzione che determina se una stringa orizzontale del cruciverba
//sia presente nel dizionario o meno
int vediSeEsisteO(const int x,int y){
  char appoggio[COLONNE+1];//piu lunghe non le potrei trovare perche non entrerebbero nella tabella
  int c,trovato;

  //torno indietro a inizio parola qualora non ci fossi gia
  while('\0'!=cruciverba[x][y-1])
    y--;
    
  //copio la parola in appoggio
  for(c=0;'\0'!=cruciverba[x][y+c];c++)
    appoggio[c]=cruciverba[x][y+c];
  appoggio[c]='\0';
  
  trovato=0;
    
  if(strlen(appoggio)<3)//se la parola e' lunga 1 o 2 
    trovato=1;//tutto apposto
  
  if(strlen(appoggio)>LPAROLE+2){//se la parola e' piu lunga del dizionario
    trovato=2;//risultera' come vero nella condizione del for e quindi lo saltera' ma potro' riconventirlo in 0 dopo
  }
  
  //cerco se esiste la parola nel dizionario 
  for(c=0;c<NPAROLE && !trovato;c++) 
    if(strCompara(appoggio,dizionario[strlen(appoggio)-3][c]))//comparo tutte le stringhe della stessa lunghezza
      trovato=1;

  if(2==trovato)
    trovato=0;//riconverto in zero
  
  return trovato;
}

//funzione che determina se una stringa verticale del cruciverba
//sia presente nel dizionario o meno
int vediSeEsisteV(int x, const int y){
  char appoggio[RIGHE+1];//piu lunghe non entrerebbero nel cruciverba
  int c,trovato;

  //torno indietro a inizio parola qualora non ci fossi gia
  while('\0'!=cruciverba[x-1][y])
    x--;
  
  //copio la parola in appoggio
  for(c=0;'\0'!=cruciverba[x+c][y];c++)
    appoggio[c]=cruciverba[x+c][y];
  appoggio[c]='\0';

  trovato=0;
  
  if(strlen(appoggio)<3)//se la parola e' lunga 1 o 2 
    trovato=1;//tutto apposto

  if(strlen(appoggio)>LPAROLE+2){//se la parola e' piu lunga del dizionario non puo' esistere
    trovato=2;//risultera' come vero nella condizione del for e quindi lo saltera' ma potro' riconventirlo in 0 dopo
  }

  //cerco se esiste la parola nel dizionario 
  for(c=0;c<NPAROLE && !trovato;c++) 
    if(strCompara(appoggio,dizionario[strlen(appoggio)-3][c]))//comparo tutte le stringhe della stessa lunghezza
      trovato=1;

  if(2==trovato)//reimposto valore reale di trovato
    trovato=0;
  
  return trovato;
}


//==================================================================
//==================================================================
//Funzioni per controllare la correttezza del cruciverba
//==================================================================
//==================================================================

//funzione da lanciare prima del cruciCheck per evitari falsi positivi dovuti agli spazi
int cruciCheckSpazi(){
  int bene,a,b;
  bene=1;
  
  for(a=1;a<RIGHE+1 && bene;a++)//per ogni riga utile
    for(b=1;b<COLONNE+1 && bene;b++)//per ogni colonna utile
      if(' '==cruciverba[a][b])//se trovo uno spazio
	bene=0;//non va bene il cruciverba
  
  return bene;
}

//funzione che controlla che un cruciverba senza spazi sia corretto
int cruciCheck(){
  int bene,a,b;
  bene=1;
  
  for(a=1;a<RIGHE+1 && bene;a++){//per ogni riga utile
    for(b=1;b<COLONNE+1 && bene;b++)//per ogni colonna utile
      if(!(vediSeEsisteV(a,b) && vediSeEsisteO(a,b)))
	bene=0;
      //      putchar('0'+!(vediSeEsisteV(a,b) && vediSeEsisteO(a,b)));
    //    putchar('\n');
  }
  
  return bene;
}


//==================================================================
//==================================================================
//Funzioni per completare le parole iniziate nel cruciverba
//==================================================================
//==================================================================

//funzione che data una posizione nel cruciverba, va a inizio parola orizzontale e se e' iniziata
//cerca nel dizionario un possibile completamento, se lo trova lo scrive subito nel cruciverba
int completaO(const int x, const int y){
  char appoggio[COLONNE+1]; //parole piu grosse non entrano nel cruciverba
  int c,trovato,inizio,l,u,i,j,spazio,cond,preesistente;

  //inizializzo
  u=y;//dovro far riferimento alle coordinate iniziali alla fine, quindi le salvo
  trovato=0;// non so se la trovero...
  preesistente=0; //non so se ci sta gia scritta una parola completa nel cruciverba

  //torno indietro a inizio parola qualora non ci fossi gia
  while('\0'!=cruciverba[x][u-1])
    u--;

  //devo sapere quanto spazio ho 
  spazio=contaOrizzontale(x,u);

  if(spazio<3){
    trovato=1;//parole piu corte di 3 lettere vanno sempre bene
    if(1==spazio)
      copiaAsteriscoNelCruciverbaO("*",x,u);
    else if(2==spazio)//se invece ci sono due spazi
      copiaAsteriscoNelCruciverbaO("**",x,u);//stampo un asterisco
    preesistente=1;//in ogni caso non ho bisogno di eseguire la copia dopo
  }

  //non e' utile eseguire questi passaggi se ho gia stabilito che va bene
  if(!trovato){
    //copio la parola in appoggio
    for(c=0;'\0'!=cruciverba[x][u+c];c++)//copio tutta la stringa fino al carattere di terminazione
      appoggio[c]=cruciverba[x][u+c];
    appoggio[c]='\0';

    //scorro da fine stringa alla ricerca del primo carattere non spazio
    while(' '==appoggio[--c]); //c all'inizio su c.t. quindi deincremento e poi considero

    //imposto la fine della stringa dopo l'ultimo carattere non spazio
    appoggio[c+1]='\0';//quando esco dal while c punta all'ultimo carattere letterale che non voglio sovrascrivere (+1)

    //jollificazione degli spazi infraparola
    while(-1!=--c)//per ogni carattere letterale precedente all'ultimo
      if(' '==appoggio[c])//se incontro uno spazio
	appoggio[c]='*';//lo jollifico perche vuol dire che se non l'ho scritto finora non incrocia con nulla
    
    //devo sapere quanto e' lunga la parola da completare
    l=strlen(appoggio);

    //se la lunghezza coincide con la parola che trovo scritta vuol dire che e' gia completa sse non ci sono jolly
    if(l==spazio){
      for(c=0;'\0'!=appoggio[c] && '*';c++);
      if(c==l){//se non ho fallito il for di prima prima della fine della parola
	preesistente=1;
	trovato=1;
      }
    }

    //sorteggio una lunghezza NON INDICE compresa tra l e spazio (disponibile) dalla quale cominciare a scandagliare il dizionario
    do
      inizio=sorteggiaLunghezza(spazio);
    while(inizio<l);

    //imposto condizione in funzione della lunghezza della parola da continuare
    if(l>=3)
      cond=spazio-l+1;
    else
      cond=spazio-2;
  }
  
  c=0;//devo provare una volta ogni lunghezza nel peggiore dei casi
  while(!trovato && c<cond){//fintanto che non ho trovato come continuare la parola e non ho provato tutte le lunghezze ammissibili
    
    j=rand()%NPAROLE;//faccio in modo che non appaiano sono i risultati di inizio vettore
    
    for(i=0;i<NPAROLE && !trovato;i++){//per ogni parola di quella lunghezza
      j++;//questa cosa accadra i volte
      if(j>=NPAROLE)//questa quindi al piu una...
	j=0;
      if(strnCompara(appoggio,dizionario[inizio-3][j],l) && !tabUtilizzo[inizio-3][j])//se puo' essere un suo continuo e non l'ho gia usata
	trovato=1;//esco dai cicli di ricerca
    }
    if(!trovato){
      inizio++;//eseguo ricerca con la prossima lunghezza
      if(inizio>spazio){//se sto uscendo dalle righe della matrice dizionario
	if(l<3)//riporto alla lunghezza della stringa da completare
	  inizio=3;
	else
	  inizio=l;
      }
      c++;//conto un altro ciclo di non trovato
    }
  }

  //se ho trovato la parola la scrivo
  if(trovato && !preesistente){
    copiaNelCruciverbaO(dizionario[inizio-3][j],x,u);
    tabUtilizzo[inizio-3][j]=1; //ricordo che uso la parola
  }

  return trovato;
}


//funzione che data una posizione nel cruciverba, va a inizio parola verticale e se e' iniziata
//cerca nel dizionario un possibile completamento, se lo trova lo scrive subito nel cruciverba
int completaV(const int x, const int y){
  char appoggio[RIGHE+1]; //parole piu grandi non le posso trovare perche non ci entrano nella tabella
  int c,trovato,inizio,l,u,i,j,spazio,cond,preesistente;
  
  //inizializzo
  u=x;//dovro far riferimento alle coordinate iniziali alla fine, quindi le salvo
  trovato=0;// non so se la trovero...
  preesistente=0; //non so se ci sta gia scritta una parola completa nel cruciverba per il momento
  
  //torno indietro a inizio parola qualora non ci fossi gia
  while('\0'!=cruciverba[u-1][y])
    u--;
  
  //devo sapere quanto spazio ho 
  spazio=contaVerticale(u,y);
 
  if(spazio<3){
    trovato=1;//parole piu corte di 3 lettere vanno sempre bene
    if(1==spazio)
      copiaAsteriscoNelCruciverbaV("*",u,y);
    else if(2==spazio)//se invece ci sono due spazi
      copiaAsteriscoNelCruciverbaV("**",u,y);//stampo un asterisco
    preesistente=1;
  }

  //non e' utile eseguire questi passaggi se ho gia stabilito che va bene
  if(!trovato){
    //copio la parola in appoggio
    for(c=0;'\0'!=cruciverba[u+c][y];c++)//copio tutta la stringa fino al carattere di terminazione
      appoggio[c]=cruciverba[u+c][y];
    appoggio[c]='\0';

    //scorro da fine stringa alla ricerca del primo carattere non spazio
    while(' '==appoggio[--c]); //c all'inizio su c.t. quindi deincremento e poi considero

    //imposto la fine della stringa dopo l'ultimo carattere non spazio
    appoggio[c+1]='\0';//quando esco dal while c punta all'ultimo carattere letterale che non voglio sovrascrivere (+1)

    //jollificazione degli spazi infraparola
    while(-1!=--c)//per ogni carattere letterale precedente all'ultimo
      if(' '==appoggio[c])//se incontro uno spazio
	appoggio[c]='*';//lo jollifico perche vuol dire che se non l'ho scritto finora non incrocia con nulla

 
    //devo sapere quanto e' lunga la parola da completare
    l=strlen(appoggio);

    //se la lunghezza coincide con la parola che trovo scritta vuol dire che e' gia completa sse non ci sono jolly
    if(l==spazio){
      for(c=0;'\0'!=appoggio[c] && '*';c++);
      if(c==l){//se non ho fallito il for di prima prima della fine della parola
	preesistente=1;
	trovato=1;
      }
    }    

    //sorteggio una lunghezza NON INDICE compresa tra l e spazio (disponibile) dalla quale cominciare a scandagliare il dizionario
    do
      inizio=sorteggiaLunghezza(spazio);
    while(inizio<l);
    
    //imposto condizione in funzione della lunghezza della parola da continuare
    if(l>=3)
      cond=spazio-l+1;
    else
      cond=spazio-2;
  }

  c=0;//devo provare una volta ogni lunghezza nel peggiore dei casi
  while(!trovato && c<cond){//fintanto che non ho trovato come continuare la parola e non ho provato tutte le lunghezze ammissibili
    
    j=rand()%NPAROLE;//faccio in modo che non appaiano sono i risultati di inizio vettore

    for(i=0;i<NPAROLE && !trovato;i++){//per ogni parola di quella lunghezza
      j++;//questa cosa accadra i volte
      if(j==NPAROLE)//questa quindi al piu una...
	j=0;
      if(strnCompara(appoggio,dizionario[inizio-3][j],l) && !tabUtilizzo[inizio-3][j])//se puo' essere un suo continuo e non l'ho gia usata
	trovato=1;//esco dai cicli di ricerca
    }
    if(!trovato){
      inizio++;//eseguo ricerca con la prossima lunghezza
      if(inizio>=spazio){//se sto uscendo dalle righe della matrice dizionario
	if(l<3)//riporto alla lunghezza della stringa da completare
	  inizio=3;
	else
	  inizio=l;
      }
      c++;//conto un altro ciclo di non trovato
    }
  }

  //se ho trovato la parola la scrivo
  if(trovato && !preesistente){
    copiaNelCruciverbaV(dizionario[inizio-3][j],u,y);
    tabUtilizzo[inizio-3][j]=1; //ricordo che uso la parola
  }
 
  return trovato;
}
 


//==================================================================
//==================================================================
//Funzione per l'approccio brutale (migliorato)
//==================================================================
//==================================================================

//funzione che riempie il cruciverba scrivendo anche in verticale
//ATTENZIONE: usare questa funzione solo su cruciverba quadrati 
int cruciFill3(){
  int a,b,l,bene;
  
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
	l=contaOrizzontale(a,b);
	
	//inserisci una parola di almeno tre lettere in orizzontale
	if(l<3){
	  if(1==l)
	    copiaNelCruciverbaO("*",a,b);
	  else
	    copiaNelCruciverbaO("**",a,b);
	}
	else
	  copiaNelCruciverbaO(parola(contaOrizzontale(a,b)),a,b);

	//volutamente eseguo le istruzioni anche del default
	
	//se e' una casella con una lettera
      default :
	//completo la parola in orizzontale e poi in verticale se possibile o necessario
	bene=completaO(a,b);
	if(bene)//se quello di prima va male e quello dopo va bene avrei un falso positivo
	  bene=completaV(a,b);
	if(bene)
	  bene=completaO(b,a);
	if(bene)
	  bene=completaV(b,a);
      }

  return bene;
}

