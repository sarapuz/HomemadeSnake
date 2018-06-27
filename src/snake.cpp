#include "snake.h"

//Prof:
// Implementacija Snake klase.






Snake::Snake(int blockSize)
{
    msize = blockSize;

    sf::Vector2f size_(msize, msize);
    mbodyRect.setSize( size_ );
    mbodyRect.setOutlineColor(sf::Color::Black);
    mbodyRect.setOutlineThickness(1.0);

    mdir = Direction::None;

    mspeed = 5;
    mlives = 3;
    mlost = false;
    mscore = 0;

    // neka pocetna varijabla bude (4, 10) i neka zmijica gleda za dole
    for ( int i = 0; i < 4; ++i){
        SnakeSegment segment(4, 10 - i);
        mSnakeBody.push_back( segment );
    }
}

// vraća poziciju glave zmije
sf::Vector2i Snake::getPosition()
{
    // vraca poziciju glave zmije- glava je prvi element vektora
    sf::Vector2i pozicija(mSnakeBody[0].x, mSnakeBody[0].y );
    return pozicija;

}

// produzi zmiju za jedan blok u smjeru suprotnom od smjera kretanja
void Snake::extend()
{
    // produziti zmiju za jedan blok - dodati element u vektor
    //                               - vektor se sastoji od segmenata (x, y) koordinate
    // zadnji element uzmi zadnji element vektora i na odnosu toga izracunaj poziciju novog zadnjeg bloka

    SnakeSegment newBlock(mSnakeBody[mSnakeBody.size()-1].x, mSnakeBody[mSnakeBody.size()-1].y );

    switch ( mdir ) {
    case Direction::Left :
        newBlock.x++;
        break;
    case Direction::Right :
        newBlock.x--;
        break;
    case Direction::Up :
        newBlock.y++;
        break;
    case Direction::Down :
        newBlock.y--;
        break;
    default:
        break;
    }
    mSnakeBody.push_back(newBlock);
}

void Snake::reset()
{
    // vrati zmiju na velicinu 4, u gornji lijevi kut ekrana sa smjerom None
    mSnakeBody.clear();
    for ( int i = 0; i < 4; ++i){
        SnakeSegment segment(4, 10 - i);
        mSnakeBody.push_back( segment );
    }
    mscore = 0;
    mlives = 3;
    setDirection(Direction::None);
}


void Snake::update()
{
    static sf::Clock clock;
    static sf::Time LastUpdate = sf::Time::Zero;
    const sf::Time delta_t = sf::milliseconds(1000/mspeed);
    if ( LastUpdate + delta_t > clock.getElapsedTime() )
        return;
    LastUpdate += delta_t;
    move();
    checkCollision();
}

// Odsijeca zadnjih n blokova, popa iz vektora zadnjih n elemenata
void Snake::cut(int n)
{
    mlives--;
    for (int i = 0; i < n ; ++i ){
        mSnakeBody.pop_back();
    }
}

// mijenja zmijin vektor za jedan u smjeru kretnje - prvi element dobiva nove vrijednosti a svi stari samo od prethodnika
void Snake::move()
{
    // krecemo od zadnjeg element vekotra i svakom dajemo vrijednost onoga koji je sljedeci
    // tako radimo sve do glave; glavi dajemo nove koordinate

    if ( mdir != Direction::None ){
        for( int i = mSnakeBody.size()-1; i > 0; --i){
            mSnakeBody[i] = mSnakeBody[i-1];
        }
    }
    // ovisno o smjeru zmiji se povecava i smanjuje x ili y varijabla
    switch ( mdir ) {
    case Direction::Left :
        mSnakeBody[0].x--;
        break;
    case Direction::Right :
        mSnakeBody[0].x++;
        break;
    case Direction::Up :
        mSnakeBody[0].y--;
        break;
    case Direction::Down :
        mSnakeBody[0].y++;
        break;
    default:
        break;
    }

}

// treba provjeriti jesu li bilo koj dva elementa vekotra ( zmijinog tijela jednaki) to ce znati da je zmija sama sebe pregazila
void Snake::checkCollision()
{
    for( int i = 1; i < mSnakeBody.size(); ++i){
        // provjeravam je li glava presjekla neki dio svoga tijela
        if( mSnakeBody[0].x == mSnakeBody[i].x && mSnakeBody[0].y == mSnakeBody[i].y  ){
            // ako je presjekla zovem funkciju cut(size-i) tako da odrezem taj dio tijela
            cut(mSnakeBody.size() - i );
            return;
        }
    }
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    // treba li ovdje negdje recu da su ti kvadrati velicine msize x msize - NE to cemo u konstruktoru
     for( int i = 0; i < mSnakeBody.size(); ++i){
         if ( i == 0 )
             mbodyRect.setFillColor(sf::Color::Yellow);
         else
             mbodyRect.setFillColor(sf::Color::Green);
         mbodyRect.setPosition( mSnakeBody[i].x*msize, mSnakeBody[i].y*msize  );
         mbodyRect.setSize(sf::Vector2f(msize, msize));
         target.draw( mbodyRect );
     }
}

