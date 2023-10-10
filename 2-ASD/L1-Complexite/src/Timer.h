//
// Created by Guillaume Trüeb on 23.02.23.
//

#ifndef ASD2022_L1_COMPLEXITE_TIMER_H
#define ASD2022_L1_COMPLEXITE_TIMER_H

#include <ctime>

class Timer {
public:
    void start();
    void stop();
    void reset();
    int getElapsedTime();
private:
    double startTime;
    double stopTime;
};


#endif //ASD2022_L1_COMPLEXITE_TIMER_H
