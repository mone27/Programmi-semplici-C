#include "Libreria.h"

int main() {
  int num_segreto[CIFRE];
  int num_chiamata[CIFRE];
  int vettorePunti[2];

  //ottengo numero segreto
  printf("Immetti il numero SEGRETO\n");
  do{//controllo che si immetta un numero senza cifre ripetute
    getNumber(num_segreto);
  }while(checkUguali(num_segreto));
  
  system("clear");//nascondo il numero SEGRETO con un comando per sistemi compatibili a GNU/Linux

  puts("Ora puoi immettere le chiamate avversarie:");
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
