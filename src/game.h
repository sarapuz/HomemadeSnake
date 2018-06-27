#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>
#include "aux_states.h"
#include "playing_state.h"
#include "game_state.h"

// Klasa koja predstavlja igru.
class Game{
public:
    Game();
    void run();

    // sve metode pozivaju ovu metodu kako bi mijenjale stanje
    void changeState(GameState::State newState){ mpCurrentGameState = mpGameStates[newState]; }
    // ostali dio sučelja

    sf::Font mFont;
    sf::RenderWindow mWindow;
    sf::Time         mTimePerFrame;
    int mSize;
    int getGlobalScore(){ return mGlobalScore; }
    void setGlobalScore( int Score ){ mGlobalScore = Score; }

private:

    void processEvents();
    // trenutno stanje igre određeno je ovim pokazivačem.
    GameState *      mpCurrentGameState;

    // Sva stanja igre. GameState::Count daje broj stanja. 

    std::array<GameState*,GameState::Count> mpGameStates;
    // ostale privatne varijable
    int mGlobalScore;

    // eventualne friend deklaracije
};

#endif // GAME-V1_H_INCLUDED
