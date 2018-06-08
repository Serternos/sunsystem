#ifndef _TIME_H
#define _TIME_H

#include <chrono>
#include <iostream>

class Time
{
public:
	Time();
	~Time();

	///<summary>
	/// time in seconds between last two calls to update()
	///</summary>
	static float deltaTime();

	static int fps();

	///<summary>
	/// sets a new deltaTime value
	///</summary>
	static void update();
};

#endif //_TIME_H

