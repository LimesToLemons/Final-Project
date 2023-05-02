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

// hi

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
	for (int i = 0; i < 5000; i++) {
		int num1 = rand() % 108, num2 = rand() % 108; // initializes random number from 0-108 representing the array values to swap it
		temp = deck[num1]; // runs the loop 5000 times to ensure cards are shuffled
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
				printf("anycolor 2");
			}
			else if (thisnode->value == 11) {
				if (strcmp(thisnode->color, "green") == 0) {
					printf(RESET GREEN "%s #", thisnode->color);
				}
				else if (strcmp(thisnode->color, "red") == 0) {
					printf(RESET RED "%s #", thisnode->color);
				}
				else if (strcmp(thisnode->color, "blue") == 0) {
					printf(RESET BLUE "%s #", thisnode->color);
				}
				else if (strcmp(thisnode->color, "yellow") == 0) {
					printf(RESET YELLOW "%s #", thisnode->color);
				}
			}
			else {
				if (strcmp(thisnode->color, "green") == 0) {
					printf(RESET GREEN "%s %d", thisnode->color, thisnode->value);
				}
				else if (strcmp(thisnode->color, "red") == 0) {
					printf(RESET RED "%s %d", thisnode->color, thisnode->value);
				}
				else if (strcmp(thisnode->color, "blue") == 0) {
					printf(RESET BLUE "%s %d", thisnode->color, thisnode->value);
				}
				else if (strcmp(thisnode->color, "yellow") == 0) {
					printf(RESET YELLOW "%s %d", thisnode->color, thisnode->value);
				}
			}
		}
		else if (thisnode->value == 2) {
			printf("anycolor 2, ");
		}
		else if (thisnode->value == 11) {
			if (strcmp(thisnode->color, "green") == 0) {
				printf(RESET GREEN "%s #, ", thisnode->color);
			}
			else if (strcmp(thisnode->color, "red") == 0) {
				printf(RESET RED "%s #, ", thisnode->color);
			}
			else if (strcmp(thisnode->color, "blue") == 0) {
				printf(RESET BLUE "%s #, ", thisnode->color);
			}
			else if (strcmp(thisnode->color, "yellow") == 0) {
				printf(RESET YELLOW "%s #, ", thisnode->color);
			}
		}
		else {
			if (strcmp(thisnode->color, "green") == 0) {
				printf(RESET GREEN "%s %d, ", thisnode->color, thisnode->value);
			}
			else if (strcmp(thisnode->color, "red") == 0) {
				printf(RESET RED "%s %d, ", thisnode->color, thisnode->value);
			}
			else if (strcmp(thisnode->color, "blue") == 0) {
				printf(RESET BLUE "%s %d, ", thisnode->color, thisnode->value);
			}
			else if (strcmp(thisnode->color, "yellow") == 0) {
				printf(RESET YELLOW "%s %d, ", thisnode->color, thisnode->value);
			}
		}
		printf(RESET);
		thisnode = thisnode->pt;
	}
	thisnode = headNode;
	printf("\n");
}

int card_Count(card* thisnode, card* headNode) {
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

void card_LastNode(card** thisnode, card** headnode, card** lastnode) {
	*thisnode = *headnode;
	while ((*thisnode)->pt != NULL) {
		*thisnode = (*thisnode)->pt;
	}
	*lastnode = *thisnode;
	*thisnode = *headnode;
}

void card_CreateLoopHand(card* thisNode, card* lastNode, card* thisNode2, card* lastNode2, card* headNode, card* headNode2, card deck[], card* nextCard, int* counter, int loopNum) {
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
		thisNode = (card*)malloc(sizeof(card));
		thisNode2 = (card*)malloc(sizeof(card));
	}
}

void card_CreateLoop(card* thisNode, card* lastNode, card* headnode, card deck[], card* nextCard, int* counter, int loopNum) {
	for (int i = 0; i < loopNum; i++) {
		thisNode = (card*)malloc(sizeof(card));
		card_Create(thisNode, deck, NULL, *counter);
		card_After(lastNode, thisNode);
		lastNode = thisNode;
		*counter = *counter - 1;
		thisNode = (card*)malloc(sizeof(card));
	}
}

