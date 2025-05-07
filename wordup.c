// Justin Wolterbeek
// Purpose: Plays wordle with user based on a 5 letter word inside another file
// Date: 4/21/25

#include <stdio.h>
#include <stdbool.h>
#define FILENAME "word.txt"
#define STR_CAP 35
// checks other file for word
void wordFind(FILE* fPtr, char word[STR_CAP]); 

// - display rules || - prompt user 
void guessPrompter(char userGuess[STR_CAP], int gCounter);

// makes userGuess all lowercase
void convertLow(char userGuess[STR_CAP]); 

// check user guess for correctness
void guessCheck(char userGuess[STR_CAP], char word[STR_CAP]);

// checks if guess is only letters
void gValidCheck(char userGuess[STR_CAP], int* validGPtr); 

// checks if guess is correct length
void gLenCheck(char userGuess[STR_CAP], int* validGPtr); 

// Capitalize correct letters || returns value for correct letters
int letterCap(char userGuess[STR_CAP], char word[STR_CAP]); 

// points to incorrectly placed letters
void letterPoint(char userGuess[STR_CAP], char word[STR_CAP], char pointArr[STR_CAP]);

// stores all of the users guess
void guessHistory(char userGuess[STR_CAP], char prevGuesses[][STR_CAP], int gCounter, char pointArr[STR_CAP]);

int main(void){
	char word[STR_CAP]; // mystery word
	char userGuess[STR_CAP]; // the word the user types in
	int capCount; // how many capital letters there are
	int i = 0; // index
	int gCounter = 0; // tracks which guess the user is on
	bool guessStatus = false; // false until user guesses correct
	int validG = 0; // tracks if the user has a valid guess (correct format)
	int* validGPtr = &validG; // points to validG
	char prevGuesses[11][STR_CAP]; // holds all of the users guesses
	char pointArr[STR_CAP]; // points to incorrectly placed letters 
	
	FILE* fPtr;
	fPtr = fopen(FILENAME, "r");
	
	if(fPtr == NULL){
		printf("Cannot open file for reading.\n");
		return 0;
	}
	wordFind(fPtr, word); // gets mystery word
	fclose(fPtr);

	// loops until user guess correctly 
 	do{
 		// loops until user enters a valid guess
		do{	
			// prompts user for guess
			guessPrompter(userGuess, gCounter);
			
			// converts userGuess to lowercase
			convertLow(userGuess); 
			
			// checks if userGuess is only letters
			gValidCheck(userGuess, validGPtr); 
			
			// checks if userGuess is too long
			gLenCheck(userGuess, validGPtr); 
			
			printf("======================================\n");
			
		}while(validG == 0); 
		
		// sets capCount = number of letters that are in correct place
		capCount = letterCap(userGuess, word); 
		
		// points to incorrectly placed letters
		letterPoint(userGuess, word, pointArr);
		
		// adds userGuess and pointArr to a 2d collection of all guesses
		guessHistory(userGuess, prevGuesses, gCounter, pointArr);
		
		// displays all of the users guesses 
		for (int rowI = 0; rowI < (gCounter + 1) * 2; rowI++){
			for (int colI = 0; colI < 6; colI++){
				printf("%c",prevGuesses[rowI][colI]);
			}
			printf("\n");
		} 
		// checks if user guessed correctly
		if (capCount == 5){
			guessStatus = true;	
		}
		gCounter++;
		
	}while(guessStatus == false && gCounter < 6);
	
	printf("======================================\n");
	
	// checks if user won or lost
	if (guessStatus == true){
		printf("You won! The correct word was: %s\n", userGuess);
	}else{
		printf("You lost, Better luck next time!\n");
	}
	
	return 0;
}
// Get the word from word.txt file
void wordFind(FILE* fPtr, char word[STR_CAP]){
	fscanf(fPtr, "%s", word);
}
// Prompts user for a guess
void guessPrompter(char userGuess[STR_CAP], int gCounter){
	if (gCounter == 5){
		printf("FINAL GUESS:", gCounter + 1);	
		scanf("%s", userGuess);
	
	}else{
		printf("GUESS %d! Enter your guess:", gCounter + 1);	
		scanf("%s", userGuess);
	}

	
	
}
// sets userGuess to lowercase
void convertLow(char userGuess[STR_CAP]){
	for (int i =0; userGuess[i] != '\0'; i++){
		if (userGuess[i] >= 'A' && userGuess[i] <= 'Z'){
		userGuess[i] = userGuess[i] + 32;	
	}
	}

}
// checks if userGuess is only letters
void gValidCheck(char userGuess[STR_CAP], int* validGPtr){

	int gCheck = 0;
	for (int i = 0; userGuess[i] != '\0' && gCheck == 0 ; i++){
		if (userGuess[i] >= 'a' && userGuess[i] <= 'z'){
			*validGPtr = 1;
		}else{ 
			*validGPtr = 0;
			gCheck = 1;
		}
		if (*validGPtr == 0){
			printf("Invalid response. Please use only letters.\n");	
		}
	}
}
// Checks if userGuess is 5 letters or not
void gLenCheck(char userGuess[STR_CAP], int* validGPtr){
	int i2 = 0;
	for (int i = 0; userGuess[i] != '\0'; i++){
		i2 += 1;
	}
	if (i2 != 5){
		printf("Please enter a 5 letter word\n");
		*validGPtr = 0;
	}
}
// Capitlizes letters in correct spot
int letterCap(char userGuess[STR_CAP],char word[STR_CAP]){
	int capCount = 0;
	for (int i = 0; userGuess[i] != '\0'; i++){
		if (userGuess[i] == word[i]){
			userGuess[i] = userGuess[i] - 32;
			capCount += 1;
		}
	}
	return capCount;
}
// points to any correct letters
void letterPoint(char userGuess[STR_CAP], char word[STR_CAP], char pointArr[STR_CAP]){
	int i;
	for (i = 0; userGuess[i] != '\0'; i++){ 
		pointArr[i] = ' ';
		int i2 = 0;
		for(i2 = 0; word[i2] != '\0'; i2++){
			if (userGuess[i] == word[i2]){
				pointArr[i] = '^';
			}
		}	
	}	
}
// adds all userGuesses to a 2d array of all userGuesses
void guessHistory(char userGuess[STR_CAP], char prevGuesses[][STR_CAP], int gCounter, char pointArr[STR_CAP]){
	int i2 = gCounter + 1;
	for (int i = 0; i < 6; i++){
		// manually adds latest userGuess[] to prevGuesses[][]
		switch (i2){
			case 1:
				prevGuesses[0][i] = userGuess[i];
				prevGuesses[1][i] = pointArr[i];
				break;
			case 2:
				prevGuesses[2][i] = userGuess[i];
				prevGuesses[3][i] = pointArr[i];
				break;
			case 3:
				prevGuesses[4][i] = userGuess[i];
				prevGuesses[5][i] = pointArr[i];
				break;
			case 4:
				prevGuesses[6][i] = userGuess[i];
				prevGuesses[7][i] = pointArr[i];
				break;
			case 5:
				prevGuesses[8][i] = userGuess[i];
				prevGuesses[9][i] = pointArr[i];
				break;
			case 6:
				prevGuesses[10][i] = userGuess[i];
				prevGuesses[11][i] = pointArr[i];
				break;
		}	
	}
}





