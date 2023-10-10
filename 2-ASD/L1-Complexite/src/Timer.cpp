#include <cmath>
#include "Timer.h"

void Timer::start() {
    startTime = (double)clock();
}

void Timer::stop() {
    stopTime = (double)clock();
}

void Timer::reset() {
    startTime = 0;
    stopTime = 0;
}

int Timer::getElapsedTime() {
    return int(((stopTime - startTime) / CLOCKS_PER_SEC) * pow(10, 6));
}