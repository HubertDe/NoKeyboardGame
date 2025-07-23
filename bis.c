#include<stdio.h>
#include<ctype.h>
#include<stdbool.h>

void test(int* p){
	printf("\n%d\n", *p);
}

bool isTrue(bool a, bool b){
	return a&&b;

}


int main(){

	int x = 3;
	int* y = &x;
	char* letter = "Arab";
	bool a = 1;
	bool* c = &a;
	bool b = 0;
	printf("%b",isTrue(a,b));


	if(isupper(letter[0])){printf("Prawda bo to %c",letter[0]);}

	test(y);
}
