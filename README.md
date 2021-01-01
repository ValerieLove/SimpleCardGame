# SimpleCardGame
A simple text based card game using linked lists in C.

This is a simple card game with simple rules. This game uses linked lists to keep track of a player's hand.

RULES

A command line argument is passed showing how many cards each player will start with. The player's hands are stored in a linked list and each card the player draws is a randomly generated node that is inserted into the linked list in order by its value. Each card has three attributes, a card type, a card value, and a pointer to the next card in the list. When a player draws a new card, it gets added into the hand in order by its value. There are three types of of cards: ATTACK, DEFEND, and RUN. After the players play their cards, the cards go into the discard pile, called "the abyss." There are nine possible scenarios that can occur with these cards.

Both players ATTACK
-If both players, play ATTACK cards with the same value, nothing happens. Otherwise, the player who plays the higher value card will draw a new card and add it to their hand and the player with the lower value card will lose their next card into the abyss.

One player ATTACKs and the other player DEFENDs
-If attacking player's card has a higher value card than the defending player's card, the attacking player gets a new card. Otherwise, if the attacking player's card has an equal or lesser value than the defending player's card, the attacking player loses a card.

One player ATTACKs and one player RUNs
-The running player automatically loses their next card into the abyss regardless of the running player's card value.

Both players DEFEND
-If both players defend, nothing happens.

One player DEFENDs, and the other player RUNs.
-The running player automatically loses their next card into the abyss regardless of the running player's card value. The defending player draws a new card and adds it to their hand.

Both players RUN
-Both players automatically lose their next cards into the abyss

If a player cannot play a card, they lose the game. It is possible for both players to lose the game.
