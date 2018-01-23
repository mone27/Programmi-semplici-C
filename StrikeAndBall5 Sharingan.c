/*
 * Quando si segnano nella callTab i punti fatti bisogna scrivere il tipo di punto e quanti.
 * ESEMPIO1: 2 strike 1 ball = s2b1 oppure b1s2
 * ESEMPIO2: 2 ball = b2 ASSOLUTAMENTE NON b2s0 !!
 * ESEMPIO3: 0 strike 0 ball = 0 oppure " " (spazio) ma ASSOLUTAMENTE NON s0b0!!!
*/

/*
 * CASI POSSIBILI:
 * 	Zero Strike e Zero Ball		fatto
 * 	Tot Strike e Zero Ball
 * 	Zero Strike e Tot Ball		fatto
 * 	Tot Strike e Tot Ball
 * 	Zero Strike e 5 Ball		fatto
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define G 5  //cinque numeri

char s[G+1];//numero segreto

int main(){
//inizializzo
	void contaPunti(void);
	void numeroSegreto(void);
	void triangolazione(void);
//programma
	numeroSegreto();//ottengo numero segreto e lo immagazzino per poi utilizzare la funzione contaPunti
	while(1){//per motivi di comodità questo ciclo non finirà mai
		contaPunti();//chiamo alternativamente le due funzioni di attacco e difesa (rispondo alla chiamata avversaria)
		triangolazione();//(cerco di effettuare la chiamata vincente)
	}
	return 0;
}

//funzione che scorre un vettore comparando ogni locazione con una determinata lettera; se trova uguaglianze restituisce uno altrimenti zero
int cercaBall(char * const val,const char vet[]){
	int x;
	for(x=0;x<G;x++)//per ogni locazione
		if(*val==vet[x])//se ho due valori uguali
			return 1;//ritorno un valore positivo
	return 0;//se no zero
}

//funzione che conta numero di strike e di ball presenti in una chiamata
void contaPunti(void){
	char m[G+1];
	int strike=0,ball=0,x;
	int cercaBall(char * const val,const char vet[]);
	printf("Scrivi la chiamata avversaria \t\t\t\t\t[Q per terminare]\n\n>");
	scanf("%s",m);//immagazzino la chiamata
	for(x=0;x<G;x++){//per ogni posizione
		if(s[x]==m[x])//se sono uguali le posizioni della chiamata è strike
			strike++;//aggiungo al numero degli strike
		else//se no
			if(cercaBall(&s[x],m))//controllo se quel numero è nel numero
				ball++;//se cè è un ball in piu
	}
	printf("Nella chiamata sono presenti %d Strike e %d Ball\t\t\t",strike,ball);//messaggio di risposta all'interrogazione
	if(strike==4||ball==4)//aggiungo un po di swag
		printf("[%s]",strike==4?"Fatality":"Critical");//swag
	printf("\n\n\n");//spazio tra le interrogazioni
	strike=0;//reinizializzo tutto per il prossimo giro
	ball=0;//reinizializzo tutto per il prossimo giro
}

//funzione base che ottiene la prima volta il numero segreto del giocatore
void numeroSegreto(void){
	int x;
	printf("Scrivi i numeri segreti che hai scelto.\n>");
	scanf("%s",s);//ottengo stringa
	for(x=0;x<100;x++)//stampo per cento volte #
		printf("#\n");//per nascondere l'immissione
}

//funzione che tiene memoria delle chiamate effettuate e in base ai precedenti e incroci di dati arriva a scoprire il numero avversario
void triangolazione(void){
//inizializzo
	static char *callTab[30];//chiamate   (immagazzino fino a trenta chiamate con relative risposte dell'avversario)
	static char *rispTab[30];//risposte alle chiamate
	static short mainTab[10][5]={0}; //numeri x posizioni [booleana](sotto ogni posizione tengo a zero i possibili numeri per quella posizione, porto a uno se ho le prove che un dato numero non può essere in quella posizione)
	char stringa[10];//stringa di appoggio
	int x=0,y;
	for(x=0;x<30;x++)
		callTab[x]="";//inizializzo tutte le prime colonne
//programma
	x=0;
	while(callTab[x]!=""){//fintanto che ho ancora chiamate da analizzare
	//processo chiamata
		puntatore=strchr(rispTab[x],'s');//salvo nel puntatore la locazione della lettera s nella risposta
		if(*puntatore==NULL){//se non è presente la lettera s nella risposta alla chiamata (se non ci sono strike)
			if(strchr(rispTab[x],'b')==NULL){//se non sono presenti nemmeno ball elimino i cinque numeri
				for(y=0;y<5;y++)//per ogni cifra contenuta nel numero rispTab preso in considerazione
					for(z=0;z<5,z++)//elimino tutti le potenziali occorrenze nella mainTab
						mainTab[(int)rispTab[y]][z]=1;//elimino i cinque numeri dalla mainTab in maniera permanente da tutte le posizioni
				printf("zero\n");
			}
			else{//se sono presenti uno o piu ball
				puntatore=strchr(rispTab[x],'b');
				if(*puntatore[1]!=5){//se dopo la b trovata da strchr non cè 5 non posso sfruttare la proprietà e procedo normalmente
					printf("solo ball\n");//se sono presenti
					for(y=0;y<5;y++)//per ogni cifra contenuta nella rispTab
						mainTab[(int)rispTab[y]][y]=1;//elimino i cinque numeri dalla mainTab ma solo dalla loro posizione attuale
				}
				else{//se sono 5 ball ho tutti i numeri e posso eliminare gli altri dalla mainTab
					stringa=callTab[x];//utilizzo la stringa di appoggio
					for(y=0;y<10;y++)//per ogni numero da 0 a 9
						for(z=0;z<5;z++)//per ogni posizione
							if(strchr(stringa,y+48)==NULL)//se il numero non è presente nella chiamata fortunata aggiungo il 48 ad y perchè la funzione strchr richiede una stringa ed un intero che rappresenta un carattere se avessi passato il numero uno non avrei passato il carattere uno che corrisponde a 49 (0=48)
								mainTab[y][z]=1;//elimino dalla tabella
				}
			}
		}
		else{//se ho strike quindi ho una locazione salvata nel puntatore
			switch(*puntatore[1]){//mi muovo di conseguenza rispetto al numero di strike che mi trovo
				case 1://se ho uno strike solo genero 5 tabelle
					genTab(callTab[x],1,5);
					break;
				case 2://se ho due strike genero 20 tabelle ecc...
					break;
				case 3://la formula che prevede le tabelle è:
					break;
				case 4://Dnk=n*(n-1)*(n-2)....(n-k) dove n è il numero di posizioni utilizzabili e k il numero di posizioni occupabili meno gli strike
					break;
			}
		}
		x++;
	}
}

//lo scopo di questa funzione è quello di generare ricorsivamente tutte le possibili combinazioni degli strike
void genTab(const char numero[],const short strike){

	for(x=0;x<strike;x++)
}
