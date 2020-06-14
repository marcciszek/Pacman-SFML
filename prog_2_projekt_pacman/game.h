#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>

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

/////////////////////////////////////////////////////////////////
// \brief Klasa za pomoca ktorej mozna latwo stworzyc grafike 
// gotowa do wyswietlenia podajac lokalizacje tekstury
// \param przyklad: Grafika obrazek("lokalizacja/tekstura.png");
/////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////
// \brief Klasa opisujaca postac gracza
/////////////////////////////////////////////////////////////////
class PacMan
{
public:
    sf::Vector2f pozycja_rysowania;                                              //koordynaty pozycji gracza
    Grafika postac = Grafika("grafiki/sprite_sheet.png");
    Kierunki kierunek_aktualny=STOP;                                                  //kierunek wykonywany przez program { STOP = 0, LEWO, PRAWO, GORA, DOL }
    Kierunki kierunek_nastepny=STOP;                                                  //nastepny kierunek zamierzany przez gracza { STOP = 0, LEWO, PRAWO, GORA, DOL }
    Kierunki kierunek_ostatni=STOP;
    int Ilosc_punktow = 0;
    int boost_aktywny = 0;                                                       //zmienna mowiaca czy pacman moze atakowac przeciwnikow (jesli 1)
    PacMan() {
        postac.sprajt.setTextureRect(sf::IntRect(3, 3, 26, 26));                 //tekstura postaci wycieta z arkusza tekstur
        //Pozycje startowe gracza
        pozycja_rysowania.x = 387;
        pozycja_rysowania.y = (float)441.9;
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);     //ustawienie pozycji gracza
    }
    void Ruch_postaci();
    /////////////////////////////////////////////////////////////////
    // \brief metoda odpowiadajaca za animacje postaci,
    // pozycja poczatkowa w konstruktorze klasy
    /////////////////////////////////////////////////////////////////
    void Animacja_postaci();
    /////////////////////////////////////////////////////////////////
    // \brief metoda zbierajaca punkty i usuwajaca je z planszy
    // \param pozycja logiczna gracza x, pozycja logiczna gracza y
    /////////////////////////////////////////////////////////////////
    void zbieranie_pkt(int pozycja_x, int pozycja_y);
    /////////////////////////////////////////////////////////////////
    // \brief metoda poprawiajaca pozycje gracza,
    // naprawia blad, ktory nie pozwala ruszyc,
    // gdy postac sie zatrzyma o sciane
    // \param odleglosc od kratki logicznej x, odleglosc od kratki logicznej y
    /////////////////////////////////////////////////////////////////
    void poprawa_pozycji(float wzgledna_x, float wzgledna_y);
};
class Blinky  //czerwony przeciwnik (podaza za pacmanem)
{
public:
    sf::Vector2f pozycja_rysowania;
    Grafika czerwony = Grafika("grafiki/sprite_sheet.png");
    Kierunki kierunek_aktualny = LEWO;
    Kierunki kierunek_nastepny;
    int pozycja_ostatniej_zmiany_x = 0;
    int pozycja_ostatniej_zmiany_y = 0;
    bool czy_wybrac_nowy_kierunek = true;
    int ucieczka = 0;                                                                //zmienna mowiaca jaki tryb poruszania sie ma duszek 0-zwykly, 1-ucieczka przed graczem, 2-powrot do bazy
    Blinky() {
        czerwony.sprajt.setTextureRect(sf::IntRect(4, 146, 26, 26));                 //tekstura postaci wycieta z arkusza tekstur
        pozycja_rysowania.x = 387;
        pozycja_rysowania.y = (float)209.6;
        czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);       //ustawienie pozycji gracza
    }
    void Ruch();
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);
    void Animacja();
};

class Pinky  //rozowy przeciwnik (zachodzi droge)
{
public:
    sf::Vector2f pozycja_rysowania;
    Grafika rozowy = Grafika("grafiki/sprite_sheet.png");
    Kierunki kierunek_aktualny = PRAWO;
    Kierunki kierunek_nastepny;
    int pozycja_ostatniej_zmiany_x = 0;
    int pozycja_ostatniej_zmiany_y = 0;
    bool czy_wybrac_nowy_kierunek = true;
    int ucieczka = 0; 
    Pinky() {
        rozowy.sprajt.setTextureRect(sf::IntRect(4, 178, 26, 26));
        pozycja_rysowania.x = 387;
        pozycja_rysowania.y = (float)268;
        rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
    }
    void Ruch();
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);
    void Animacja();
};

class Inky  //blekitny przeciwnik (zmieniajace sie decyzje)
{
public:
    sf::Vector2f pozycja_rysowania;
    Grafika niebieski = Grafika("grafiki/sprite_sheet.png");
    Kierunki kierunek_aktualny;
    Kierunki kierunek_nastepny;
    int pozycja_ostatniej_zmiany_x = 0;
    int pozycja_ostatniej_zmiany_y = 0;
    bool czy_wybrac_nowy_kierunek = true;
    int ucieczka = 0; 
    bool start = false;
    Inky() {
        niebieski.sprajt.setTextureRect(sf::IntRect(4, 210, 26, 26));
        pozycja_rysowania.x = 348;
        pozycja_rysowania.y = (float)268;
        niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
    }
    void Ruch();
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);
    void Animacja();
};

