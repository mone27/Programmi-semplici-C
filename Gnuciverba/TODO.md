# Obbiettivi progetto
Lo scopo del programma GeneratoreDiCruciverba.c e' quello di creare un cruciverba di dimensioni
variabili utilizzando un dizionario. Il dizionario e' una collezione di vettori di stringhe che
contengono parole della stessa lunghezza. L'algoritmo da implementare per il momento potrebbe
essere espresso cosi' sotto forma di *pseudocodice*:
1  Data una matrice char n+1 x m+1
2  inizializzata a spazio e con caratteri di terminazione lungo la riga n e colonna m
3  fintanto che non sono arrivato alla riga con tutti caratteri di terminazione
4    fintanto che non ho scritto tutte le caselle fino a fine riga
5      sorteggio una parola dal dizionario di una lunghezza che entra nello spazio disponibile
6      se in verticale ho possibilita' di creare una parola di quattro lettere o piu (nel dizionario)
7        scrivo la parola sorteggiata nella matrice con tutto il carattere di terminazione
8        rimuovo dal dizionario la parola sorteggiata (pongo un flag in caso di backtrack) 
9      altrimenti
10       sorteggio un altra parola
11   vado a capo e inizio a scrivere una nuova riga
  
## Possibili problemi:
Durante l'istruzione della riga 6 potrebbe andarsi a creare un ciclo infinito a causa di una
combinazione di lettere che non puo' portare a nessuna parola presente nel dizionario, sara' percio'
necessario utilizzare un algoritmo backtrack per tornare indietro sulle scelte fatte e riprovare con
una nuova combinazione.
Invece di utilizzare il backtrack potrebbe invece rivelarsi utile utilizzare come espediente quello
di porre una parola piu' breve per far si che non capitino combinazioni fuori dizionario.

  
  
  
  
    	    
