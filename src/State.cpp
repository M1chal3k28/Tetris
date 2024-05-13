#include "State.hpp"

States::State::State() : state(States::ApplicationState::Menu) {}

States::ApplicationState States::State::GetState() {
    return this->state;
}

void States::State::SetState(States::ApplicationState newState) {
    this->state = newState;
}
