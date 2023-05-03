#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define RESET "\x1b[0m"

// I mentioned this on piazza but my partner did not end up doing much until the day before it was due, and at that point I had already done basically all the code because I did not want to rely on him and he not get it done.
// He does not have the new finalized code, but he does have an older version of it, so there may be some similarities between the two codes, so just keep that in mind please.
// He may have still named me as a partner in his project though.
// If you have any questions or need to contact me about anything email ahattab@arizona.edu

// I only commented the first player because the code for the other 3 are the same but just repeated over using the variables for their linked lists, such as currObj2 for player 2, currObj4 for player 3, and currObj5 for player 4.

typedef struct card_s {
	char color[10];
	int value;
	char action[15];
	struct card_s* pt;
} card;

void createDeck(card deck[]) {
	int counter = 0;
	char yellow[10] = "yellow", red[10] = "red", green[10] = "green", blue[10] = "blue", hash[2] = "#", two[15] = "Multi-Color 2", null[15] = "anycolor";
	for (int j = 0; j < 4; ++j) {
		for (int i = (j * 22); i < ((j + 1) * 22); i++) {
			if (j == 0) {
				strcpy(deck[i].color, yellow);
			}
			else if (j == 1) {
				strcpy(deck[i].color, red);
			}
			else if (j == 2) {
				strcpy(deck[i].color, green); // this will add cards based on the DOS deck, with some cards having 3 and some having 2
			}								  // will loop through all 4 colors and then move on to adding the special cards, the # and then the twos
			else if (j == 3) {
				strcpy(deck[i].color, blue);
			}
			if ((i >= (0 + (22 * j)) && (i <= 2 + (22 * j)))) {
				deck[i].value = 1;
			}
			else if ((i >= 3 + (22 * j)) && (i <= 5 + (22 * j))) {
				deck[i].value = 3;
			}
			else if ((i >= 6 + (22 * j)) && (i <= 8 + (22 * j))) {
				deck[i].value = 4;
			}
			else if ((i >= 9 + (22 * j)) && (i <= 11 + (22 * j))) {
				deck[i].value = 5;
			}
			else {
				deck[i].value = ((i / 2) % 11);
			}
		}
	}
	for (int i = 88; i < 108; i++) { // will start to add the special cards, such as the anycolor 2 and the anyvalue cards
		if (i < 96) {
			if ((i == 88) || (i == 89)) {
				strcpy(deck[i].color, yellow);
			}
			else if ((i == 90) || (i == 91)) {
				strcpy(deck[i].color, red);
			}
			else if ((i == 92) || (i == 93)) {
				strcpy(deck[i].color, green);
			}
			else if ((i == 94) || (i == 95)) {
				strcpy(deck[i].color, blue);
			}
			strcpy(deck[i].action, hash);
			deck[i].value = 11;
		}
		else {
			strcpy(deck[i].color, null);
			strcpy(deck[i].action, two);
			deck[i].value = 2;
		}
	}
}

int createDeckFile(card deck[], FILE* inp) { // will read input from a file and create the deck based around that instead of random shuffling
	int count = 0;
	if (inp != NULL) {
		while (!feof(inp)) {
			fscanf(inp, "%s %d %s", deck[count].color, &deck[count].value, deck[count].action);
			if (deck[count].value == 11) {
				strcpy(deck[count].action, "#");
			}
			else if (deck[count].value == 2) {
				strcpy(deck[count].action, "Multi-Color 2");
			}
			count = count + 1;
		}
	}
	return count - 1;
}

void randomizeDeck(card deck[]) {
	srand((int)time(0));
	card temp;
	char hash[2] = "#", two[15] = "Multi-Color 2";
	for (int i = 0; i < 5000; i++) {   // runs the loop 5000 times to ensure cards are shuffled
		int num1 = rand() % 108, num2 = rand() % 108; // initializes random number from 0-107 representing the array values to swap it
		temp = deck[num1]; 
		deck[num1] = deck[num2];  //swaps the two cards aroudn using a temporary card
		deck[num2] = temp;
	}
}

void card_Create(card* cards, card deck[], card* nextCard, int counter) { // i used the template from 10.6 Section in zyBooks, but I modified it to use the deck
	if (deck[counter].value == 2) { // checks if value of card is 2, so it will copy the color, action, and value over since if it was a card beside # or 2, theres' not rreally a point to copy the action
		strcpy(cards->color, deck[counter].color);
		strcpy(cards->action, deck[counter].action);
		cards->value = deck[counter].value;
	}
	else if (deck[counter].value == 11) {
		strcpy(cards->color, deck[counter].color);
		strcpy(cards->action, deck[counter].action);
		cards->value = deck[counter].value;
	}
	else {
		strcpy(cards->color, deck[counter].color);
		cards->value = deck[counter].value;
	}
	cards->pt = nextCard; // makes the next card(pt) equal to NULL
}

void card_After(card* cards, card* newCards) { // used from zyBooks to make the card point to the card afterwards using a temp variable
	card* tempNxt = NULL;
	tempNxt = cards->pt;
	cards->pt = newCards;
	newCards->pt = tempNxt;
}

