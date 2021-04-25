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

//TODO
//shufle discard back in
//if fist discard is 8 shuffle back in
// AI

using namespace std;

class CrazyEight{
public:
	CrazyEight(int numPlayers, bool multyDraw = true);
	~CrazyEight();

private:
	deckOfCards* deck;
	int numPlayers;
	void play();
	void playAI();
	Player *players;
	void dealCards();
	Player discardPile;
	cardNode drawCard();
	bool validMove(cardNode a, cardNode b);
	void drawScreen();
	int currentPlayer;
	int numCards;
	int crazySuit;
	bool multyDraw;

};

void CrazyEight::playAI(){

	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn = 0;
	dealCards();
	discardPile.addCard(drawCard());

	cardNode* playersCards = new cardNode[numCards];
	cardNode* validCards;
	cardNode chosenCard;
	cardNode discardTop[1];

	char crazySuit = 0;
	int cardIndex;
	int crazyEight;
	int suitCount[4];
	//3 → ♥//4 → ♦//5 → ♣//6 → ♠


	bool valid = true;

	while (!endOfGame){	

		if (currentPlayer >= numPlayers){
			currentPlayer = 0;
		}

		for (int i = 0; i < 4; i++)		{
			suitCount[i] = 0;
		}
		system("cls");

		players[currentPlayer].getHand(playersCards, players[currentPlayer].getCardCount());


		discardPile.getHand(discardTop, 1);
		cout << "Player " << currentPlayer + 1 << "'s turn. What Card to play? (1 through " << players[currentPlayer].getCardCount() << ") or "
			<< players[currentPlayer].getCardCount() + 1 << " to draw new card" << endl;

		players[currentPlayer].showAllCards();

		cout << "Discard Pile: ";
		if (crazySuit){
			discardTop[0].suit = crazySuit;
		}
		cout << discardTop[0].face << discardTop[0].suit;
		crazySuit = 0;
		cout << endl;


		if (currentPlayer==0){

			if (!valid){
				cout << chosenCard.face << chosenCard.suit << endl;
				cout << "Not Valid!" << endl << "Select a different card" << endl;
			}

			valid = true;
			cin >> playerIn;

			if (playerIn > 0 && playerIn < players[currentPlayer].getCardCount() + 1){
				chosenCard = playersCards[playerIn - 1];

				cout << chosenCard.face << chosenCard.suit << endl;

				if (chosenCard.face == '8'){
					cout << "Its an 8, choose new suit" << endl;
					cout << "1)" << char(HEARTS) << " 2)" << char(DIOMONDS) << " 3)" << char(CLUBS) << " 4)" << char(SPADES) << endl;
					playerIn = 0;

					players[currentPlayer].removeCard(chosenCard);
					discardPile.addCard(chosenCard);

					while (playerIn <= 0 || playerIn > 4){
						cin >> playerIn;
					}
					playerIn += 2;
					crazySuit = playerIn;
					goto endOfTurn;

				}

				if (validMove(chosenCard, discardTop[0])){
					cout << "Valid" << endl;
					players[currentPlayer].removeCard(chosenCard);
					discardPile.addCard(chosenCard);
					goto endOfTurn;

				} else{
					valid = false;
					goto endOfTurn;

				}
			} else if (playerIn == players[currentPlayer].getCardCount() + 1){
				players[currentPlayer].addCard(drawCard());
				if (multyDraw){
					continue;
				}
				goto endOfTurn;
			}

		} else	{
			
			//AI
			validCards = new cardNode[players[currentPlayer].getCardCount()];
			cardIndex = 0;
			crazyEight = 0;
			for (int i = 0; i < players[currentPlayer].getCardCount(); i++)		{

				if (validMove(playersCards[i], discardTop[0])){
					if (playersCards[i].face != '8')	{
						validCards[cardIndex++] = playersCards[i];
					} else	{
						crazyEight = i;
						cout << "FOUND 8" << endl;
					}
					cout<<"Valid: " << playersCards[i].face << playersCards[i].suit << endl;

				}
				suitCount[playersCards[i].suit - 3]++;
			}

			if (cardIndex && !crazyEight){
				chosenCard = validCards[cardIndex];
				if (validMove(chosenCard, validCards[cardIndex])){
					cout << "AI playng " << chosenCard << endl;
					players[currentPlayer].removeCard(chosenCard);
					discardPile.addCard(chosenCard);
				} else{
					cout << "oops" << endl;
				}
				cin >> playerIn;
				goto endOfTurn;
			}

			if (crazyEight){
				cout << "Only 8" << endl;
			} else{
				cout << "No valid move?" << endl;
			}


			delete [] validCards;



		}



		cin >> playerIn;



	endOfTurn:
		if (players[currentPlayer].getCardCount() == 0){
			endOfGame = true;
		}
		if (valid){
			currentPlayer++;
		}

	}

	cout << "Congrats player " << currentPlayer << " You Won!";

	delete[] playersCards;

}

