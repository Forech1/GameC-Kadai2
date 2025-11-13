//リバーシのデータを保存しています。
#include <string>
#include <iostream>
#include "Reversi.h"
#include <format>
#include <vector>
#include <array>
#include <chrono>
#include <random>

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


Reversi::Reversi(IsMass _playerMass, IsMass _enemyMass, int massMax):_massMax(massMax),mass(_massMax,std::vector<MassDate>(_massMax)) {
	for (int y = 0; y < _massMax; y++) {
		for (int x = 0; x < _massMax; x++) {
			mass[y][x].SetThisMass(IsMass::None);
		}
	}
	playerMassCol = _playerMass;
	enemyMassCol = _enemyMass;
}

//xy指定した場所のマスデータを取得
IsMass Reversi::FindMassDate(int x, int y) const {
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
//マスをセットします
bool Reversi::SetMassDate(int x, int y, IsMass setIsMass) {
	//範囲内
	if (x >= _massMax)
		return false;
	if (x < 0)
		return false;
	if (y >= _massMax)
		return false;
	if (y < 0)
		return false;

	mass[y][x].SetThisMass(setIsMass);

	return true;
}

//ルールに乗っ取ってマスをセットします。
bool Reversi::RuleSetMassDate(int x, int y, IsMass setIsMass,IsMass targetMass) {
	if (SetCheack(targetMass, setIsMass,y,x)) {

		if (SetMassDate(x, y, setIsMass))
			return true;
		else
			return false;
	}
	return false;
}
//ルールに乗っ取ってマスをセットして、影響するマスをすべてひっくり返します。
bool Reversi::RuleSetAndVariationMassDate(int x, int y, IsMass setIsMass, IsMass targetMass) {
	if (SetMassDate(x, y, setIsMass)) {
		
		if (SetCheackVariation(targetMass, setIsMass, y, x)) {
			//cout << "許可" << '\n';
			return true ;
		}
			
		else {
			SetMassDate(x, y, IsMass::None);
			
			return false;
		}
			
	}
	//cout << "範囲外配置" << '\n';
	return false;
}

//グリッドを表示します
void Reversi::ShowGrid()const {
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
					fripMass = "〇";
					break;
			case IsMass::White:
				fripMass = "＠";
				break;
			}

			cout << fripMass << "|";
		}
		cout << '\n' << "----------------------------" << '\n';
	}

	
}

////終了ならtrueが返ってきます
//bool Reversi::InputSetMass(IsMass setIsMass, IsMass targetMass) {
//	string coments[12] = { "入力受付状態：1～",
//		"｛横軸｝で配置したい位置を入力してください。 : ｛0｝で入力値をリセットします",
//		"｛縦軸｝で配置したい位置を入力してください。 : ｛0｝で入力値をリセットします",
//		"数字で1～",
//		"あなたは",
//		"縦",
//		"横",
//		"の位置に配置しました。" ,
//		"そこにはすでに何かが存在します。",
//		"その位置はマスを置けません。",
//		"までの値を受け付けます。また、｛e｝と打つと終了します",
//		"までの値を入力してください。"
//	};
//
//	bool returnEnd = false;
//	bool returnFlag = false;
//	int setPoint[2] = { 0,0 };
//	do {
//		returnFlag = false;
//
//		cout << coments[0]<<_massMax<<coments[10]<<  '\n';
//
//
//		bool endFlagY = false;
//		bool endFlagX = false;
//		do {
//			cout << coments[1] << '\n';
//
//			int input = Reversi::InputFx();
//
//			if (input == -1) {
//				cout << coments[3]<< _massMax << coments[11] << '\n';
//			}
//			else if (input == -2) {
//				returnEnd = true;
//				endFlagY = true;
//				endFlagX = true;
//			}
//			else if (input == -3) {
//				endFlagY = true;
//				endFlagX = true;
//				returnFlag = true;
//			}
//			else {
//				setPoint[1] = input;
//				endFlagX = true;
//			}
//
//		} while (!endFlagX);
//
//		if (!endFlagY) {
//			do {
//				cout << coments[2] << '\n';
//
//				int input = Reversi::InputFx();
//
//				if (input == -1) {
//					cout << coments[3] << _massMax << coments[11]<< '\n';
//				}
//				else if (input == -2) {
//					returnEnd = true;
//					endFlagY = true;
//					endFlagX = true;
//				}
//				else if (input == -3) {
//					endFlagY = true;
//					endFlagX = true;
//					returnFlag = true;
//				}
//				else {
//					setPoint[0] = input;
//					endFlagY = true;
//				}
//
//			} while (!endFlagY);
//		}
//
//		if(!returnEnd)
//			if (Reversi::FindMassDate(setPoint[1], setPoint[0]) != IsMass::None) {
//				cout << coments[9] << '\n';
//				returnFlag = true;
//
//				Reversi::ShowGrid();
//			}
//
//		if (!returnEnd && !returnFlag) {
//			if (!Reversi::RuleSetAndVariationMassDate(setPoint[1], setPoint[0], setIsMass, targetMass)) {
//				cout << coments[9] << '\n';
//				returnFlag = true;
//				Reversi::ShowGrid();
//				continue;
//			}
//			string teamMess = "";
//			if (setIsMass == playerMassCol) {
//				teamMess = coments[4];
//			}
//			//else	if (setIsMass == enemyMassCol) {
//			//	teamMess = coments[5];
//			//}
//
//			cout << teamMess << coments[6] << setPoint[0] + 1 << coments[5] << setPoint[1] + 1 << coments[7] << '\n';
//
//		}
//
//		cout << "============================================"<<'\n';
//
//	} while (returnFlag);
//
//	return returnEnd;
//}
//
////ランダムでマスを配置します。
//void Reversi::RandomSetMass(IsMass setIsMass, IsMass targetMass,string mess) {
//
//	std::mt19937 engine{ std::random_device{}() };
//
//
//	std::vector<std::vector<int>> randomPoint;
//	int count = 0;
//
//	//配置できる位置データのみを取得
//	for (int y = 0; y < _massMax; y++) {
//		for (int x = 0; x < _massMax; x++) {
//			if (SetCheack(targetMass, setIsMass, y, x)) {
//				randomPoint.push_back(std::vector<int>());
//				randomPoint[count].push_back(y);
//				randomPoint[count].push_back(x);
//				count++;
//			}
//		}
//	}
//	std::uniform_int_distribution<int> dist(0, randomPoint.size()-1);
//
//	//ランダムで置ける配置に接地します。
//	auto target = dist(engine);
//	RuleSetAndVariationMassDate(randomPoint[target][1], randomPoint[target][0], setIsMass, targetMass);
//
//	std::cout << mess << "横" << randomPoint[target][1] + 1 << "縦" << randomPoint[target][0] + 1 << "置きました。" << '\n';
//
//}


