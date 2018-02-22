/*
//vettore di vettori di stringhe (abbandonato per scomodita di inizializzazione)
//Programma di prova della struttura dati
#include <stdio.h>

char *TreLettere[]={"GNU","TUX","LUG","MIT","GCC","GPG","APT","NSA","GIT","FSF","EFF","USB"};
char *QuattroLettere[]={"ARCH","RUST","JAVA","HTML","SUDO","ROOT","SNAP","KALI","WINE"};
char *CinqueLettere[]={"LINUS","LINUX","UNIX","PRISM","APPLE"};
char *SeiLettere[]={"DISTRO","FEDORA","DEBIAN","KERNEL","PACMAN","GITHUB","OLIMEX","GENTOO","JULIAN","EDWARD","UBUNTU"};
char *SetteLettere[]={"RICHARD","MRROBOT","ASSANGE","WINDOWS","SNOWDEN","TEMPORA","PRIVACY","KUBUNTU","XUBUNTU"};
char *OttoLettere[]={"TORVALDS","STALLMAN","GUARDIAN"};
char *NoveLettere[]={"RASPBERRY","WIKILEAKS","CANONICAL"};
  
int main() {
  char **dizionario[7];
  dizionario[0]=TreLettere;
  dizionario[1]=QuattroLettere;
  dizionario[2]=CinqueLettere;
  dizionario[3]=SeiLettere;
  dizionario[4]=SetteLettere;
  dizionario[5]=OttoLettere;
  dizionario[6]=NoveLettere;
  
  puts(*(dizionario[1]+2));
  puts(dizionario[3][3]);
  
  return 0;
}

*/

//===============================================================================================
//Questo dizionario comprende parole riguardanti l'informatica, la privacy e il sistema GNU/Linux
//===============================================================================================


//matrice di stringhe, meno personalizzabile di un vettore di vettori di stringhe ma molto piu' comoda da dichiarare
//per far riferimento a PRIVACY occorre chiamare dizionario[4][6] senza alcun operatore di risoluzione.
#ifdef LINUX
 
  #define NPAROLE 15  //Numero di parole per ogni lunghezza
  #define LPAROLE 7   //Nuero di lunghezze di parole

  char *dizionario[LPAROLE][NPAROLE]={
  {"GNU","TUX","LUG","MIT","GCC","GPG","APT","NSA","GIT","FSF","EFF","USB"},
  {"ARCH","RUST","JAVA","HTML","SUDO","ROOT","SNAP","KALI","WINE"},
  {"LINUS","LINUX","UNIX","PRISM","APPLE"},
  {"DISTRO","FEDORA","DEBIAN","KERNEL","PACMAN","GITHUB","OLIMEX","GENTOO","JULIAN","EDWARD","UBUNTU"},
  {"RICHARD","MRROBOT","ASSANGE","WINDOWS","SNOWDEN","TEMPORA","PRIVACY","KUBUNTU","XUBUNTU"},
  {"TORVALDS","STALLMAN","GUARDIAN"},
  {"RASPBERRY","WIKILEAKS","CANONICAL"}
  };
#endif 
