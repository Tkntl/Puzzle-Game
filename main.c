#include <stdio.h>
#include <stdlib.h>
#include "randomi.h"
#include "libgame.h"
#include <unistd.h>
#include <time.h>

#define CLOCK_TYPE CLOCK_MONOTONIC_RAW

int main(int argc, char *argv[]) {
    
    int opt;
    int mode = 0;
    int needs = 0;
    
    int gridSize = 2;
    int zeroPos[2];
   
    int cont = 1;
    int moves = 0;
    char input;
    struct timespec startTime_val, stopTime_val, startTime_res;
    

    while((opt = getopt(argc, argv, "MARBS:")) != -1)
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
             case 'B':
                mode = 4;
                needs = 1;
                break;
            case 'S' :
                gridSize = atoi(optarg);
                break;
        }
        
    if(mode == 0){
        printf("\nusage: puzzle -Option\n\n");
        printf("-M Manual solve\n-A use random solve\n-R use random solve with neighbour check\n-B best-first search\n-S size");
        exit(13);
    }

    int pGrid[gridSize][gridSize];
    
    //init puzzle
    int solvablePuzzle = 0;
    while(solvablePuzzle == 0) {
        fillPuzzle(gridSize, pGrid, zeroPos);
        solvablePuzzle = isPuzzleSolvable(gridSize,pGrid,zeroPos[0]);
    }
    
    printf("\nPuzzle is Ready\n\n");
    
    clock_gettime(CLOCK_TYPE, &startTime_val);
    clock_getres(CLOCK_TYPE, &startTime_res);
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
      
    }
    clock_gettime(CLOCK_TYPE, &stopTime_val);
    printf("You won!\nYou used %d moves\n",moves);
    
    printf("in %ld uS\n", (stopTime_val.tv_sec*1000000 + stopTime_val.tv_nsec/1000)-(startTime_val.tv_sec*1000000 + startTime_val.tv_nsec/1000));
}
