// Kevin Niland
// G00342279
// Procedural Programming project - War card game
// Write a program that implements the game "War"

// Inclusion of appropriate libraries
#include <stdio.h>
#include <stdlib.h>
// #include <stdbool.h>
#include <time.h>

// File that various information will be loaded to
FILE* War;

/* Initialisation of arrays used throughout the program */
int PLAYER_CARDS[10]; // Stores the picked cards. Used to compare player cards and determine which player will win each round
int CARD_DECK[10][13]; // Used to create a card deck

/* Initialisation of variables used throughout the program */
// bool isDraw = true;
// char displayDeckChoice;
char starterChoice;
int card;
int numOfPlayers;
int playerCard;
int playerCards;
int playerCardSelection;
int playerChoice;
int players;
int round;
int winner;
int highestCard = -1;
int total = 0;
int pointsAccumulation = 0;
// int whichPlayer;
int winningPlayerCounter = 0;

void information()
{
	printf("\nAt the beginning of the game, the amount of players that will be playing are determined. Every player is ");
	printf("13 cards - a full suit of cards consisting an Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, and King. ");
	printf("The goal of War is to have the highest, unique card. You can only use each card once. If two players pick the same ");
	printf("card, they will 'cancel' each other out. This means a player can win a round with a card of value 2 as long as it is");
	printf("the highest, unique card on the playing round. The player who wins an individual round will gain points based on the values");
	printf("of their and their opponents cards. If all cards 'cancel' each other out, the points will roll over to the next round. There are ");
	printf("13 rounds per game.");

	fprintf(War, "\nAt the beginning of the game, the amount of players that will be playing are determined. Every player is ");
	fprintf(War, "13 cards - a full suit of cards consisting an Ace, 2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, and King. ");
	fprintf(War, "The goal of War is to have the highest, unique card. You can only use each card once. If two players pick the same ");
	fprintf(War, "card, they will 'cancel' each other out. This means a player can win a round with a card of value 2 as long as it is");
	fprintf(War, "the highest, unique card on the playing round. The player who wins an individual round will gain points based on the values");
	fprintf(War, "of their and their opponents cards. If all cards 'cancel' each other out, the points will roll over to the next round. There are ");
	fprintf(War, "13 rounds per game.");
}

// Asks the player if they want to learn how to play the game and how many players will be playing
void start()
{
	// Asks user if they wish to learn how to play the game
	printf("Welcome to the card game, War. Press 'i' to learn how to play the game or press any other key to continue: ");
	scanf("%c", &starterChoice);

	// Prints the above statement to the text file
	fprintf(War, "Welcome to the card game, War. Press 'i' to learn how to play the game or press any other key to continue: ");

	// if the user enters the character 'i' or'I', the information() function is called
	if (starterChoice == 'i' || starterChoice == 'I')
	{
		information();
	}

	// Prompts user for the number of players that will be playing
	printf("\n\nPlease enter the number of players: ");
	scanf("%d", &numOfPlayers);

	/* printf("Please enter your player number: ");
	scanf("%d", &whichPlayer); 

	fprintf(War, "\n\nPlease enter the number of players: ");

	fprintf(War, "Please enter your player number: ");
	scanf("%d", &whichPlayer); */
}

// Creates a deck
void createDeck(int CARD_DECK[][14], int n)
{
	for (players = 0; players < n; players++)
	{
		for (playerCards = 0; playerCards <= 13; playerCards++)
		{
			CARD_DECK[players][playerCards] = playerCards;
		}
	}
}

// Display player decks
void displayDecks(int CARD_DECK[][14], int n)
{
	// for loop for number of players
	for (players = 0; players < n; players++)
	{
		printf("\nPlayer %d: ", players + 1);

		fprintf(War, "\nPlayer %d: ", players + 1);

		// for loop for player cards
		for (playerCards = 0; playerCards <= 13; playerCards++)
		{
			// switch statement to change 1, 11, 12, and 13 to A, J, Q, and K
			switch (CARD_DECK[players][playerCards])
			{
			case 1:
				printf("%c, ", 'A');
				fprintf(War, "%c, ", 'A');
				break;
			case 11:
				printf("%c, ", 'J');
				fprintf(War, "%c, ", 'J');
				break;
			case 12:
				printf("%c, ", 'Q');
				fprintf(War, "%c, ", 'Q');
				break;
			case 13:
				printf("%c ", 'K');
				fprintf(War, "%c ", 'K');
				break;
			case NULL:
				printf("");
				fprintf(War, "");
				break;
			default:
				printf("%d, ", CARD_DECK[players][playerCards]);
				fprintf(War, "%d, ", CARD_DECK[players][playerCards]);
			}
		}
	}
}

