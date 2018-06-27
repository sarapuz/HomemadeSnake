#include "world.h"
//Prof:
// Implementacija World klase. 

#include <ctime>
#include <random>
#include <iostream>

// Implementacija klase World dolazi ovdje.


// metoda draw ima ovakvu signaturu, uzima referencu na target i na njemu pozivamo draw i iscrtavamo - slicno cemo napraviti u zmiji
World::World(sf::Vector2i windowSize): mWindowSize(windowSize)
{
    mBlockSize = 10;
    auto radius = getBlockSize();
    mApple.setRadius(radius/2);
    mApple.setFillColor( sf::Color::Red );

    auto maxX = mWindowSize.x / getBlockSize();
    auto maxY = mWindowSize.y / getBlockSize();

    std::random_device rd;
    std::mt19937 gen1(rd());
    std::mt19937 gen2(rd());
    std::uniform_int_distribution<> disx(1, maxX-2);
    std::uniform_int_distribution<> disy(1, maxY-2);
    sf::Vector2f  position_(disx(gen1)*mBlockSize, disy(gen2)*mBlockSize);

    mApple.setPosition(position_);

    mBounds[0].setFillColor(sf::Color::Blue);
    mBounds[0].setSize(sf::Vector2f( mBlockSize, windowSize.y));
    mBounds[0].setPosition(windowSize.x-mBlockSize, 0);

    mBounds[1].setFillColor(sf::Color::Blue);
    mBounds[1].setSize(sf::Vector2f(mBlockSize,windowSize.y));
    mBounds[1].setPosition(0, 0);

    mBounds[2].setFillColor(sf::Color::Blue);
    mBounds[2].setSize(sf::Vector2f( windowSize.x,  mBlockSize));
    mBounds[2].setPosition(0,0);

    mBounds[3].setFillColor(sf::Color::Blue);
    mBounds[3].setSize(sf::Vector2f(windowSize.x,mBlockSize));
    mBounds[3].setPosition(0, windowSize.y-mBlockSize);
}

void World::respawnApple()
{
    auto maxX = mWindowSize.x / getBlockSize();
    auto maxY = mWindowSize.y / getBlockSize();

    // uniformno izabrani brojevi
    std::random_device rd;
    std::mt19937 gen1(rd());
    std::mt19937 gen2(rd());
    std::uniform_int_distribution<> disx(1, maxX-2);
    std::uniform_int_distribution<> disy(1, maxY-2);
    sf::Vector2f  position_(disx(gen1)*mBlockSize, disy(gen2)*mBlockSize);

    mApple.setPosition(position_);
}

void World::update(Snake &snake)
{

    // provjerimo kolizije

    // je li udarila zid ?
    auto snake_position = snake.getPosition();
    if ( snake_position.x == 0 || snake_position.y == 0 )
        snake.lose();
        //snake.reset();
    if ( snake_position.x+1 == mWindowSize.x/mBlockSize || snake_position.y+1 == mWindowSize.y/mBlockSize )
        snake.lose();
        //snake.reset();


    // je li pojela jabuku?
    auto apple_positon = mApple.getPosition();
     if ( snake_position.x == apple_positon.x/mBlockSize && snake_position.y == apple_positon.y/mBlockSize ){
         // povecaj zmiju, povecaj score, respavnaj jabuku
         snake.extend();
         snake.increaseScore();
         respawnApple();
     }
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(int i=0; i<4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}
