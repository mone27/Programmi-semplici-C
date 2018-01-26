//Funzionante: conta i punti, controlla doppie cifre Alessio

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CIFRE 4 //numero di cifre con cui si gioca

void getNumber(int numero[]);
void ritornaVettorePunti(const int segreto[CIFRE],const int chiamata[CIFRE], int sb[2]);
bool checkUguali(const int numero[]);

int main() {
  int num_segreto[CIFRE];
  int num_chiamata[CIFRE];
  int vettorePunti[2];

  //ottengo numero segreto
  printf("Immetti il numero SEGRETO\n");
  do{//controllo che si immetta un numero senza cifre ripetute
    getNumber(num_segreto);
  }while(checkUguali(num_segreto));
  
  system("clear");//nascondo il numero SEGRETO con un comando standard per sistemi compatibili a GNU/Linux

  while(1){//per il momento per sempre
    
    //ottengo prossima chiamata avversaria
    do{
      getNumber(num_chiamata);
    }while(checkUguali(num_chiamata));
    
    //calcolo punti e stampo
    ritornaVettorePunti(num_segreto,num_chiamata,vettorePunti);
    printf("%ds%db\n",vettorePunti[0],vettorePunti[1]);
  }
  return 0;
}


//Funzione che prende in input il vettore del numero segreto quello della chiamata avversaria e uno vuoto da riempire
//Restituisce un vettore di due locazioni con il numero di strike in 0 e il numero di ball in 1
void ritornaVettorePunti(const int segreto[CIFRE],const int chiamata[CIFRE], int sb[2]){
  int i,j;
  sb[0]=0;
  sb[1]=0;
  
  //per ogni posto della chiamata compara con tutte le altre del numero segreto
  for(i=0; i<CIFRE; i++){
    for(j=0; j<CIFRE; j++){
      if( chiamata[i] == segreto[j] ){//se un numero e' stato azzeccato
	if( i==j )//se il numero di posizione e' uguale
	  sb[0]++;//incremento numero di strike
	else
	  sb[1]++;//incremento numero di ball
      }
    }
  }
  return;
}

//Funzione che restituisce il numero preso in input dall'utente
void getNumber(int numero[]){
  int i;
  printf("Immetti le cifre del numero separate da spazio\n--> ");
  for(i=0;i<CIFRE;i++)//immagazzino cifre nelle varie locazioni  
    scanf("%d",&numero[i]);
    while(numero[i] >= 0 && numero[i] <= 9){
      puts("Solo numeri compresi tra 0 e 9");
      scanf("%d",&numero[i]);
    }
  return;
}

//Funzione che controlla che non ci siano due cifre uguali all'interno di uno stesso numero
//restituisce 1 se trova cifre uguali
bool checkUguali(const int numero[]){
  int a,j;
  bool uguali = false; 
  uguali = 0;// se trovo due cifre uguali diventa vero e mi inculo l'utente
  for (a = 0; a < CIFRE && !uguali ; a++){ 
    for (j = 0; j < CIFRE && !uguali ; j++)
      if ((numero[a] == numero[j]) && (a != j)){
	uguali = true;
	printf("ERRORE: Sono state immesse almeno due cifre uguali, ricontrollare istanza\n");
      }
  }
  return uguali;
}
