#include "aux_states.h"
#include "game.h"
#include <unistd.h>
#include <string>
#include <iostream>
// Implementacija pomoćnih stanja.



/*-------------- WELCOME STATE --------------------------*/

WelcomeState::WelcomeState( Game *game ):GameState(game){

    mIme.setFont( game->mFont );
    mIme.setCharacterSize(20);
    mIme.setColor(sf::Color::White);
    mIme.setString("SNAKE GAME BY Sara P. a.k.a. Belzebub");
    mIme.setOrigin(sf::Vector2f(319.0/2.0, 16.0/2.0 ));
    mIme.setPosition(sf::Vector2f(mpGame->mSize /2.0f , mpGame->mSize /2.0f-16));

//    auto position = mIme.getLocalBounds();
//    std::cout<< position.height << position.width <<std::endl;

    mAnyKey.setFont( game->mFont);
    mAnyKey.setString("HIT ANY KEY TO CONTINUE");
    mAnyKey.setCharacterSize(14);
    mAnyKey.setOrigin(sf::Vector2f(205.0/2.0, 11.0/2.0 ));
    mAnyKey.setPosition(sf::Vector2f(mpGame->mSize /2.0f - 20, mpGame->mSize /2.0f + 80));
}

void WelcomeState::update(sf::Time dt)
{}

void WelcomeState::handlePlayerInput(sf::Keyboard::Key code)
{
   // na pritisak bilo koje tipke prelazim u Playing state
    mpGame->changeState(GameState::Playing);
}

void WelcomeState::render()
{
    // iscrtaj poruku
    mpGame->mWindow.draw(mIme);
    mpGame->mWindow.draw(mAnyKey);
}


/*-------------- EXITING STATE --------------------------*/

ExitingState::ExitingState(Game *game):GameState(game), mCounter(3)
{
    mGoodbye.setFont( game->mFont );
    std::string new_string = "GAME OVER " + std::to_string(mCounter);
    mGoodbye.setString(new_string);
    mGoodbye.setCharacterSize(20);
    mGoodbye.setColor(sf::Color::White);
    mGoodbye.setPosition(sf::Vector2f(mpGame->mSize /2.0f - 100, mpGame->mSize /2.0f-18));

    //mGoodbye.setPosition(sf::Vector2f(200, 200));

}

void ExitingState::update(sf::Time dt)
{

    static sf::Clock clock;
    static sf::Time LastUpdate = sf::Time::Zero;

    const sf::Time delta_t = sf::milliseconds(1000);
    if (  delta_t > LastUpdate ){
        LastUpdate += clock.getElapsedTime();
        return;
    }
    if ( mCounter > 0 ){
        sleep(1);
        mCounter--;
        std::string new_string = "GAME OVER " + std::to_string(mCounter);
        mGoodbye.setString(new_string);
        LastUpdate = sf::Time::Zero;
        clock.restart();
    }
    else
        exit(0);
}

void ExitingState::handlePlayerInput(sf::Keyboard::Key code)
{}

void ExitingState::render()
{
    mpGame->mWindow.draw(mGoodbye);
}


/*-------------- WON STATE --------------------------*/

WonState::WonState(Game *game):GameState(game)
{

    int score = mpGame->getGlobalScore();
    std::string print_score = "CONGRATULATIONS! YOU WON, SCORE = " + std::to_string(score);


    mCongratz.setFont( game->mFont );
    mCongratz.setString(print_score);
    mCongratz.setCharacterSize(20);
    mCongratz.setColor(sf::Color::White);
    mCongratz.setPosition(sf::Vector2f(mpGame->mSize /2.0f - 180, mpGame->mSize /2.0f-18));

    mDirections.setFont( game->mFont);
    mDirections.setString("HIT C TO CONTINUE, X to EXIT");
    mDirections.setCharacterSize(14);
    mDirections.setPosition(sf::Vector2f(mpGame->mSize /2.0f -20, mpGame->mSize /2.0f+80));

}


void WonState::update(sf::Time dt)
{
    int score = mpGame->getGlobalScore();
    std::string print_score = "CONGRATULATIONS! YOU WON, SCORE = " + std::to_string(score);
    mCongratz.setString(print_score);
}

void WonState::handlePlayerInput(sf::Keyboard::Key code)
{
    switch (code) {
    case sf::Keyboard::Key::C:
        mpGame->changeState(GameState::Playing);
        break;
    case sf::Keyboard::Key::X:
        mpGame->changeState(GameState::Exiting);
        break;
    default:
        break;
    }
}

void WonState::render()
{
    mpGame->mWindow.draw(mCongratz);
    mpGame->mWindow.draw(mDirections);
}


/*-------------- LOST STATE --------------------------*/

LostState::LostState(Game *game):GameState(game)
{


    int score = mpGame->getGlobalScore();
    std::string print_score = " YOU LOST,  SCORE = " + std::to_string(score);
    mNotCongratz.setFont( game->mFont );
    mNotCongratz.setString(print_score);
    mNotCongratz.setCharacterSize(20);
    mNotCongratz.setColor(sf::Color::White);
    //mNotCongratz.setPosition(sf::Vector2f(200, 200));
    mNotCongratz.setPosition(sf::Vector2f(mpGame->mSize /2.0f - 100, mpGame->mSize /2.0f-18));


    mDirections.setFont( game->mFont);
    mDirections.setString("HIT C TO CONTINUE, X TO  EXIT");
    mDirections.setCharacterSize(14);
   // mDirections.setPosition(340,340);
    mDirections.setPosition(sf::Vector2f(mpGame->mSize /2.0f - 20, mpGame->mSize /2.0f+80));

}

void LostState::update(sf::Time dt)
{
    int score = mpGame->getGlobalScore();
    std::string print_score = " YOU LOST,  SCORE = " + std::to_string(score);
    mNotCongratz.setString(print_score);
}

void LostState::handlePlayerInput(sf::Keyboard::Key code)
{
    switch (code) {
    case sf::Keyboard::Key::C:
        mpGame->changeState(GameState::Playing);
        break;
    case sf::Keyboard::Key::X:
        mpGame->changeState(GameState::Exiting);
        break;
    default:
        break;
    }
}

void LostState::render()
{
    mpGame->mWindow.draw(mNotCongratz);
    mpGame->mWindow.draw(mDirections);
}

