#ifndef STATE_H
#define STATE_H

namespace States {
    enum ApplicationState {
        Menu = 1,
        Paused = 2,
        Game = 3,
        GameOver = 4
    };

    class State {
    private:
        States::ApplicationState state;

    public:
        State();

        States::ApplicationState GetState();
        void SetState(States::ApplicationState newState);
    };
}

#endif