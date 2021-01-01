#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "cards.h"

int main(int argc, char* argv[]){
	srand(time(NULL));//initializes the random number generator.
	Card* player1Hand = NULL;//stores the linked list for player 1 which represents the player's hand.
	Card* player2Hand = NULL;//stores the linked list for player 2 which represents the player's hand.
	Card* drawCard = NULL;//stores any new card created to be added to players hand.
	int numberOfCards;//stores the number of cards as determined by the command line argument.
	int roundNumber = 1;
	
	if(argc != 2){//ends the program if there are not two arguments.
		printf("ERROR: No valid arguments\n");
		return 1;
	}

	if(atoi(argv[1]) <= 0){//ends the program if command line argument is less than or equal to zero.
		printf("ERROR: Please enter a valid number\n");
		return -1;
	}
	
	numberOfCards = atoi(argv[1]);//stores the starting number of cards.
	
	printf("./project3 %d\n", numberOfCards);//prints the number of cards.
	
	player1Hand = buildCards(numberOfCards);//generates player 1's hand.
	player2Hand = buildCards(numberOfCards);//generate player 2's hand.
	
	//prints both player's starting hands
	printf("\n============= PLAYER 1 V PLAYER 2 SHOWDOWN ============\n");
	printf("Start size: %d cards\n", numberOfCards);
	printf("Player 1 starting cards: ");
	printCards(player1Hand);
	printf("Player 2 starting cards: ");
	printCards(player2Hand);
	printf("\n");
	
	//main game starts
	while(player1Hand != NULL && player2Hand != NULL){//start of the while loop
		printf("\n----- ROUND %d -----\n", roundNumber);//prints round number
		printf("Player 1 (%d): ", getLength(player1Hand));
		printCard(player1Hand);
		printf("\nPlayer 2 (%d): ", getLength(player2Hand));
		printCard(player2Hand);
		
		if(player1Hand->type == DEFEND && player2Hand->type == DEFEND){//Both players defend
			printf("\nBoth players DEFEND.\nNothing happens.\n");
			player1Hand = removeCard(player1Hand);
			player2Hand = removeCard(player2Hand);
		}
		else if(player1Hand->type == RUN && player2Hand->type == RUN){//Both players run
			printf("\nBoth players RUN.\nBoth players lose their next cards into the abyss.\n");
			player1Hand = removeCard(player1Hand);//card that player 1 just played.
			player1Hand = removeCard(player1Hand);//card that player 1 just lost.
			player2Hand = removeCard(player2Hand);//card that player 2 just played.
			player2Hand = removeCard(player2Hand);//card that player 2 just lost.
		}
		else if(player1Hand->type == ATTACK && player2Hand->type == ATTACK){//Both players attack.
			printf("\nBoth players ATTACK.\n");
			
			if(player1Hand->value == player2Hand->value){//nothing happens if the cards have the same value
				printf("Nothing happens.\n");
				player1Hand = removeCard(player1Hand);
				player2Hand = removeCard(player2Hand);
			}
			else if(player1Hand->value > player2Hand->value){//the player with the higher value gains a card and the player with the lesser value loses a card
				player1Hand = removeCard(player1Hand);
				player2Hand = removeCard(player2Hand);
				printf("Player 1 wins and gets a new card. Player 2 loses their next card into the abyss.\n");
				drawCard = createCard();
				player1Hand = addCard(player1Hand, drawCard);
				player2Hand = removeCard(player2Hand);
			}
			else{
				player1Hand = removeCard(player1Hand);
				player2Hand = removeCard(player2Hand);
				printf("Player 2 wins and gets a new card. Player 1 loses their next card into the abyss.\n");
				drawCard = createCard();
				player2Hand = addCard(player2Hand, drawCard);
				player1Hand = removeCard(player1Hand);
			}
		}
		else if(player1Hand->type == ATTACK && player2Hand->type == DEFEND){//Player 1 attacks and player 2 defends.
				printf("\nPlayer 1 ATTACKs and Player 2 DEFENDs.\n");
				//if the card is a higher attack value then the defense the attacking player gets a new card.
				if(player1Hand->value > player2Hand->value){
					player1Hand = removeCard(player1Hand);
					player2Hand = removeCard(player2Hand);
					printf("Player 1 wins. Player 1 gets a new card.\n");
					drawCard = createCard();
					player1Hand = addCard(player1Hand, drawCard);
				}
				else{//if the defense value is equal or greater than the attack, the attacking player loses a card.
					player1Hand = removeCard(player1Hand);
					player2Hand = removeCard(player2Hand);
					printf("Player 1 loses and Player 2 survives.\nPlayer 1 loses their next card into the abyss.\n");
					player1Hand = removeCard(player1Hand);
				}
			
			
		}
		else if(player2Hand->type == ATTACK && player1Hand->type == DEFEND){//Player 2 attacks and player 1 defends.
				printf("\nPlayer 2 ATTACKs and Player 1 DEFENDs.\n");
				
				if(player2Hand->value > player1Hand->value){
					player1Hand = removeCard(player1Hand);
					player2Hand = removeCard(player2Hand);
					printf("Player 2 wins. Player 2 gets a new card.\n");
					drawCard = createCard();
					player2Hand = addCard(player2Hand, drawCard);
				}
				else{
					player1Hand = removeCard(player1Hand);
					player2Hand = removeCard(player2Hand);
					printf("Player 2 loses and Player 1 survives.\nPlayer 2 loses their next card into the abyss.\n");
					player2Hand = removeCard(player2Hand);
				}
		}
		else if(player1Hand->type == ATTACK && player2Hand->type == RUN){//Player 1 attacks and player 2 runs.
			player1Hand = removeCard(player1Hand);
			player2Hand = removeCard(player2Hand);
			printf("\nPlayer 1 ATTACKs and player 2 RUNs.\nPlayer 2 loses their next card into the abyss.\n");
			player2Hand = removeCard(player2Hand);//running player loses their next card.
		}
		else if(player2Hand->type == ATTACK && player1Hand->type == RUN){//Player 2 attacks and player 1 runs.
			player1Hand = removeCard(player1Hand);
			player2Hand = removeCard(player2Hand);
			printf("\nPlayer 2 ATTACKs and player 1 RUNs.\nPlayer 1 loses their next card into the abyss.\n");
			player1Hand = removeCard(player1Hand);
		}
		else if(player1Hand->type == DEFEND && player2Hand->type == RUN){//Player 1 defends and Player 2 runs.
			player1Hand = removeCard(player1Hand);
			player2Hand = removeCard(player2Hand);
			printf("\nPlayer 1 DEFENDs and player 2 RUNs.\nPlayer 1 gets a new card. Player 2 loses their next card into the abyss.\n");
			drawCard = createCard();//defending player gets a new card and running layer loses a card.
			player1Hand = addCard(player1Hand, drawCard);
			player2Hand = removeCard(player2Hand);
		}
		else if(player2Hand->type == DEFEND && player1Hand->type == RUN){//Player 1 runs and player 2 defends.
			player1Hand = removeCard(player1Hand);
			player2Hand = removeCard(player2Hand);
			printf("\nPlayer 2 DEFENDs and player 1 RUNs.\nPlayer 2 gets a new card. Player 1 loses their next card into the abyss.\n");
			drawCard = createCard();
			player2Hand = addCard(player2Hand, drawCard);
			player1Hand = removeCard(player1Hand);
		}
		else{
			printf("An exception has occurred.\n");
			break;
		}
		
		roundNumber++;//increments round number by one.
	}//end of the while loop
	//prints player hands after the game ends
	printf("\n============ GAME OVER  =============\n\n");
	printf("Player 1 ending cards: ");
	printCards(player1Hand);
	printf("Player 2 ending cards: ");
	printCards(player2Hand);
	//prints the winner. There is a case in which both players lose.
	if(player1Hand == NULL && player2Hand != NULL){
		printf("\nPlayer 1 ran out of cards. Player 2 wins.\n");
		destroyCards(player2Hand);
	}
	else if(player2Hand == NULL && player1Hand != NULL){
		printf("\nPlayer 2 ran out of cards. Player 1 wins.\n");
		destroyCards(player1Hand);
	}
	else{
		printf("\nBoth players ran out of cards. Nobody wins.\n");
	}
	printf("The end.\n");
	
	return 0;
}
