#include <stdio.h>

void stampaTab(int tab [3][3]);
int controllaVincitore(int tab[3][3]);

int main() 
{
    char giocatore[2]= {'X', 'O'};
    int tab [3][3];
    int x,y;
    int fine=0;
	int giocatoreAttivo=0;
	int cox;
	int coy;
	int c=0;
	
// creo spazi vuoti

	for(x=0; x<3; x++) 
		{
		   for(y=0; y<3; y++)
		   tab[x][y]= ' ';
        }
		
//stampaTab(tab);//debug

	while(controllaVincitore(tab)==2 && c<9) 
	  {
          stampaTab(tab);
		   printf("Giocatore %c: immetti coordinate del punto che vuoi marcare \n [Immetti numero di riga e numero di colonna compresa tra 0 e 2] \n", giocatoreAttivo?'O':'X');
	      scanf("%d%d", &cox, &coy);
	      if(tab[cox][coy]!=' ')
			   printf("la casella e\' gia\' marcata, bufu \n");
	      else 
		     {
				tab[cox][coy]= giocatore[giocatoreAttivo];
			    giocatoreAttivo=!giocatoreAttivo;
			    c++;
		     }
      }
  
	fine=controllaVincitore(tab);
	switch(fine) 
	   {
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
	   
	//system("PAUSE");
}


void stampaTab(int tab [3][3]) 
{
	int x,y;
	for(x=0; x<3; x++) 
		{
		   for(y=0; y<3; y++)
		   printf(" %c %c", tab [x][y], y!=2 ? '|' : ' ');
		   printf("%s", x!=2 ? "\n------------\n" : "\n");
        }

}

int controllaVincitore(int tab[3][3]) 
{
	int x,y;
	int vincitore=2;
	for(x=0; x<3; x++)       // controllo ogni colonna
		{ 
			if(tab[x][0]!=' ' && tab[x][0]==tab[x][1] && tab[x][1]==tab[x][2])
				vincitore=tab[x][0];
	    }   
	for(y=0; y<3; y++)       // controllo ogni riga
		{ 
			if (tab[0][y]!=' ' && tab[0][y]==tab[1][y] && tab[1][y]==tab[2][y])
			vincitore=tab[0][y];
        } 
	//controllo diagonali (non è presente
	if(tab[0][0]!=' ' && tab[0][0]==tab[1][1] && tab[1][1]==tab[2][2])
		vincitore=tab[0][0];
	else if (tab[0][2]!=' ' && tab[0][2]==tab[1][1] && tab[1][1]==tab[2][0])
		vincitore=tab[0][2];

	if (vincitore=='X' || vincitore=='O') 
		{
			if (vincitore=='X')
				vincitore=0;
			else
				vincitore=1;
		}
	return vincitore;
}
