//==============
//Configurazioni
//==============
#define GENERICO 1 //attiva dizionario LINUX
#define COLONNE 2  //scegli numero di caselle di lunghezza del cruciverba7
#define RIGHE 2 //scegli numero di caselle di altezza del cruciverb*/a 5

////--------------------------------------------------------------------

#include "Libreria.c" //include: stdio.h, string.h, ctype.h, time.h, stdlib.h


int main(){
    //  time_t inizio;
    //  double secondi;
    //  int ore,minuti;

    //  //prendo il tempo ad inizio esecuzione
    //  inizio= clock();

    //  //stampo ora di inizio esecuzione
    printf("Esecuzione lanciata\n");
    //Inizio generazione--------------------------------------------------------


    //  tabInit();
    cruciInit();

    while(!allZ('\0')){
        cruciPlusPlus(1,1);
        if(cruciCheck())
            cruciPrint();
    }

    ////Fine generazione----------------------------------------------------------

    //  //ricavo e raffino tempo di esecuzione del programma
    //  secondi=(double)(clock()-inizio)/CLOCKS_PER_SEC;
    //  minuti=secondi/60;
    //  secondi-=(double)minuti*60;
    //  ore=minuti/60;
    //  minuti-=ore*60;
    //  printf("\nProgramma terminato con successo\nTempo di esecuzione: %d Ore %d Minuti %.3f Secondi\n\a",ore,minuti,secondi);
    return 0;
}
