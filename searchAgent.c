#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLimit(int size)
{
    float limit;
    float A = 1.5434;
    float exp = 2.71828;
    
    limit = exp;
    for(int i = 0; i < (size - 1);i++)
        limit *= exp;
    
    limit = limit*A; 
    return limit + 1;
}

char * availableMoves(int *zero, int gridSize)
{
    char * moves;
    
    if(zero[0] == 0 && zero[1] == 0)
        moves = "sd";
    else if(zero[0] == 0 && zero[1] == (gridSize -1))
        moves = "as";
    else if(zero[0] == (gridSize - 1) && zero[1] == (gridSize -1))
        moves = "aw";
    else if(zero[0] == (gridSize - 1) && zero[1] == 0)
        moves = "wd";
    else if(zero[0] == 0)
        moves = "asd";
    else if(zero[0] == gridSize - 1)
        moves = "awd";
    else if(zero[1] == 0)
        moves = "wsd";
    else if(zero[1] == gridSize - 1)
        moves = "was";
    else
        moves = "wasd";
    
    return moves;
}

int testState(int gridSize, int *arrs)
{
    int test = 0;
    
    int fail_yx[2];
    int val_yx[2];
    int digits = 0;
    int dada = 0;
    int low, high;
    int n=1;
    int yAxel[gridSize];
    int yRow;
    int xRow;
    int found;

    for(int y = 0; y < gridSize; y++){
        for(int x = 0;x < gridSize; x++){
            if(*(arrs + y * gridSize + x) != test && *(arrs + y * gridSize + x) != 0){
                fail_yx[0] = *(arrs + y * gridSize + x) / gridSize;
                fail_yx[1] = *(arrs + y * gridSize + x) % gridSize;
                val_yx[0] = y - fail_yx[0];
                val_yx[1] = x - fail_yx[1];
                if (val_yx[0] < 0)
                    val_yx[0] *= -1;
                if(val_yx[1] < 0)
                    val_yx[1] *= -1;
                
                digits += val_yx[0] + val_yx[1];
                
                xRow = 0;
                yRow = 0;
                if(x > 0){
                    if(y == 0 && *(arrs + y * gridSize + x) < gridSize){
                        low = 0;
                        high = gridSize - 1;
                        xRow = 1;
                    }
                    else if((*(arrs + y * gridSize + x) > y * gridSize) && (*(arrs + y * gridSize + x) < (y * gridSize + gridSize- 1))){
                        low = y * gridSize;
                        high = y * gridSize + gridSize-1;
                        xRow = 1;
                    }
                }
                else if (y > 0){
                    for(int yy = 0; yy < gridSize; yy++){
                        yAxel[yy]= yy * gridSize + x;
                        if(*(arrs + y * gridSize + x) == yAxel[yy]){
                            yRow = 1;
                            
                        }
                    }
                    if(yRow != 0)
                        for(int yyy = yRow; yyy < gridSize; yyy++)
                            if(*(arrs + (y - n) * gridSize + x) == yAxel[yyy]){
                                if(*(arrs + y * gridSize + x) < *(arrs + (y - n) * gridSize + x))
                                    dada++;
                            }
                }
               if(xRow){
                    if((*(arrs + y * gridSize + x) < *(arrs + y * gridSize + x - n)) && ((*(arrs + y * gridSize + x - n) < high) && (*(arrs + y * gridSize + x - n) > low)))
                        dada++;
                    
               }
               digits += 2*dada;
            }
            test++;
        }
    }
    return digits;
}

int dropMove(char move, char oldMove, int digits, int depthCntr, int dropLimit)
{
    int block = 0;
    if((move == 'w' && oldMove == 's') || (move == 'a' && oldMove == 'd') || (move == 's' && oldMove == 'w') || (move == 'd' && oldMove == 'a'))
        block = 1;
    if ((digits > (dropLimit - depthCntr)) || block == 1 )
        return 1;
    else
        return 0;
}

int hashFunction(int size, int *data)
{   
    int tmp;
    int hash = 0;
    int hash2 = 0;

        for(int x = 0; x < (size * size); x++){
            hash = hash * 10;
            if(*(data + x)>=10)
                hash = hash * 10;
            hash += *(data + x);
        }
  
    return hash;
}

int *createTable(int columns) {
    int *tablePtr = malloc(columns * sizeof(int));

    return tablePtr;
}

int *addColumns(int columns,int *Addr) {
    Addr = realloc(Addr, columns * sizeof(int));
    
    return Addr;
}

int * createHashCntr(int rows, int value) {
    int *cntrs = malloc(rows * sizeof(int));
    
    for(int i = 0; i < rows; i++)
        *(cntrs + i) = value;
    return cntrs;
}

