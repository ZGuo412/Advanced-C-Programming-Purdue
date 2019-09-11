#include "shuffle.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// You may add more functions in this file.
void divide(CardDeck orig_deck, CardDeck * upper_deck, CardDeck * lower_deck) {
  for(int i = 0; i < orig_deck.size - 1; i++)
  {   
      upper_deck[i].size = i + 1;
	  lower_deck[i].size = orig_deck.size - i - 1;
      for(int j = 0; j <= i; j++)
	  {
      	upper_deck[i].cards[j] = orig_deck.cards[j];
	  }
	  for(int j = i + 1; j <= orig_deck.size - 1; j++)
	  {
	  	lower_deck[i].cards[j - i - 1] = orig_deck.cards[j];
	  }

  }
	  return;
}

          
void _getcard(CardDeck upper_deck, CardDeck lower_deck, CardDeck takecard){
CardDeck newdeck = {
	  	.size = upper_deck.size - 1,
		.cards = {0}
	  };
	
	  if(upper_deck.size > 0)
	  {
     	takecard.cards[takecard.size++] = upper_deck.cards[0];
      	memcpy(newdeck.cards, upper_deck.cards + 1, (upper_deck.size -1) * sizeof(upper_deck.cards[1]));
      	_getcard(newdeck, lower_deck,takecard);
      	takecard.size--;
	  }
	  newdeck.size = lower_deck.size - 1;
	  if(lower_deck.size > 0)
	  {
     	takecard.cards[takecard.size++] = lower_deck.cards[0];
      	memcpy(newdeck.cards, lower_deck.cards + 1, (lower_deck.size -1) * sizeof(lower_deck.cards[1]));
      	_getcard(upper_deck,newdeck,takecard);
      	takecard.size--;
	  }
      if (upper_deck.size == 0 && lower_deck.size == 0)
      {
	  	print_deck(takecard);
		fprintf(stdout, "\n");
	  }
	  return;  
}
void interleave(CardDeck upper_deck, CardDeck lower_deck) {
     CardDeck takecard = {
	 	.size = 0,
		.cards = {0}
	};
	_getcard(upper_deck, lower_deck, takecard);
	  return;
}
void shuffle(CardDeck orig_deck) {
	int numpairs = orig_deck.size -1;

	CardDeck * upper_deck = malloc(sizeof(*upper_deck) * (orig_deck.size - 1));
	CardDeck * lower_deck = malloc(sizeof(*lower_deck) * (orig_deck.size - 1));

	// allocate memory
	if (upper_deck == NULL) {
	free(lower_deck);
	return;
	}
	if (lower_deck == NULL) {
	free(upper_deck);
	return;
	}
    divide(orig_deck, upper_deck, lower_deck);
	// call divideDeck to fill upper_deck and lower_deck 
	

	while (numpairs > 0) {
	interleave(upper_deck[numpairs - 1], lower_deck[numpairs - 1]);
	numpairs--;


		// for each pairs call interleave
	}
	free(upper_deck);
	free(lower_deck);
	return;
} 
