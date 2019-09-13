#include <stdio.h>
#include <stdlib.h>
#include "randomi.h"
#include "libgame.h"
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    int opt;
    int mode = 0;
    int needs = 0;
    
    int gridSize = 2;
    int zeroPos[2];
   
    int cont = 1;
    int moves = 0;
    char input;
    

    while((opt = getopt(argc, argv, "MARS:")) != -1)
        switch(opt){
            case 'M':
                mode = 1;
                break;
            case 'A':
                mode = 2;
                break;
            case 'R':
                mode = 3;
                needs = 1;
                break;
            case 'S' :
                gridSize = atoi(optarg);
                break;
        }
        
    if(mode == 0){
        printf("\nusage: puzzle -Option\n\n-M Manual solve\n-A use random solve\n-R use random solve 2\n-S size");
        exit(13);
    }

    int pGrid[gridSize][gridSize];
    
    //init puzzle
    fillPuzzle(gridSize, pGrid, zeroPos);
    
    printf("\nPuzzle is Ready\n\n");
    
    while(cont) {
        
        printPuzzle(gridSize, pGrid);
        
        if(!testIfsolved(gridSize, pGrid))
            break;
        
        if(!needs)
            input = readInput(mode); 
        else
            input = readInput2(mode, gridSize, pGrid);
        
        if(makeAmove(input, zeroPos, gridSize, pGrid))
            moves++;
        else
            printf("Illegal move\n");
     //   printf("%d - %d\n",zeroPos[0],zeroPos[1]);
      
    }
    printf("You won!\nYou used %d moves\n",moves);
}
