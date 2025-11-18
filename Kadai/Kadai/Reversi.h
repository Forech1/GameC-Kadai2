#pragma once

//リバーシヘッダ部

#ifndef __REVERSI_H
#define __REVERSI_H

#include <string>
#include <iostream>
#include "Reversi.h"
#include <format>
#include <vector>
#include <array>
#include <chrono>
#include <random>
#include <memory> 

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

	bool noSetPlayer=false;
	bool noSetEnemy = false;

public:
	Reversi(IsMass _playerMass,IsMass _enemyMass,int massMax);
	IsMass GetPlayerColor() const { return playerMassCol; }
	IsMass GetEnemyColor() const { return enemyMassCol; }
	bool GetPlayerGameSet() const { return noSetPlayer; }
	void EndPlayerSet();
	bool GetEnemyGameSet() const { return noSetEnemy; }
	void EndEnemySet();
	IsMass FindMassDate(int x, int y)const;
	bool RuleSetMassDate(int x, int y, IsMass setIsMass, IsMass targetMass);
	bool RuleSetAndVariationMassDate(int x, int y, IsMass setIsMass, IsMass targetMass);
	bool SetMassDate(int x, int y, IsMass setIsMass);
	void ShowGrid()const;
	void Variation(IsMass targetMass, IsMass myMass);
	bool SetCheack(IsMass targetMass, IsMass myMass, int y, int x)const;
	bool SetCheackVariation(IsMass targetMass, IsMass myMass, int y, int x);
	std::vector<std::vector<int>> FindAllOkSetMassPoints(IsMass targetMass, IsMass myMass);
	bool EndGame();
	void Result();

private:

	bool CheackReverse(int x, int y, IsMass targetMass, IsMass myMass, int _x, int _y);
	bool Cheack(int x, int y, IsMass targetMass, IsMass myMass, int _x, int _y)const;
	
};

//配置、操作に関するクラス
class ReversiAI {
private:
	std::shared_ptr<Reversi> game;
	const int _massMax;

public:
	ReversiAI(std::shared_ptr<Reversi> _game, int massMax);
	bool InputSetMass(IsMass setIsMass, IsMass targetMass);
	void RandomSetMass(IsMass setIsMass, IsMass targetMass, std::string mess);

private:
	int InputFx(char endif = 'e', char returnif = '0');
};


#endif