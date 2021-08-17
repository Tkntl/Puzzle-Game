#include <stdio.h>
#include "randomi.h"
#include "searchAgent.h"

int fillPuzzle(int gridSize, int (*pGrid)[gridSize], int *zeroPos) {
      
    int nOe = gridSize*gridSize;
    int tmp[nOe];
    
    for(int i = 0;i < nOe;i++){
        tmp[i] = getRandNum(nOe);
        for(int ii = 0;ii < i;ii++){
             if(tmp[i]==tmp[ii])
                 i--;
        }
    }
    for(int y = 0,index = 0;y < gridSize;y++) {
        for(int x = 0; x < gridSize;x++) {
            *(*(pGrid + y) + x) = tmp[index];
            if(tmp[index] == 0){
                *(zeroPos + 0) = y;
                *(zeroPos + 1) = x;
            }
            index++;
        }
    }
    
    return 0;
}

int isPuzzleSolvable(int gridSize, int (*pGrid)[gridSize], int zeroLine) {
    
    int number;
    int isSmaller = 0;
    int inversions = 0;
    int num[gridSize*gridSize-1];
    int index = 0;
    int isZeroLineOdd;
    
    for(int y = 0;y < gridSize;y++){
        for(int x = 0;x < gridSize; x++) {
            if( *(*(pGrid + y) + x) != 0) {
                number =  *(*(pGrid + y) + x);
                num[index] =  *(*(pGrid + y) + x);
                    for(int i = 0;i <= index; i++){
                        if(num[i] < number){
                            isSmaller++;
                        }
                    }
                inversions += number - isSmaller -1;
                isSmaller = 0;
                index++;
            }
        }
    }
    if((gridSize % 2 == 1) && (inversions % 2 == 0))
        return 1;
    else if(gridSize % 2 == 0 && inversions != 0) {
        isZeroLineOdd = (gridSize-zeroLine) % 2;
        
        if((inversions % 2 == 0 && isZeroLineOdd == 0) || (inversions % 2 == 1 && isZeroLineOdd == 1))
            return 1;
    }
    
    return 0;
}

void printPuzzle(int gridSize, int (*pGrid)[gridSize]) {
    
    for(int y = 0;y < gridSize;y++) {
        for(int x = 0; x < gridSize;x++) {
            if(*(*(pGrid +y) + x) == 0)
                printf("   ");
            else {
                if(*(*(pGrid +y) + x) < 10)
                    printf("%d  ",*(*(pGrid +y) + x));
                else
                    printf("%d ",*(*(pGrid +y) + x));
                }
        }
            printf("\n\n");
    }
    printf("\n");
}

int testIfsolved(int gridSize, int (*pGrid)[gridSize]) {

    int solved = 0;
    int test = 0;
    
    for(int y = 0;y < gridSize;y++) {
        for(int x = 0; x < gridSize;x++) {
            if(*(*(pGrid +y) + x) != test)
                solved = 1;
            test++;
        }
    }
    if(solved)
        return 1;
    else
        return 0;
}

char readInput(int mode) {

    char input;
    
    if(mode == 1) {
        printf("Your Move:\n");        
            
        input = getchar();
        if(input == '\n')
            input = getchar();
    }
    else if(mode == 2)
        input = randSolve();
    
    return input;
}

char readInput2(int mode, int gridSize, int pGrid[][gridSize]) {

    char input;
    
    
    if(mode == 3)
        input = randSolve2(gridSize, pGrid);
    else if (mode == 4)
        input = searchAgent(gridSize,pGrid);
    return input;
}


int makeAmove(char in, int *zeroPos, int gridSize, int (*pGrid)[gridSize]) {

    int newZeroPos[2];
    newZeroPos[0] = zeroPos[0];
    newZeroPos[1] = zeroPos[1];
    
    switch(in){
            case 'w' :
                newZeroPos[0]--;
                break;
            case 's' :
                newZeroPos[0]++;
                break;
            case 'a' :
                newZeroPos[1]--;
                break;
            case 'd' :
                newZeroPos[1]++;
                break;
            default :
                printf("use wasd to move\n");
        }
        
        if((newZeroPos[0] >= 0 && newZeroPos[0] < gridSize) && (newZeroPos[1] >= 0 && newZeroPos[1] < gridSize)){
                        
            *(*(pGrid + zeroPos[0]) + zeroPos[1]) = *(*(pGrid + newZeroPos[0]) + newZeroPos[1]);
            *(*(pGrid + newZeroPos[0]) + newZeroPos[1]) = 0;
            
            *(zeroPos + 0) = newZeroPos[0];
            *(zeroPos + 1) = newZeroPos[1];
            return 1;
        }
        else
            return 0;
}
