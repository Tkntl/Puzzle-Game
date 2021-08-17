#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

unsigned int getURandom(void) {
    
    int f;
    int n;
    unsigned int rnd;
    f = open("/dev/urandom", O_RDONLY);

    if (f < 0) {
        perror("Failed to open urandom");
        return 1;
    }
    n = read(f, &rnd, sizeof(rnd));
    
    if (n != sizeof(rnd)) {
        perror("Problem reading urandom");
        return 1;
    }
    close(f);
    return rnd;
    }

int getRandNum(int size) {

    unsigned int rnd;
    int number;

    rnd = getURandom();
    number = rnd % size;
        
    return number;
}    
    
char randSolve(void) {

    unsigned int rnd;
    int dire;
    
    rnd = getURandom();
    
    dire = rnd % 4;
        
    switch(dire) {
        case 0 :
            return 'w';
        case 1 :
            return 's';
        case 2 :
            return 'a';
        case 3 :
            return 'd';
        default :
            printf("ERROR");
    }
}




char randSolve2(int size, int data[][size]){
    
    unsigned int rnd;
    int zero[2];
    int newZero[2];
    int dire;
    char move;
    int correct;
    int cntr = 0;
    
    for(int y = 0;y < size;y++){
        for(int x = 0;x < size;x++){
            if(data[y][x] == 0) {
                zero[0] = y;
                zero[1] = x;
            }
        }
    }

    while(1) {
        rnd = getURandom();
    
        dire = rnd % 4;
    
        newZero[0] = zero[0];
        newZero[1] = zero[1];
    
        switch(dire) {
            case 0 :
                move = 'w';
                newZero[0]--;
                break;
            case 1 :
                move = 's';
                newZero[0]++;
                break;
            case 2 :
                move = 'a';
                newZero[1]--;
                break;
            case 3 :
                move = 'd';
                newZero[1]++;
                break;
            default :
                printf("ERROR");
        }
    
        if((newZero[0] >= 0 && newZero[0] < size) && (newZero[1] >= 0 && newZero[1] < size)){
            if(newZero[0] > 0)
                correct = newZero[0]*3+newZero[1];
            else
                correct = newZero[1];
    
            if(data[newZero[0]][newZero[1]] != correct)
                return move;
            else if(cntr > 4)
                return move;
        }
        cntr++;
    }
}
    
    
    
