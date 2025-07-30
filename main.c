#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>

char* matchFile(char* file){
	char* fileName;
	switch(file){
		case "1":
			fileName = "giveup.txt";
			return fileName;
		default:
			return "giveup.txt";
	}
}
char* getUserFileChoice() {
    puts("Choose a file: 1 - GONNAGIVEUP");
    char* chosenFile = malloc(10 * sizeof(char));
    if (chosenFile == NULL) {
        puts("Memory allocation failed!");
        return NULL; 
    }
    fgets(chosenFile, 10, stdin); 
    chosenFile[strcspn(chosenFile, "\n")] = 0; 
    if (strcmp(chosenFile, "1") != 0) {
        puts("You cannot choose that. Try again!");
        free(chosenFile); 
        return getUserFileChoice(); 
    }

    return chosenFile; 
}

int randomInteger(FILE* file){
	srand(time(NULL));
	int end = fseek(file, 0 , SEEK_END);
	long fileEnd = ftell(file);
	int fileSize = (int)fileEnd ;
	int	randomInteger =1+ rand()/((RAND_MAX + 1u)/fileSize);
	return randomInteger;
}

char* getRandomSentence(int chosenFile){

	FILE* file = fopen(matchFile(chosenFile), "r");

	if(!file){puts("File cannot be opened"); return NULL;}

	int sentenceStart= randomInteger(file);
	int sentenceLength = randomInteger(file);
	if(sentenceLength <= 0){fclose(file); return NULL;}
	int* start = &sentenceStart;
	int* length = &sentenceLength;
	char*  randomSentence = malloc(sizeof(char) * (*length + 1));
	if(!randomSentence){puts("Malloc fail");fclose(file);return NULL;}
	fseek(file, (long) *start, SEEK_SET);
	fgets(randomSentence, (*length+1), file);
	while(isupper(randomSentence[0]) == 0 || ispunct(randomSentence[*length-1]) == 0){
		(*length)++;
		(*start)--;

		char*  temp = realloc(randomSentence, sizeof(char)*(*length + 1));
		if(!temp){puts("Malloc fail"); free(randomSentence);fclose(file);return NULL;}
		randomSentence = temp;
  		fseek(file, (long) *start, SEEK_SET);
	    fgets(randomSentence, (*length +1), file);
		if(feof(file)||*start<0){
			*start = randomInteger(file); 
			*length = randomInteger(file);
			if(*length <= 0){fclose(file); return NULL;}
		}
	}

	char* sentence = randomSentence;
	free(randomSentence);	
	fclose(file);
	return sentence;
}

int main(){
	while(true){
		char* chosenFile = getUserFileChoice();
		char* sentence = getRandomSentence(chosenFile);
		printf("Type this sentence as fast as you can! Try to do it without looking on your keyboard.\n.....\n");
		char* userSentence = malloc((strlen(sentence) + 1) * sizeof(char));
		if(!userSentence){puts("Malloc error");exit(EXIT_FAILURE);}
		printf("%s \n", sentence);
		clock_t start = clock();
		fgets(userSentence, (strlen(sentence) + 1) * sizeof(char), stdin);
		while (strcmp(sentence, userSentence) != 0) {
			puts("Sentences do not match! Try again.");
			fgets(userSentence, (strlen(sentence) + 1) * sizeof(char), stdin);
		}
		clock_t end = clock();
		free(userSentence);
		double timePassed = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("You answered correctly in %f seconds! \n", timePassed);
		puts("Would you like to continue? y/n");
		while(getchar() != '\n');
		char choice;
		while(true){
			choice = getchar();
			if (choice == 'y'){
				while(getchar() != '\n');
				break;
			}else if (choice == 'n'){
				while(getchar() != '\n');
				goto end;
			}else{
				puts("That is not an option. Try once more.");
				while(getchar() != '\n');
			}
		}
	}
	end:;
	return 0;
}
