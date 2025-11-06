//リバーシのデータを保存しています。
#include <string>
#include <iostream>
#include "Reversi.h"
#include <format>
#include <vector>
#include <array>

using namespace std;

MassDate::MassDate() {
	thisMass = IsMass::None;
}
MassDate::MassDate(IsMass startDate) {
	thisMass = startDate;
}
//マスデータをセット
void MassDate::SetThisMass(IsMass ismass) {
	thisMass = ismass;
}


Reversi::Reversi() {
	for (int y = 0; y < _massMax; y++) {
		for (int x = 0; x < _massMax; x++) {
			mass[y][x].SetThisMass(IsMass::None);
		}
	}
}

//xy指定した場所のマスデータを取得
IsMass Reversi::FindMassDate(int x, int y) {
	//範囲内
	if (x >= _massMax)
		return IsMass::Error;
	if (x < 0)
		return IsMass::Error;
	if (y >= _massMax)
		return IsMass::Error;
	if (y < 0)
		return IsMass::Error;

	return mass[y][x].GetThisMass();
}

bool Reversi::SetMassDate(int x, int y, IsMass setIsMass) {
	//範囲内
	if (x >= _massMax)
		return false;
	if (x < 0)
		return false;
	if (y >= _massMax)
		return false;
	if (y <0)
		return false;

	mass[y][x].SetThisMass(setIsMass);

	return true;
}

void Reversi::ShowGrid() {

	for (int i = 0; i < _massMax; i++) {
		cout << "＠";
		cout<<i + "ー";
	}
	cout << '\n';

	for (int y = 0; y < _massMax; y++) {
		cout << y + "|";
		for (int x = 0; x < _massMax; x++) {
			string fripMass="　";
			switch (mass[y][x].GetThisMass())
			{
			case IsMass::Black:
					fripMass = "●";
					break;
			case IsMass::White:
				fripMass = "〇";
				break;
			}

			cout << fripMass + "|"<<'\n';
		}
	}

	
}