void CrazyEight::play(){

	bool endOfGame = false;
	int playerIn;
	int curPlayersTurn =0;
	dealCards();
	discardPile.addCard(drawCard());

	cardNode* PlayersCards = new cardNode[numCards];

	cardNode chosenCard;
	cardNode discardTop[1];

	char crazySuit = 0;
	
	//3 → ♥//4 → ♦//5 → ♣//6 → ♠

	bool valid = true;

	while (!endOfGame){

		if (currentPlayer>=numPlayers)	{
			currentPlayer = 0;
		}
		system("cls");
		players[currentPlayer].getHand(PlayersCards, players[currentPlayer].getCardCount());
		

		discardPile.getHand(discardTop, 1);
		cout << "Player " << currentPlayer+1 << "'s turn. What Card to play? (1 through " << players[currentPlayer].getCardCount() << ") or "
			<< players[currentPlayer].getCardCount() + 1 << " to draw new card" << endl;

		players[currentPlayer].showAllCards();

		cout << "Discard Pile: ";
		if (crazySuit){
			discardTop[0].suit = crazySuit;
		}
		cout << discardTop[0].face << discardTop[0].suit;
		crazySuit = 0;
		cout << endl;

		if (!valid)	{
			cout << chosenCard.face << chosenCard.suit << endl;
			cout << "Not Valid!" << endl<< "Select a different card"<<endl;
		}
		valid = true;
		cin >> playerIn;

		if (playerIn > 0 && playerIn < players[currentPlayer].getCardCount() + 1){
			chosenCard = PlayersCards[playerIn - 1];

			cout << chosenCard.face << chosenCard.suit << endl;

			if (chosenCard.face == '8'){
				cout << "Its an 8, choose new suit" << endl;
				cout << "1)" << char(HEARTS) << " 2)" << char(DIOMONDS) << " 3)" << char(CLUBS) << " 4)" << char(SPADES) << endl;
				playerIn = 0;

				players[currentPlayer].removeCard(chosenCard);
				discardPile.addCard(chosenCard);

				while (playerIn <=0 || playerIn > 4)	{
					cin >> playerIn;
				}
				playerIn+=2;
				crazySuit = playerIn;
				goto endOfTurn;

			}

			if (validMove(chosenCard, discardTop[0])){
				cout << "Valid" << endl;
				players[currentPlayer].removeCard(chosenCard);
				discardPile.addCard(chosenCard);
				goto endOfTurn;

			} else{
				valid = false;
				goto endOfTurn;
				
			}
		} else if (playerIn == players[currentPlayer].getCardCount() + 1){
			players[currentPlayer].addCard(drawCard());
			if (multyDraw){
				continue;
			}
			goto endOfTurn;
		}

	endOfTurn:
		if (players[currentPlayer].getCardCount()==0)	{
			endOfGame = true;		
		}
		if (valid)	{
			currentPlayer++;
		}


	}

	cout << "Congrats player " << currentPlayer << " You Won!";

	delete [] PlayersCards;
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

CrazyEight::CrazyEight(int numPlayers, bool multyDraw){
	this->numPlayers = numPlayers;
	this->multyDraw = multyDraw;

	bool AI = false;

	int handSize = 7;
	int numDecks =1;

	currentPlayer = 0;
	if (this->numPlayers == 1){
		numDecks = 1;
		handSize = 7;
		AI = true;
		this->numPlayers = 2;
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
	players = new Player[this->numPlayers];

	deck->shuffleDeck();

	numCards = 52 * numDecks;
	
	for (int i = 0; i < this->numPlayers; i++)		{
		players[i].createPlayer(handSize , numCards);
	}

	discardPile.createPlayer(0, numCards);

	if (AI)	{
		playAI();
	}
	else{
		play();
	}




}

CrazyEight::~CrazyEight(){

	delete [] players;
	delete deck;
}

#endif