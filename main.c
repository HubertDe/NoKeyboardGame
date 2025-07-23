#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>


int randomInteger(FILE* file){
	srand(time(NULL));
	int end = fseek(file, 0 , SEEK_END);
	long fileEnd = ftell(file);
	int fileSize = (int)fileEnd ;
	int	randomInteger =1+ rand()/((RAND_MAX + 1u)/fileSize);
	return randomInteger;
}


void getRandomSentence(){

	FILE* giveup = fopen("giveup.txt", "r");

	if(!giveup){printf("File cannot be opened");}

	int sentenceStart= randomInteger(giveup);
	int sentenceLength = randomInteger(giveup);
	int* start = &sentenceStart;
	int* length = &sentenceLength;
	char*  randomSentence = malloc(sizeof(char) * (*length + 1));
	if(!randomSentence){printf("Malloc fail");fclose(giveup);return;}
	fseek(giveup, (long) *start, SEEK_SET);
	fgets(randomSentence, *length+1, giveup);
	while(isupper(randomSentence[0]) == 0 || ispunct(randomSentence[*length-1]) == 0){
		(*length)++;
		(*start)--;

		char*  temp = realloc(randomSentence, sizeof(char)*(*length + 1));
		if(!temp){printf("Malloc fail"); free(randomSentence);fclose(giveup);return;}
		randomSentence = temp;
  		fseek(giveup, (long) *start, SEEK_SET);
	    fgets(randomSentence, *length +1, giveup);
		if(feof(giveup)||*start<0){*start = randomInteger(giveup); *length = randomInteger(giveup);}
	}

	printf("%s\n", randomSentence);
	free(randomSentence);	
	fclose(giveup);
	
}


int main(){
	getRandomSentence();
	return 0;
}