class Clyde //pomaranczowy przeciwnik (goni, ale gdy jest blisko pacmana zaczyna uciekac)
{
public:
    sf::Vector2f pozycja_rysowania;
    sf::Vector2f pozycja_rog;
    Grafika pomaranczowy = Grafika("grafiki/sprite_sheet.png");
    Kierunki kierunek_aktualny;
    Kierunki kierunek_nastepny;
    int pozycja_ostatniej_zmiany_x = 0;
    int pozycja_ostatniej_zmiany_y = 0;
    bool czy_wybrac_nowy_kierunek = true;
    int ucieczka = 0; 
    bool start = false;
    Clyde() {
        pomaranczowy.sprajt.setTextureRect(sf::IntRect(3, 242, 26, 26));
        pozycja_rysowania.x = 427;
        pozycja_rysowania.y = (float)268;
        pozycja_rog.x = 3.5;
        pozycja_rog.y = 31.5;
        pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
    }
    void Ruch();
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);
    void Animacja();
};
/////////////////////////////////////////////////////////////////
// \brief Klasa boosterow wyswietlanych na mapie,
// pozwalaja graczowi zjadac przeciwnikow
/////////////////////////////////////////////////////////////////
class punkty_boost {
public:
    Grafika punkt = Grafika("grafiki/sprite_sheet.png");
    sf::Vector2f pozycja_wzgledna;
    sf::Vector2i pozycja_logiczna;
    punkty_boost() {
        punkt.sprajt.setTextureRect(sf::IntRect(10, 339, 16, 16));
    }
    
    /////////////////////////////////////////////////////////////////
    // \brief metoda ustawia parametry boostera w oparciu o tablice logiczna
    // oraz pozycje na mapie rysowanej
    // \param pozycja logiczna x boostera, pozycja logiczna y boostera
    /////////////////////////////////////////////////////////////////
    void Ustawienie(int x, int y);
};
/////////////////////////////////////////////////////////////////
// \brief Klasa punktow wyswietlanych na mapie,
// po zebraniu wszystkich koniec gry (wygrana)
/////////////////////////////////////////////////////////////////
class punkty {
public:
    Grafika punkt = Grafika("grafiki/sprite_sheet.png");
    sf::Vector2f pozycja_wzgledna;
    sf::Vector2i pozycja_logiczna;
    punkty() {
        punkt.sprajt.setTextureRect(sf::IntRect(49, 346, 4, 4));
    }
    /////////////////////////////////////////////////////////////////
    // \brief metoda ustawia parametry punktu w oparciu o tablice logiczna
    // oraz pozycje na mapie rysowanej
    // \param pozycja logiczna x punktu, pozycja logiczna y punktu
    /////////////////////////////////////////////////////////////////
    void Ustawienie(int x, int y);
};

//Tablica logiczna
// '0' -> domyslne pole, mozliwy ruch dla wszystkich
// '-' -> pole zablokowane dla ruchu
// '#' -> punkty, ktore trzeba zbierac
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
const char poziom_1_skrzyzowania[][28] =
{
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',
'-','0','0','0','0','0','?','0','0','0','0','0','0','-','-','0','0','0','0','0','0','?','0','0','0','0','0','-',
'-','0','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','0','-',
'-','0','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','0','-',
'-','0','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','0','-',
'-','?','0','0','0','0','?','0','0','?','0','0','?','0','0','?','0','0','?','0','0','?','0','0','0','0','?','-',
'-','0','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','0','-',
'-','0','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','0','-',
'-','0','0','0','0','0','?','-','-','0','0','0','0','-','-','0','0','0','0','-','-','?','0','0','0','0','0','-',
'-','-','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','0','0','0','?','0','0','?','0','0','0','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','0','-','-','-','9','9','-','-','-','0','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','0','-','9','9','9','0','9','9','-','0','-','-','0','-','-','-','-','-','-',
'2','0','0','0','0','0','?','0','0','?','-','9','0','0','0','0','9','-','?','0','0','?','0','0','0','0','0','3',
'-','-','-','-','-','-','0','-','-','0','-','9','9','9','9','9','9','-','0','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','?','0','0','0','0','0','0','0','0','?','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-',
'-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-',
'-','0','0','0','0','0','?','0','0','?','0','0','0','-','-','0','0','0','?','0','0','?','0','0','0','0','0','-',
'-','0','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','0','-',
'-','0','-','-','-','-','0','-','-','-','-','-','0','-','-','0','-','-','-','-','-','0','-','-','-','-','0','-',
'-','0','0','0','-','-','?','0','0','?','0','0','?','0','0','?','0','0','?','0','0','?','-','-','0','0','0','-',
'-','-','-','0','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','0','-','-','-',
'-','-','-','0','-','-','0','-','-','0','-','-','-','-','-','-','-','-','0','-','-','0','-','-','0','-','-','-',
'-','0','0','?','0','0','0','-','-','0','0','0','0','-','-','0','0','0','0','-','-','0','0','0','?','0','0','-',
'-','0','-','-','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','-','-','0','-',
'-','0','-','-','-','-','-','-','-','-','-','-','0','-','-','0','-','-','-','-','-','-','-','-','-','-','0','-',
'-','0','0','0','0','0','0','0','0','0','0','0','?','0','0','?','0','0','0','0','0','0','0','0','0','0','0','-',
'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'
};

extern PacMan gracz1;
extern Blinky czerwony;
extern Pinky rozowy;
extern Inky niebieski;
extern Clyde pomaranczowy;
extern rozmiar_okna rozmiar_menu;
extern rozmiar_okna rozmiar_gry;
extern Game gra;
extern Grafika start;
extern Grafika logo;
extern Grafika tlo;
extern bool czy_wlaczona;                       //Zmienna logiczna -> potrzeba do petli glownej programu
extern int typ_menu;                            //zmienna odpowiadajaca za typ okna: 1 - MENU; 2- GRA; 3 - OPCJE
extern punkty_boost boost[4];
extern punkty punkt[242];