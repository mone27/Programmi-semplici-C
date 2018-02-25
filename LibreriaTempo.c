//Thanks to:
//https://www.geeksforgeeks.org/how-to-measure-time-taken-by-a-program-in-c/
/* Program to demonstrate time taken by function fun() */

#include <stdio.h>
#include <time.h>
 
// A function that terminates when enter key is pressed
void fun(){
  void carica();
  printf("fun() starts \n");
  printf("Press enter to stop fun \n");
  while(1){
      carica();
      if (getchar())
	break;
    }
  printf("\nfun() ends \n");
}

// The main program calls fun() and measures time taken by fun()
int main(){
  // Calculate the time taken by fun()
  clock_t t;
  t = clock();
  fun();
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  
  printf("fun() took %f seconds to execute \n", time_taken);
  return 0;
}

void carica(){
  static int a=-1;
  static clock_t b;
  char vet[]={'|','/','-','\\'};
  
  //inizializzo la prima volta
  if(-1==a){
    b=clock();
    printf("Elaboro ");
  }
  
  //se passa il tempo specificato
  if(((double)(clock()-b))/CLOCKS_PER_SEC>2.0){
    //stampa cambiamento
    printf("%c\b",vet[a]);
    //incrementa senza sforare
    a++;
    if(4==a)
      a=0;
    //evito che succeda di nuovo prima del tempo
    b=clock();
  }
}


