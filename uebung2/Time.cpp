#include "Time.h"

static float deltaTimeValue = 0.0f;
static std::chrono::time_point<std::chrono::high_resolution_clock> lastNow = std::chrono::high_resolution_clock::now();

static float timeSinceLastSecond = 0.0f;
static int updatesSinceLastSecond = 0;
static int fpsValue;

Time::Time()
{
}

Time::~Time()
{
}

void Time::update() {
	std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
	auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(now - lastNow);
	deltaTimeValue = ((float)microseconds.count()) / 1'000'000.0f;
	deltaTimeValue = (deltaTimeValue < 0.0f) ? 0 : deltaTimeValue;
	updatesSinceLastSecond++;

	timeSinceLastSecond += deltaTimeValue;
	if (timeSinceLastSecond >= 1.0f) {
		timeSinceLastSecond -= 1.0f;
		fpsValue = updatesSinceLastSecond;
		updatesSinceLastSecond = 0;
	}

	lastNow = now;
}

float Time::deltaTime() {
	return deltaTimeValue;
}

int Time::fps() {
	return fpsValue;
}


