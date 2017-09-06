#pragma once
#include <iostream>
#include "windows.h"

using namespace std;

class CalFPS
{
public:
	CalFPS();
	~CalFPS();
	void init();
	void printFPS();
	int Frame_Count;
	double Last_Time, Current_Time;
private:

};

CalFPS::CalFPS()
{
}

CalFPS::~CalFPS()
{
}

void CalFPS::init()
{
	Frame_Count = 0;
	Last_Time = GetTickCount();
}
void CalFPS::printFPS()
{
	Frame_Count++;
	Current_Time = GetTickCount();
	double stamp = Current_Time - Last_Time;  //µ¥Î»£ººÁÃë
	if (stamp > 1000)
	{
		cout <<"current FPS: " << Frame_Count << endl;
		Frame_Count = 0;
		Last_Time = Current_Time;
	}
}