/***********************************************************
*CardGameProject.h
*By: Julian Stanton, Ryan, and Josh
*
*
*Program Description:
*	A driver program to play card games
*************************************************************/

#include "Crazy8.h"
#include <iostream>


int main(){


	int game = 1;
	int playerCount = 1;
	cout << "What Game?";
	//cin >> game;

	if (game==1){
		//Julian's Game Crazy Eights
		//cout << "players?" << endl;
		//cin >> playerCount;
		CrazyEight c8(playerCount, false);

	} else	if (game == 2){
		//Josh's game
	}
	else if (game == 3){
		//Ryan's game
	}


	return 0;
}
