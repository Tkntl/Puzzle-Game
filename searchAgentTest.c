#include <stdio.h>
#include "searchAgent.h"

int main()
{
    int grid[3][3]={{3,1,2},{4,7,5},{6,8,0}};
    //int grid[4][4]={{4,1,2,3},{8,5,6,7},{9,13,10,11},{12,0,14,15}};
    int gridSize = 3;
    char move = 'o';
    
    while(move != '\0'){
        move = searchAgent(gridSize, grid);
        printf("%c,", move);
    }
    printf("\n");
}
