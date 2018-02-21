//Includo dipendenze
#include <stdio.h>
#include <string.h>
#include <ctype.h>


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
