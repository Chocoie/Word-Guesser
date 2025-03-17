#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<conio.h>

//macro variables
#define length 6

//function prototypes
void playRound(char starword[], char answer[]); //play a round of word guessor
void maskWord (char starword[], char answer[], int size); //mask word with stars to display
int guessTheWord(char answer [], char userguess[]); //guess the word
void updateStarWord(char starword[], char answer[], char userguess[]); //replace respective *
void playAgain(int *play); //ask user to play again

//Dr. Steinberg functions
void clearBuffer();
void chomp(char word[]);


int main()
{
	//Intro Statements and rules of game
	printf("\n");
	printf("Welcome to the Word Guesser Game!\n");
	printf("************************************************************************\n");
	printf("This is a 2 player game in which one player will enter a word that the second person must guess\n");
	printf("************************************************************************\n");
	printf("Here are the rules:\n");
	printf("Player 1 will be prompted to enter a 5 letter word in all lowercase letters.\n");
	printf("After, Player 2 will guess the word.\n");
	printf("The word will be hidden to Player 2 using * representing alphbetic letters.\n");
	printf("For every correct letter guessed, it will be revealed in the word.\n");
	printf("Player 2 will keep guessing until they can guess the word fully.");
	printf("Then Player 2 will choose a word for Player 1.\n");
	printf("The player who takes the least amount of attempts of guessing their prospective word wins!\n");
	printf("Are you ready? Here we go!\n");
	printf("************************************************************************\n");
	printf("\n");
	
	//variables
	char starword[length];
	char answer[length];
	int play = 1;
	int round = 1;
	int *playPtr = &play;

	//continues game as long as play equals 1
	while(play == 1)
	{		
		//welcomes user to round
		printf("************************************************************************\n");
		printf("Welcome to the Round %d!\n", round);
			
		//stores whatever is returned
		playRound(starword, answer); //function call
		round++;
		//function call
		playAgain(playPtr);
	}
	
	
	if(play == 2);
	{
		//ending statments
		printf("************************************************************************\n");
		printf("Thanks for playing!\n");
	}
	
	return 0;
}

void playRound(char starword[], char answer[])
{
	//variables
	char userguess[length];
	int guessCountP1 = 1, guessCountP2 = 1;
	int correctOrNot = -1;
	int size = strlen(starword);
	int valid = 0;
	int i = 0;
	char ch;
	
	printf("Player 1, enter a 5 letter word: ");
	//ensures user enters valid word
	while(valid != 1)
	{
		i = 0;
		//mask work
		while (i < length) {
			ch = getch();  //read a character without echoing it
	
			if (ch == '\r' || ch == '\n')  //stop on Enter key
				break;
	
			if (ch == 8 && i > 0) {  //handle Backspace (ASCII 8)
				printf("\b \b");  //erase character from screen
				i--;
			} else if (i < length) {
				answer[i++] = ch;
				printf("*");  //print an asterisk instead of the letter
			}
		}
	
		answer[i] = '\0';  //null-terminate the string
	
		//printf("\nYou entered: %s\n", answer);  //debug output
		printf("\n");

		if(strlen(answer) == (length-1))
			valid = 1;
		else
			printf("Try again\n");

	}

	//function call
	maskWord(starword, answer, length-1);

	printf("Player 2, you must try and guess Player 1's word.\n");

	while(correctOrNot != 0)
	{
		printf("Guess %d: ", guessCountP1);
		correctOrNot = guessTheWord(answer, userguess);
		if(correctOrNot == 0)
		{
			printf("Congrats, you guessed the word!\n");
			break;
		}
		else
		{
			updateStarWord(starword, answer, userguess);
			guessCountP1++;
		}
	}
	printf("************************************************************************\n");
	printf("************************************************************************\n");
	printf("Player 2, enter a 5 letter word: ");
	valid = 0;
	correctOrNot = -1;
	while(valid != 1)
	{
		i = 0;
		//mask work
		while (i < length) {
			ch = getch();  //read a character without echoing it
	
			if (ch == '\r' || ch == '\n')  //stop on Enter key
				break;
	
			if (ch == 8 && i > 0) {  //handle Backspace (ASCII 8)
				printf("\b \b");  //erase character from screen
				i--;
			} else if (i < length) {
				answer[i++] = ch;
				printf("*");  //print an asterisk instead of the letter
			}
		}
	
		answer[i] = '\0';  //null-terminate the string
	
		//printf("\nYou entered: %s\n", answer);  //debug output
		printf("\n");

		if(strlen(answer) == (length-1))
			valid = 1;
		else
			printf("Try again\n");

	}

	//function call
	maskWord(starword, answer, length-1);
	//printf("%s\n", starword);

	printf("Player 1, you must try and guess Player 2's word.\n");

	while(correctOrNot != 0)
	{
		printf("Guess %d: ", guessCountP2);
		correctOrNot = guessTheWord(answer, userguess);
		if(correctOrNot == 0)
		{
			printf("Congrats, you guessed the word!\n");
			break;
		}
		else
		{
			updateStarWord(starword, answer, userguess);
			guessCountP2++;
		}
	}
	
	//check who won
	if(guessCountP1 > guessCountP2)
		printf("Player 1 wins!\n");
	else if(guessCountP1 > guessCountP2)
		printf("Player 2 wins!\n");
	else
		printf("It's a tie!\n");

}

void maskWord(char starword[], char answer[], int size)
{
	//replaces each letter with star
	for(int i = 0; i < size; i++)
		starword[i] = '*';
	starword[size] = '\0';
}

int guessTheWord(char answer[], char userguess[])
{
	//user guess
	scanf("%s", userguess);
	chomp(userguess);
	//checks if user guess matches answer
	int correctOrNot = strcmp(userguess, answer);
	
	if(correctOrNot == 0)
		return 0;
	else
		return -1;
}
void updateStarWord(char starword[], char answer[], char userguess[])
{
	for(int i = 0; i < strlen(answer); i++)
	{
		if(userguess[i] == answer[i])
			starword[i] = userguess[i];
	}
	chomp(starword);
	//reprints starword
	printf("%s\n", starword);
}

void playAgain(int *play)
{
	//checks if user wants to play again
	printf("************************************************************************\n");
	printf("Would you like to play another round?\n");
	printf("1: Yes\n");
	printf("2: No\n");
	printf("Choice: ");
	scanf("%d", play);
}

//Dr. Steinberg Functions
void clearBuffer()
{
	while(getchar() != '\n');
}

void chomp(char word[])
{
	if(word[strlen(word) - 1] == '\n')
		word[strlen(word) - 1] = '\0';
}