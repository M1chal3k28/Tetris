#include "Timer.hpp"

Timer::Timer() : lifeTime(0) {}

void Timer::StartTimer(float lifeTime) {
    this->lifeTime = lifeTime;
}

bool Timer::UpdateTimer(float deltaTime) {
    this->lifeTime -= deltaTime;

    return this->CheckTimer();
}

bool Timer::CheckTimer() { return this->lifeTime <= 0.f; }