//現状のマスの中で変化が発生する場合は処理を行います。
//(変化する対象のマスの種類,基準になるマス)
void Reversi::Variation(IsMass targetMass,IsMass myMass) {
	for (int y = 0; y < _massMax; y++) {
		for (int x = 0; x < _massMax; x++) {
			
			if (mass[y][x].GetThisMass() != myMass)
				continue;

			//各方向でマスの状態を確認し、マスに変更を行います。

			//x++
			CheackReverse(y, x, targetMass, myMass, 0, 1);
			//x--
			CheackReverse(y, x, targetMass, myMass, 0, -1);
			//y++
			CheackReverse(y, x, targetMass, myMass, 1, 0);
			//y--
			CheackReverse(y, x, targetMass, myMass, -1, 0);
			//x+y+
			CheackReverse(y, x, targetMass, myMass, 1, 1);
			//x-y-
			CheackReverse(y, x, targetMass, myMass, -1, -1);
			//x+y-
			CheackReverse(y, x, targetMass, myMass, -1, 1);
			//y-x+
			CheackReverse(y, x, targetMass, myMass, 1, -1);



		}
	}
}

//五目のチェックシステムを元に作られたマス確認システムのC++バージョン
bool Reversi::CheackReverse(int y,int x, IsMass targetMass, IsMass myMass,int _y,int _x) {

	int count = 0;

	//横での確認
	for (int z = 1; z <= _massMax + 1; z++) {

		

		//オーバーで終了
		if (x + (z * _x) >= _massMax || y + (z * _y) >= _massMax || x + (z * _x) < 0 || y + (z * _y) < 0)
			return false;

		//自分のマスを確認したら
		if (mass[y + (z * _y)][x + (z * _x)].GetThisMass() == myMass)
		{
			if(z==1)
				return false;
			else {

				//それまでのマスを全て変える
				int _xz = x + (z * _x);
				int _yz = y + (z * _y);
				for (int i = 1; i <= count; i++) {
					/*cout << _yz - (i * _y) << " " << _xz - (i * _x)<<'\n';*/
					mass[_yz - (i * _y)][_xz - (i * _x)].SetThisMass(myMass);
				}
				/*cout << '\n';*/
				return true;
			}
		}
		//敵ますなら続行
		else if (mass[y + (z * _y)][x + (z * _x)].GetThisMass() == targetMass) {
			count++;
		}
		//空欄やそれ以外なら終了
		else {
			return false;
		}
	}
	return false;
}

