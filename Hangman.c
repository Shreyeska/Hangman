
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_WORD_LENGTH 200
#define MAX_TRIES 6

// words and their hints
struct WordWithHint {
	char word[MAX_WORD_LENGTH];
	char hint[MAX_WORD_LENGTH];
};

// Displaying the current state of the word
void displayWord(const char word[], const bool guessed[]);

// Drawing the hangman
void drawHangman(int tries);


int main()
{

	srand(time(NULL));
	
	
	// Words with hints
	struct WordWithHint wordList[] = {
		{ "alligator", "A creature that excels at blending in during family picnics near murky waters. Known for its killer smile and impeccable fashion sense—green is the new black, after all." },
		{ "bear", "Picture this: a large, furry woodland creature with a taste for honey and a talent for making camping trips just a tad more exciting. Not your average picnic buddy, that's for sure." },
		{ "cat", "It's a word that's as mysterious as your sudden bursts of energy at 3 AM. Spoiler: It's not 'Naptime'." },
		{ "dog", "A four-legged creature known for its uncanny ability to be both a loyal companion and an expert in napping. Not that your cat cares about such mundane beings, of course." },
		{"elephant", "It's a massive, majestic creature with a memory that puts your cat's selective amnesia to shame. You know, the kind of animal that makes your cat reconsider its life choices."}
	};

	
	int wordIndex = rand() % 5;

	const char* secretWord = wordList[wordIndex].word;
	const char* hint = wordList[wordIndex].hint;

	int wordLength = strlen(secretWord);
	char guessedWord[MAX_WORD_LENGTH] = { 0 };
	bool guessedLetters[26] = { false };

	printf("Welcome to Hangman!\n");
	printf("May the hangman odds be ever in your animal's favor!\n \n");
	printf("Hint: %s\n", hint);

	int tries = 0;

	while (tries < MAX_TRIES) {
		printf("\n");
		displayWord(guessedWord, guessedLetters);
		drawHangman(tries);

		char guess;
printf("\n Enter a letter: ");
if (scanf(" %c", &guess) != 1 || !isalpha(guess) || !islower(guess)) {
    printf("Invalid input. Please enter a valid lowercase letter.\n");
    continue; 
}


		if (guessedLetters[guess - 'a']) {
			printf("You've already guessed that letter. "
				"Try again.\n");
			continue;
		}

		guessedLetters[guess - 'a'] = true;

		bool found = false;
		for (int i = 0; i < wordLength; i++) {
			if (secretWord[i] == guess) {
				found = true;
				guessedWord[i] = guess;
			}
		}

		if (found) {
			printf("Good guess!\n");
		}
		else {
			printf("Sorry, the letter '%c' is not in the "
				"word.\n",
				guess);
			tries++;
		}

		if (strcmp(secretWord, guessedWord) == 0) {
			printf("\nCongratulations! You've guessed the "
				"word: %s\n",
				secretWord);
			break;
		}
	}

	if (tries >= MAX_TRIES) {
		printf("\nSorry, you've run out of tries. The word "
			"was: %s\n",
			secretWord);
	}

	return 0;
}

void displayWord(const char word[], const bool guessed[])
{
	printf("Word: ");
	for (int i = 0; word[i] != '\0'; i++) {
		if (guessed[word[i] - 'a']) {
			printf("%c ", word[i]);
		}
		else {
			printf("_ ");
		}
	}
	printf("\n");
}

void drawHangman(int tries)
{
	const char* hangmanParts[]
		= { "	 _________", " |		 |",
			" |		 O", " |	 /|\\",
			" |	 / \\", " |" };

	printf("\n");
	for (int i = 0; i <= tries; i++) {
		printf("%s\n", hangmanParts[i]);
	}
}
