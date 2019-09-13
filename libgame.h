
int fillPuzzle(int gridSize,int pGrid[][gridSize], int *zeroPos);
void printPuzzle(int gridSize, int (*pGrid)[gridSize]);
int testIfsolved(int gridSize, int (*pGrid)[gridSize]);
char readInput(int mode);
char readInput2(int mode, int gridSize, int pGrid[][gridSize]);
int makeAmove(char in, int *zeroPos, int gridSize, int (*pGrid)[gridSize]);
