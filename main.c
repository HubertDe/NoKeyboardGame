#include<stdio.h>
#include<time.h>
#include<stdlib.h>
int randomInteger(FILE* file){
	srand(time(NULL));
	int end = fseek(file, 0 , SEEK_END);
	long fileEnd = ftell(file);
	int fileStart = 0;
	int fileSize = (int)fileEnd - fileStart;
	int	randomInteger =1+ rand()/((RAND_MAX + 1u)/fileSize);
	return randomInteger;
}

void getRandomSentence(){

	FILE* giveup = fopen("giveup.txt", "r");

	if(!giveup){
		printf("File cannot be opened");
	}
	int sentenceStart= randomInteger(giveup);
	int sentenceLength = randomInteger(giveup);
	char  randomSentence[sentenceLength];
	int seek = fseek(giveup, (long) sentenceStart, SEEK_SET);
  	char* words = fgets(randomSentence, sizeof sentenceLength, giveup);

	printf("%s\n", randomSentence);

	fclose(giveup);
}


int main(){
	getRandomSentence();
	return 0;
}
