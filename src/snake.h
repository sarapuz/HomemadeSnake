#ifndef SNAKE_H_IS_INCLUDED
#define SNAKE_H_IS_INCLUDED
//Prof:
// Smjestite vašu Snake klasu ovdje


#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

// Implemntacija : zmija je vektor segmenata (-dvije cijelobrojne koordinate)
// podijeliti board na mrežu

struct SnakeSegment{
    SnakeSegment(int x_, int y_) : x(x_), y(y_) {}
    int x;
    int y;
};

using SnakeContainer = std::vector<SnakeSegment>;

// Direction::Up - koristimo s Direction, kad je Direction = None zmija miruje ( na početku )
enum class Direction{ None, Up, Down, Left, Right };

class Snake : public sf::Drawable {
public:
    Snake(int blockSize);
    ~Snake(){}

    void setDirection(Direction dir){ mdir = dir; }
    Direction getDirection() const { return mdir; }

    sf::Vector2i getPosition();

    int  getLives() const { return mlives; }

    // Prikazivanje score-a i života ne treba napraviti!
    int  getScore() const { return mscore; }
    void increaseScore(){ mscore += 10; }
    void incSpeed(){ ++mspeed; }
    void decSpeed(){ if (mspeed > 1) --mspeed; }

    bool hasLost() const {return mlost; }
    void lose(){ mlost = true; } // Igra je izgubljena - game ovom metodom javlja zmiji da je igra gotova
    void toggleLost(){ mlost = !mlost; }

    void extend();   // Povećaj zmiju za jedan blok.
    void reset();    // Vrati zmiju na startnu startnu poziciju.
    void update();   // Update metoda.
    void cut(int n); // Odsjeci zadnjih n segmenata.

private:
    void move();     // Pomakni zmiju za jedan blok u danom smjeru.

    // Provjeri samopresjecanje i napravi odgovarajuću radnju.
    void checkCollision();

    SnakeContainer mSnakeBody; // Segment vector.
    int msize;      // Veličina jednog bloka zmije.
    Direction mdir; // Trenutni smjer kretanja.
    int mspeed;     // Brzina zmije.
    int mlives;     // Broj preostalih života.
    int mscore;     // Postignuti bodovi.
    bool mlost;     // Zastavica za kraj igre.

    // blok u tijelu zmije - služi za iscrtavanje zmije
    mutable sf::RectangleShape mbodyRect;
    // iscrtavanje
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};
#endif

