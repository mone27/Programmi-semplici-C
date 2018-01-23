#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define G 4
#define FUN 2

int main(){
	void contaPunti(void);
	void Genera(void);
	void (*menu[FUN])(void)={Genera,contaPunti};
	int x;
	do{
		printf("Come posso esserti di aiuto?\t\t\t\t\t[EOF per terminare]\n[O] Implmenetato [X] Non implementato\n\n1) Genera numero [X]\n2) Strike and Ball Helper [O]\n\n>");//prompt
		scanf("%d",&x);//ricevo comando
		if(x>0&&x<=FUN)//evito errori a tempo di esecuzione
			(*menu[x-1])();//chiamo funzione desiderata
	}while(x!=EOF);//fintanto che voglio fare qualcosa
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
	char s[G],m[G];
	int strike=0,ball=0,x,uguali;
	int cercaBall(char * const val,const char vet[]);
	printf("Scrivi i numeri segreti che hai scelto.\n>");
	scanf("%s",s);//ottengo stringa
    uguali = 0;
    for (int ai = 0; ai < 4 ; ai++) //ciclo controllo del numero segreto. uguali
        {
            for (int j = 0; j < 4; j++)
                if ((s[ai] == s[j]) && (ai != j))
                    uguali = 1;
            if (!uguali)
                uguali=0;
        }
        if(uguali==1){ //se non sono uguali esci
            printf("Hai almeno una coppia uguale\n ");
            exit(1);
            }
	for(x=0;x<100;x++)
		printf("#\n");//nascondo l'immissione
	while(1){//fintanto che m non è una stringa composta anche da lettere
		printf("Scrivi la chiamata avversaria \t\t\t\t\t[Q per terminare]\n\n>");
		scanf("%s",m);//immagazzino la chiamata
		if(!isalpha(m[0])){//se non è una lettera eseguo il compito
			for(x=0;x<G;x++){//per ogni posizione
				if(s[x]==m[x])
					strike++;
				else
					if(cercaBall(&s[x],m))
						ball++;
			}
			printf("Nella chiamata sono presenti %d Strike e %d Ball\t\t\t",strike,ball);//messaggio di risposta all'interrogazione
			if(strike==G||ball==G)//aggiungo un po di swag
				printf("[%s]",strike==G
				?"Fatality":"Critical");//swag
			printf("\n\n\n");//spazio tra le interrogazioni
			strike=0;//reinizializzo tutto per il prossimo giro
			ball=0;//reinizializzo tutto per il prossimo giro
		}
		else//se no
			break;//se è una lettera esco
	}
	printf("\nProgramma Helper Terminato\n\n\n");
}
void Genera(void){
    exit(1);
}