bool card_GetMatch(card* thisnode, int cardValue, int cardValue2, char card1Col[], char card2Col[], int* singleMatch, int* doubleMatch, int howMany) {
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

void card_ReleaseCenter(card** thisnode, card** headnode, card** lastnode, int* card1) {
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

void card_Release(card** thisnode, card** headnode, card** lastnode, int card1) {
	card* tmp = { 0 };
	if (card_Count(*thisnode, *headnode) == 1) {
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

card* card_GetCard(card* thisnode, card* headnode, int card1) {
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

int card_GetPoints(card* thisnode, card* headnode) {
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
	int card1 = 0;
	if ((*singleMatch != 0) || (*doubleMatch != 0)) {
		if (*singleMatch != 0) {
			for (int i = *singleMatch; i > 0; i--) {
				card temp[1] = { 0 };
				int tmp = 0;
				printf("You single matched %d card(s). Select a card from 1-%d to put in the center.\n", *singleMatch, card_Count(*thisnode, *headnode));
				card_Print(*thisnode, *headnode);
				scanf("%d", &card1);
				strcpy(temp[0].color, card_GetCard(*thisnode, *headnode, card1)->color), temp[0].value = card_GetCard(*thisnode, *headnode, card1)->value;
				card_Release(thisnode, headnode, lastnode, card1);
				if (card_Count(*thisnode, *headnode) == 0) {
					return;
				}
				card_LastNode(thisnode, headnode, lastnode);
				card_LastNode(thisnode2, headnode2, lastnode2), card_CreateLoop(*thisnode2, *lastnode2, *headnode2, temp, NULL, &tmp, 1);
				card_LastNode(thisnode, headnode, lastnode), card_LastNode(thisnode2, headnode2, lastnode2);
			}
		}
		if (*doubleMatch != 0) {
			for (int i = *doubleMatch; i > 0; i--) {
				card temp[1] = { 0 };
				int tmp = 0;
				printf("You double matched %d card(s). Select a card from 1-%d to put in the center.\n", *doubleMatch, card_Count(*thisnode, *headnode));
				card_Print(*thisnode, *headnode);
				scanf("%d", &card1);
				strcpy(temp[0].color, card_GetCard(*thisnode, *headnode, card1)->color), temp[0].value = card_GetCard(*thisnode, *headnode, card1)->value;
				card_Release(thisnode, headnode, lastnode, card1);
				if (card_Count(*thisnode, *headnode) == 0) {
					return;
				}
				card_LastNode(thisnode, headnode, lastnode);
				card_LastNode(thisnode2, headnode2, lastnode2), card_CreateLoop(*thisnode2, *lastnode2, *headnode2, temp, NULL, &tmp, 1);
				card_LastNode(thisnode, headnode, lastnode), card_LastNode(thisnode2, headnode2, lastnode2);
			}
		}
	}
}

void card_Draw(card* thisnode, card* headnode, card* lastnode, card deck[], int* counter, int* doubleMatch) {
	for (int i = *doubleMatch; i > 0; --i) {
		card_CreateLoop(thisnode, lastnode, headnode, deck, NULL, counter, 1);
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
		createDeck(DeckOfCards);
	}
	else if (userIn == 2) {
		char userInFile[100];
		printf("Please enter the file name to load from\n");
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

	while ((playerPoints1 < 200) && (playerPoints2 < 200) && (playerPoints3 < 200) && (playerPoints4 < 200)) {
		if (userIn == 1) {
			counter = 107;
		}
		else {
			counter = createDeckFile(DeckOfCards, inp);
		}
		if ((playerPoints1 == 0) && (playerPoints2 == 0) && (playerPoints3 == 0) && (playerPoints4 == 0)) {
			printf("Let's play a round of DOS!\n");
		}
		else {
			printf("\nPoint totals not met! Let's play another round of DOS!\n");
		}
		randomizeDeck(DeckOfCards);
		printf("The deck is shuffled. Enter any key to deal cards\n");
		scanf(" %c", &userPress);
		int playerCardCount1, playerCardCount2, playerCardCount3 = 1, playerCardCount4 = 1, centerCardCount = 1, currentCardCount = 0, turnCount = 0, currentCard = 1, drawCount = 0;
		card* headObj = NULL, * headObj2 = NULL, * headObj3 = NULL, * headObj4 = NULL, * headObj5 = NULL;
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
		counter = counter - 1;
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
		while ((counter > 0) && (playerCardCount1 > 0) && (playerCardCount2 > 0) && (playerCardCount3 > 0) && (playerCardCount4 > 0)) {
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
					printf("Select a card from 1-%d:", card_Count(currObj, headObj));
					scanf("%d", &card1);
					card2 = 0;
				}
				if (howMany == 2) {
					printf("Select two cards from 1-%d (x,y):", card_Count(currObj, headObj));
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
					trueOrFalse = card_GetMatch(currObj3, card1Val, card2Val, card1Col, card2Col, &singleMatch, &doubleMatch, howMany);
					if (trueOrFalse == 0) {
						printf("The selection does not total to the center row card. Select again\n");
					}
					if ((trueOrFalse == 1)) {
						if (howMany == 2) {
							currObj = headObj;
							card_Release(&currObj, &headObj, &lastObj, card2);
							card_Release(&currObj, &headObj, &lastObj, card1);
							if (headObj == NULL) {
								playerCardCount1 = 0;
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
						else if (howMany == 1) {
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
				if (endTurn == 1) {
					if (turnCount % playerCount != 0) {
						if (drawCount == 0) {
							card_LastNode(&currObj, &headObj, &lastObj);
							card_CreateLoop(currObj, lastObj, headObj, DeckOfCards, NULL, &counter, 1);
							counter = counter - 1;
							card_LastNode(&currObj, &headObj, &lastObj);
							printf("You drew the card %s %d.\n", lastObj->color, lastObj->value);
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
						printf("Place one of your cards to the middle 1-%d: ", card_Count(currObj, headObj)), card_Print(currObj, headObj);
						scanf("%d", &card1);
						strcpy(temp[0].color, card_GetCard(currObj, headObj, card1)->color), temp[0].value = card_GetCard(currObj, headObj, card1)->value;
						card_Release(&currObj, &headObj, &lastObj, card1), card_LastNode(&currObj, &headObj, &lastObj);
						card_LastNode(&currObj3, &headObj3, &lastObj3), card_CreateLoop(currObj3, lastObj3, headObj3, temp, NULL, &tmp, 1);
						card_LastNode(&currObj3, &headObj3, &lastObj3), card_LastNode(&currObj3, &headObj3, &lastObj3);
					}
				}
				if (turnCount % playerCount != 0) {
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
				if (headObj == NULL) {
					playerCardCount1 = 0;
				}
			}
			if ((playerCardCount1 != 0) && (playerCardCount2 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
				if (card_Count(currObj, headObj) != 0) {
					printf("Player 1's hand: "), card_Print(currObj, headObj);
					printf("Player 2's turn.\n");
					centerCardCount = card_Count(currObj3, headObj3);
					drawCount = 0;
					singleMatch = 0;
					doubleMatch = 0;
					currentCard = 1;
					endTurn = 0;
				}
				if (headObj != NULL) {
					playerCardCount1 = card_Count(currObj, headObj);
				}
				else if (headObj == NULL) {
					playerCardCount1 = 0;
				}
			}

			while ((turnCount % playerCount == 1) && (playerCardCount2 != 0) && (playerCardCount1 != 0) && (playerCardCount3 != 0) && (playerCardCount4 != 0)) {
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
							printf("You drew the card %s %d.\n", lastObj2->color, lastObj2->value);
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
								printf("You drew the card %s %d.\n", lastObj4->color, lastObj4->value);
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
						card_Matches(&currObj5, &headObj5, &lastObj5, &currObj3, &headObj3, &lastObj3, &currObj, &headObj, &lastObj, DeckOfCards, &singleMatch, &doubleMatch, &counter, &currentCard, turnCount, howMany, playerCount);
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
						printf("You drew the card %s %d.\n", lastObj5->color, lastObj5->value);
						turnCount = 2;
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
		}
		printf("Point Totals:\nPlayer 1: %d\nPlayer 2: %d\n", playerPoints1, playerPoints2);
		if (playerCount >= 3) {
			printf("Player 3: %d\n", playerPoints3);
			if (playerCount >= 4) {
				printf("Player 4: %d\n", playerPoints4);
			}
	}
	}
	if (playerPoints1 > 200) {
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
