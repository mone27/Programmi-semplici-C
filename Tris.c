#include <stdio.h>

void stampaTab(int tab [3][3]);
int controllaVincitore(int tab[3][3]);

int main() {
  char giocatore[2]= {'X', 'O'}; //segnalino da commutare durante la partita
  int tab [3][3];
  int x,y,cox,coy;
  int c=0;
  int fine=0;
  int giocatoreAttivo=0;//indice segnalino giocatore (questo verra' commutato durante la partita)
	
// inizializzo campo del tris a soli spazi bianchi
  for(x=0; x<3; x++) {
    for(y=0; y<3; y++)
      tab[x][y]= ' ';
  }

// Fintanto che non vince nessuno e che ci sono ancora spazi vuoti
  while(controllaVincitore(tab)==2 && c<9) {

    //metto nella condizione il giocatore di poter giocare stampando la situazione attuale e un prompt
    stampaTab(tab);
    printf("Giocatore %c: immetti coordinate del punto che vuoi marcare \n[Immetti numero di riga e numero di colonna compresa tra 0 e 2] \n", giocatoreAttivo?'O':'X');
    scanf("%d%d", &cox, &coy);

    //controllo che sia possibile effettuare la mossa immessa dal giocatore
    if(tab[cox][coy]!=' ')
      printf("la casella e\' gia\' marcata, bufu \n");
    else {
      tab[cox][coy]= giocatore[giocatoreAttivo];//marco casella con segnalino giocatore attivo
      giocatoreAttivo=!giocatoreAttivo;//ora tocca all'altro
      c++;//ho fatto un altra mossa (devo arrivare a nove per finire il campo)
    }
  }//fine while

//come e' finita?
  fine=controllaVincitore(tab);
  switch(fine) {
  case 0:
    printf("Ha vinto il giocatore X \n");
    break;
  case 1:
    printf("Ha vinto il giocatore O \n");
    break;
  case 2:
    printf("Non ha vinto nessuno \n");
    break;
  }
  stampaTab(tab);
  
  return 0;// programma terminato
}

//funzione che stampa il campo del tris formattato carino
void stampaTab(int tab [3][3]) {
  int x,y;
  printf(" 0   1   2\n");
  for(x=0; x<3; x++) {
    for(y=0; y<3; y++)
      printf(" %c %c", tab [x][y], y!=2 ? '|' : ' ');
    printf(" %d%s", x,x!=2 ? "\n-----------\n" : "\n");
  }
  return; 
}

int controllaVincitore(int tab[3][3]) {
  int x,y;
  int vincitore=2;
  
//controllo se ci sono tris nelle colonne
  for(x=0; x<3; x++) { 
    if(tab[x][0]!=' ' && tab[x][0]==tab[x][1] && tab[x][1]==tab[x][2])
      vincitore=tab[x][0];
  }
  
//controllo se ci sono tris nelle righe
  for(y=0; y<3; y++) { 
    if (tab[0][y]!=' ' && tab[0][y]==tab[1][y] && tab[1][y]==tab[2][y])
      vincitore=tab[0][y];
  }
  
//controllo se ci sono tris nelle diagonali
  if(tab[0][0]!=' ' && tab[0][0]==tab[1][1] && tab[1][1]==tab[2][2])
    vincitore=tab[0][0];
  else if (tab[0][2]!=' ' && tab[0][2]==tab[1][1] && tab[1][1]==tab[2][0])
    vincitore=tab[0][2];

//assegno 0 se ha vinto il giocatore X, 1 se ha vinto il giocatore O, 2 se non ha vinto nessuno
  if (vincitore=='X' || vincitore=='O') {
    if (vincitore=='X')
      vincitore=0;
    else
      vincitore=1;
  }
  return vincitore;
}//fine controllaVincitore
