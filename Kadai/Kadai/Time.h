#pragma once
#ifndef __TIME_H
#define __TIME_H

#include <string>
#include <iostream>
#include "Reversi.h"
#include <format>
#include <vector>
#include <array>
#include <chrono>
#include <random>
#include <memory> 

class Timer {
private:

public:
	Timer();
	bool WaitTime(float waitTimes);
};

#endif