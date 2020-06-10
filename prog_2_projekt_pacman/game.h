#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

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
        this->okno_aplikacji.create(sf::VideoMode(x, y, 32), "PacMan");
    }
};


// \brief Klasa za pomoca ktorej mozna latwo stworzyc grafike gotowa do wyswietlenia podajac lokalizacje tekstury
// \param przyklad: Grafika obrazek("lokalizacja/tekstura.png");
class Grafika
{
public:
    sf::Texture tekstura;                         //objekt przechowujacy teksture
    sf::Sprite sprajt;                            //objekt do wyswietlenia na ekranie

    Grafika(std::string plik)
    {                                    
        this->tekstura.loadFromFile(plik);        //Zaladowanie tekstury do zmiennej
        this->sprajt.setTexture(tekstura);        //Ustawienie tekstury dla sprite
    }
};

extern rozmiar_okna rozmiar_menu;
extern rozmiar_okna rozmiar_gry;
extern Game gra;
extern Grafika start;
extern Grafika logo;
extern Grafika opcje;
extern bool czy_wlaczona;                       //Zmienna logiczna -> potrzeba do petli glownej programu
extern int typ_menu;                            //zmienna odpowiadajaca za typ okna: 1 - MENU; 2- GRA; 3 - OPCJE