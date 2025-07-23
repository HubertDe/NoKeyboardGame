#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>

typedef enum{GONNAGIVEUP} files;


char* matchFile(files file){
	char* fileName;
	switch(file){
		case GONNAGIVEUP:
			fileName = "giveup.txt";
			return fileName;
	}
}
files getUserFileChoice(){
	printf("Choose a file: GONNAGIVEUP\n");
	int chosenFile;
	scanf("%d", &chosenFile);
	return (files)chosenFile;
}
int randomInteger(FILE* file){
	srand(time(NULL));
	int end = fseek(file, 0 , SEEK_END);
	long fileEnd = ftell(file);
	int fileSize = (int)fileEnd ;
	int	randomInteger =1+ rand()/((RAND_MAX + 1u)/fileSize);
	return randomInteger;
}


void getRandomSentence(files chosenFile){

	FILE* file = fopen(matchFile(chosenFile), "r");

	if(!file){printf("File cannot be opened");}

	int sentenceStart= randomInteger(file);
	int sentenceLength = randomInteger(file);
	int* start = &sentenceStart;
	int* length = &sentenceLength;
	char*  randomSentence = malloc(sizeof(char) * (*length + 1));
	if(!randomSentence){printf("Malloc fail");fclose(file);return;}
	fseek(file, (long) *start, SEEK_SET);
	fgets(randomSentence, *length+1, file);
	while(isupper(randomSentence[0]) == 0 || ispunct(randomSentence[*length-1]) == 0){
		(*length)++;
		(*start)--;

		char*  temp = realloc(randomSentence, sizeof(char)*(*length + 1));
		if(!temp){printf("Malloc fail"); free(randomSentence);fclose(file);return;}
		randomSentence = temp;
  		fseek(file, (long) *start, SEEK_SET);
	    fgets(randomSentence, *length +1, file);
		if(feof(file)||*start<0){*start = randomInteger(file); *length = randomInteger(file);}
	}

	printf("%s\n", randomSentence);
	free(randomSentence);	
	fclose(file);
	
}


int main(){
	files chosenFile = getUserFileChoice();
	getRandomSentence(chosenFile);
	return 0;
}
