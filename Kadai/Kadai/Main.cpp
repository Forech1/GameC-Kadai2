
#include <string>
#include <iostream>
#include "Reversi.h"

int main() {
	using namespace std;

	Reversi gamedate(IsMass::White,IsMass::Black);

	bool endFlag = false;
	do {
		gamedate.SetMassDate(1, 0, IsMass::Black);
		gamedate.SetMassDate(2, 0, IsMass::Black);
		gamedate.SetMassDate(3, 0, IsMass::Black);
		gamedate.SetMassDate(4, 0, IsMass::Black);
		gamedate.SetMassDate(5, 0, IsMass::Black);
		gamedate.SetMassDate(6, 0, IsMass::Black);
		gamedate.SetMassDate(7, 0, IsMass::White);

		gamedate.SetMassDate(0, 1, IsMass::Black);
		gamedate.SetMassDate(0, 2, IsMass::Black);
		gamedate.SetMassDate(0, 3, IsMass::Black);
		gamedate.SetMassDate(0, 4, IsMass::Black);
		gamedate.SetMassDate(0, 5, IsMass::Black);
		gamedate.SetMassDate(0, 6, IsMass::Black);
		gamedate.SetMassDate(0, 7, IsMass::White);
		
		endFlag = gamedate.InputSetMass(IsMass::White);
		gamedate.ShowGrid();
	} while (!endFlag);




	

}