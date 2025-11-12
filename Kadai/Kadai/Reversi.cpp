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


Reversi::Reversi(IsMass _playerMass, IsMass _enemyMass) {
	for (int y = 0; y < _massMax; y++) {
		for (int x = 0; x < _massMax; x++) {
			mass[y][x].SetThisMass(IsMass::None);
		}
	}
	playerMassCol = _playerMass;
	enemyMassCol = _enemyMass;
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
	cout << "＠|";
	for (int i = 1; i < _massMax+1; i++) {
		
		cout << std::format("{:2}",i) << "|";
	}
	cout << '\n'<<"----------------------------"<<'\n';

	for (int y = 1; y < _massMax + 1; y++) {
		cout << std::format("{:2}", y) + "|";
		for (int x = 1; x < _massMax + 1; x++) {
			string fripMass="　";
			switch (mass[y-1][x - 1].GetThisMass())
			{
			case IsMass::Black:
					fripMass = "＊";
					break;
			case IsMass::White:
				fripMass = "〇";
				break;
			}

			cout << fripMass << "|";
		}
		cout << '\n' << "----------------------------" << '\n';
	}

	
}

//終了ならtrueが返ってきます
bool Reversi::InputSetMass(IsMass setIsMass) {
	string coments[10] = { "入力受付状態：1～８までの値を受け付けます。また、｛e｝と打つと終了します",
		"｛横軸｝で配置したい位置を入力してください。 : ｛0｝で入力値をリセットします",
		"｛縦軸｝で配置したい位置を入力してください。 : ｛0｝で入力値をリセットします",
		"数字で1～８までの値を入力してください。",
		"あなたは",
		"AIは",
		"縦",
		"横",
		"の位置に配置しました。" ,
		"そこにはすでに何かが存在します。"
	};

	bool returnEnd = false;
	bool returnFlag = false;
	int setPoint[2] = { 0,0 };
	do {
		returnFlag = false;

		cout << coments[0]<<'\n';


		bool endFlagY = false;
		bool endFlagX = false;
		do {
			cout << coments[1] << '\n';

			int input = Reversi::InputFx();

			if (input == -1) {
				cout << coments[3] << '\n';
			}
			else if (input == -2) {
				returnEnd = true;
				endFlagY = true;
				endFlagX = true;
			}
			else if (input == -3) {
				endFlagY = true;
				endFlagX = true;
				returnFlag = true;
			}
			else {
				setPoint[1] = input;
				endFlagX = true;
			}

		} while (!endFlagX);

		if (!endFlagY) {
			do {
				cout << coments[2] << '\n';

				int input = Reversi::InputFx();

				if (input == -1) {
					cout << coments[3] << '\n';
				}
				else if (input == -2) {
					returnEnd = true;
					endFlagY = true;
					endFlagX = true;
				}
				else if (input == -3) {
					endFlagY = true;
					endFlagX = true;
					returnFlag = true;
				}
				else {
					setPoint[0] = input;
					endFlagY = true;
				}

			} while (!endFlagY);
		}

		if(!returnEnd)
			if (Reversi::FindMassDate(setPoint[1], setPoint[0]) != IsMass::None) {
				cout << coments[9] << '\n';
				returnFlag = true;

				Reversi::ShowGrid();
			}

		if (!returnEnd && !returnFlag) {


			Reversi::SetMassDate(setPoint[1], setPoint[0], setIsMass);

			string teamMess = "";
			if (setIsMass == playerMassCol) {
				teamMess = coments[4];
			}
			else	if (setIsMass == enemyMassCol) {
				teamMess = coments[5];
			}

			cout << teamMess << coments[6] << setPoint[0] + 1 << coments[7] << setPoint[1] + 1 << coments[8] << '\n';

		}

		cout << "============================================"<<'\n';

	} while (returnFlag);

	return returnEnd;
}

//プレイヤーから数字を獲得します。
//-1エラー -2終了 -3やりなおし
int Reversi::InputFx(char endif,char returnif) {
	string input;
	cin >> input;


	int reutrnInt = 0;
	for (int i = 0; i < input.length();i++) {
		//数字1～９なら
		if (input[i] >= '1' && input[i] <= '9') {
			//以前にリターンに変更が加えられてるなら２桁目
			if (reutrnInt != 0) {
				reutrnInt = -1;
				break;
			}
			reutrnInt = (input[i] - '0')-1;
		}
		//終了判定
		else if (input[i] == endif) {
			reutrnInt = -2;
		}
		//やりなおし判定
		else if (input[i] == returnif) {
			reutrnInt = -3;
		}
		//エラー判定
		else {
			reutrnInt = -1;
		}
	}

	return reutrnInt;

}

//現状のマスの中で変化が発生する場合は処理を行います。
void Reversi::Variation(IsMass targetMass,IsMass myMass) {
	for (int y = 0; y < _massMax; y++) {
		for (int x = 0; x < _massMax; x++) {
			
			if (mass[y][x].GetThisMass() != myMass)
				break;



		}
	}
}

void Reversi::AllCheack(int x,int y, IsMass targetMass, IsMass myMass,int _x,int _y) {

	//横での確認
	for (int z = 1; z < _massMax + 1; z++) {

		int count = 0;

		//オーバーで終了
		if (x + z >= _massMax)
			break;

		//自分のマスを確認したら
		if (mass[y][x + z].GetThisMass() == myMass)
		{
			//それまでのマスを全て変える
			int _z = x + z;
			for (int i = 0; i < count; i++) {
				mass[y][_z - i].SetThisMass(myMass);
			}
		}
		//空欄なら終了
		if (mass[y][x + z].GetThisMass() == IsMass::None) {
			break;
		}

		count++;
	}
}