char * agentFlow(int gridSize, int grid[][gridSize])
{
    int zero[2];
    
    int Rcntr = 0;
    int cntr = 0;
    
    char moves[5] = "wasd";
    
    int nOfmoves = 0;
    
    int NumOfNodes = 1;
    int NumOfNodesNext = 0;
    int depthCntr = 0;
    int nodeCntr = 0;
    
    int dropLimit;
    
    int tRows = gridSize * gridSize;
    int arraySize = tRows * sizeof(int);
    int nodeArraySize;
    
    struct node {
        int data[tRows];
        int visited;
        int digits;
        int depthCntr;
        char *moves;
    };
    struct closest {
        int addr;
        int min;
    };
        
    struct node *nodes;
    struct closest smallestVal;
    
    dropLimit = getLimit(gridSize);
    nOfmoves = strlen(moves);
    
    nodes = malloc((1 + nOfmoves) * sizeof(*nodes));
    nodeArraySize = 1+ nOfmoves;
    (nodes)->moves = malloc((depthCntr + 1) * sizeof(char));
    
    for(int y = 0; y < gridSize; y++)
                for(int x = 0;x < gridSize; x++)
                        (nodes + Rcntr)->data[y * gridSize + x] = grid[y][x];
    (nodes + Rcntr)->digits = testState(gridSize, (nodes + Rcntr)->data);
    cntr++;
    
    while(1) {
        
        for(int y = 0; y < gridSize; y++)
            for(int x = 0; x < gridSize; x++)
                if((nodes + Rcntr)->data[y * gridSize + x] == 0) {
                    zero[0] = y;
                    zero[1] = x;
                    goto ZeroDone;
                }
        ZeroDone:
        strcpy(moves,availableMoves(zero, gridSize));
        
        nOfmoves = strlen(moves);

        for(int i = 0, mCntr = 0; i < nOfmoves; mCntr++) {
            memcpy((nodes + cntr + i)->data,(nodes + Rcntr)->data,arraySize);
                               
            if (moves[mCntr] == 'w'){
                
                (nodes + cntr + i)->data[zero[0] * gridSize + zero[1]] = (nodes + cntr + i)->data[(zero[0] - 1) * gridSize + zero[1]];
                (nodes + cntr + i)->data[(zero[0] - 1) * gridSize + zero[1]] = 0;
                
            }
            else if (moves[mCntr] == 'a'){
                
                (nodes + cntr + i)->data[zero[0] * gridSize + zero[1]] = (nodes + cntr + i)->data[zero[0] * gridSize + (zero[1] - 1)];
                
                (nodes + cntr + i)->data[zero[0] * gridSize + (zero[1] - 1)] = 0;
                
            }
            else if (moves[mCntr] == 's'){
                (nodes + cntr + i)->data[zero[0] * gridSize + zero[1]] = (nodes + cntr + i)->data[(zero[0] + 1) * gridSize + zero[1]];
                (nodes + cntr + i)->data[(zero[0] + 1) * gridSize + zero[1]] = 0;
            }
            else if (moves[mCntr] == 'd'){
                (nodes + cntr + i)->data[zero[0] * gridSize + zero[1]] = (nodes + cntr + i)->data[zero[0] * gridSize + (zero[1] + 1)];
                (nodes + cntr + i)->data[zero[0] * gridSize + (zero[1] + 1)] = 0;
            }
            (nodes + cntr + i)->moves = malloc(((nodes + Rcntr)->depthCntr + 2) * sizeof(char));
            
            strcpy((nodes + cntr + i)->moves, (nodes + Rcntr)->moves);
            
            (nodes + cntr + i)->moves[(nodes + Rcntr)->depthCntr] = moves[mCntr];

            (nodes + cntr + i)->moves[(nodes + Rcntr)->depthCntr + 1] = '\0';
            
            (nodes + cntr + i)->digits = testState(gridSize, (nodes + cntr + i)->data);          
            if((nodes + cntr + i)->digits == 0){
                char *retVal = malloc(sizeof((nodes + cntr + i)->moves) + 1 * sizeof(char));
                strcpy(retVal, (nodes + cntr + i)->moves);
                return retVal;
            } 
            
            if(dropMove(moves[mCntr], (nodes + cntr + i)->moves[depthCntr - 1], (nodes + cntr + i)->digits, depthCntr, dropLimit))
                nOfmoves--;
            
            else{
                int notInTheList = 1;
                for(int Dcntr = cntr + i - 1; Dcntr >= 0; Dcntr--)
                    if((nodes + cntr + i)->digits == (nodes + Dcntr)->digits)
                    if(memcmp((nodes + cntr + i)->data,(nodes + Dcntr)->data,arraySize) == 0){
                        nOfmoves--;
                        notInTheList = 0;
                        break;
                    }
                
                if(notInTheList){
                    
                    (nodes + cntr + i)->depthCntr = (nodes +Rcntr)->depthCntr + 1;
                    
                    i++;
                }
            }
        }
        
        (nodes + Rcntr)->visited = 1;
         
        cntr += nOfmoves;
    
        if((nodeArraySize - 4 < cntr)){
            nodes = realloc(nodes,(2 * nodeArraySize) * sizeof(*nodes));
            nodeArraySize = nodeArraySize * 2;
        }
        smallestVal.min = dropLimit;
        
        for(int ii = cntr - 1; ii >= 0; ii--){
            if((nodes + ii)->digits + (nodes + ii)->depthCntr < smallestVal.min && (nodes + ii)->visited == 0){
                smallestVal.min = (nodes + ii)->digits + (nodes + ii)->depthCntr;
                smallestVal.addr = ii;
            }
        }
        Rcntr = smallestVal.addr;
    }
}

char searchAgent(int size, int data[][size])
{
    static int calculated = 0;
    static int charCntr = 0;
    static char * moveArray;

    if(!calculated){
        moveArray = agentFlow(size, data);
        calculated = 1;
    }
    else
        charCntr++;
    
    return moveArray[charCntr];
}
