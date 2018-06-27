#include "playing_state.h"

// Implementacija PlayingState klase

#include <iostream>
#include <string>

// Implementacija Game klase dolazi ovdje.

PlayingState::PlayingState(Game *_game):GameState( _game), mSnake(10), mWorld(sf::Vector2i(500,500))
{
    mTimePerFrame = sf::seconds(1.0/60);
}


void PlayingState::update(sf::Time dt){

    mSnake.update();
    mWorld.update(mSnake);

    if ( mSnake.getLives() == 0 || mSnake.hasLost() ){
        //mpGame->mGlobalScore = mSnake.getScore();
        mpGame->setGlobalScore( mSnake.getScore() );
        if ( mSnake.getScore() >= 100 )
            mpGame->changeState(GameState::Won);
        else
            mpGame->changeState(GameState::Lost);
        mSnake.reset();
        mWorld.respawnApple();
        mSnake.toggleLost();
        mSnake.incSpeed();
    }
}


void PlayingState::render(){

    mpGame->mWindow.draw(mSnake);
    mpGame->mWindow.draw(mWorld);
}


void PlayingState::handlePlayerInput(sf::Keyboard::Key code){

    // ovo ispraviti tako da ne gleda smjer nego odnos zmijine glave i tijela! tako gleda stvarni smjer zmije, a ne ono sto pise u varijabli

    switch ( code ) {
    case (sf::Keyboard::Key::Up) :
        if( (mSnake.getDirection() != Direction::Down) && (mSnake.getDirection() != Direction::None) )
            mSnake.setDirection(Direction::Up);
        break;
    case (sf::Keyboard::Key::Down) :
        if( mSnake.getDirection() != Direction::Up )
            mSnake.setDirection(Direction::Down);
        break;
    case (sf::Keyboard::Key::Left) :
        if( mSnake.getDirection() != Direction::Right )
            mSnake.setDirection(Direction::Left);
        break;
    case (sf::Keyboard::Key::Right) :
        if( mSnake.getDirection() != Direction::Left )
            mSnake.setDirection(Direction::Right);
        break;
    case (sf::Keyboard::Key::W ):
        mSnake.incSpeed();
        break;
    case (sf::Keyboard::Key::S ):
        mSnake.decSpeed();
        break;
    default:
        break;
    }
}
