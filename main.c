#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>

bool areTheWordsTheSame(char* firstWord, char* secondWord){

    bool check = true;

    if(strlen(firstWord) != strlen(secondWord)) return check = false;
    for(int pos = 0; pos < strlen(firstWord); pos++){
        if(firstWord[pos] != secondWord[pos]) check = false;
    }
    return check;
}

char* matchFile(char file){
	char* fileName;
    if(file == '1' ){
        fileName = "giveup.txt";
        return fileName;
    }else{
        fileName = "No match";
        return fileName;
    }
}
void clearBuffer(){
     int c= 0;
        while ((c = getchar()) != '\n' && c != EOF);
}

char getUserFileChoice() {
    char chosenFile;
    
    while (true) {
        puts("Choose a file: 1 - GONNAGIVEUP");
        chosenFile = getchar();
        
        clearBuffer();
        if (chosenFile == '1') {
            break; 
        } else{
            puts("You cannot choose that. Try again!");
        }
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

char* getRandomSentence(char chosenFile){

	FILE* file = fopen(matchFile(chosenFile), "r");

	if(!file){
        puts("File cannot be opened"); 
        return NULL;
    }

	int searcher = randomInteger(file);
	int* search = &searcher;

    fseek(file, *search, SEEK_SET);
    char potentialCapital = fgetc(file);
    char* letter = &potentialCapital;
    while (isupper(potentialCapital) == 0){
        (*search) ++;
        fseek(file,*search, SEEK_SET);
         *letter = fgetc(file);
         if(feof(file)!= 0) *search = randomInteger(file);   
    }
    int sentenceStart = *search;
    
    fseek(file, *search, SEEK_SET);
    char potentialDot = fgetc(file);
    char* dot = &potentialDot;
    while(potentialDot != '.'){
        (*search) ++;
        fseek(file, *search, SEEK_SET);
        *dot = fgetc(file);
        if(feof(file)!= 0) *search = randomInteger(file);
    }
    int sentenceEnd = *search;

    int sentenceLength = sentenceEnd - sentenceStart;
    fseek(file, sentenceStart, SEEK_SET);
    char* randomSentence = malloc((sentenceLength + 1) * sizeof(char));
    fgets(randomSentence, sentenceLength + 2, file);

	return randomSentence;
}

int main(){
	while(true){
		char chosenFile = getUserFileChoice();
        FILE* file = fopen(matchFile(chosenFile), "r");
        if(!file){
            puts("file cannot be openned");
            fclose(file);
        }
        char* sentence = malloc(((int)ftell(file) + 1) * sizeof(char));
        if(!sentence){
            puts("Malloc fail");
            exit(EXIT_FAILURE);
        }
        fclose(file);
		sentence = getRandomSentence(chosenFile);
        assert(isupper(sentence[0]));
		printf("Type this sentence as fast as you can! Try to do it without looking on your keyboard.\n.....\n");
		char* userSentence = malloc((strlen(sentence) + 1) * sizeof(char));
		if(!userSentence){
            puts("Malloc error");
            exit(EXIT_FAILURE);
        }
		printf("%s \n", sentence);
		clock_t start = clock();
		fgets(userSentence, (strlen(sentence) + 1) * sizeof(char), stdin);
        if (strchr(userSentence, '\n') != nullptr) {
            clearBuffer();
        }
		while (!areTheWordsTheSame(sentence, userSentence)) {
			puts("Sentences do not match! Try again.");
			fgets(userSentence, (strlen(sentence) + 1) * sizeof(char), stdin);
		}
		clock_t end = clock();
		free(userSentence);
		double timePassed = ((double) (end - start))/CLOCKS_PER_SEC;
		printf("You answered correctly in %f seconds! \n", timePassed);
		puts("Would you like to continue? y/n");
		char choice;
		while(true){
            while (getchar() != '\n');
			choice = getchar();
			if (choice == 'y'){
				break;
			}else if (choice == 'n'){
				goto end;
			}else{
				puts("That is not an option. Try once more.");
			}
		}
        free(sentence);
	}
	end:;
	return 0;
}
