#pragma once

//リバーシヘッダ部

#ifndef __REVERSI_H
#define __REVERSI_H

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
	void SetThisMass(IsMass ismass);


};

//リバーシなど全体を見ている
class Reversi {
private:
	static const int _massMax = 8;
	MassDate mass[_massMax][_massMax];

public:
	Reversi();
	IsMass FindMassDate(int x, int y);
	bool SetMassDate(int x, int y, IsMass setIsMass);
	void ShowGrid();
};


#endif