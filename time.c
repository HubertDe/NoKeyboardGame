#include<time.h>
#include<stdio.h>

int main(){
    time_t start;
    time_t* s = &start;
    time(s);

    getchar();

    time_t end;
    time_t* e = &end;
    time(e);
    
    double diff = difftime(end, start);

    printf("The diff is %.0f", diff);
    return 0;
}
