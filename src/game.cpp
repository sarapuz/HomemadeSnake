#include "game.h"

// Implementacija Game klase

Game::Game():mTimePerFrame ( sf::seconds(1.0/60) ),mSize(500), mWindow( sf::VideoMode(500, 500),  "Snake"), mGlobalScore(0)
{


   // Ovdje alocirati sva stanja i postaviti pokazivač na trenutno stanje.
   /*
    * Inicijaizacija stanja
    */
    mpGameStates[GameState::Welcome] = new WelcomeState(this);
    mpGameStates[GameState::Playing] = new PlayingState(this);
    mpGameStates[GameState::Won]     = new WonState(this);
    mpGameStates[GameState::Lost]    = new LostState(this);
    mpGameStates[GameState::Exiting] = new ExitingState(this);


   /*
    * Postavljanje pocetnog stanja
    */
    mpCurrentGameState=mpGameStates[GameState::Welcome];

   /*
    * Ucitavanja fonta
    */
    if(!mFont.loadFromFile("YIKES!__.ttf"))
                throw std::runtime_error("Cannot load fonts YIKES!__.ttf");

}



// Primjer run - metode. Zavisni dijelovi koda se delegiraju GameState klasama
// kroz pokazivač mpCurrentGameState.


void Game::run(){
    sf::Clock clock;     
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       processEvents();
       timeSinceLastUpdate += clock.restart();
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();
          mpCurrentGameState->update(mTimePerFrame);
       }
       // rendering
       mWindow.clear();
       mpCurrentGameState->render();
       mWindow.display();
    }
}

// obrada događaja
void Game::processEvents(){

   // implementacija  
    sf::Event event;
        while(mWindow.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    mWindow.close();
                    break;
                case sf::Event::KeyPressed:
                    mpCurrentGameState->handlePlayerInput(event.key.code);
                    break;
            }
        }
}
