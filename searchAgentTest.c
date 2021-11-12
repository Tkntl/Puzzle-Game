#include <stdio.h>
#include "searchAgent.h"

int main()
{
    int grid[3][3]={{8,5,0},{3,6,7},{2,1,4}};
    //int grid[4][4]={{4,1,2,3},{8,5,6,7},{9,13,10,11},{12,0,14,15}};
    int gridSize = 3;
    char move = 'o';
        printf("start\n");
        while(move != '\0'){
        
            move = searchAgent(gridSize, grid);
            printf("%c,", move);
        }
    printf("\n");
}
