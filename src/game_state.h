#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SFML/Graphics.hpp>
// includes ...

class Game;
// Samo referenca da se ne uvode cirkularne zavisnosti!

class GameState{
public:
    // Sva moguća stanja igre.
    enum State {
        Welcome,
        Playing,
        Won,
        Lost,
        Exiting,
        Count     // Count će dati broj stanja. 
    };
    GameState(Game * game) : mpGame(game) {}

    // Metode koje ovise o stanju.
    virtual void update(sf::Time dt) = 0;
    virtual void handlePlayerInput(sf::Keyboard::Key code)= 0;
    virtual void render() = 0;

protected:
    Game * mpGame;
};

#endif // GAME_STATE_H

//


// koji se dio koda mijenja ovisno o stanju?
    // mjenja se update, render, ali nece se mijenjati citavi proces event
    // dovoljno je mjenjati handle player input
    // game klasa drzi pokazivac na GameState klasu : ( ona implemntira stvari... update, handle player i render ovise o stanju)
    // update nece biti u klasi game, ni render ni handle.. njih cemo pzivati preko pokazivaca na tsanje
    // jer ce svako stanje to implementirati za sebe

// prijelazi stanja :
    // iz Welcome state na pritisak bilo cega idemo u game
    // svako stanje ce pozvati metodu iz game klase changeState

// Game klasa implementira stanja u svom konstruktoru
//neke informacije trebamo predai iz jednog stanja u drugo! (pr. broj bodova) pronaci nacin komunikacija
    // primjer : svako stanje ima pokazivac na game klasu!

// da bi iscrtali tekst, trebaju nam fontovi, klasa font, a imamo klasu text za ispis teksta
