
#include <string>
#include <iostream>
#include "Reversi.h"
#include "Time.h"
#include <memory> 

int main() {
	using namespace std;

	int maxsize = 8;
	auto gamedate = std::make_shared<Reversi>(IsMass::White, IsMass::Black, maxsize);
	ReversiAI ai(gamedate, maxsize);
	Timer time=Timer();

	bool endFlag = false;

	gamedate->SetMassDate(3, 3, gamedate->GetPlayerColor());
	gamedate->SetMassDate(4, 4, gamedate->GetPlayerColor());
	gamedate->SetMassDate(3, 4, gamedate->GetEnemyColor());
	gamedate->SetMassDate(4,3, gamedate->GetEnemyColor());

	do {

		gamedate->ShowGrid();

		endFlag = ai.InputSetMass(gamedate->GetPlayerColor(), gamedate->GetEnemyColor());

		gamedate->ShowGrid();

		cout << "“G‚ªl‚¦‚Ä‚¢‚Ü‚·c" << '\n';

		time.WaitTime(1.5f);

		if(!endFlag)
			ai.RandomSetMass(gamedate->GetEnemyColor(), gamedate->GetPlayerColor(),"“G‚Í");

		endFlag = gamedate->EndGame();

	} while (!endFlag);


	//cout << "ƒQ[ƒ€ƒGƒ“ƒh" << '\n';

	

}