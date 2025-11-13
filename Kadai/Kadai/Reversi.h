#pragma once

//リバーシヘッダ部

#ifndef __REVERSI_H
#define __REVERSI_H

#include <vector>
#include <iostream>

enum class IsMass
{
	None,
	Error,
	Black,
	White,
	
};

//位置情報とその裏表をみている
class MassDate {
private:
	IsMass thisMass = IsMass::None;


public:
	MassDate();
	MassDate(IsMass startDate);
	IsMass GetThisMass() const { return thisMass; }
	void SetThisMass (IsMass ismass);


};

//リバーシなど全体を見ている
class Reversi {
private:
	 const int _massMax;
	
	 std::vector<std::vector<MassDate>> mass;

	//std::shared_ptr<MassDate[][_massMax]> mass = std::shared_ptr<MassDate[][_massMax]>(new MassDate[_massMax][_massMax]);

	IsMass playerMassCol;
	IsMass enemyMassCol;

public:
	Reversi(IsMass _playerMass,IsMass _enemyMass,int massMax);
	IsMass GetPlayerColor() const { return playerMassCol; }
	IsMass GetEnemyColor() const { return enemyMassCol; }
	IsMass FindMassDate(int x, int y)const;
	bool SetMassDate(int x, int y, IsMass setIsMass);
	void ShowGrid()const;
	bool InputSetMass(IsMass setIsMass);
	void Variation(IsMass targetMass, IsMass myMass);

private:
	int InputFx(char endif = 'e', char returnif = '0');
	void AllCheack(int x, int y, IsMass targetMass, IsMass myMass, int _x, int _y);
};


#endif