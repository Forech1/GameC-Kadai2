
#include <string>
#include <iostream>
#include "Reversi.h"

int main() {
	using namespace std;

	Reversi gamedate(IsMass::White,IsMass::Black,8);

	bool endFlag = false;
	//gamedate.SetMassDate(0, 0, IsMass::White);
	//gamedate.SetMassDate(0, 3, IsMass::White);
	//gamedate.SetMassDate(0, 4, IsMass::White);
	//gamedate.SetMassDate(0, 7, IsMass::White);

	//gamedate.SetMassDate(3, 0, IsMass::White);
	//gamedate.SetMassDate(4, 0, IsMass::White);
	//gamedate.SetMassDate(7, 0, IsMass::White);

	//gamedate.SetMassDate(3, 7, IsMass::White);
	//gamedate.SetMassDate(4, 7, IsMass::White);
	//gamedate.SetMassDate(7, 7, IsMass::White);

	//gamedate.SetMassDate(7, 3, IsMass::White);
	//gamedate.SetMassDate(7, 4, IsMass::White);

	//gamedate.SetMassDate(1, 1, IsMass::Black);
	//gamedate.SetMassDate(2, 2, IsMass::Black);

	//gamedate.SetMassDate(1, 3, IsMass::Black);
	//gamedate.SetMassDate(2, 3, IsMass::Black);
	//gamedate.SetMassDate(1, 4, IsMass::Black);
	//gamedate.SetMassDate(2, 4, IsMass::Black);

	//gamedate.SetMassDate(1, 6, IsMass::Black);
	//gamedate.SetMassDate(2, 5, IsMass::Black);
	//gamedate.SetMassDate(1, 6, IsMass::Black);
	//gamedate.SetMassDate(2, 5, IsMass::Black);

	//gamedate.SetMassDate(0, 1, IsMass::Black);
	//gamedate.SetMassDate(0, 2, IsMass::Black);
	//gamedate.SetMassDate(0, 3, IsMass::Black);
	//gamedate.SetMassDate(0, 4, IsMass::Black);
	//gamedate.SetMassDate(0, 5, IsMass::Black);
	//gamedate.SetMassDate(0, 6, IsMass::Black);
	//gamedate.SetMassDate(0, 7, IsMass::White);
	do {


		
		gamedate.ShowGrid();

		endFlag = gamedate.InputSetMass(IsMass::White);

		//gamedate.Variation(gamedate.GetPlayerColor(), gamedate.GetPlayerColor());
		gamedate.Variation(gamedate.GetEnemyColor(), gamedate.GetPlayerColor());
		//gamedate.Variation(gamedate.GetPlayerColor(), gamedate.GetEnemyColor());

		

		gamedate.ShowGrid();
	} while (!endFlag);




	

}