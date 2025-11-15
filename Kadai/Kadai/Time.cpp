#include <string>
#include <iostream>
#include "Time.h"
#include <format>
#include <vector>
#include <array>
#include <chrono>
#include <random>

using namespace std;

Timer::Timer() {

}

bool Timer::WaitTime(float waitTimes) {


	long whrteWaitTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::duration<float>(waitTimes)).count();
	long startTime = std::chrono::time_point_cast<std::chrono::seconds>(chrono::system_clock::now()).time_since_epoch().count();

	long waitTime = startTime + whrteWaitTime;

	long maxtime = 0;
	while (true) {
		
		long nowTime = std::chrono::time_point_cast<std::chrono::seconds>(chrono::system_clock::now()).time_since_epoch().count();


		if (nowTime > waitTime) {
			break;
		}
		//–³ŒÀƒ‹[ƒv‰ñ”ð
		if (maxtime > 1000000000000000000) {
			break;
		}
		maxtime++;
	}

	return true;
}