#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

enum Kierunki { STOP = 0, LEWO, PRAWO, GORA, DOL };

struct rozmiar_okna
{
    int x;
    int y;
};

class Game                                       //podstawowa klasa odpowiedzialna za gre
{
public:
    //Funkcja obslugujaca zdarzenia (zdarzenia.cpp)
    void Event();
    
    //Funkcja do renderowania okna (wstepnie)
    //Trzeba pozniej wywolac funkcje odpowiedzialna za konkretne okno
    void Render();
    
    //Funkcja do renderowania okna (menu)
    void Menu_Render();
    
    //Funkcja do renderowania okna (gra)
    void Game_Render();

    sf::RenderWindow okno_aplikacji;             //Deklaracja glownego okna aplikacji
    sf::Event zdarzenie;                         //Zmienna obslugujaca zdarzenia w aplikacji
    void Init(int x, int y)
    {
        this->okno_aplikacji.create(sf::VideoMode(x, y, 32), "PacMan", sf::Style::Close);
    }
};


// \brief Klasa za pomoca ktorej mozna latwo stworzyc grafike gotowa do wyswietlenia podajac lokalizacje tekstury
// \param przyklad: Grafika obrazek("lokalizacja/tekstura.png");
class Grafika
{
public:
    sf::Texture tekstura;                         //objekt przechowujacy teksture
    sf::Sprite sprajt;                            //objekt do wyswietlenia na ekranie
    //Grafika() {};
    Grafika(std::string plik)
    {                                    
        this->tekstura.loadFromFile(plik);        //Zaladowanie tekstury do zmiennej
        this->sprajt.setTexture(tekstura);        //Ustawienie tekstury dla sprite
    }
};

//Klasa postaci ktora steruje gracz
class PacMan
{
public:
    sf::Vector2i pozycja_rysowania;                                              //koordynaty pozycji gracza
    Grafika postac = Grafika("grafiki/sprite_sheet.png");
    Kierunki kierunek_aktualny;                                                  //kierunek aktualnie wybrany przez gracza
    PacMan() {
        postac.sprajt.setTextureRect(sf::IntRect(3, 3, 26, 26));                 //tekstura postaci wycieta z arkusza tekstur
        //Pozycje startowe gracza
        pozycja_rysowania.x = 387;
        pozycja_rysowania.y = 442;
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);     //ustawienie pozycji gracza
    }
    void Ruch_postaci();
};
class Blinky  //czerwony przeciwnik (podaza za pacmanem)
{

};

class Pinky  //rozowy przeciwnik (zachodzi droge)
{

};

class Inky  //blekitny przeciwnik (zmieniajace sie decyzje)
{

};

class Clyde //pomaranczowy przeciwnik (goni, ale gdy jest blisko pacmana zaczyna uciekac)
{

};

//Tablica logiczna
// '0' -> domyslne pole, mozliwy ruch dla wszystkich
// '-' -> pole zablokowane dla ruchu
// '#' -> punkty, ktore trzeba zbierac, po zebraniu staja sie '0'
// 'X' -> boostery, pozwalajace zjadac duchy
// '2' -> teleport do 3 (dostepne tylko dla gracza)
// '3' -> teleport do 2 (dostepne tylko dla gracza)
// '9' -> pole ruchu dostepne tylko dla przeciwnikow
const char poziom_1[][28] =
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'-','#','#','#','#','#','#','#','#','#','#','#','#','-','-','#','#','#','#','#','#','#','#','#','#','#','#','-',
'-','#','-','-','-','-','#','-','-','-','-','-','#','-','-','#','-','-','-','-','-','#','-','-','-','-','#','-',
'-','X','-','-','-','-','#','-','-','-','-','-','#','-','-','#','-','-','-','-','-','#','-','-','-','-','X','-',
'-','#','-','-','-','-','#','-','-','-','-','-','#','-','-','#','-','-','-','-','-','#','-','-','-','-','#','-',
'-','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','-',
'-','#','-','-','-','-','#','-','-','#','-','-','-','-','-','-','-','-','#','-','-','#','-','-','-','-','#','-',
'-','#','-','-','-','-','#','-','-','#','-','-','-','-','-','-','-','-','#','-','-','#','-','-','-','-','#','-',
'-','#','#','#','#','#','#','-','-','#','#','#','#','-','-','#','#','#','#','-','-','#','#','#','#','#','#','-',
'-','-','-','-','-','-','#','-','-','-','-','-','0','-','-','0','-','-','-','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','-','-','-','0','-','-','0','-','-','-','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','0','0','0','0','0','0','0','0','0','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','-','-','-','9','9','-','-','-','0','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','-','9','9','9','9','9','9','-','0','-','-','#','-','-','-','-','-','-',
'2','0','0','0','0','0','#','0','0','0','-','9','9','9','9','9','9','-','0','0','0','#','0','0','0','0','0','3',
'-','-','-','-','-','-','#','-','-','0','-','9','9','9','9','9','9','-','0','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','-','-','-','-','-','-','-','-','0','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','0','0','0','0','0','0','0','0','0','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','-','-','-','-','-','-','-','-','0','-','-','#','-','-','-','-','-','-',
'-','-','-','-','-','-','#','-','-','0','-','-','-','-','-','-','-','-','0','-','-','#','-','-','-','-','-','-',
'-','#','#','#','#','#','#','#','#','#','#','#','#','-','-','#','#','#','#','#','#','#','#','#','#','#','#','-',
'-','#','-','-','-','-','#','-','-','-','-','-','#','-','-','#','-','-','-','-','-','#','-','-','-','-','#','-',
'-','#','-','-','-','-','#','-','-','-','-','-','#','-','-','#','-','-','-','-','-','#','-','-','-','-','#','-',
'-','X','#','#','-','-','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','-','-','#','#','X','-',
'-','-','-','#','-','-','#','-','-','#','-','-','-','-','-','-','-','-','#','-','-','#','-','-','#','-','-','-',
'-','-','-','#','-','-','#','-','-','#','-','-','-','-','-','-','-','-','#','-','-','#','-','-','#','-','-','-',
'-','#','#','#','#','#','#','-','-','#','#','#','#','-','-','#','#','#','#','-','-','#','#','#','#','#','#','-',
'-','#','-','-','-','-','-','-','-','-','-','-','#','-','-','#','-','-','-','-','-','-','-','-','-','-','#','-',
'-','#','-','-','-','-','-','-','-','-','-','-','#','-','-','#','-','-','-','-','-','-','-','-','-','-','#','-',
'-','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','-',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'
};

extern PacMan gracz1;
extern rozmiar_okna rozmiar_menu;
extern rozmiar_okna rozmiar_gry;
extern Game gra;
extern Grafika start;
extern Grafika logo;
extern Grafika tlo;
extern bool czy_wlaczona;                       //Zmienna logiczna -> potrzeba do petli glownej programu
extern int typ_menu;                            //zmienna odpowiadajaca za typ okna: 1 - MENU; 2- GRA; 3 - OPCJE