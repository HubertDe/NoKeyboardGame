#include<stdio.h>

char favNum(){return '1';}
char favLetter(){return 'k';}

void printFavLetter(char (*fav)(void)){
    printf("My fav sybol is %c", fav());
}


int main(){
    printFavLetter(favLetter);
    puts("");
    printFavLetter(favNum);
    return 0;
}
