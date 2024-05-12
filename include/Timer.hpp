#ifndef TIMER_H
#define TIMER_H

class Timer {
private:
    float lifeTime;

    bool CheckTimer();
public:
    Timer(); // Assigned with no val

    void StartTimer(float lifeTime);
    bool UpdateTimer(float deltaTime);
};

#endif