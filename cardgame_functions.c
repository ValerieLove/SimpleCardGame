#include<stdio.h>
#include<stdlib.h>
#include "cards.h"

Card* createCard(){//Function that generates a new card.
	Card* newCard = (Card*)malloc(sizeof(Card));//allocates memory for new card struct pointer.
	int chance = rand();//determines the chance of which card type is assigned to the card.
	int cardValue;//value of the card.
	
	switch(chance % 10){
		case 0://there is a 10% of this case executing.
			newCard->type = RUN;
			newCard->value = (rand() % 8) + 1;
			break;
		case 1:
		case 2:
		case 3:
		case 4://there is a 40 percent chance of either case 1 through 4.
			newCard->type = ATTACK;
			newCard->value = (rand() % 5) + 1;
			break;
		default://there is a 50 percent chance no case listed above will execute.
			newCard->type = DEFEND;
			newCard->value = (rand() % 6) + 3;
			break;
	}
	newCard->next = NULL;//newCard
	return newCard;
}

Card* removeCard(Card* head){//Function that removes the card the head points to.
	if(head == NULL){
		return NULL;
	}
	Card* removedCard = head;//stores the head
	Card* newFirstCard = removedCard->next;//stores the new head's pointer location.
	free(removedCard);//destroys the removed card
	
	return newFirstCard;//returns the updated head.
}

Card* addCard(Card* head, Card* c){//Function that adds a new card to the linked list in descending order by its value.
	Card* currentCard = head;
	Card* previousCard = NULL;
	
	while(currentCard != NULL && currentCard->value >= c->value){//while loop keeps iterating until the value of the currentCard is NULL and if the currentCard value is less than c's value.
		previousCard = currentCard;
		currentCard = currentCard->next;
	}
	
	if(previousCard == NULL){//if the value of c is greater than the value of the head, then c becomes the new head.
		c->next = currentCard;
		return c;
	}
	
	c->next = currentCard;//updates the value of c's pointer to point to the currentCard.
	previousCard->next = c;//updates the value of the previous card's pointer to point to c.
	return head;//returns the updated head.
}

int getLength(Card* head){//returns the number of cards in the list.
	int length = 0;//stores number of cards.
	Card* updateCard = head;//stores head to card pointer variable to be updated.
	while(updateCard != NULL){
		length++;//adds one until updateCard is null.
		updateCard = updateCard->next;//updates the variable to the next item on the list.
	}
	return length;

}

void printCard(Card* head){
	switch(head->type){
		case ATTACK:
			printf("A%d ", head->value);
			break;
		case DEFEND:
			printf("D%d ", head->value);
			break;
		case RUN:
			printf("R%d ", head->value);
			break;
		}
}

void printCards(Card* head){//prints all cards.
	if(head == NULL){//if a null pointer is passed in, a new line prints and the function is terminated.
		printf("\n");
		return;
	}
	else{
		printCard(head);//prints the current card
		printCards(head->next);//recursive call to function by passing the next card the current card points to.
	}

}

Card* buildCards(int n){//builds the players hands
	int i;//loop variable
	Card* newHand = NULL;//stores the card to be added to the linked list
	Card* currentHead = NULL;//stores the current head of the linked list
	
	for(i = 0; i < n; i++){//iterates n number of times.
		newHand = createCard();//creates a card
		currentHead = addCard(currentHead, newHand);//adds card to the list
	}

	return currentHead;
}

Card* destroyCards(Card* head){//frees all players hands
	while(head != NULL){
		Card* destroyedCard = head;
		head = head->next;
		free(destroyedCard);
	}
	return NULL;
}
