#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "game.h"
#include "game_state.h"
#include "snake.h"
#include "world.h"

// Naša glavna state-klasa. Veći dio koda iz 
// prethodne Game klase završit će ovdje s manjim izmjenama.   
class PlayingState : public GameState{

public:
    PlayingState(Game *game);
    // Procesiraj događaje
    void processEvents();
    // konstruiraj novo stanje igre
    void update(sf::Time dt);
    // iscrtaj novo stanje
    void render();

    void handlePlayerInput(sf::Keyboard::Key code);


private:
    World mWorld;
    Snake mSnake;


    // fiksiranje vremenskog koraka
    sf::Time mTimePerFrame;


};


#endif // PLAYING_STATE_H
// ovdje ide vecina koda iz nase snake klase!!


/*
 * klasa game iz snake zadace
 *
class Game{
public:
    Game();
    void run();
private:
    // Procesiraj događaje
    void processEvents();
    // konstruiraj novo stanje igre
    void update(sf::Time dt);
    // iscrtaj novo stanje
    void render();
private:
    sf::RenderWindow mWindow;

    World mWorld;
    Snake mSnake;

    // fiksiranje vremenskog koraka
    sf::Time mTimePerFrame;

    void handlePlayerInput(sf::Keyboard::Key code);
};

*/
