#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

int randomInteger(FILE* file){
	srand(time(NULL));
	int end = fseek(file, 0 , SEEK_END);
	long fileEnd = ftell(file);
	int fileSize = (int)fileEnd ;
	int	randomInteger =1+ rand()/((RAND_MAX + 1u)/fileSize);
	return randomInteger;
}

bool checkIfItIsASentence(int &sentenceLength, char randomSentence[&sentenceLength]){
	bool firstLetterIsCapital = 0;
	int* start = &firstLetterIsCapital;
	bool endsWithADot = 0;
	int* end = &endsWithADot;
	

	if(randomSentence[0]>0) { *start = 1;}
	if(randomSentence[*sentenceLength] == ".") { *end =1;}

	return firstLetterIsCapital && endsWithADot;
}

void getRandomSentence(){

	FILE* giveup = fopen("giveup.txt", "r");

	if(!giveup){printf("File cannot be opened");}

	int sentenceStart= randomInteger(giveup);
	int sentenceLength = randomInteger(giveup);
	int* startPtr = &sentenceStart;
	int* lengthPtr = &sentenceLength;

	char  randomSentence[*lengthPtr];
	int seek = fseek(giveup, (long) *startPtr, SEEK_SET);
  	char* words = fgets(randomSentence, sizeof *lengthPtr, giveup);
	
	while(!checkIfIsASentance(lengthPtr, randomSentence[lengthPtr])){
			--*startPtr;
			++*lengthPtr;

		char  randomSentence[*lengthPtr];
		int seek = fseek(giveup, (long) *startPtr, SEEK_SET);
  		char* words = fgets(randomSentence, sizeof *lengthPtr, giveup);
	
		}

	printf("%s", words);
	
	fclose(giveup);
	
}


int main(){
	getRandomSentence();
	return 0;
}
