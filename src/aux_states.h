#ifndef AUX_STATES_H
#define AUX_STATES_H

#include "game_state.h"

// Sva pomoćna stanja (osim PlayingState). Njihove implementacije
// su prilično slične pa ih možemo grupirati u jedan file. 

class WelcomeState : public GameState{

    public:

    WelcomeState( Game *game);

    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    private:

    sf::Text mIme;
    sf::Text mAnyKey;
};


class ExitingState : public GameState{

    public:

    ExitingState(Game *game);

    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    private:

    sf::Text mGoodbye;
    int mCounter;
};


class WonState : public GameState{

    public:

    WonState(Game *game);

    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    private:

    sf::Text mCongratz;
    sf::Text mDirections;
};


class LostState : public GameState{

    public:

    LostState(Game *game);

    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();

    private:

    sf::Text mNotCongratz;
    sf::Text mDirections;
};

#endif // AUX_STATES_H
