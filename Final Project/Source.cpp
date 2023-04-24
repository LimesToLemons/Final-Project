#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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
	for (int i = 88; i < 108; i++) {
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

int createDeckFile(card deck[], FILE* inp) {
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
	for (int i = 0; i < 1000; i++) {
		int num1 = rand() % 108, num2 = rand() % 108; // initializes random number from 0-108 representing the array values to swap it
		temp = deck[num1]; // runs the loop 1000 times to ensure cards are shuffled
		deck[num1] = deck[num2];
		deck[num2] = temp;
	}
}

void card_Create(card* cards, card deck[], card* nextCard, int counter) {
	if (deck[counter].value == 2) {
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
	cards->pt = nextCard;
}

void card_After(card* cards, card* newCards) {
	card* tempNxt = NULL;
	tempNxt = cards->pt;
	cards->pt = newCards;
	newCards->pt = tempNxt;
}

void card_Print(card* thisnode, card* headNode) {
	thisnode = headNode;
	while (thisnode != NULL) {
		if (thisnode->pt == NULL) {
			if (thisnode->value == 2) {
				printf("anycolor %d", thisnode->value);
			}
			else if (thisnode->value == 11) {
				printf("%s %s", thisnode->color, thisnode->action);
			}
			else {
				printf("%s %d", thisnode->color, thisnode->value);
			}
		}
		else if (thisnode->value == 2) {
			printf("anycolor %d, ", thisnode->value);
		}
		else if (thisnode->value == 11) {
			printf("%s %s, ", thisnode->color, thisnode->action);
		}
		else {
			printf("%s %d, ", thisnode->color, thisnode->value);
		}
		thisnode = thisnode->pt;
	}
	thisnode = headNode;
	printf("\n");
}

int card_Count(card* thisnode, card* headNode) {
	int count = 0;
	thisnode = headNode;
	while (thisnode != NULL) {
		count = count + 1;
		thisnode = thisnode->pt;
	}
	return count;
	}

void center_Card(card* thisnode) {
	if (thisnode->value == 2) {
		printf("anycolor %d, ", thisnode->value);
	}
	else if (thisnode->value == 11) {
		printf("%s %s, ", thisnode->color, thisnode->action);
	}
	else {
		printf("%s %d, ", thisnode->color, thisnode->value);
	}
}

void card_GetChecker(card* thisnode, card deck) {
	deck = *thisnode;
}

void card_CreateLoopHand(card* thisNode, card* lastNode, card* thisNode2, card* lastNode2, card deck[], card* nextCard, int *counter, int loopNum) {
	for (int i = 0; i < loopNum; i++) {
		thisNode = (card*)malloc(sizeof(card));
		thisNode2 = (card*)malloc(sizeof(card));
		card_Create(thisNode, deck, NULL, (*counter));
		card_After(lastNode, thisNode);
		card_Create(thisNode2, deck, NULL, (*counter) - 1);
		card_After(lastNode2, thisNode2);
		lastNode = thisNode;
		lastNode2 = thisNode2;
		*counter = (*counter) - 2;
	}
}

void card_CreateLoop(card* thisNode, card* lastNode, card deck[], card* nextCard, int* counter, int loopNum) {
	for (int i = 0; i < loopNum; i++) {
		thisNode = (card*)malloc(sizeof(card));
		card_Create(thisNode, deck, NULL, *counter);
		card_After(lastNode, thisNode);
		lastNode = thisNode;
		*counter = *counter - 1;
	}
}

bool card_GetMatch(card* thisnode, int cardValue, int cardValue2) {
	int trueOrNah = 0;
	if ((cardValue == 11) || (cardValue2 == 11)) {
		if ((cardValue == 11) && (cardValue2 == 11)) {
			trueOrNah = 1;
		}
		else if ((cardValue + cardValue2) - 11 < thisnode->value) {
			trueOrNah = 1;
		}
	}
	else if ((cardValue + cardValue2) == thisnode->value) {
		trueOrNah = 1;
	}
	return trueOrNah;
}

void card_Release(card* thisnode, card* headnode, int card1, int card2, int twoOrone) {
	card* tmp, * tmp2;
	thisnode = headnode;
	if (thisnode != NULL) {
		if (twoOrone == 1) {
			if (card1 == 1) {
				tmp = headnode;
				headnode = headnode->pt;
				free(tmp);
			}
			else {
				thisnode = headnode;
				for (int i = 0; i < card1 - 2; ++i) {
					thisnode = thisnode->pt;
				}
				tmp = thisnode->pt;
				thisnode = thisnode->pt->pt;
				free(tmp);
			}
		}
		else if (twoOrone == 2) {
			thisnode = headnode;
			thisnode = headnode;
			for (int i = 0; i < card2 - 2; ++i) {
				thisnode = thisnode->pt;
			}
			tmp = thisnode->pt;
			if (thisnode->pt == NULL) {
				thisnode = headnode;
			}
			else if (thisnode->pt->pt == NULL) {
				thisnode = thisnode->pt;
			}
			free(tmp);
			if (card1 == 1) {
				tmp2 = headnode;
				headnode = headnode->pt;
				free(tmp2);
			}
			else {
				thisnode = headnode;
				for (int i = 0; i < card1 - 2; ++i) {
					thisnode = thisnode->pt;
				}
				tmp2 = thisnode->pt;
				if (thisnode->pt == NULL) {
					thisnode = thisnode;
				}
				else if (thisnode->pt->pt == NULL) {
					thisnode = thisnode->pt;
				}
				free(tmp2);
			}
			}
		}
		//thisnode = headnode;
		card_Print(thisnode, headnode);
	}

void playSequence(card* thisnode, card* lastnode, card* centernode, card* centernodelast, card* centernodehead, card* headnode, card deck[], int* counter, int* turncount) {
	int howMany = 0, card1 = 0, card2 = 0, card1Val = 0, card2Val = 0, trueOrFalse = 0, currentCard = 1;
	char comma;
	card* tmp;
	card_Print(thisnode, headnode);
	printf("Centerline ");
	card_Print(centernode, centernodehead);
	centernode = centernodehead;
	for (int i = 0; i < currentCard; ++i) {
		centernode = centernode->pt;
		printf("How many cards do you want to play on %s %d:", centernode->color, centernode->value);
	}
	scanf("%d", &howMany);
	if (howMany == 1) {
		printf("Select a card from 1-%d:", card_Count(thisnode, headnode));
		scanf("%d", &card1);
		card2 = 0;
	}
	if (howMany == 2) {
		printf("Select two cards from 1-%d (x,y):", card_Count(thisnode, headnode));
		scanf("%d%c%d", &card1, &comma, &card2);
	}
	thisnode = headnode;
	for (int i = 0; i < card1 - 1; ++i) {
		thisnode = thisnode->pt;
	}
	card1Val = thisnode->value;
	thisnode = headnode;
	for (int i = 0; i < card2 -1; ++i) {
		thisnode = thisnode->pt;
	}
	card2Val = thisnode->value;
	if (howMany == 1) {
		card2Val = 0;
	}
	centernode = centernodehead;
	trueOrFalse = card_GetMatch(centernode, card1Val, card2Val);
	if (trueOrFalse == 0) {
		printf("The selection does not total to the center row card. Select again\n");
	}
	if ((trueOrFalse == 1) && (*turncount % 2 == 1)) {
		printf("Player 1's cards: ");
		card_Release(thisnode, headnode, card1, card2, howMany);
	}
	else if ((trueOrFalse == 1) && (*turncount % 2 == 0)) {
		printf("Player 2's cards: ");
		card_Release(thisnode, headnode, card1, card2, howMany);
	}
}

int main() {
	int userIn, playerCardCount1, playerCardCount2, centerCardHolder = 0, centerCardCount, currentCardCount = 0, cardPlayed, cardPlayed2 = 0, trueOrFalse = 0, turnCount = 1;
	char userPress = 0;
	printf("Let's Play a Game of DOS\n");
	printf("Press 1 to shuffle the DOS deck or 2 to load a deck from a file:\n");
	scanf("%d", &userIn);
	card DeckOfCards[108], centerCard = {}, playedCard[2] = {};
	int counter = 107;
	if (userIn == 1) {
		createDeck(DeckOfCards);
		randomizeDeck(DeckOfCards);
		printf("The deck is shuffled. Enter any key to deal cards\n");
		scanf(" %c", &userPress);
	}
	else if (userIn == 2) {
		char userInFile[100];
		FILE* inp;
		printf("Please enter the file name to load from\n");
		scanf("%s", userInFile);
		inp = fopen(userInFile, "r");
		if (inp != NULL) {
			counter = createDeckFile(DeckOfCards, inp);
		}
		else {
			printf("Error: File not found!");
		}
	}
	
	card* headObj = NULL, * headObj2 = NULL, * headObj3 = NULL;
	card* currObj = NULL, * currObj2 = NULL, * currObj3 = NULL;
	card* lastObj = NULL, * lastObj2 = NULL, * lastObj3 = NULL;
	headObj = (card*)malloc(sizeof(card));
	headObj2 = (card*)malloc(sizeof(card));
	card_Create(headObj, DeckOfCards, NULL, counter);
	lastObj = headObj;
	counter = counter - 1;
	card_Create(headObj2, DeckOfCards, NULL, counter);
	lastObj2 = headObj2;
	counter = counter - 1;
	card_CreateLoopHand(currObj, lastObj, currObj2, lastObj2, DeckOfCards, NULL, &counter, 6);
	//printf("Player 1 Hand: ");
	//card_Print(currObj, headObj);
	//printf("Player 2 Hand: ");
	//card_Print(currObj2, headObj2);
	headObj3 = (card*)malloc(sizeof(card));
	lastObj3 = headObj3;
	counter = counter - 1;
	card_Create(headObj3, DeckOfCards, NULL, counter);
	centerCardCount = card_Count(currObj3, headObj3);
	playerCardCount1 = card_Count(currObj, headObj);
	playerCardCount2 = card_Count(currObj2, headObj2);

	while ((centerCardCount > 0) && (playerCardCount1 > 0) && (playerCardCount2 > 0)) {
		if (centerCardCount < 2) {
			card_CreateLoop(headObj3, lastObj3, DeckOfCards, NULL, &counter, (2 - centerCardCount));
		}
		if (turnCount % 2 == 1) {
			printf("Player 1's cards: ");
			playSequence(currObj, lastObj, currObj3, lastObj3, headObj3, headObj, DeckOfCards, &counter, &turnCount);
			centerCardCount = 0;
		}

	}

	/*if ((counter > 0) && (playerCardCount1 > 0) && (playerCardCount2 > 0)) {
		while (centerCardCount > 0) {
			currObj = headObj;
			currObj2 = headObj2;
			if (currObj != NULL) {
				printf("Player 1 Cards: ");
				while (currObj != NULL) {
					card_Print(currObj);
					currObj = card_GetNext(currObj);
				}
			}
			printf("\n");
			if (currObj3 != NULL) {
				printf("Centerline: ");
				while (currObj3 != NULL) {
					card_Print(currObj3);
					currObj3 = card_GetNext(currObj3);
				}
			}
			printf("\nHow many cards do you want to play on ");
			currObj3 = headObj3;
			for (int i = centerCardCount; i > 0; --i) {
				card_GetChecker(currObj3, centerCard);
				card_Print(currObj3);
			}
			scanf("%d", &cardPlayed);
			if (cardPlayed == 1) {
				printf("Select a card from 1-%d\n", playerCardCount1);
				scanf("%d", &cardPlayed);
				trueOrFalse = card_GetMatch(currObj, headObj, centerCard, cardPlayed, 0);

			}
			else if (cardPlayed == 2) {
				printf("Select two cards from 1-%d\n", playerCardCount1);
				scanf("%d %c %d", &cardPlayed, &userPress, &cardPlayed2);
				trueOrFalse = card_GetMatch(currObj, headObj, centerCard, cardPlayed, cardPlayed2);
			}
			if (trueOrFalse == 0) {
				printf("\nThe selection does not total the center row. Select again.");
			}
			else if (trueOrFalse == 1) {
				currObj = headObj;
				currObj3 = headObj3;
				for (int i = 0; i < cardPlayed; ++i) {
					currObj = card_GetNext(currObj);
				}
				currObj->pt = NULL;
				currObj = headObj;
				for (int i = 0; i < cardPlayed2; ++i) {
					currObj = card_GetNext(currObj);
				}
				currObj->pt = NULL;
				currObj = headObj;
				while (currObj != NULL) {
					card_Print(currObj);
					currObj = card_GetNext(currObj);
				}
			}
		}
	}*/
}