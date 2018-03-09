//==============
//Configurazioni
//==============
#define LINUX 1 //attiva dizionario LINUX
#define COLONNE 9 //scegli numero di caselle di lunghezza del cruciverba7
#define RIGHE 9 //scegli numero di caselle di altezza del cruciverba 5 
//--------------------------------------------------------------------

#include "Libreria.c" //include: stdio.h, string.h, ctype.h, time.h, stdlib.h
/* Funzioni incluse in Libreria.c
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


//funzione che riempie cruciverba di qualsiasi dimenzione
int cruciFill4(){
  int a,b,bene,n,lunO,lunV;
  //per riempimento quadrato trovo lato minore
  n= RIGHE>COLONNE ? COLONNE+1 : RIGHE+1;
  
  //sempre tutto bene all'inizio
  bene=1;

  //per ogni casella del cruciverba significativa
  for(a=1;a<n && bene;a++)//per ogni riga
    for(b=1;b<n && bene;b++){//per ogni colonna
      
      //se la casella e' vuota
      if(' '==cruciverba[a][b]){
	printf("Casella %d,%d vuota\t",a,b);//debug
	lunO=contaOrizzontale(a,b);
	lunV=contaVerticale(a,b);
	if(lunO>=lunV){//se ho piu' spazio libero in orizzontale
	  printf("Ho piu spazio in orizzontale\t");//debug
	  if(lunO<3)//se ho una o due caselle metto un asterisco (magari in quello dopo lunV>lunO)
	    cruciverba[a][b]='*';
	  else
	    copiaNelCruciverbaO(parola(lunO),a,b);//immetto nuova parola
	  bene=completaV(a,b);// vedo se posso dare un senso anche nell'altra dimenzione
	}
	else{ //se invece ho piu spazio in verticale
	  printf("Ho piu spazio in verticale\t");//debug
	  if(lunV<3)//se ho solo uno o due caselle metto asterischi
	    if(1==lunV)
	      copiaAsteriscoNelCruciverbaV("*",a,b);
	    else//se invece ci sono due spazi
	      copiaAsteriscoNelCruciverbaV("**",a,b);
	  copiaNelCruciverbaV(parola(lunV),a,b);//immetto nuova parola
	  bene=completaO(a,b);// vedo se posso dare un senso anche nell'altra dimenzione
	}
	putchar('\n');//debug
      }

      //se la casella ha una lettera
      else if(isalpha(cruciverba[a][b])){
	printf("Casella %d,%d piena\t",a,b);//debug
	bene+=completaO(a,b);
	printf("%d\n",bene);
	bene+=completaV(a,b);
	printf("%d\n",bene);
	bene+=completaO(b,a);
	printf("%d\n",bene);
      	bene+=completaV(b,a);
	printf("%d\n",bene);
	if(4==bene)
	  bene=1;
	else
	  bene=0;
      }

      //se e' un carattere di terminazione skippo
    }

  return bene;
}


int main() {
  time_t inizio;
  double secondi;
  int ore,minuti,a;
  
  //prendo il tempo ad inizio esecuzione
  inizio= clock();
  
  //insemino funzione rand()
  srand(time(NULL));
  
  //stampo ora di inizio esecuzione
  printf("Esecuzione lanciata\n");
//Inizio generazione--------------------------------------------------------

  /*
  do{
    cruciClean();
    a=cruciFill3();
  }while(!a && !cruciCheck());
  */
  cruciClean();
  cruciFill4();
  
//Fine generazione----------------------------------------------------------
  stampaCruciverbaVuoto();
  stampaCruciverba();
  
  //ricavo e raffino tempo di esecuzione del programma
  secondi=(double)(clock()-inizio)/CLOCKS_PER_SEC;
  minuti=secondi/60;
  secondi-=(double)minuti*60;
  ore=minuti/60;
  minuti-=ore*60;
  printf("Programma terminato con successo\nTempo di esecuzione: %d Ore %d Minuti %.3f Secondi\n\a",ore,minuti,secondi);
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