//チェックのみ行い、リバースはしない。
bool Reversi::Cheack(int y, int x, IsMass targetMass, IsMass myMass, int _y, int _x)const {

	//横での確認
	for (int z = 1; z < _massMax + 1; z++) {

		//オーバーで終了
		if (x + (z * _x) >= _massMax || y + (z * _y) >= _massMax || x + (z * _x) < 0 || y + (z * _y) < 0)
			return false;

		//自分のマスを確認したら
		if (mass[y + (z * _y)][x + (z * _x)].GetThisMass() == myMass)
		{
			//始めから自分ますの場合は不可
			if (z == 1)
				return false;
			else
				return true;
		}
		//敵ますなら続行
		else if (mass[y + (z * _y)][x + (z * _x)].GetThisMass() == targetMass) {

		}
		//空欄やそれ以外なら終了
		else {
			return false;
		}
	}
	return false;
}

//していますが配置可能ならtrueが帰ります。y
bool Reversi::SetCheack(IsMass targetMass, IsMass myMass,int y,int x)const {
	if (Reversi::FindMassDate(x, y) != IsMass::None)
		return false;

	//各方向でマスの状態を確認します
	//x++
	if (Cheack(y, x, targetMass, myMass, 0, 1))
		return true;
	//x--
	if (Cheack(y, x, targetMass, myMass, 0, -1))
		return true;
	//y++
	if (Cheack(y, x, targetMass, myMass, 1, 0))
		return true;
	//y--
	if (Cheack(y, x, targetMass, myMass, -1, 0))
		return true;
	//x+y+
	if (Cheack(y, x, targetMass, myMass, 1, 1))
		return true;
	//x-y-
	if (Cheack(y, x, targetMass, myMass, -1, -1))
		return true;
	//x+y-
	if (Cheack(y, x, targetMass, myMass, -1, 1))
		return true;
	//y-x+
	if (Cheack(y, x, targetMass, myMass, 1, -1))
		return true;

	return false;
}

//していますが配置可能ならtrueが帰ります。その上成功したらマスも入れ替わります。
bool Reversi::SetCheackVariation(IsMass targetMass, IsMass myMass, int y, int x) {
	//if (Reversi::FindMassDate(x, y) != IsMass::None) {
	//	cout << "マスかぶり" << '\n';
	//	return false;
	//}
		
	bool returnbool = false;;

	//各方向でマスの状態を確認します
	//x++
	if (CheackReverse(y, x, targetMass, myMass, 0, 1))
		returnbool = true;
	//x--
	if (CheackReverse(y, x, targetMass, myMass, 0, -1))
		returnbool = true;
	//y++
	if (CheackReverse(y, x, targetMass, myMass, 1, 0))
		returnbool = true;
	//y--
	if (CheackReverse(y, x, targetMass, myMass, -1, 0))
		returnbool = true;
	//x+y+
	if (CheackReverse(y, x, targetMass, myMass, 1, 1))
		returnbool = true;
	//x-y-
	if (CheackReverse(y, x, targetMass, myMass, -1, -1))
		returnbool = true;
	//x+y-
	if (CheackReverse(y, x, targetMass, myMass, -1, 1))
		returnbool = true;
	//y-x+
	if (CheackReverse(y, x, targetMass, myMass, 1, -1))
		returnbool = true;

	//if (!returnbool)
	//	cout << "持続失敗" << '\n';

	return returnbool;
}

//終了かどうかを反転します
void Reversi::EndPlayerSet() {
	noSetPlayer = !noSetPlayer;
}
void Reversi::EndEnemySet() {
	noSetEnemy = !noSetEnemy;
}

std::vector<std::vector<int>> Reversi::FindAllOkSetMassPoints(IsMass targetMass, IsMass setIsMass) {
	std::vector<std::vector<int>> randomPoint;
	int count = 0;

	//配置できる位置データのみを取得
	for (int y = 0; y < _massMax; y++) {
		for (int x = 0; x < _massMax; x++) {
			if (SetCheack(targetMass, setIsMass, y, x)) {
				randomPoint.push_back(std::vector<int>());
				randomPoint[count].push_back(y);
				randomPoint[count].push_back(x);
				count++;
			}
		}
	}

	return randomPoint;
}

bool Reversi::EndGame() {

	if (noSetPlayer == true && noSetEnemy == true) {
		int white = 0;
		int black = 0;

		//配置できる位置データのみを取得
		for (int y = 0; y < _massMax; y++) {
			for (int x = 0; x < _massMax; x++) {
				if (mass[y][x].GetThisMass() == IsMass::White)
					white++;
				else if (mass[y][x].GetThisMass() == IsMass::Black)
					black++;

			}
		}

		cout << "黒 " << black << " 個 " << "白 " << white << " 個 " << '\n';
		string winer = "引き分け";
		if (black > white)
			winer = "敵の勝ち";
		else if (black < white)
			winer = "プレイヤーの勝ち";
		cout << "結果は " << winer<<'\n';


		return true;
	}
	else {

		noSetEnemy = false;
		noSetPlayer = false;
		return false;
	}
}