// Allows user to pick a card
int pickCard(int CARD_DECK[][14], int i, int n)
{
	printf("Player %d: ", i + 1);
	scanf("%d", &playerCard);

	fprintf(War, "Player %d: ", i + 1);

	// for loop for number of players
	for (players = 0; players < n; players++)
	{
		/* Attempt at allowing player to enter A, J, Q, or K to pick a card. */
		/* switch (playerCard)
		{
			case 'A':
				playerCard = 1;
				break;
			case 'J':
				playerCard = 11;
				break;
			case 'Q':
				playerCard = 12;
				break;
			case 'K':
				playerCard = 13;
				break;
		} */

		// if statement to check if players is equal to the current player number i.e if the Player 1 is asked to enter a card,...
		if (players == i)
		{
			// ... for loop for player's cards
			for (playerCards = 0; playerCards <= 13; playerCards++)
			{
				// Checks if the card entered has already been selected i.e if the card picked isn't in the array anymore...
				if ((CARD_DECK[players][playerCard] == NULL) && (playerCard >= 1 || playerCard <= 13))
				{
					// ...informs user that the card they picked has been used
					printf("Cards can only be used once. Please try again: ");
					scanf("%d", &playerCard);

					fprintf(War, "Cards can only be used once. Please try again: ");
				}
				else if (playerCard < 1 || playerCard > 13)
				{
					printf("Player card selection is not valid. %d is not in the deck. Please try again: ", playerCard);
					scanf("%d", &playerCard);
				}
				// else the card picked is valid and is subsequently removed from the CARD_DECK array
				else
				{
					card = CARD_DECK[players][playerCard];
					CARD_DECK[players][playerCard] = NULL;

					return card; // The picked card value is returned
				}
			}
		}
	}
}

void rounds()
{
	printf("\nRound %d", (round + 1));
	printf("\n=========\n");

	fprintf(War, "\nRound %d", (round + 1));
	fprintf(War, "\n=========\n");

	for (players = 0; players < numOfPlayers; players++)
	{
		playerCardSelection = pickCard(CARD_DECK, players, numOfPlayers);
		PLAYER_CARDS[players] = playerCardSelection;
	}
}

// Calculates the score for each round
int score(int PLAYER_CARDS[10], int numOfPlayers)
{
	// for loop for number of players
	for (players = 0; players < numOfPlayers; players++)
	{
		// if the player enters the card value 1,...
		if (PLAYER_CARDS == 1)
		{
			total += 14; //...14 is added to the total score
		}
		else
		{
			total += PLAYER_CARDS[players]; // else the value entered is added to the total
		}
	}
}

void pointsRollover()
{
	// for loop for number of players
	for (players = 0; players < numOfPlayers; players++)
	{
		pointsAccumulation += PLAYER_CARDS[players]; // The number of points that will be rolled over is stored into the PLAYER_CARDS array
	
		if (PLAYER_CARDS[players] != PLAYER_CARDS[0])
		{
			printf("\nPlayer %d wins round %d. ", winner, (round + 1));
			printf("\nPlayer %d's points after round %d: %d \n\n", winner, (round + 1), total);

			fprintf(War, "\nPlayer %d wins round %d. ", winner, (round + 1));
			fprintf(War, "Player %d's points after round %d: %d \n\n", winner, (round + 1), total);
		}
		// NOTE: For some reason, this will print out regardless of whether or not players choose the same card. However, the correct message will print out if players do pick the same card
		else
		{
			printf("There is no winner this round. Points not won this round will rollover to round %d.", (round + 1));
			printf("\n");

			fprintf(War, "There is no winner this round. Points not won this round will rollover to round %d.", (round + 1));
			fprintf(War, "\n");
		}
	}
}

// Decides which player wins each round
int winningPlayer(int PLAYER_CARDS[10], int n)
{
	// for loop for number of players
	for (players = 0; players < n; players++)
	{
		// if the player's card is greater than the current highest card,....
		if (PLAYER_CARDS[players] > highestCard)
		{
			highestCard = PLAYER_CARDS[players]; //...the new highest card is this player
			winningPlayerCounter = players + 1; // The current 'winning' player is now this player
		}
	}

	return winningPlayerCounter; // Return the winning player's number. This is incremented once as the variable 'players' starts at 0
}

// main()
void main()
{
	// Creates the text file
	War = fopen("War.txt", "w");

	// Calls the 'start()' function
	start();

	// if the number of players is greater than or equal to 2 and less than or equal to 10,...
	if ((numOfPlayers >= 2) && (numOfPlayers <= 10))
	{
		CARD_DECK[numOfPlayers][14]; // ...initialises the CARD_DECK with the number of players in the first row and the 13 cards in the second row
		PLAYER_CARDS[numOfPlayers]; // ...creates a PLAYER_CARDS array. The size of this array is based on the number of players

		createDeck(CARD_DECK, numOfPlayers); // ...creates a number of decks by taking in the CARD_DECK array and based on the number of players
		displayDecks(CARD_DECK, numOfPlayers); // ...displays a number of decks by taking in the CARD_DECK array and based on the number of players

		printf("\n");

		// for loop for each round
		for (round = 0; round < 13; round++)
		{
			rounds();
			score(PLAYER_CARDS, numOfPlayers); // Calls the score function 
			winner = winningPlayer(PLAYER_CARDS, numOfPlayers); // Calls the winningPlayer function and stores the result of this into winner
			pointsRollover();

			printf("\n");

			// fclose(War);
		}

		printf("Player %d wins with %d points!", winningPlayerCounter, total);

		fprintf("Player %d wins with %d points!", winningPlayerCounter, total);
	}
	else
	{
		printf("\nNumber of players is invalid. There must be at least 2 players and no more than 10 players.");

		fprintf(War, "\nNumber of players is invalid. There must be at least 2 players and no more than 10 players.");
	}

	getch();
}
