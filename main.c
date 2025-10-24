#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdbool.h>
#include<string.h>
#include<assert.h>


#define checkIfFileCannotBeOpened(file) /* File* */                 \
    do {                                                            \
        if (!(file)) {                                              \
            perror("checkIfFileCannotBeOpened()");                  \
            printf("Occured at line %d \n" , __LINE__);             \
            exit(EXIT_FAILURE);                                     \
        }                                                           \
    } while (0)


#define checkIfMallocFailure(sentence) /* char* */                  \
    do{                                                             \
        if(!sentence){                                              \
            perror("checkIfMallocFailure()");                       \
            printf("Occured at line %d \n", __LINE__);              \
            exit(EXIT_FAILURE);                                     \
        }                                                           \
    } while(0)                                                      \

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
    }else if(file == '2'){
        fileName = "shrek.txt";
        return fileName;
    }else{
        fileName = "No match";
        return fileName;
    }
}
void clearBuffer(void){
     int c = 0;
        while ((c = getchar()) != '\n' && c != EOF);
}

const char getUserFileChoice(void) {
    int chosenFile;
    
    while (true) {
        puts("Choose a file: 1 - GONNAGIVEUP, 2 - ALLSTAR");
        chosenFile = getchar();
        assert(chosenFile != EOF);

        clearBuffer();
        if (chosenFile == '1' || chosenFile == '2') {
            break; 
        } else{
            puts("You cannot choose that. Try again!");
        }
    }

    return (char) chosenFile;
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
    checkIfFileCannotBeOpened(file);

	int searcher = randomInteger(file);
	int* search = &searcher;

    fseek(file, *search, SEEK_SET);
    int potentialCapital = fgetc(file);
    assert(potentialCapital != EOF);
    int* letter = &potentialCapital;
    while (isupper(potentialCapital) == 0){
        (*search) ++;
        fseek(file,*search, SEEK_SET);
         *letter = fgetc(file);
         if(feof(file)!= 0) *search = randomInteger(file);   
    }
    assert(letter != nullptr);
    assert(search != nullptr);
    const int sentenceStart = *search;
    
    fseek(file, *search, SEEK_SET);
    int potentialDot = fgetc(file);
    assert(potentialDot != EOF);
    int* dot = &potentialDot;
    while(potentialDot != '.'){
        (*search) ++;
        fseek(file, *search, SEEK_SET);
        *dot = fgetc(file);
        if(feof(file)!= 0) *search = randomInteger(file);
    }
    assert(dot != nullptr);
    assert(search != nullptr);
    const int sentenceEnd = *search;

    const int sentenceLength = sentenceEnd - sentenceStart;
    fseek(file, sentenceStart, SEEK_SET);
    char* randomSentence = malloc((sentenceLength + 1) * sizeof(char));
    checkIfMallocFailure(randomSentence);
    fgets(randomSentence, sentenceLength + 2, file);

	return randomSentence;
}

int main(){
    puts("Press any key to start");
	while(true){
        clearBuffer();
		const char chosenFile = getUserFileChoice();
        FILE* file = fopen(matchFile(chosenFile), "r");
        checkIfFileCannotBeOpened(file);
        char* sentence = malloc(((int)ftell(file) + 1) * sizeof(char));
        checkIfMallocFailure(sentence);
        fclose(file);
		sentence = getRandomSentence(chosenFile);
        assert(isupper(sentence[0]));
		printf("Type this sentence as fast as you can! Try to do it without looking on your keyboard.\n.....\n");
		char* userSentence = malloc((strlen(sentence) + 1) * sizeof(char));
		checkIfMallocFailure(userSentence);
        printf("%s \n", sentence);
		time_t start = time(&start);
		fgets(userSentence, (strlen(sentence) + 1) * sizeof(char), stdin);
        if (strchr(userSentence, '\n') != nullptr) {
            clearBuffer();
        }
		while (!areTheWordsTheSame(sentence, userSentence)) {
			puts("Sentences do not match! Try again.");
			fgets(userSentence, (strlen(sentence) + 1) * sizeof(char), stdin);
		}
		time_t end = time(&end);
		free(userSentence);
		double timePassed = difftime(end, start);
		printf("You answered correctly in %.0f seconds! \n", timePassed);
        fclose(file);
		puts("Would you like to continue? y/n");
		int choice;
		while(true){
            while (getchar() != '\n');
			choice = getchar();
            assert(choice != EOF);
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