void card_Print(card* thisnode, card* headNode) { // used from zyBooks but modified to print out ascii art of the cards, as well as used colored text to print out to make it more readable when playing. 
	thisnode = headNode;
	int lols = 1; 
	while (thisnode != NULL) {
			if (thisnode->value == 2) {
				printf("\n----------" "Card %d: anycolor 2\n", lols);
				printf("|    A   |\n"
					   "|        |\n"
					   "|        |\n"
					   "|    2   |\n"
					   "|        |\n"
				       "----------\n");
			}
			else if (thisnode->value == 11) {
				if (strcmp(thisnode->color, "green") == 0) {
					printf("\n----------" RESET GREEN "Card %d: %s #\n" RESET, lols, thisnode->color);
					printf("|    G   |\n"
						   "|        |\n"
						   "|        |\n"
						   "|    #   |\n"
						   "|        |\n"
						   "----------\n");
				}
				else if (strcmp(thisnode->color, "red") == 0) {
					printf("\n----------" RESET RED "Card %d: %s #\n" RESET, lols, thisnode->color);
					printf("|    R   |\n"
						   "|        |\n"
						   "|        |\n"
						   "|    #   |\n"
						   "|        |\n"
						   "----------\n");
				}
				else if (strcmp(thisnode->color, "blue") == 0) {
					printf("\n----------" RESET BLUE "Card %d: %s #\n" RESET, lols, thisnode->color);
					printf("|    B   |\n"
						   "|        |\n"
						   "|        |\n"
						   "|    #   |\n"
						   "|        |\n"
						   "----------\n");
				}
				else if (strcmp(thisnode->color, "yellow") == 0) {
					printf("\n----------" RESET YELLOW "Card %d: %s #\n" RESET, lols, thisnode->color);
					printf("|    Y   |\n"
						   "|        |\n"
						   "|        |\n"
						   "|    #   |\n"
						   "|        |\n"
						   "----------\n");
				}
			}
			else if (thisnode->value == 10) {
				if (strcmp(thisnode->color, "green") == 0) {
					printf("\n----------" RESET GREEN "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    G   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d  |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
				else if (strcmp(thisnode->color, "red") == 0) {
					printf("\n----------" RESET RED "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    R   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d  |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
				else if (strcmp(thisnode->color, "blue") == 0) {
					printf("\n----------" RESET BLUE "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    B   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d  |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
				else if (strcmp(thisnode->color, "yellow") == 0) {
					printf("\n----------" RESET YELLOW "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    Y   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d  |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
			}
			else {
				if (strcmp(thisnode->color, "green") == 0) {
					printf("\n----------" RESET GREEN "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    G   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d   |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
				else if (strcmp(thisnode->color, "red") == 0) {
					printf("\n----------" RESET RED "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    R   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d   |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
				else if (strcmp(thisnode->color, "blue") == 0) {
					printf("\n----------" RESET BLUE "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    B   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d   |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
				else if (strcmp(thisnode->color, "yellow") == 0) {
					printf("\n----------" RESET YELLOW "Card %d: %s %d\n" RESET, lols, thisnode->color, thisnode->value);
					printf("|    Y   |\n"
						   "|        |\n"
				           "|        |\n"
						   "|    %d   |\n"
						   "|        |\n"
						   "----------\n", thisnode->value);
				}
			}
			thisnode = thisnode->pt;
			lols = lols + 1;
		}
	thisnode = headNode;
	printf("\n");
}

int card_Count(card* thisnode, card* headNode) { //keeps a counter that increments each time the for loop is run, and will run from the first card tll the last card, thus giving the card count
	int count = 0;
	thisnode = headNode;
	if (headNode != NULL) {
		if ((headNode->value <= 11) && (headNode->value >= 1)) {
			if (thisnode != NULL) {
				while (thisnode != NULL) {
					count = count + 1;
					thisnode = thisnode->pt;
				}
			}
		}
	}
	return count;
}

void card_LastNode(card** thisnode, card** headnode, card** lastnode) { //this function iterates through the linked list to find the new last element and makes lastnode equal to that element
	*thisnode = *headnode;
	while ((*thisnode)->pt != NULL) {
		*thisnode = (*thisnode)->pt;
	}
	*lastnode = *thisnode;
	*thisnode = *headnode;
}

void card_CreateLoopHand(card* thisNode, card* lastNode, card* thisNode2, card* lastNode2, card* headNode, card* headNode2, card deck[], card* nextCard, int* counter, int loopNum) { // used the base code from 10.6 on zyBooks, but modified it to be a loop so it would be modular
	for (int i = 0; i < loopNum; i++) { // put them both into the same function so that the cards that they draw will be alternating, player 1 gets the first card, then player 2 gets the second and so on.
		thisNode = (card*)malloc(sizeof(card));
		thisNode2 = (card*)malloc(sizeof(card));
		card_Create(thisNode, deck, NULL, (*counter));
		card_After(lastNode, thisNode);
		card_Create(thisNode2, deck, NULL, (*counter) - 1);
		card_After(lastNode2, thisNode2);
		lastNode = thisNode;
		lastNode2 = thisNode2;
		*counter = (*counter) - 2;
		thisNode = (card*)malloc(sizeof(card));
		thisNode2 = (card*)malloc(sizeof(card));
	}
}

void card_CreateLoop(card* thisNode, card* lastNode, card* headnode, card deck[], card* nextCard, int* counter, int loopNum) { // used this for the center cards because they are only 1 not 2.
	for (int i = 0; i < loopNum; i++) {
		thisNode = (card*)malloc(sizeof(card));
		card_Create(thisNode, deck, NULL, *counter);
		card_After(lastNode, thisNode);
		lastNode = thisNode;
		*counter = *counter - 1;
		thisNode = (card*)malloc(sizeof(card));
	}
}

bool card_GetMatch(card* thisnode, int cardValue, int cardValue2, char card1Col[], char card2Col[], int* singleMatch, int* doubleMatch, int howMany) { // just a bunch of if statements to check if the cards equal the center card, and if they do, checks if there is a single or double match
	int trueOrNah = 0;
	if (howMany == 1) {
		if (thisnode->value == 11) {
			trueOrNah = 1;
			if (cardValue == 2) {
				*singleMatch = *singleMatch + 1;
			}
		}
		else if ((cardValue == 2) && (thisnode->value == 2)) {
			trueOrNah = 1;
		}
		else if (cardValue == 11) {
			trueOrNah = 1;
		}
		else if (cardValue == thisnode->value) {
			trueOrNah = 1;
		}
		if ((strcmp(card1Col, thisnode->color) == 0) && (trueOrNah == 1)) {
			*singleMatch = *singleMatch + 1;
		}
		else if ((thisnode->value == 2) && (trueOrNah == 1)) {
			*singleMatch = *singleMatch + 1;
		}
	}
	else if (howMany == 2) {
		if (thisnode->value == 11) {
			if ((cardValue != 11) && (cardValue2 != 11)) {
				if (((cardValue + cardValue2)) < 11) {
					trueOrNah = 1;
				}
			}
		}
		if ((cardValue == 11) || (cardValue2 == 11)) {
			if (((cardValue + cardValue2) - 11) < thisnode->value) {
				trueOrNah = 1;
				if (thisnode->value == 2) {
					*doubleMatch = *doubleMatch + 1;
				}
			}
		}
		if ((cardValue == 11) && (cardValue2 == 11)) {
			if (thisnode->value >= 2) {
				trueOrNah = 1;
			}
		}
		if ((cardValue + cardValue2) == thisnode->value) {
			trueOrNah = 1;
			if (thisnode->value == 2) {
				*doubleMatch = *doubleMatch + 1;
			}
		}
		if ((cardValue != 2) && (cardValue2 != 2)) {
			if ((strcmp(card1Col, thisnode->color) == 0) && (strcmp(card2Col, thisnode->color)) == 0) {
				*doubleMatch = *doubleMatch + 1;
			}
		}
		if ((cardValue == 2) || (cardValue2 == 2)) {
			if ((cardValue == 2) && (cardValue2 == 2)) {
				*doubleMatch = *doubleMatch + 1;
			}
			else if ((cardValue2 == 2) && (strcmp(card1Col, thisnode->color) == 0)) {
				*doubleMatch = *doubleMatch + 1;
			}
			else if ((cardValue == 2) && (strcmp(card2Col, thisnode->color) == 0)) {
				*doubleMatch = *doubleMatch + 1;
			}
		}
	}
	return trueOrNah;
}

void card_ReleaseCenter(card** thisnode, card** headnode, card** lastnode, int* card1) { // made this specifically for the center card because it takes in a pointer for card1 because it uses the variable currentCard, so it needs to decrease it based on if it removes a card
	card* tmp = { 0 }; 
	if (*card1 == 1) { 
		tmp = *headnode; 
		*headnode = (*headnode)->pt;
		free(tmp);
		*card1 = 1;
	}
	else if (*card1 != 1) {
		*thisnode = *headnode;
		for (int i = 1; i < *card1 - 1; ++i) {
			*thisnode = (*thisnode)->pt;
		}
		tmp = (*thisnode)->pt;
		(*thisnode)->pt = (*thisnode)->pt->pt;
		free(tmp);
	}
	*thisnode = *headnode;
	if (*card1 != 1) {
		while ((*thisnode)->pt != NULL) {
			*thisnode = (*thisnode)->pt;
		}
	}
	*lastnode = *thisnode;
}

void card_Release(card** thisnode, card** headnode, card** lastnode, int card1) { // uses a double pointer because when I use one pointer and call this function in other functions, it would return the pointer value as uninitalized and mess up.
	card* tmp = { 0 }; // to remove card  2 with this function for example, it will get to card 1, then assign a variable to card 1, make card 1 point to card 3, then free the memory for card 2.
	if (card_Count(*thisnode, *headnode) == 1) { // if card1  is to be removed, I need to move the headnode to point to card 2 and release the first card using a temporary variable.
		*headnode = NULL;
	}
	else if (card1 == 1) {
		tmp = *headnode;
		if ((*headnode)->pt != NULL) {
			*headnode = (*headnode)->pt;
		}
		free(tmp);
		card1 = 1;
	}
	else if (card1 != 1) {
		*thisnode = *headnode;
		for (int i = 1; i < card1 - 1; ++i) {
			*thisnode = (*thisnode)->pt;
		}
		tmp = (*thisnode)->pt;
		(*thisnode)->pt = (*thisnode)->pt->pt;
		free(tmp);
	}
	*thisnode = *headnode;
	if (card_Count(*thisnode, *headnode) == 0) {
		return;
	}
	if ((*thisnode) == NULL) {

	}
	else if ((*thisnode)->pt != NULL) {
		while ((*thisnode)->pt != NULL) {
			*thisnode = (*thisnode)->pt;
		}
	}
	*lastnode = *thisnode;
}

card* card_GetCard(card* thisnode, card* headnode, int card1) { // this function returns a pointer to a card in a specific location. I use this to get to a specific card to then add it to center.
	thisnode = headnode;
	card* tmp = { 0 };
	for (int i = 1; i < card1; ++i) {
		if (thisnode->pt != NULL) {
			thisnode = thisnode->pt;
		}
	}
	tmp = thisnode;
	thisnode = headnode;
	return tmp;
}

int card_GetPoints(card* thisnode, card* headnode) { // this function is called at the end of the round when the points need to be tallied. It has # as 40 points, 2's as 20 points, and any other card as its face value.
	int cardTotal = 0;
	thisnode = headnode;
	if (thisnode != NULL) {
		while (thisnode->pt != NULL) {
			if (thisnode->value == 11) {
				cardTotal = cardTotal + 40;
			}
			else if (thisnode->value == 2) {
				cardTotal = cardTotal + 20;
			}
			else {
				cardTotal = cardTotal + thisnode->value;
			}
			thisnode = thisnode->pt;
		}
	}
	if (thisnode->pt == NULL) {
		if (thisnode->value == 11) {
			cardTotal = cardTotal + 40;
		}
		else if (thisnode->value == 2) {
			cardTotal = cardTotal + 20;
		}
		else {
			cardTotal = cardTotal + thisnode->value;
		}
	}
	return cardTotal;
}

void card_Matches(card** thisnode, card** headnode, card** lastnode, card** thisnode2, card** headnode2, card** lastnode2, card** thisnode3, card** headnode3, card** lastnode3, card deck[], int* singleMatch, int* doubleMatch, int* counter, int* currentCard, int turnCount, int howMany, int playerCount) {
	int card1 = 0; // just put this into a function because it is called multiple times throughout and would be too large a chunk of code to leave outside of a function.
	if ((*singleMatch != 0) || (*doubleMatch != 0)) { // it checks if there is a singlecard match or a doublecard match, and if there is, it asks the user to put one of their cards to the middle, and if there is a double match, it makes everyone draw
		if (*singleMatch != 0) {
			for (int i = *singleMatch; i > 0; i--) {
				card temp[1] = { 0 };
				int tmp = 0;
				printf("You single matched %d card(s). Select a card from 1-%d to put in the center.\n", *singleMatch, card_Count(*thisnode, *headnode));
				card_Print(*thisnode, *headnode);
				scanf("%d", &card1);
				strcpy(temp[0].color, card_GetCard(*thisnode, *headnode, card1)->color), temp[0].value = card_GetCard(*thisnode, *headnode, card1)->value; // gets card in position that user specifies
				card_Release(thisnode, headnode, lastnode, card1); // releases the card upon putting it into temp
				if (card_Count(*thisnode, *headnode) == 0) {
					return;
				}
				card_LastNode(thisnode, headnode, lastnode);
				card_LastNode(thisnode2, headnode2, lastnode2), card_CreateLoop(*thisnode2, *lastnode2, *headnode2, temp, NULL, &tmp, 1); // will add the temporary value to the center, thus moving it from the player's hand to the center.
				card_LastNode(thisnode, headnode, lastnode), card_LastNode(thisnode2, headnode2, lastnode2); // makes lastnode point to the last card in the center row.
			}
		}
		if (*doubleMatch != 0) {
			for (int i = *doubleMatch; i > 0; i--) {
				card temp[1] = { 0 };
				int tmp = 0;
				printf("You double matched %d card(s). Select a card from 1-%d to put in the center.\n", *doubleMatch, card_Count(*thisnode, *headnode));
				card_Print(*thisnode, *headnode);
				scanf("%d", &card1);
				strcpy(temp[0].color, card_GetCard(*thisnode, *headnode, card1)->color), temp[0].value = card_GetCard(*thisnode, *headnode, card1)->value; // gets card in position that user specifies
				card_Release(thisnode, headnode, lastnode, card1); // releases the card upon putting it into temp
				if (card_Count(*thisnode, *headnode) == 0) {
					return;
				}
				card_LastNode(thisnode, headnode, lastnode);
				card_LastNode(thisnode2, headnode2, lastnode2), card_CreateLoop(*thisnode2, *lastnode2, *headnode2, temp, NULL, &tmp, 1); // will add the temporary value to the center, thus moving it from the player's hand to the center.
				card_LastNode(thisnode, headnode, lastnode), card_LastNode(thisnode2, headnode2, lastnode2); // makes lastnode point to the last card in the center row.
			}
		}
	}
}

void card_Draw(card* thisnode, card* headnode, card* lastnode, card deck[], int* counter, int* doubleMatch) {
	for (int i = *doubleMatch; i > 0; --i) {
		card_CreateLoop(thisnode, lastnode, headnode, deck, NULL, counter, 1); // just makes each player draw x amount of cards when x amount of doublematches happen
	}
}

int main() {
	int userIn, playerPoints1 = 0, playerPoints2 = 0, playerPoints3 = 0, playerPoints4 = 0, playerCount = 0;
	char userPress = 0, userPlay = 0;
	FILE* inp = NULL;
	printf("Let's Play a Game of DOS\n");
	printf("Press 1 to shuffle the DOS deck or 2 to load a deck from a file:\n");
	scanf("%d", &userIn);
	card DeckOfCards[108], centerCard = {}, playedCard[2] = {};
	int counter = 107;
	if (userIn == 1) {
		createDeck(DeckOfCards); // if the user wants to shuffle the deck, it will create a deck of cards using the template in the function
	}
	else if (userIn == 2) { // if the user wants to load from a file, it checks if the file exists. If it does, it will load from that file, and if not, it will exit the function.
		char userInFile[100];
		printf("Please enter the file name to load from (max of 100 characters)\n");
		scanf("%s", userInFile);
		inp = fopen(userInFile, "r");
		if (inp != NULL) {
			counter = createDeckFile(DeckOfCards, inp);
		}
		else {
			printf("Error: File not found!");
			return 0;
		}
	}
	printf("Enter the number of players (2-4).\n");
	scanf("%d", &playerCount);

	while ((playerPoints1 < 200) && (playerPoints2 < 200) && (playerPoints3 < 200) && (playerPoints4 < 200)) { // function will keep running till a player gets to 200 points!
		if (userIn == 1) {
			counter = 107; // resets the counter to the first card
		}
		else {
			counter = createDeckFile(DeckOfCards, inp); // resets the counter to the number returned by the function, incase testing with less cards
		}
		if ((playerPoints1 == 0) && (playerPoints2 == 0) && (playerPoints3 == 0) && (playerPoints4 == 0)) { // if it is the first round, it will say lets play a round, else it will say that the total has not been met
			printf("Let's play a round of DOS!\n");
		}
		else {
			printf("\nPoint totals not met! Let's play another round of DOS!\n");
		}
		if (userIn == 1) { // will randomize the deck after each round if the user has not selected load from file
			randomizeDeck(DeckOfCards);
		}
		printf("The deck is shuffled. Enter any key to deal cards\n");
		scanf(" %c", &userPress);
		int playerCardCount1, playerCardCount2, playerCardCount3 = 1, playerCardCount4 = 1, centerCardCount = 1, currentCardCount = 0, turnCount = 0, currentCard = 1, drawCount = 0;
		card* headObj = NULL, * headObj2 = NULL, * headObj3 = NULL, * headObj4 = NULL, * headObj5 = NULL; // headObj is plyer 1, headObj2 is player 2, headObj3 is the center, headObj4 is player 3, and headObj5 is player 4.
		card* currObj = NULL, * currObj2 = NULL, * currObj3 = NULL, * currObj4 = NULL, * currObj5 = NULL;
		card* lastObj = NULL, * lastObj2 = NULL, * lastObj3 = NULL, * lastObj4 = NULL, * lastObj5 = NULL;
		headObj = (card*)malloc(sizeof(card));
		headObj2 = (card*)malloc(sizeof(card));
		card_Create(headObj, DeckOfCards, NULL, counter);
		lastObj = headObj;
		counter = counter - 1;
		card_Create(headObj2, DeckOfCards, NULL, counter);
		lastObj2 = headObj2;
		counter = counter - 1;
		card_CreateLoopHand(currObj, lastObj, currObj2, lastObj2, headObj, headObj2, DeckOfCards, NULL, &counter, 6);
		headObj3 = (card*)malloc(sizeof(card));
		lastObj3 = headObj3;
		card_Create(headObj3, DeckOfCards, NULL, counter);
		lastObj3 = headObj3;
		counter = counter - 1; // will initalize player 1 and 2 but will wait to see if there will be 3 or 4 players to initailize their linked lists.
		if (playerCount >= 3) {
			headObj4 = (card*)malloc(sizeof(card));
			card_Create(headObj4, DeckOfCards, NULL, counter);
			lastObj4 = headObj4;
			counter = counter - 1;
			if (playerCount >= 4) {
				headObj5 = (card*)malloc(sizeof(card));
				card_Create(headObj5, DeckOfCards, NULL, counter);
				lastObj5 = headObj5;
				counter = counter - 1;
				card_CreateLoopHand(currObj4, lastObj4, currObj5, lastObj5, headObj4, headObj5, DeckOfCards, NULL, &counter, 6);
			}
			else {
				card_CreateLoop(currObj4, lastObj4, headObj4, DeckOfCards, NULL, &counter, 6);
			}
		}
		card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
		centerCardCount = card_Count(currObj3, headObj3);
		playerCardCount1 = card_Count(currObj, headObj);
		playerCardCount2 = card_Count(currObj2, headObj2);
		currObj3 = headObj3;
		while ((counter > 0) && (playerCardCount1 > 0) && (playerCardCount2 > 0) && (playerCardCount3 > 0) && (playerCardCount4 > 0)) { // will keep running till a player runs out of cards or the deck runs out of cards
			int howMany = 0, card1 = 0, card2 = 0, card1Val = 0, card2Val = 0, trueOrFalse = 0, stop = 0, singleMatch = 0, doubleMatch = 0, checker = 0, endTurn = 0;
			char card1Col[10], card2Col[10];
			char comma;
			while ((turnCount % playerCount == 0) && (playerCardCount1 != 0) && (playerCardCount2 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
				printf("Player 1's cards: ");
				card_Print(currObj, headObj);
				printf("Centerline ");
				card_Print(currObj3, headObj3);
				currObj3 = headObj3;
				for (int i = 1; i < currentCard; ++i) {
					if (currObj3->pt != NULL) {
						currObj3 = currObj3->pt;
					}
				}
				if (currObj3->value == 11) {
					if (strcmp(currObj3->color, "green") == 0) {
						printf(RESET "How many cards do you want to play on " GREEN "%s # " RESET "(0, 1, or 2):", currObj3->color); // asks the user to place cards on the center card, and prints it out in color for readability
					}
					else if (strcmp(currObj3->color, "blue") == 0) {
						printf(RESET "How many cards do you want to play on " BLUE"%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
					else if (strcmp(currObj3->color, "yellow") == 0) {
						printf(RESET "How many cards do you want to play on " YELLOW "%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
					else if (strcmp(currObj3->color, "red") == 0) {
						printf(RESET "How many cards do you want to play on " RED "%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
				}
				else if (currObj3->value == 2) {
					printf(RESET "How many cards do you want to play on anycolor 2 (0, 1, or 2):");
				}
				else {
					if (strcmp(currObj3->color, "green") == 0) {
						printf(RESET "How many cards do you want to play on " GREEN "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
					else if (strcmp(currObj3->color, "blue") == 0) {
						printf(RESET "How many cards do you want to play on " BLUE "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
					else if (strcmp(currObj3->color, "yellow") == 0) {
						printf(RESET "How many cards do you want to play on " YELLOW "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
					else if (strcmp(currObj3->color, "red") == 0) {
						printf(RESET "How many cards do you want to play on " RED "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
				}
				printf(RESET);
				scanf(" %d", &howMany);
				if (howMany == 1) {
					printf("Select a card from 1-%d:", card_Count(currObj, headObj)); // asks the user for cards based on their input from above
					scanf("%d", &card1);
					card2 = 0;
				}
				if (howMany == 2) {
					printf("Select two cards from 1-%d (x,y):", card_Count(currObj, headObj));
					scanf(" %d%c%d", &card1, &comma, &card2);
				}
				if (howMany == 0) { // if the player wishes to not play any cards, it will check if it is the last card in the center row. If it is, it will proceed to card matches, otherwise it will move on to the next center card.
					if ((card_Count(currObj3, headObj3) == 0) || (currentCard == card_Count(currObj3, headObj3))) {
						if ((card_Count(currObj3, headObj3) == 0)) {
							printf("There are no more center cards, ending turn.\n");
						}
						if (((doubleMatch == 0) && (singleMatch == 0)) && (drawCount == 0)) {
						}
						else {
							if ((card_Count(currObj3, headObj3) < 2)) {
								if (card_Count(currObj3, headObj3) == 0) {
									headObj3 = (card*)malloc(sizeof(card));
									card_Create(headObj3, DeckOfCards, NULL, counter);
									lastObj3 = headObj3;
									counter = counter - 1;
									card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 2);
									currentCard = 2;
								}
								else {
									card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
									currentCard = 2;
								}
							}
							card_Matches(&currObj, &headObj, &lastObj, &currObj3, &headObj3, &lastObj3, &currObj2, &headObj2, &lastObj2, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount + 1, howMany, playerCount);
							if (doubleMatch > 0) {
								printf("Dealing %d card(s) to other players.\n", doubleMatch);
								card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch); // if there is double mathces it will make the other players draw
								if (playerCount >= 3) { // will only make the other players draw if they are activated
									card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
									if (playerCount >= 4) {
										card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
									}
								}
							}
						}
						if ((currentCard) < card_Count(currObj3, headObj3)) { 
							turnCount = turnCount + 1;
							endTurn = 1;
						}
					}
					if ((currentCard) < card_Count(currObj3, headObj3)) { // checks the status of wether or not we are at the end of the cards, or if we need to move on to the next card
						currentCard = currentCard + 1;
					}
					else if ((currentCard) > card_Count(currObj3, headObj3)) {
						turnCount = turnCount + 1;
						endTurn = 1;
					}
					else if ((card_Count(currObj3, headObj3)) == currentCard) {
						turnCount = turnCount + 1;
						endTurn = endTurn + 1;;
						currentCard = 1;

					}
				}
				if (howMany != 0) { // if we are playing a card on the center card, it will then grab the inputs that the player inputted and assign them to variables
					currObj = headObj;
					for (int i = 0; i < card1 - 1; ++i) {
						currObj = currObj->pt;
					}
					card1Val = currObj->value;
					strcpy(card1Col, currObj->color);
					currObj = headObj;
					for (int i = 0; i < card2 - 1; ++i) {
						currObj = currObj->pt;
					}
					card2Val = currObj->value;
					strcpy(card2Col, currObj->color);
					if (howMany == 1) {
						card2Val = 0;
					}
					trueOrFalse = card_GetMatch(currObj3, card1Val, card2Val, card1Col, card2Col, &singleMatch, &doubleMatch, howMany); // checks if the cards the user gave equals up to the center card
					if (trueOrFalse == 0) {
						printf("The selection does not total to the center row card. Select again\n"); // repeats the function and asks the user for another card
					}
					if ((trueOrFalse == 1)) {
						if (howMany == 2) {
							currObj = headObj;
							card_Release(&currObj, &headObj, &lastObj, card2); // if the cards equal up, then the user's cards are removed from the linked list
							card_Release(&currObj, &headObj, &lastObj, card1);
							if (headObj == NULL) {
								playerCardCount1 = 0;
							}
							else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) { // if there is only one card left in the center row, it will first add a card before removing to avoid the center uninitailzing
								turnCount = turnCount + 1;
								endTurn = endTurn + 1;
								if (card_Count(currObj3, headObj3) == 0) {
									printf("There are no more center cards, ending turn.\n");
								}
								if ((doubleMatch == 0) && (singleMatch == 0)) {
								}
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								if ((doubleMatch != 0) || (singleMatch != 0)) {
									if ((card_Count(currObj3, headObj3) < 2)) {
										if (card_Count(currObj3, headObj3) == 0) {
											headObj3 = (card*)malloc(sizeof(card));
											card_Create(headObj3, DeckOfCards, NULL, counter);
											lastObj3 = headObj3;
											counter = counter - 1;
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
										else {
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1); // replenishes the center row before puting the users cards to the middle
											currentCard = 2;
										}
									}
									card_Matches(&currObj, &headObj, &lastObj, &currObj3, &headObj3, &lastObj3, &currObj2, &headObj2, &lastObj2, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
									if (doubleMatch > 0) { // will check for double and single matches and add the respective amount of cards to other players
										printf("Dealing %d card(s) to other players.\n", doubleMatch);
										card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
										if (playerCount >= 3) {
											card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
											if (playerCount >= 4) {
												card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
								}
							}
							else {
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard); // if there is more than one card, then it will just remove it
								checker = 1;
							}
							drawCount = drawCount + 1; // since the user succesfully matched a card, drawcount increments so the user will not draw a card at the end of the round
						}
						else if (howMany == 1) { // repeats the same thing but only releases one card instead of two this time.
							currObj = headObj;
							card_Release(&currObj, &headObj, &lastObj, card1);
							if (headObj == NULL) {
								playerCardCount1 = 0;
							}
							else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
								checker = 1;
								turnCount = turnCount + 1;
								endTurn = endTurn + 1;
								if (card_Count(currObj3, headObj3) == 0) {
									printf("There are no more center cards, ending turn.\n");
								}
								if ((doubleMatch == 0) && (singleMatch == 0)) {
								}
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								if ((doubleMatch != 0) || (singleMatch != 0)) {
									if ((card_Count(currObj3, headObj3) < 2)) {
										if (card_Count(currObj3, headObj3) == 0) {
											headObj3 = (card*)malloc(sizeof(card));
											card_Create(headObj3, DeckOfCards, NULL, counter);
											lastObj3 = headObj3;
											counter = counter - 1;
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
										else {
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
									}
									card_Matches(&currObj, &headObj, &lastObj, &currObj3, &headObj3, &lastObj3, &currObj2, &headObj2, &lastObj2, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
									if (doubleMatch > 0) {
										printf("Dealing %d card(s) to other players.\n", doubleMatch);
										card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
										if (playerCount >= 3) {
											card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
											if (playerCount >= 4) {
												card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
								}
							}
							else {
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								checker = 1;
							}
							drawCount = drawCount + 1;
						}
						if (card_Count(currObj3, headObj3) == 1) {
							if (currentCard > card_Count(currObj3, headObj3)) {
								currentCard = 1;
							}
							else if (card_Count(currObj3, headObj3) != 1) {
								if (currObj3 = headObj3) {
									currentCard = 1;
								}
								else if (checker != 1) {
									currentCard = currentCard + 1;
								}
							}
						}
						else if ((card_Count(currObj3, headObj3) != 1) && (checker != 1)) {
							currentCard = currentCard + 1;
						}

					}
				}
				if (endTurn == 1) { // checks if it is the users first rotation through and if they have not played a card. if they have not, they will draw and then run through the center cards again to try and match.
					if (turnCount % playerCount != 0) {
						if (drawCount == 0) {
							card_LastNode(&currObj, &headObj, &lastObj);
							card_CreateLoop(currObj, lastObj, headObj, DeckOfCards, NULL, &counter, 1);
							counter = counter - 1;
							card_LastNode(&currObj, &headObj, &lastObj);
							if (lastObj->value == 11) {
								printf("You drew the card %s #.\n", lastObj->color);
							}
							else {
								printf("You drew the card %s %d.\n", lastObj->color, lastObj->value);
							}
							turnCount = turnCount - 1;
							currentCard = 1;
						}
					}
				}
				else if (endTurn == 2) { // if they still didnt match a car the second time around, it asks the user to place one of their cards to the center
					if (drawCount == 0) {
						card temp[1] = { 0 };
						int tmp = 0;
						drawCount = 0;
						printf("Place one of your cards to the middle 1-%d: ", card_Count(currObj, headObj)), card_Print(currObj, headObj);
						scanf("%d", &card1);
						strcpy(temp[0].color, card_GetCard(currObj, headObj, card1)->color), temp[0].value = card_GetCard(currObj, headObj, card1)->value;
						card_Release(&currObj, &headObj, &lastObj, card1), card_LastNode(&currObj, &headObj, &lastObj);
						card_LastNode(&currObj3, &headObj3, &lastObj3), card_CreateLoop(currObj3, lastObj3, headObj3, temp, NULL, &tmp, 1);
						card_LastNode(&currObj3, &headObj3, &lastObj3), card_LastNode(&currObj3, &headObj3, &lastObj3);
					}
				}
				if (turnCount % playerCount != 0) { // if the turn is over, it replenishes the center row if it is empty or missing cards and then moves on
					if ((card_Count(currObj3, headObj3) < 2)) {
						if (card_Count(currObj3, headObj3) == 0) {
							headObj3 = (card*)malloc(sizeof(card));
							card_Create(headObj3, DeckOfCards, NULL, counter);
							lastObj3 = headObj3;
							counter = counter - 1;
							card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
						}
						else {
							card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, (2 - card_Count(currObj3, headObj3)));
						}
					}
				}
				if (headObj == NULL) { // if the user no longer has cards, it makes the count equal to 0
					playerCardCount1 = 0;
				}
			}
			if ((playerCardCount1 != 0) && (playerCardCount2 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) { // checks if any players have won the round, otherwise it will printout player 1's hand and end player 1's turn.
				if (card_Count(currObj, headObj) != 0) {
					printf("Player 1's hand: "), card_Print(currObj, headObj);
					printf("Player 2's turn.\n");
					centerCardCount = card_Count(currObj3, headObj3); // updates the count of the center
					drawCount = 0; // resets all the variables to 0 for the next player
					singleMatch = 0;
					doubleMatch = 0;
					currentCard = 1;
					endTurn = 0;
				}
				if (headObj != NULL) { // if headObj is not null, it makes the count equal what the count is, otherwise it makes it 0 becasue the function would otherwise error
					playerCardCount1 = card_Count(currObj, headObj);
				}
				else if (headObj == NULL) {
					playerCardCount1 = 0;
				}
			}

			while ((turnCount % playerCount == 1) && (playerCardCount2 != 0) && (playerCardCount1 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) { // repeats the same but using the variables for player 2
				printf("Player 2's cards: ");
				card_Print(currObj2, headObj2);
				printf("Centerline ");
				card_Print(currObj3, headObj3);
				currObj3 = headObj3;
				for (int i = 1; i < currentCard; ++i) {
					if (currObj3->pt != NULL) {
						currObj3 = currObj3->pt;
					}
				}
				if (currObj3->value == 11) {
					if (strcmp(currObj3->color, "green") == 0) {
						printf(RESET "How many cards do you want to play on " GREEN "%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
					else if (strcmp(currObj3->color, "blue") == 0) {
						printf(RESET "How many cards do you want to play on " BLUE"%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
					else if (strcmp(currObj3->color, "yellow") == 0) {
						printf(RESET "How many cards do you want to play on " YELLOW "%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
					else if (strcmp(currObj3->color, "red") == 0) {
						printf(RESET "How many cards do you want to play on " RED "%s # " RESET "(0, 1, or 2):", currObj3->color);
					}
				}
				else if (currObj3->value == 2) {
					printf(RESET "How many cards do you want to play on anycolor 2 (0, 1, or 2):");
				}
				else {
					if (strcmp(currObj3->color, "green") == 0) {
						printf(RESET "How many cards do you want to play on " GREEN "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
					else if (strcmp(currObj3->color, "blue") == 0) {
						printf(RESET "How many cards do you want to play on " BLUE "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
					else if (strcmp(currObj3->color, "yellow") == 0) {
						printf(RESET "How many cards do you want to play on " YELLOW "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
					else if (strcmp(currObj3->color, "red") == 0) {
						printf(RESET "How many cards do you want to play on " RED "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
					}
				}
				printf(RESET);
				scanf(" %d", &howMany);
				if (howMany == 1) {
					printf("Select a card from 1-%d:", card_Count(currObj2, headObj2));
					scanf("%d", &card1);
					card2 = 0;
				}
				if (howMany == 2) {
					printf("Select two cards from 1-%d (x,y):", card_Count(currObj2, headObj2));
					scanf(" %d%c%d", &card1, &comma, &card2);
				}
				if (howMany == 0) {
					if ((card_Count(currObj3, headObj3) == 0) || (currentCard == card_Count(currObj3, headObj3))) {
						if ((card_Count(currObj3, headObj3) == 0)) {
							printf("There are no more center cards, ending turn.\n");
						}
						if (((doubleMatch == 0) && (singleMatch == 0)) && (drawCount == 0)) {
						}
						else {
							if ((card_Count(currObj3, headObj3) < 2)) {
								if (card_Count(currObj3, headObj3) == 0) {
									headObj3 = (card*)malloc(sizeof(card));
									card_Create(headObj3, DeckOfCards, NULL, counter);
									lastObj3 = headObj3;
									counter = counter - 1;
									card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 2);
									currentCard = 2;
								}
								else {
									card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
									currentCard = 2;
								}
							}
							card_Matches(&currObj2, &headObj2, &lastObj2, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount + 1, howMany, playerCount);
							if (doubleMatch > 0) {
								printf("Dealing %d card(s) to other players.\n", doubleMatch);
								card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
								if (playerCount >= 3) {
									card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
									if (playerCount >= 4) {
										card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
									}
								}
							}
						}
						if ((currentCard) < card_Count(currObj3, headObj3)) {
							turnCount = turnCount + 1;
							endTurn = 1;
						}
					}
					if ((currentCard) < card_Count(currObj3, headObj3)) {
						currentCard = currentCard + 1;
					}
					else if ((currentCard) > card_Count(currObj3, headObj3)) {
						turnCount = turnCount + 1;
						endTurn = 1;
					}
					else if ((card_Count(currObj3, headObj3)) == currentCard) {
						turnCount = turnCount + 1;
						endTurn = endTurn + 1;;
						currentCard = 1;

					}
				}
				if (howMany != 0) {
					currObj2 = headObj2;
					for (int i = 0; i < card1 - 1; ++i) {
						currObj2 = currObj2->pt;
					}
					card1Val = currObj2->value;
					strcpy(card1Col, currObj2->color);
					currObj2 = headObj2;
					for (int i = 0; i < card2 - 1; ++i) {
						currObj2 = currObj2->pt;
					}
					card2Val = currObj2->value;
					strcpy(card2Col, currObj2->color);
					if (howMany == 1) {
						card2Val = 0;
					}
					trueOrFalse = card_GetMatch(currObj3, card1Val, card2Val, card1Col, card2Col, &singleMatch, &doubleMatch, howMany);
					if (trueOrFalse == 0) {
						printf("The selection does not total to the center row card. Select again\n");
					}
					if ((trueOrFalse == 1)) {
						if (howMany == 2) {
							currObj2 = headObj2;
							card_Release(&currObj2, &headObj2, &lastObj2, card2);
							card_Release(&currObj2, &headObj2, &lastObj2, card1);
							if (headObj2 == NULL) {
								playerCardCount2 = 0;
							}
							else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
								turnCount = turnCount + 1;
								endTurn = endTurn + 1;
								if (card_Count(currObj3, headObj3) == 0) {
									printf("There are no more center cards, ending turn.\n");
								}
								if ((doubleMatch == 0) && (singleMatch == 0)) {
								}
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								if ((doubleMatch != 0) || (singleMatch != 0)) {
									if ((card_Count(currObj3, headObj3) < 2)) {
										if (card_Count(currObj3, headObj3) == 0) {
											headObj3 = (card*)malloc(sizeof(card));
											card_Create(headObj3, DeckOfCards, NULL, counter);
											lastObj3 = headObj3;
											counter = counter - 1;
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
										else {
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
									}

									card_Matches(&currObj2, &headObj2, &lastObj2, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
									if (doubleMatch > 0) {
										printf("Dealing %d card(s) to other players.\n", doubleMatch);
										card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
										if (playerCount >= 3) {
											card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
											if (playerCount >= 4) {
												card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
								}
							}
							else {
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								checker = 1;
							}
							drawCount = drawCount + 1;
						}
						else if (howMany == 1) {
							currObj2 = headObj2;
							card_Release(&currObj2, &headObj2, &lastObj2, card1);
							if (headObj2 == NULL) {
								playerCardCount2 = 0;
							}
							else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
								checker = 1;
								turnCount = turnCount + 1;
								endTurn = endTurn + 1;
								if (card_Count(currObj3, headObj3) == 0) {
									printf("There are no more center cards, ending turn.\n");
								}
								if ((doubleMatch == 0) && (singleMatch == 0)) {
								}
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								if ((doubleMatch != 0) || (singleMatch != 0)) {
									if ((card_Count(currObj3, headObj3) < 2)) {
										if (card_Count(currObj3, headObj3) == 0) {
											headObj3 = (card*)malloc(sizeof(card));
											card_Create(headObj3, DeckOfCards, NULL, counter);
											lastObj3 = headObj3;
											counter = counter - 1;
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
										else {
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
									}
									card_Matches(&currObj2, &headObj2, &lastObj2, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
									if (doubleMatch > 0) {
										printf("Dealing %d card(s) to other players.\n", doubleMatch);
										card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
										if (playerCount >= 3) {
											card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
											if (playerCount >= 4) {
												card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
								}
							}
							else {
								card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
								checker = 1;
							}
							drawCount = drawCount + 1;
						}
						if (card_Count(currObj3, headObj3) == 1) {
							if (currentCard > card_Count(currObj3, headObj3)) {
								currentCard = 1;
							}
							else if (card_Count(currObj3, headObj3) != 1) {
								if (currObj3 = headObj3) {
									currentCard = 1;
								}
								else if (checker != 1) {
									currentCard = currentCard + 1;
								}
							}
						}
						else if ((card_Count(currObj3, headObj3) != 1) && (checker != 1)) {
							currentCard = currentCard + 1;
						}

					}
				}
				if (endTurn == 1) {
					if (turnCount % playerCount != 1) {
						if (drawCount == 0) {
							card_LastNode(&currObj2, &headObj2, &lastObj2);
							card_CreateLoop(currObj2, lastObj2, headObj2, DeckOfCards, NULL, &counter, 1);
							counter = counter - 1;
							card_LastNode(&currObj2, &headObj2, &lastObj2);
							if (lastObj2->value == 11) {
								printf("You drew the card %s #.\n", lastObj2->color);
							}
							else {
								printf("You drew the card %s %d.\n", lastObj2->color, lastObj2->value);
							}
							turnCount = turnCount - 1;
							currentCard = 1;
						}
					}
				}
				else if (endTurn == 2) {
					if (drawCount == 0) {
						card temp[1] = { 0 };
						int tmp = 0;
						drawCount = 0;
						printf("Place one of your cards to the middle 1-%d: ", card_Count(currObj2, headObj2)), card_Print(currObj2, headObj2);
						scanf("%d", &card1);
						strcpy(temp[0].color, card_GetCard(currObj2, headObj2, card1)->color), temp[0].value = card_GetCard(currObj2, headObj2, card1)->value;
						card_Release(&currObj2, &headObj2, &lastObj2, card1), card_LastNode(&currObj2, &headObj2, &lastObj2);
						card_LastNode(&currObj3, &headObj3, &lastObj3), card_CreateLoop(currObj3, lastObj3, headObj3, temp, NULL, &tmp, 1);
						card_LastNode(&currObj3, &headObj3, &lastObj3), card_LastNode(&currObj3, &headObj3, &lastObj3);
					}
				}
				if (turnCount % playerCount != 1) {
					if ((card_Count(currObj3, headObj3) < 2)) {
						if (card_Count(currObj3, headObj3) == 0) {
							headObj3 = (card*)malloc(sizeof(card));
							card_Create(headObj3, DeckOfCards, NULL, counter);
							lastObj3 = headObj3;
							counter = counter - 1;
							card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
						}
						else {
							card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, (2 - card_Count(currObj3, headObj3)));
						}
					}
				}
				if (headObj2 == NULL) {
					playerCardCount2 = 0;
				}
			}
			if ((playerCardCount1 != 0) && (playerCardCount2 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
				if (card_Count(currObj2, headObj2) != 0) {
					printf("Player 2's hand: "), card_Print(currObj2, headObj2);
					if (playerCount >= 3) {
						printf("Player 3's turn.\n");
					}
					else {
						printf("Player 1's turn.\n");
					}
					centerCardCount = card_Count(currObj3, headObj3);
					drawCount = 0;
					singleMatch = 0;
					doubleMatch = 0;
					currentCard = 1;
					endTurn = 0;
				}
				if (headObj2 != NULL) {
					playerCardCount2 = card_Count(currObj2, headObj2);
				}
				else if (headObj2 == NULL) {
					playerCardCount2 = 0;
				}
			}

			if (playerCount >= 3) {
				while ((turnCount % playerCount == 2) && (playerCardCount2 != 0) && (playerCardCount1 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
					printf("Player 3's cards: ");
					card_Print(currObj4, headObj4);
					printf("Centerline ");
					card_Print(currObj3, headObj3);
					currObj3 = headObj3;
					for (int i = 1; i < currentCard; ++i) {
						if (currObj3->pt != NULL) {
							currObj3 = currObj3->pt;
						}
					}
					if (currObj3->value == 11) {
						if (strcmp(currObj3->color, "green") == 0) {
							printf(RESET "How many cards do you want to play on " GREEN "%s # " RESET "(0, 1, or 2):", currObj3->color);
						}
						else if (strcmp(currObj3->color, "blue") == 0) {
							printf(RESET "How many cards do you want to play on " BLUE"%s # " RESET "(0, 1, or 2):", currObj3->color);
						}
						else if (strcmp(currObj3->color, "yellow") == 0) {
							printf(RESET "How many cards do you want to play on " YELLOW "%s # " RESET "(0, 1, or 2):", currObj3->color);
						}
						else if (strcmp(currObj3->color, "red") == 0) {
							printf(RESET "How many cards do you want to play on " RED "%s # " RESET "(0, 1, or 2):", currObj3->color);
						}
					}
					else if (currObj3->value == 2) {
						printf(RESET "How many cards do you want to play on anycolor 2 (0, 1, or 2):");
					}
					else {
						if (strcmp(currObj3->color, "green") == 0) {
							printf(RESET "How many cards do you want to play on " GREEN "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
						}
						else if (strcmp(currObj3->color, "blue") == 0) {
							printf(RESET "How many cards do you want to play on " BLUE "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
						}
						else if (strcmp(currObj3->color, "yellow") == 0) {
							printf(RESET "How many cards do you want to play on " YELLOW "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
						}
						else if (strcmp(currObj3->color, "red") == 0) {
							printf(RESET "How many cards do you want to play on " RED "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
						}
					}
					printf(RESET);
					scanf(" %d", &howMany);
					if (howMany == 1) {
						printf("Select a card from 1-%d:", card_Count(currObj4, headObj4));
						scanf("%d", &card1);
						card2 = 0;
					}
					if (howMany == 2) {
						printf("Select two cards from 1-%d (x,y):", card_Count(currObj4, headObj4));
						scanf(" %d%c%d", &card1, &comma, &card2);
					}
					if (howMany == 0) {
						if ((card_Count(currObj3, headObj3) == 0) || (currentCard == card_Count(currObj3, headObj3))) {
							if ((card_Count(currObj3, headObj3) == 0)) {
								printf("There are no more center cards, ending turn.\n");
							}
							if (((doubleMatch == 0) && (singleMatch == 0)) && (drawCount == 0)) {
							}
							else {
								if ((card_Count(currObj3, headObj3) < 2)) {
									if (card_Count(currObj3, headObj3) == 0) {
										headObj3 = (card*)malloc(sizeof(card));
										card_Create(headObj3, DeckOfCards, NULL, counter);
										lastObj3 = headObj3;
										counter = counter - 1;
										card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 2);
										currentCard = 2;
									}
									else {
										card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
										currentCard = 2;
									}
								}
								card_Matches(&currObj4, &headObj4, &lastObj4, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount + 1, howMany, playerCount);
								if (doubleMatch > 0) {
									printf("Dealing %d card(s) to other players.\n", doubleMatch);
									card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
									card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
									if (playerCount >= 4) {
										card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
									}
								}
							}
							if ((currentCard) < card_Count(currObj3, headObj3)) {
								turnCount = turnCount + 1;
								endTurn = 1;
							}
						}
						if ((currentCard) < card_Count(currObj3, headObj3)) {
							currentCard = currentCard + 1;
						}
						else if ((currentCard) > card_Count(currObj3, headObj3)) {
							turnCount = turnCount + 1;
							endTurn = 1;
						}
						else if ((card_Count(currObj3, headObj3)) == currentCard) {
							turnCount = turnCount + 1;
							endTurn = endTurn + 1;;
							currentCard = 1;

						}
					}
					if (howMany != 0) {
						currObj4 = headObj4;
						for (int i = 0; i < card1 - 1; ++i) {
							currObj4 = currObj4->pt;
						}
						card1Val = currObj4->value;
						strcpy(card1Col, currObj4->color);
						currObj4 = headObj4;
						for (int i = 0; i < card2 - 1; ++i) {
							currObj4 = currObj4->pt;
						}
						card2Val = currObj4->value;
						strcpy(card2Col, currObj4->color);
						if (howMany == 1) {
							card2Val = 0;
						}
						trueOrFalse = card_GetMatch(currObj3, card1Val, card2Val, card1Col, card2Col, &singleMatch, &doubleMatch, howMany);
						if (trueOrFalse == 0) {
							printf("The selection does not total to the center row card. Select again\n");
						}
						if ((trueOrFalse == 1)) {
							if (howMany == 2) {
								currObj4 = headObj4;
								card_Release(&currObj4, &headObj4, &lastObj4, card2);
								card_Release(&currObj4, &headObj4, &lastObj4, card1);
								if (headObj4 == NULL) {
									playerCardCount3 = 0;
								}
								else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
									turnCount = turnCount + 1;
									endTurn = endTurn + 1;
									if (card_Count(currObj3, headObj3) == 0) {
										printf("There are no more center cards, ending turn.\n");
									}
									if ((doubleMatch == 0) && (singleMatch == 0)) {
									}
									card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
									if ((doubleMatch != 0) || (singleMatch != 0)) {
										if ((card_Count(currObj3, headObj3) < 2)) {
											if (card_Count(currObj3, headObj3) == 0) {
												headObj3 = (card*)malloc(sizeof(card));
												card_Create(headObj3, DeckOfCards, NULL, counter);
												lastObj3 = headObj3;
												counter = counter - 1;
												card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
												currentCard = 2;
											}
											else {
												card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
												currentCard = 2;
											}
										}
										card_Matches(&currObj4, &headObj4, &lastObj4, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
										if (doubleMatch > 0) {
											printf("Dealing %d card(s) to other players.\n", doubleMatch);
											card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
											card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
											if (playerCount >= 4) {
												card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
								}
								else {
									card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
									checker = 1;
								}
								drawCount = drawCount + 1;
							}
							else if (howMany == 1) {
								currObj4 = headObj4;
								card_Release(&currObj4, &headObj4, &lastObj4, card1);
								if (headObj4 == NULL) {
									playerCardCount3 = 0;
								}
								else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
									checker = 1;
									turnCount = turnCount + 1;
									endTurn = endTurn + 1;
									if (card_Count(currObj3, headObj3) == 0) {
										printf("There are no more center cards, ending turn.\n");
									}
									if ((doubleMatch == 0) && (singleMatch == 0)) {
									}
									card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
									if ((doubleMatch != 0) || (singleMatch != 0)) {
										if ((card_Count(currObj3, headObj3) < 2)) {
											if (card_Count(currObj3, headObj3) == 0) {
												headObj3 = (card*)malloc(sizeof(card));
												card_Create(headObj3, DeckOfCards, NULL, counter);
												lastObj3 = headObj3;
												counter = counter - 1;
												card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
												currentCard = 2;
											}
											else {
												card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
												currentCard = 2;
											}
										}
										card_Matches(&currObj4, &headObj4, &lastObj4, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
										if (doubleMatch > 0) {
											printf("Dealing %d card(s) to other players.\n", doubleMatch);
											card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
											card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
											if (playerCount >= 4) {
												card_Draw(currObj5, headObj5, lastObj5, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
								}
								else {
									card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
									checker = 1;
								}
								drawCount = drawCount + 1;
							}
							if (card_Count(currObj3, headObj3) == 1) {
								if (currentCard > card_Count(currObj3, headObj3)) {
									currentCard = 1;
								}
								else if (card_Count(currObj3, headObj3) != 1) {
									if (currObj3 = headObj3) {
										currentCard = 1;
									}
									else if (checker != 1) {
										currentCard = currentCard + 1;
									}
								}
							}
							else if ((card_Count(currObj3, headObj3) != 1) && (checker != 1)) {
								currentCard = currentCard + 1;
							}

						}
					}
					if (endTurn == 1) {
						if (turnCount % playerCount != 2) {
							if (drawCount == 0) {
								card_LastNode(&currObj4, &headObj4, &lastObj4);
								card_CreateLoop(currObj4, lastObj4, headObj4, DeckOfCards, NULL, &counter, 1);
								counter = counter - 1;
								card_LastNode(&currObj4, &headObj4, &lastObj4);
								if (lastObj4->value == 11) {
									printf("You drew the card %s #.\n", lastObj4->color);
								}
								else {
									printf("You drew the card %s %d.\n", lastObj4->color, lastObj4->value);
								}
								turnCount = turnCount - 1;
								currentCard = 1;
							}
						}
					}
					else if (endTurn == 2) {
						if (drawCount == 0) {
							card temp[1] = { 0 };
							int tmp = 0;
							drawCount = 0;
							printf("Place one of your cards to the middle 1-%d: ", card_Count(currObj4, headObj4)), card_Print(currObj4, headObj4);
							scanf("%d", &card1);
							strcpy(temp[0].color, card_GetCard(currObj4, headObj4, card1)->color), temp[0].value = card_GetCard(currObj4, headObj4, card1)->value;
							card_Release(&currObj4, &headObj4, &lastObj4, card1), card_LastNode(&currObj4, &headObj4, &lastObj4);
							card_LastNode(&currObj3, &headObj3, &lastObj3), card_CreateLoop(currObj3, lastObj3, headObj3, temp, NULL, &tmp, 1);
							card_LastNode(&currObj3, &headObj3, &lastObj3), card_LastNode(&currObj3, &headObj3, &lastObj3);
						}
					}
					if (turnCount % playerCount != 2) {
						if ((card_Count(currObj3, headObj3) < 2)) {
							if (card_Count(currObj3, headObj3) == 0) {
								headObj3 = (card*)malloc(sizeof(card));
								card_Create(headObj3, DeckOfCards, NULL, counter);
								lastObj3 = headObj3;
								counter = counter - 1;
								card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
							}
							else {
								card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, (2 - card_Count(currObj3, headObj3)));
							}
						}
					}
					if (headObj2 == NULL) {
						playerCardCount3 = 0;
					}
				}
				if ((playerCardCount1 != 0) && (playerCardCount2 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
					if (card_Count(currObj4, headObj4) != 0) {
						printf("Player 3's hand: "), card_Print(currObj4, headObj4);
						if (playerCount >= 4) {
							printf("Player 4's turn.\n");
						}
						else {
							printf("Player 1's turn.\n");
						}
						centerCardCount = card_Count(currObj3, headObj3);
						drawCount = 0;
						singleMatch = 0;
						doubleMatch = 0;
						currentCard = 1;
						endTurn = 0;
					}
					if (headObj4 != NULL) {
						playerCardCount4 = card_Count(currObj4, headObj4);
					}
					else if (headObj4 == NULL) {
						playerCardCount4 = 0;
					}
				}

				if (playerCount >= 4) {
					while ((turnCount % playerCount == 3) && (playerCardCount2 != 0) && (playerCardCount1 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
						printf("Player 4's cards: ");
						card_Print(currObj5, headObj5);
						printf("Centerline ");
						card_Print(currObj3, headObj3);
						currObj3 = headObj3;
						for (int i = 1; i < currentCard; ++i) {
							if (currObj3->pt != NULL) {
								currObj3 = currObj3->pt;
							}
						}
						if (currObj3->value == 11) {
							if (strcmp(currObj3->color, "green") == 0) {
								printf(RESET "How many cards do you want to play on " GREEN "%s # " RESET "(0, 1, or 2):", currObj3->color);
							}
							else if (strcmp(currObj3->color, "blue") == 0) {
								printf(RESET "How many cards do you want to play on " BLUE"%s # " RESET "(0, 1, or 2):", currObj3->color);
							}
							else if (strcmp(currObj3->color, "yellow") == 0) {
								printf(RESET "How many cards do you want to play on " YELLOW "%s # " RESET "(0, 1, or 2):", currObj3->color);
							}
							else if (strcmp(currObj3->color, "red") == 0) {
								printf(RESET "How many cards do you want to play on " RED "%s # " RESET "(0, 1, or 2):", currObj3->color);
							}
						}
						else if (currObj3->value == 2) {
							printf(RESET "How many cards do you want to play on anycolor 2 (0, 1, or 2):");
						}
						else {
							if (strcmp(currObj3->color, "green") == 0) {
								printf(RESET "How many cards do you want to play on " GREEN "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
							}
							else if (strcmp(currObj3->color, "blue") == 0) {
								printf(RESET "How many cards do you want to play on " BLUE "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
							}
							else if (strcmp(currObj3->color, "yellow") == 0) {
								printf(RESET "How many cards do you want to play on " YELLOW "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
							}
							else if (strcmp(currObj3->color, "red") == 0) {
								printf(RESET "How many cards do you want to play on " RED "%s %d " RESET "(0, 1, or 2):", currObj3->color, currObj3->value);
							}
						}
						printf(RESET);
						scanf(" %d", &howMany);
						if (howMany == 1) {
							printf("Select a card from 1-%d:", card_Count(currObj5, headObj5));
							scanf("%d", &card1);
							card2 = 0;
						}
						if (howMany == 2) {
							printf("Select two cards from 1-%d (x,y):", card_Count(currObj5, headObj5));
							scanf(" %d%c%d", &card1, &comma, &card2);
						}
						if (howMany == 0) {
							if ((card_Count(currObj3, headObj3) == 0) || (currentCard == card_Count(currObj3, headObj3))) {
								if ((card_Count(currObj3, headObj3) == 0)) {
									printf("There are no more center cards, ending turn.\n");
								}
								if (((doubleMatch == 0) && (singleMatch == 0)) && (drawCount == 0)) {
								}
								else {
									if ((card_Count(currObj3, headObj3) < 2)) {
										if (card_Count(currObj3, headObj3) == 0) {
											headObj3 = (card*)malloc(sizeof(card));
											card_Create(headObj3, DeckOfCards, NULL, counter);
											lastObj3 = headObj3;
											counter = counter - 1;
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 2);
											currentCard = 2;
										}
										else {
											card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
											currentCard = 2;
										}
									}
									card_Matches(&currObj5, &headObj5, &lastObj5, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount + 1, howMany, playerCount);
									if (doubleMatch > 0) {
										printf("Dealing %d card(s) to other players.\n", doubleMatch);
										card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
										card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
										card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
									}
								}
								if ((currentCard) < card_Count(currObj3, headObj3)) {
									turnCount = turnCount + 1;
									endTurn = 1;
								}
							}
							if ((currentCard) < card_Count(currObj3, headObj3)) {
								currentCard = currentCard + 1;
							}
							else if ((currentCard) > card_Count(currObj3, headObj3)) {
								turnCount = turnCount + 1;
								endTurn = 1;
							}
							else if ((card_Count(currObj3, headObj3)) == currentCard) {
								turnCount = turnCount + 1;
								endTurn = endTurn + 1;;
								currentCard = 1;

							}
						}
						if (howMany != 0) {
							currObj5 = headObj5;
							for (int i = 0; i < card1 - 1; ++i) {
								currObj5 = currObj5->pt;
							}
							card1Val = currObj5->value;
							strcpy(card1Col, currObj5->color);
							currObj5 = headObj5;
							for (int i = 0; i < card2 - 1; ++i) {
								currObj5 = currObj5->pt;
							}
							card2Val = currObj5->value;
							strcpy(card2Col, currObj5->color);
							if (howMany == 1) {
								card2Val = 0;
							}
							trueOrFalse = card_GetMatch(currObj3, card1Val, card2Val, card1Col, card2Col, &singleMatch, &doubleMatch, howMany);
							if (trueOrFalse == 0) {
								printf("The selection does not total to the center row card. Select again\n");
							}
							if ((trueOrFalse == 1)) {
								if (howMany == 2) {
									currObj5 = headObj5;
									card_Release(&currObj5, &headObj5, &lastObj5, card2);
									card_Release(&currObj5, &headObj5, &lastObj5, card1);
									if (headObj5 == NULL) {
										playerCardCount4 = 0;
									}
									else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
										turnCount = turnCount + 1;
										endTurn = endTurn + 1;
										if (card_Count(currObj3, headObj3) == 0) {
											printf("There are no more center cards, ending turn.\n");
										}
										if ((doubleMatch == 0) && (singleMatch == 0)) {
										}
										card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
										if ((doubleMatch != 0) || (singleMatch != 0)) {
											if ((card_Count(currObj3, headObj3) < 2)) {
												if (card_Count(currObj3, headObj3) == 0) {
													headObj3 = (card*)malloc(sizeof(card));
													card_Create(headObj3, DeckOfCards, NULL, counter);
													lastObj3 = headObj3;
													counter = counter - 1;
													card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
													currentCard = 2;
												}
												else {
													card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
													currentCard = 2;
												}
											}
											card_Matches(&currObj5, &headObj5, &lastObj5, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
											if (doubleMatch > 0) {
												printf("Dealing %d card(s) to other players.\n", doubleMatch);
												card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
												card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
												card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
									else {
										card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
										checker = 1;
									}
									drawCount = drawCount + 1;
								}
								else if (howMany == 1) {
									currObj5 = headObj5;
									card_Release(&currObj5, &headObj5, &lastObj5, card1);
									if (headObj5 == NULL) {
										playerCardCount4 = 0;
									}
									else if ((card_Count(currObj3, headObj3) == 1) || (currentCard == card_Count(currObj3, headObj3))) {
										checker = 1;
										turnCount = turnCount + 1;
										endTurn = endTurn + 1;
										if (card_Count(currObj3, headObj3) == 0) {
											printf("There are no more center cards, ending turn.\n");
										}
										if ((doubleMatch == 0) && (singleMatch == 0)) {
										}
										card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
										if ((doubleMatch != 0) || (singleMatch != 0)) {
											if ((card_Count(currObj3, headObj3) < 2)) {
												if (card_Count(currObj3, headObj3) == 0) {
													headObj3 = (card*)malloc(sizeof(card));
													card_Create(headObj3, DeckOfCards, NULL, counter);
													lastObj3 = headObj3;
													counter = counter - 1;
													card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
													currentCard = 2;
												}
												else {
													card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
													currentCard = 2;
												}
											}
											card_Matches(&currObj5, &headObj5, &lastObj5, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
											if (doubleMatch > 0) {
												printf("Dealing %d card(s) to other players.\n", doubleMatch);
												card_Draw(currObj, headObj, lastObj, DeckOfCards, &counter, &doubleMatch);
												card_Draw(currObj2, headObj2, lastObj2, DeckOfCards, &counter, &doubleMatch);
												card_Draw(currObj4, headObj4, lastObj4, DeckOfCards, &counter, &doubleMatch);
											}
										}
									}
									else {
										card_ReleaseCenter(&currObj3, &headObj3, &lastObj3, &currentCard);
										checker = 1;
									}
									drawCount = drawCount + 1;
								}
								if (card_Count(currObj3, headObj3) == 1) {
									if (currentCard > card_Count(currObj3, headObj3)) {
										currentCard = 1;
									}
									else if (card_Count(currObj3, headObj3) != 1) {
										if (currObj3 = headObj3) {
											currentCard = 1;
										}
										else if (checker != 1) {
											currentCard = currentCard + 1;
										}
									}
								}
								else if ((card_Count(currObj3, headObj3) != 1) && (checker != 1)) {
									currentCard = currentCard + 1;
								}

							}
						}
						if (endTurn == 1) {
							if (turnCount % playerCount != 3) {
								if (drawCount == 0) {
									card_LastNode(&currObj5, &headObj5, &lastObj5);
									card_CreateLoop(currObj5, lastObj5, headObj5, DeckOfCards, NULL, &counter, 1);
									counter = counter - 1;
									card_LastNode(&currObj5, &headObj5, &lastObj5);
									if (lastObj5->value == 11) {
										printf("You drew the card %s #.\n", lastObj5->color);
									}
									else {
										printf("You drew the card %s %d.\n", lastObj5->color, lastObj5->value);
									}
									turnCount = turnCount - 1;
									currentCard = 1;
								}
							}
						}
						else if (endTurn == 2) {
							if (drawCount == 0) {
								card temp[1] = { 0 };
								int tmp = 0;
								drawCount = 0;
								printf("Place one of your cards to the middle 1-%d: ", card_Count(currObj5, headObj5)), card_Print(currObj5, headObj5);
								scanf("%d", &card1);
								strcpy(temp[0].color, card_GetCard(currObj5, headObj5, card1)->color), temp[0].value = card_GetCard(currObj5, headObj5, card1)->value;
								card_Release(&currObj5, &headObj5, &lastObj5, card1), card_LastNode(&currObj5, &headObj5, &lastObj5);
								card_LastNode(&currObj3, &headObj3, &lastObj3), card_CreateLoop(currObj3, lastObj3, headObj3, temp, NULL, &tmp, 1);
								card_LastNode(&currObj3, &headObj3, &lastObj3), card_LastNode(&currObj3, &headObj3, &lastObj3);
							}
						}
						if (turnCount % playerCount != 3) {
							if ((card_Count(currObj3, headObj3) < 2)) {
								if (card_Count(currObj3, headObj3) == 0) {
									headObj3 = (card*)malloc(sizeof(card));
									card_Create(headObj3, DeckOfCards, NULL, counter);
									lastObj3 = headObj3;
									counter = counter - 1;
									card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, 1);
								}
								else {
									card_CreateLoop(currObj3, lastObj3, headObj3, DeckOfCards, NULL, &counter, (2 - card_Count(currObj3, headObj3)));
								}
							}
						}
						if (headObj5 == NULL) {
							playerCardCount2 = 0;
						}
					}
					if ((playerCardCount1 != 0) && (playerCardCount2 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
						if (card_Count(currObj5, headObj5) != 0) {
							printf("Player 4's hand: "), card_Print(currObj5, headObj5);
							printf("Player 1's turn.\n");
							centerCardCount = card_Count(currObj3, headObj3);
							drawCount = 0;
							singleMatch = 0;
							doubleMatch = 0;
							currentCard = 1;
							endTurn = 0;
						}
						if (headObj5 != NULL) {
							playerCardCount4 = card_Count(currObj5, headObj5);
						}
						else if (headObj5 == NULL) {
							playerCardCount4 = 0;
						}
					}
				}
			}
		}
		if (playerCount >= 4) { // when the game is over, it totals up the points based off who won, using if statements to check who had the least amount of points
			// makes sure to check wether or not player 3 and 4 are activated because otherwise they would also have 0 points
			if ((card_GetPoints(currObj, headObj) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj) < card_GetPoints(currObj4, headObj4)) && (card_GetPoints(currObj, headObj) < card_GetPoints(currObj5, headObj5))) {
				printf("Player 1 has won the round with %d points!\n", (card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
				playerPoints1 = card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
			}
			else if ((card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj4, headObj4)) && (card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj5, headObj5))) {
				printf("Player 2 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
				playerPoints2 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
			}
			else if ((card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj5, headObj5))) {
				printf("Player 3 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj5, headObj5)));
				playerPoints3 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj5, headObj5);
			}
			else if ((card_GetPoints(currObj5, headObj5) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj5, headObj5) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj5, headObj5) < card_GetPoints(currObj4, headObj4))) {
				printf("Player 4 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4)));
				playerPoints4 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4);
			}
			else if ((card_GetPoints(currObj, headObj) == card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj) == card_GetPoints(currObj4, headObj4)) && (card_GetPoints(currObj4, headObj4) == card_GetPoints(currObj5, headObj5))) {
				printf("Draw! No one has earned any points!\n");
			}
		}
		else if (playerCount >= 3) {
			if ((card_GetPoints(currObj, headObj) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj) < card_GetPoints(currObj4, headObj4))) {
				printf("Player 1 has won the round with %d points!\n", (card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4)));
				playerPoints1 = card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4);
			}
			else if ((card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj4, headObj4))) {
				printf("Player 2 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4)));
				playerPoints2 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4);
			}
			else if ((card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj2, headObj2))) {
				printf("Player 3 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2)));
				playerPoints3 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2);
			}
			else if ((card_GetPoints(currObj, headObj) == card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj)) == card_GetPoints(currObj4, headObj4)) {
				printf("Draw! No one has earned any points!\n");
			}
		}
		else if (playerCount <= 2) {
			if ((card_GetPoints(currObj, headObj)) < card_GetPoints(currObj2, headObj2)) {
				printf("Player 1 has won the round with %d points!\n", card_GetPoints(currObj2, headObj2));
				playerPoints1 = card_GetPoints(currObj2, headObj2);
			}
			else if ((card_GetPoints(currObj, headObj) == card_GetPoints(currObj2, headObj2))) {
				printf("Draw! No one has earned any points!\n");
			}
			else {
				printf("Player 2 has won the round with %d points!\n", card_GetPoints(currObj, headObj));
				playerPoints2 = card_GetPoints(currObj, headObj);
			}
		}
		else if (counter == 0) {
			if (playerCount >= 4) {
				if ((card_GetPoints(currObj, headObj) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj) < card_GetPoints(currObj4, headObj4)) && (card_GetPoints(currObj, headObj) < card_GetPoints(currObj5, headObj5))) {
					printf("Player 1 has won the round with %d points!\n", (card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
					playerPoints1 = card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj4, headObj4)) && (card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj5, headObj5))) {
					printf("Player 2 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
					playerPoints2 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj5, headObj5))) {
					printf("Player 3 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj5, headObj5)));
					playerPoints3 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj5, headObj5) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj5, headObj5) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj5, headObj5) < card_GetPoints(currObj4, headObj4))) {
					printf("Player 4 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4)));
					playerPoints4 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4);
				}
				else if ((card_GetPoints(currObj, headObj) == card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj) == card_GetPoints(currObj4, headObj4)) && (card_GetPoints(currObj4, headObj4) == card_GetPoints(currObj5, headObj5))) {
					printf("Draw! No one has earned any points!\n");
				}
			}
			else if (playerCount >= 3) {
				if ((card_GetPoints(currObj, headObj) < card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj) < card_GetPoints(currObj4, headObj4))) {
					printf("Player 1 has won the round with %d points!\n", (card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
					playerPoints1 = card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj2, headObj2) < card_GetPoints(currObj4, headObj4))) {
					printf("Player 2 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
					playerPoints2 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj, headObj)) && (card_GetPoints(currObj4, headObj4) < card_GetPoints(currObj2, headObj2))) {
					printf("Player 3 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj5, headObj5)));
					playerPoints3 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj, headObj) == card_GetPoints(currObj2, headObj2)) && (card_GetPoints(currObj, headObj)) == card_GetPoints(currObj4, headObj4)) {
					printf("Draw! No one has earned any points!\n");
				}
			}
			else {
				if ((card_GetPoints(currObj, headObj)) < card_GetPoints(currObj2, headObj2)) {
					printf("Player 1 has won the round with %d points!\n", (card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
					playerPoints1 = card_GetPoints(currObj2, headObj2) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
				}
				else if ((card_GetPoints(currObj, headObj) == card_GetPoints(currObj2, headObj2))) {
					printf("Draw! No one has earned any points!\n");
				}
				else {
					printf("Player 2 has won the round with %d points!\n", (card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5)));
					playerPoints2 = card_GetPoints(currObj, headObj) + card_GetPoints(currObj4, headObj4) + card_GetPoints(currObj5, headObj5);
				}
			}
		} // prints out the current point totals at the end of each round
		printf("Point Totals:\nPlayer 1: %d\nPlayer 2: %d\n", playerPoints1, playerPoints2); // since player 1 and 2 are gauranteed, it prints them out first then checks if player 3 and 4 need to be printed.
		if (playerCount >= 3) {
			printf("Player 3: %d\n", playerPoints3);
			if (playerCount >= 4) {
				printf("Player 4: %d\n", playerPoints4);
			}
		}
	}
	if (playerPoints1 > 200) { // when the game is finalyl over and a player has reached 200 points, it will find the winner and announce them as the winner.
		printf("Player 1 has won the game with %d points!", playerPoints1);
	}
	else if (playerPoints2 > 200) {
		printf("Player 2 has won the game with %d points!", playerPoints2);
	}
	else if (playerPoints3 > 200) {
		printf("Player 3 has won the game with %d points!", playerPoints3);
	}
	else {
		printf("Player 4 has won the game with %d points!", playerPoints4);
	}
}
