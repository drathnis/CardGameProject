/***********************************************************
*Crazy8.h
*By: Julian Stanton
*
*
*Program Description:
*	A class to play crazy 8s
*************************************************************/

#ifndef CRAZY8_H
#define CRAZY8_H

#include "deckOfCards.h"
#include "player.h"


class CrazyEight{
public:
	CrazyEight(int numPlayers);
	~CrazyEight();

private:
	deckOfCards* deck;
	int numPlayers;
	void play();
	Player *players;
	void dealCards();
	Player discardPile;
	cardNode drawCard();
	bool validMove(cardNode a, cardNode b);
	void drawScreen();
	int currentPlayer;
	int numCards;
	int crazySuit;


};

void CrazyEight::play(){
	cout << "Play" << endl;
	dealCards();
	players[0].showAllCards();
	cout << endl;
	players[1].showAllCards();

	bool endOfGame = false;
	int playerIn, suitIn;
	int curPlayersTurn =0;

	discardPile.addCard(drawCard());

	cardNode* cards = new cardNode[numCards];

	cardNode chosenCard;

	char crazySuit = 0;
	char harts = 3, spades = 6, clubs = 5, diomonds = 4;

	//3 → ♥
	//4 → ♦
	//5 → ♣
	//6 → ♠

	//// 003, 004, 005 & 006 
	while (!endOfGame){

		drawScreen();
		
		players[currentPlayer].getHand(cards, players[currentPlayer].getCardCount());

		cin >> playerIn;

		if (playerIn > 0 && playerIn < players[currentPlayer].getCardCount()+1){
			chosenCard = cards[playerIn-1];

			cout << chosenCard.face << chosenCard.suit << endl;
			discardPile.getHand(cards, discardPile.getCardCount());

			if (chosenCard.face=='8')	{
				cout << "Its an 8, choose new suit" << endl;
				cout << "1)" << harts << " 2)" << spades << " 3)" << clubs << " 4)" << diomonds << endl;
				cin >> suitIn;
				
				//finish this

			}

			if (validMove(chosenCard, cards[0])){
				cout << "Valid" << endl;
				players[currentPlayer].removeCard(chosenCard);
				discardPile.addCard(chosenCard);
				continue;

			} else{
				cout << "not Valid!" << endl;
			}
		} else if (playerIn == players[currentPlayer].getCardCount() + 1){
			players[currentPlayer].addCard(drawCard());
			continue;
		}
		
		cin >> playerIn;

		if (players[currentPlayer].getCardCount()==0)	{
			cout << currentPlayer << " Wins" << endl;
		}

		if (playerIn ==0 )	{
			endOfGame = true;
		}

	}

	delete [] cards;
}

void CrazyEight::drawScreen(){
	system("cls");

	cout << "Player " << currentPlayer << "'s turn. What Card to play? (1 through "<< players[currentPlayer].getCardCount() <<") or "
		<< players[currentPlayer].getCardCount()+1 <<" to draw new card"<< endl;

	players[currentPlayer].showAllCards();

	cout << "Discard Pile: ";
	discardPile.showFirstCard();
	cout << endl;
}

cardNode CrazyEight::drawCard(){
	cardNode temp;

	string str = deck->takeCard();
	temp.face = str[0];
	temp.suit = str[1];
	return temp;
}

bool CrazyEight::validMove(cardNode a, cardNode b){


	if (a.face==b.face || a.suit == b.suit)	{
		return true;
	}
	return false;
}



void CrazyEight::dealCards(){
	cout << "Dealing Cards" << endl;

	int delt =0;
	int p = 0;
	while (delt< players[p].getHandSize()*numPlayers)	{

		players[p++].addCard(drawCard());
		if (p>=numPlayers)	{
			p = 0;
		}
		delt++;

	}
}

CrazyEight::CrazyEight(int numPlayers){
	this->numPlayers = numPlayers;

	players = new Player[numPlayers];

	int handSize =7;
	int numDecks =1;
	currentPlayer = 0;
	if (this->numPlayers == 1){
		cout << "Sorry you cant play by yourself at the moment" << endl;
	} else if (this->numPlayers == 2){
		numDecks = 1;
		handSize = 7;
	} else if (this->numPlayers < 20){
		numDecks = 2;
		handSize = 5;
	} else{
		numDecks = 3;
		handSize = 5;
	}

	deck = new deckOfCards(numDecks);
	
	deck->shuffleDeck();

	numCards = 52 * numDecks;
	
	for (int i = 0; i < numPlayers; i++)		{
		players[i].createPlayer(handSize , numCards);
	}

	discardPile.createPlayer(0, numCards);

	play();
}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}

#endif