ReversiAI::ReversiAI(std::shared_ptr<Reversi> _game,int massMax) :game(_game),_massMax(massMax) {

}

//終了ならtrueが返ってきます
bool ReversiAI::InputSetMass(IsMass setIsMass, IsMass targetMass) {
	string coments[13] = { "入力受付状態：1～",
		"｛横軸｝で配置したい位置を入力してください。 : ｛0｝で入力値をリセットします",
		"｛縦軸｝で配置したい位置を入力してください。 : ｛0｝で入力値をリセットします",
		"数字で1～",
		"あなたは",
		"縦",
		"横",
		"の位置に配置しました。" ,
		"そこにはすでに何かが存在します。",
		"その位置はマスを置けません。",
		"までの値を受け付けます。また、｛e｝と打つと終了します",
		"までの値を入力してください。",
		"あなたは＠です。敵は〇です。"
	};

	std::vector<std::vector<int>> randomPoint = game->FindAllOkSetMassPoints(targetMass, setIsMass);

	if (randomPoint.size() == 0) {
		cout << "なんと" << coments[4] << "置ける場所が無い！" << '\n';
		if (setIsMass == game->GetPlayerColor()) {
			game->EndPlayerSet();
		}
		else if (setIsMass == game->GetEnemyColor()) {
			game->EndEnemySet();
		}
		return false;
	}


	bool returnEnd = false;
	bool returnFlag = false;
	int setPoint[2] = { 0,0 };
	cout << coments[12] << '\n';
	do {
		returnFlag = false;

		cout << coments[0] << _massMax << coments[10] << '\n';



		bool endFlagY = false;
		bool endFlagX = false;
		do {
			cout << coments[1] << '\n';

			int input = InputFx();

			if (input == -1) {
				cout << coments[3] << _massMax << coments[11] << '\n';
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

				int input = InputFx();

				if (input == -1) {
					cout << coments[3] << _massMax << coments[11] << '\n';
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

		if (!returnEnd)
			if (game->FindMassDate(setPoint[1], setPoint[0]) != IsMass::None) {
				cout << coments[9] << '\n';
				returnFlag = true;

				game->ShowGrid();
			}

		if (!returnEnd && !returnFlag) {
			if (!game->RuleSetAndVariationMassDate(setPoint[1], setPoint[0], setIsMass, targetMass)) {
				cout << coments[9] << '\n';
				returnFlag = true;
				game->ShowGrid();
				continue;
			}
			string teamMess = "";
			if (setIsMass == game->GetPlayerColor()) {
				teamMess = coments[4];
			}
			//else	if (setIsMass == enemyMassCol) {
			//	teamMess = coments[5];
			//}

			cout << teamMess << coments[6] << setPoint[0] + 1 << coments[5] << setPoint[1] + 1 << coments[7] << '\n';

		}

		cout << "============================================" << '\n';

	} while (returnFlag);

	return returnEnd;
}

//ランダムでマスを配置します。
void ReversiAI::RandomSetMass(IsMass setIsMass, IsMass targetMass, string mess) {

	std::mt19937 engine{ std::random_device{}() };

	std::vector<std::vector<int>> randomPoint= game->FindAllOkSetMassPoints(targetMass, setIsMass);
	
	if (randomPoint.size() == 0) {
		cout << "なんと" << mess << "置ける場所が無い！" << '\n';
		if (setIsMass == game->GetPlayerColor()) {
			game->EndPlayerSet();
		}
		else if (setIsMass == game->GetEnemyColor()) {
			game->EndEnemySet();
		}
		return;
	}
	std::uniform_int_distribution<int> dist(0, static_cast<int>(randomPoint.size()) - 1);

	//ランダムで置ける配置に接地します。
	auto target = dist(engine);
	game->RuleSetAndVariationMassDate(randomPoint[target][1], randomPoint[target][0], setIsMass, targetMass);

	std::cout << mess << "横" << randomPoint[target][1] + 1 << "縦" << randomPoint[target][0] + 1 << "置きました。" << '\n';

}

//プレイヤーから数字を獲得します。
//-1エラー -2終了 -3やりなおし
int ReversiAI::InputFx(char endif, char returnif) {
	string input;
	cin >> input;


	int reutrnInt = 0;
	for (int i = 0; i < input.length(); i++) {
		//数字1～９なら
		if (input[i] >= '1' && input[i] <= '9') {
			//以前にリターンに変更が加えられてるなら２桁目
			if (reutrnInt != 0) {
				reutrnInt = -1;
				break;
			}
			reutrnInt = (input[i] - '0') - 1;
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

