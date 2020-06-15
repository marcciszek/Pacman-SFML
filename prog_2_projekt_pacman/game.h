#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <random>
#include <string>

enum Kierunki { STOP = 0, LEWO, PRAWO, GORA, DOL };

struct rozmiar_okna
{
    int x;
    int y;
};


/////////////////////////////////////////////////////////////////
// \brief Klasa odpowiedzialna za gre
/////////////////////////////////////////////////////////////////
class Game
{
public:
    sf::RenderWindow okno_aplikacji;             //Deklaracja glownego okna aplikacji
    sf::Event zdarzenie;                         //Zmienna obslugujaca zdarzenia w aplikacji

    /////////////////////////////////////////////////////////////////
    // \brief metoda obslugujaca zdarzenia (interakcje z uzytkownikiem)
    /////////////////////////////////////////////////////////////////
    void Event();
    
    //Funkcja do renderowania okna (wstepnie)
    //Trzeba pozniej wywolac funkcje odpowiedzialna za konkretne okno
    /////////////////////////////////////////////////////////////////
    // \brief Metoda przygotowuje program oraz
    // uruchamia glowna petle wyswietlania
    /////////////////////////////////////////////////////////////////
    void Render();
    
    /////////////////////////////////////////////////////////////////
    // \brief Metoda wyswietlajaca okno menu programu
    /////////////////////////////////////////////////////////////////
    void Menu_Render();
    
    /////////////////////////////////////////////////////////////////
    // \brief Metoda wyswietlajaca okno glowne gry
    /////////////////////////////////////////////////////////////////
    void Game_Render();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda sprawdzajaca czy gracz ruszyl
    // oraz czy zebral wszystkie punkty (wygral)
    /////////////////////////////////////////////////////////////////
    void warunki_pomocnicze();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda ustawiajaca punkty i boostery na mapie gry
    /////////////////////////////////////////////////////////////////
    void ustawienie_punktow_i_boostow();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda inicjalizujaca okno programu
    // \param x - szerokosc okna  y - wysokosc okna
    /////////////////////////////////////////////////////////////////
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
    sf::Vector2f pozycja_rysowania;                                                   //koordynaty pozycji gracza
    Grafika postac = Grafika("grafiki/sprite_sheet.png");                             //zaladowanie pliku zawierajacego grafiki gracza
    Kierunki kierunek_aktualny=STOP;                                                  //kierunek w ktorym kieruje sie gracz (wykonowany przez program) { STOP = 0, LEWO, PRAWO, GORA, DOL }
    Kierunki kierunek_nastepny=STOP;                                                  //nastepny kierunek wybrany przez gracza, ale jeszcze nie mozliwy do wykonania { STOP = 0, LEWO, PRAWO, GORA, DOL }
    Kierunki kierunek_ostatni=STOP;                                                   //zapamietanie ostatniego kierunku w ktorym poruszal sie gracz, potrzebne do algorytmow wyznaczajacych droge przeciwnikom
    int Ilosc_punktow = 0;                                                            //licznik zebranych punktow
    int boost_aktywny = 0;                                                            //zmienna mowiaca czy pacman moze atakowac przeciwnikow (jesli 1)
    PacMan() {
        postac.sprajt.setTextureRect(sf::IntRect(3, 3, 26, 26));                      //pozycja startowa tekstury postaci wycieta z arkusza tekstur
        pozycja_rysowania.x = 387;                                                    //pozycja startowa rysowania tekstury gracza, horyzontalna
        pozycja_rysowania.y = (float)441.9;                                           //pozycja startowa rysowania tekstury gracza, wertykalna
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);          //ustawienie pozycji gracza w ktorej ma byc wyrysowana
    }

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch postaci
    /////////////////////////////////////////////////////////////////
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
    /////////////////////////////////////////////////////////////////
    // \brief metoda oblsugujaca reakcje na 
    // kontakt z przeciwnikiem
    // \param pozycja kratki logicznej x, pozycja kratki logicznej y 
    // (na ktorej znajduje sie gracz)
    /////////////////////////////////////////////////////////////////
    void Kontakt_z_przeciwnikiem(float wzgledna_x, float wzgledna_y);
    /////////////////////////////////////////////////////////////////
    // \brief metoda przywracajaca wartosci poczatkowe
    /////////////////////////////////////////////////////////////////
    void reset();
};

/////////////////////////////////////////////////////////////////
// \brief Klasa opisujaca postac czerownego przeciwnika
/////////////////////////////////////////////////////////////////
class Blinky  //czerwony przeciwnik (podaza za pacmanem)
{
public:
    sf::Vector2f pozycja_rysowania;                                                  //koordynaty pozycji przeciwnika czerwonego
    Grafika czerwony = Grafika("grafiki/sprite_sheet.png");                          //zaladowanie pliku zawierajacego grafiki przeciwnika
    Kierunki kierunek_aktualny = LEWO;                                               //kierunek w ktorym zacznie poruszac sie przeciwnik na starcie gry
    Kierunki kierunek_nastepny = STOP;                                               //kierunek ten jest wyznaczany przez odpowiedni algorytm, w momecie gdy zmiana jest mozliwa przypisywana wartosc jest do kierunku aktualnego
    int pozycja_ostatniej_zmiany_x = 0;                                              //koordynat x w ktorym przeciwnik czerwony zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    int pozycja_ostatniej_zmiany_y = 0;                                              //koordynat y w ktorym przeciwnik czerwony zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    bool czy_wybrac_nowy_kierunek = true;                                            //zmienna mowiaca czy w aktualnej pozycji trzeba wybrac lub wylosowac nowy kierunek (zabezpiecza to przed wieloma zmianami na jednej kratce logicznej)
    int ucieczka = 0;                                                                //zmienna mowiaca jaki tryb poruszania sie ma przecinwik czerwony 0-zwykly, 1-ucieczka przed graczem, 2-powrot do bazy
    Blinky() {
        czerwony.sprajt.setTextureRect(sf::IntRect(4, 146, 26, 26));                 //pozycja startowej tekstury przeciwnika czerwonego
        pozycja_rysowania.x = 387;                                                   //startowa horyzontalna pozycja rysowania przeciwnika czerwonego
        pozycja_rysowania.y = (float)209.6;                                          //startowa wertykalna pozycja rysowania przeciwnika czerwonego
        czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);       //ustawienie pozycji rysowania przeciwnika czerwonego
    }

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch czerwonego przeciwnika
    // przeciwnik ten goni gracza
    /////////////////////////////////////////////////////////////////
    void Ruch();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda sprawdzajaca mozliwosc poruszania 
    // czerwonego przeciwnika na skrzyzowaniach
    // \param pozycja_x -> pozycja x czerwonego przeciwnika (logiczna);
    // pozycja_y -> pozycja y czerwonego przeciwnika (logiczna)
    /////////////////////////////////////////////////////////////////
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch czerwonego przeciwnika
    // na skrzyzowaniach na mapie
    // \param pozycja_x -> pozycja x czerwonego przeciwnika (logiczna);
    // pozycja_y -> pozycja y czerwonego przeciwnika (logiczna);
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch czerwonego przeciwnika
    // na skrzyzowaniach na mapie w trybie 
    // ucieczki przed graczem
    // \param pozycja_x -> pozycja x czerwonego przeciwnika;
    // pozycja_y -> pozycja y czerwonego przeciwnika;
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch czerwonego przeciwnika
    // na skrzyzowaniach na mapie w trybie powrotu do bazy
    // \param pozycja_x -> pozycja x czerwonego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y czerwonego przeciwnika ( logiczna );
    // pozycja_powrotu_x -> pozycja x punktu docelowego ( punktu startowego przeciwnika );
    // pozycja_powrotu_y -> pozycja y punktu docelowego ( punktu startowego przeciwnika )
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_baza(float pozycja_x, float pozycja_y, float pozycja_powrotu_x, float pozycja_powrotu_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca animacje czerwonego przeciwnika
    /////////////////////////////////////////////////////////////////
    void Animacja();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda przywracajaca wszystkie parametry czerwonego
    // przeciwnika do ustawien domyslnych
    /////////////////////////////////////////////////////////////////
    void reset();
};

/////////////////////////////////////////////////////////////////
// \brief Klasa opisujaca postac rozowego przeciwnika
/////////////////////////////////////////////////////////////////
class Pinky  //rozowy przeciwnik (zachodzi droge)
{
public:
    sf::Vector2f pozycja_rysowania;                                                           //koordynaty pozycji przeciwnika rozowego
    Grafika rozowy = Grafika("grafiki/sprite_sheet.png");                                     //zaladowanie pliku zawierajacego grafiki przeciwnika rozowego
    Kierunki kierunek_aktualny = PRAWO;                                                       //kierunek w ktorym zacznie poruszac sie przeciwnik rozowy na starcie gry
    Kierunki kierunek_nastepny = STOP;                                                        //kierunek ten jest wyznaczany przez odpowiedni algorytm, w momecie gdy zmiana jest mozliwa przypisywana wartosc jest do kierunku aktualnego
    int pozycja_ostatniej_zmiany_x = 0;                                                       //koordynat x w ktorym przeciwnik rozowy zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    int pozycja_ostatniej_zmiany_y = 0;                                                       //koordynat y w ktorym przeciwnik rozowy zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    bool czy_wybrac_nowy_kierunek = true;                                                     //zmienna mowiaca czy w aktualnej pozycji trzeba wybrac lub wylosowac nowy kierunek (zabezpiecza to przed wieloma zmianami na jednej kratce logicznej)
    int ucieczka = 0;                                                                         //zmienna mowiaca jaki tryb poruszania sie ma duszek rozowy 0-zwykly, 1-ucieczka przed graczem, 2-powrot do bazy
    Pinky() {
        rozowy.sprajt.setTextureRect(sf::IntRect(4, 178, 26, 26));                            //pozycja startowej tekstury przeciwnika rozowego
        pozycja_rysowania.x = 387;                                                            //startowa horyzontalna pozycja rysowania przeciwnika rozowego
        pozycja_rysowania.y = (float)268;                                                     //startowa wertykalna pozycja rysowania przeciwnika rozowego
        rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                  //ustawienie pozycji rysowania przeciwnika rozowego
    }
    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch rozowego przeciwnika
    // przecinwik ten probuje zajsc droge graczowi
    /////////////////////////////////////////////////////////////////
    void Ruch();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda sprawdzajaca mozliwosc poruszania 
    // rozowego przeciwnika na skrzyzowaniach
    // \param pozycja_x -> pozycja x rozowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y rozowego przeciwnika ( logiczna )
    /////////////////////////////////////////////////////////////////
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch rozowego przeciwnika
    // na skrzyzowaniach na mapie
    // \param pozycja_x -> pozycja x rozowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y rozowego przeciwnika ( logiczna );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);
    
    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch rozowego przeciwnika
    // na skrzyzowaniach na mapie w trybie 
    // ucieczki przed graczem
    // \param pozycja_x -> pozycja x rozowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y rozowego przeciwnika ( logiczna );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch rozowego przeciwnika
    // na skrzyzowaniach na mapie w trybie powrotu do bazy
    // \param pozycja_x -> pozycja x rozowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y rozowego przeciwnika ( logiczna );
    // pozycja_powrotu_x -> pozycja x punktu docelowego ( punktu startowego przeciwnika );
    // pozycja_powrotu_y -> pozycja y punktu docelowego ( punktu startowego przeciwnika )
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_baza(float pozycja_x, float pozycja_y, float pozycja_powrotu_x, float pozycja_powrotu_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca animacje rozowego przeciwnika
    /////////////////////////////////////////////////////////////////
    void Animacja();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda przywracajaca wszystkie parametry rozowego
    // przeciwnika do ustawien domyslnych
    /////////////////////////////////////////////////////////////////
    void reset();
};

/////////////////////////////////////////////////////////////////
// \brief Klasa opisujaca postac niebieskiego przeciwnika
/////////////////////////////////////////////////////////////////
class Inky
{
public:
    sf::Vector2f pozycja_rysowania;                                                           //koordynaty pozycji przeciwnika niebieskiego
    Grafika niebieski = Grafika("grafiki/sprite_sheet.png");                                  //zaladowanie pliku zawierajacego grafiki przeciwnika niebieskiego
    Kierunki kierunek_aktualny;                                                               //kierunek w ktorym zacznie poruszac sie przeciwnik niebieski na starcie gry
    Kierunki kierunek_nastepny;                                                               //kierunek ten jest wyznaczany przez odpowiedni algorytm, w momecie gdy zmiana jest mozliwa przypisywana wartosc jest do kierunku aktualnego
    int pozycja_ostatniej_zmiany_x = 0;                                                       //koordynat x w ktorym przeciwnik niebieski zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    int pozycja_ostatniej_zmiany_y = 0;                                                       //koordynat y w ktorym przeciwnik niebieski zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    bool czy_wybrac_nowy_kierunek = true;                                                     //zmienna mowiaca czy w aktualnej pozycji trzeba wybrac lub wylosowac nowy kierunek (zabezpiecza to przed wieloma zmianami na jednej kratce logicznej)
    int ucieczka = 0;                                                                         //zmienna mowiaca jaki tryb poruszania sie ma duszek niebieski 0-zwykly, 1-ucieczka przed graczem, 2-powrot do bazy
    bool start = false;                                                                       //zmienna odpowiadajaca za opozniony start tego przeciwnika
    Inky() {
        niebieski.sprajt.setTextureRect(sf::IntRect(4, 210, 26, 26));                         //pozycja startowej tekstury przeciwnika niebieskiego
        pozycja_rysowania.x = 348;                                                            //startowa horyzontalna pozycja rysowania przeciwnika niebieskiego
        pozycja_rysowania.y = (float)268;                                                     //startowa wertykalna pozycja rysowania przeciwnika niebieskiego
        niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);               //ustawienie pozycji rysowania przeciwnika niebieskiego
    }

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch niebieskiego przeciwnika
    // jego pozycja jest wyznaczana na podstawie ducha czerwonego
    // oraz pozycji 2 kratki w kierunku,
    // ktorym kieruje sie gracz (punkt symetrii)
    /////////////////////////////////////////////////////////////////
    void Ruch();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda sprawdzajaca mozliwosc poruszania 
    // niebieskiego przeciwnika na skrzyzowaniach
    // \param pozycja_x -> pozycja x niebieskiego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y niebieskiego przeciwnika ( logiczna )
    /////////////////////////////////////////////////////////////////
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch niebieskiego przeciwnika
    // na skrzyzowaniach na mapie
    // \param pozycja_x -> pozycja x niebieskiego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y niebieskiego przeciwnika ( logiczna );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch niebieskiego przeciwnika
    // na skrzyzowaniach na mapie w trybie 
    // ucieczki przed graczem
    // \param pozycja_x -> pozycja x niebieskiego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y niebieskiego przeciwnika ( logiczna );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch niebieskiego przeciwnika
    // na skrzyzowaniach na mapie w trybie powrotu do bazy
    // \param pozycja_x -> pozycja x niebieskiego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y niebieskiego przeciwnika ( logiczna );
    // pozycja_powrotu_x -> pozycja x punktu docelowego ( punktu startowego przeciwnika );
    // pozycja_powrotu_y -> pozycja y punktu docelowego ( punktu startowego przeciwnika );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_baza(float pozycja_x, float pozycja_y, float pozycja_powrotu_x, float pozycja_powrotu_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca animacje niebieskiego przeciwnika
    /////////////////////////////////////////////////////////////////
    void Animacja();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda przywracajaca wszystkie parametry niebieskiego
    // przeciwnika do ustawien domyslnych
    /////////////////////////////////////////////////////////////////
    void reset();
};

/////////////////////////////////////////////////////////////////
// \brief Klasa opisujaca postac niebieskiego przeciwnika
/////////////////////////////////////////////////////////////////
class Clyde
{
public:
    sf::Vector2f pozycja_rysowania;                                                           //koordynaty pozycji przeciwnika pomaranczowego
    sf::Vector2f pozycja_rog;                                                                 //koordynaty pozycji rogu do ktorego uciekac bedzie ten przeciwnik
    Grafika pomaranczowy = Grafika("grafiki/sprite_sheet.png");                               //zaladowanie pliku zawierajacego grafiki przeciwnika pomaranczowego
    Kierunki kierunek_aktualny;                                                               //kierunek w ktorym zacznie poruszac sie pomaranczowy niebieski na starcie gry
    Kierunki kierunek_nastepny;                                                               //kierunek ten jest wyznaczany przez odpowiedni algorytm, w momecie gdy zmiana jest mozliwa przypisywana wartosc jest do kierunku aktualnego
    int pozycja_ostatniej_zmiany_x = 0;                                                       //koordynat x w ktorym przeciwnik pomaranczowy zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    int pozycja_ostatniej_zmiany_y = 0;                                                       //koordynat y w ktorym przeciwnik pomaranczowy zmienil swoj kierunek (przypisal kierunek nastepny do aktualnego)
    bool czy_wybrac_nowy_kierunek = true;                                                     //zmienna mowiaca czy w aktualnej pozycji trzeba wybrac lub wylosowac nowy kierunek (zabezpiecza to przed wieloma zmianami na jednej kratce logicznej)
    int ucieczka = 0;                                                                         //zmienna mowiaca jaki tryb poruszania sie ma duszek pomaranczowy 0-zwykly, 1-ucieczka przed graczem, 2-powrot do bazy
    bool start = false;                                                                       //zmienna odpowiadajaca za opozniony start tego przeciwnika
    Clyde() {
        pomaranczowy.sprajt.setTextureRect(sf::IntRect(3, 242, 26, 26));                      //pozycja startowej tekstury przeciwnika pomaranczowego
        pozycja_rysowania.x = 427;                                                            //startowa horyzontalna pozycja rysowania przeciwnika pomaranczowego
        pozycja_rysowania.y = (float)268;                                                     //startowa wertykalna pozycja rysowania przeciwnika pomaranczowego
        pozycja_rog.x = 3.5;                                                                  //ustawienie pozycji horyzontalnej logicznej do ktorej uciekac bedzie przeciwnik 
        pozycja_rog.y = 31.5;                                                                 //ustawienie pozycji wertykalnej logicznej do ktorej uciekac bedzie przeciwnik
        pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);            //ustawienie pozycji rysowania przeciwnika pomaranczowego
    }
    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch pomaranczowgo przeciwnika,
    // duch ten goni gracza jak czerwony na odleglosc 8 kratek,
    // gdy jest zbyt blisko zaczyna uciekac do swojego rogu (lewy dolny)
    /////////////////////////////////////////////////////////////////
    void Ruch();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda sprawdzajaca mozliwosc poruszania 
    // pomaranczowego przeciwnika na skrzyzowaniach
    // \param pozycja_x -> pozycja x pomaranczowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y pomaranczowego przeciwnika ( logiczna )
    /////////////////////////////////////////////////////////////////
    void Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch niebpomaranczowegoieskiego przeciwnika
    // na skrzyzowaniach na mapie
    // \param pozycja_x -> pozycja x pomaranczowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y pomaranczowego przeciwnika ( logiczna );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch pomaranczowego przeciwnika
    // na skrzyzowaniach na mapie w trybie 
    // ucieczki przed graczem
    // \param pozycja_x -> pozycja x pomaranczowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y pomaranczowego przeciwnika ( logiczna );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_losowe(float pozycja_x, float pozycja_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca ruch pomaranczowego przeciwnika
    // na skrzyzowaniach na mapie w trybie powrotu do bazy
    // \param pozycja_x -> pozycja x pomaranczowego przeciwnika ( logiczna );
    // pozycja_y -> pozycja y pomaranczowego przeciwnika ( logiczna );
    // pozycja_powrotu_x -> pozycja x punktu docelowego ( punktu startowego przeciwnika );
    // pozycja_powrotu_y -> pozycja y punktu docelowego ( punktu startowego przeciwnika );
    /////////////////////////////////////////////////////////////////
    void skrzyzowanie_baza(float pozycja_x, float pozycja_y, float pozycja_powrotu_x, float pozycja_powrotu_y);

    /////////////////////////////////////////////////////////////////
    // \brief Metoda obslugujaca animacje pomaranczowego przeciwnika
    /////////////////////////////////////////////////////////////////
    void Animacja();

    /////////////////////////////////////////////////////////////////
    // \brief Metoda przywracajaca wszystkie parametry pomaranczowego
    // przeciwnika do ustawien domyslnych
    /////////////////////////////////////////////////////////////////
    void reset();
};
/////////////////////////////////////////////////////////////////
// \brief Klasa boosterow wyswietlanych na mapie,
// pozwalaja graczowi zjadac przeciwnikow
/////////////////////////////////////////////////////////////////
class punkty_boost {
public:
    Grafika punkt = Grafika("grafiki/sprite_sheet.png");
    sf::Vector2f pozycja_wzgledna;                                                         //pozycja do rysowania
    sf::Vector2i pozycja_logiczna;                                                         //pozycja logiczna do zbierania
    punkty_boost() {
        punkt.sprajt.setTextureRect(sf::IntRect(10, 339, 16, 16));                         //pozycja tekstury w pliku graficznym
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
    sf::Vector2f pozycja_wzgledna;                                                         //pozycja do rysowania
    sf::Vector2i pozycja_logiczna;                                                         //pozycja logiczna do zbierania
    punkty() {
        punkt.sprajt.setTextureRect(sf::IntRect(49, 346, 4, 4));                           //pozycja tekstury w pliku graficznym
    }
    /////////////////////////////////////////////////////////////////
    // \brief metoda ustawia parametry punktu w oparciu o tablice logiczna
    // oraz pozycje na mapie rysowanej
    // \param pozycja logiczna x punktu, pozycja logiczna y punktu
    /////////////////////////////////////////////////////////////////
    void Ustawienie(int x, int y);
};

/////////////////////////////////////////////////////////////////
//Tablica logiczna
// '0' -> domyslne pole, mozliwy ruch dla wszystkich
// '-' -> pole zablokowane dla ruchu
// '#' -> punkty, ktore trzeba zbierac
// 'X' -> boostery, pozwalajace zjadac duchy
// '2' -> teleport do 3
// '3' -> teleport do 2
// '9' -> pole ruchu dostepne tylko dla przeciwnikow
/////////////////////////////////////////////////////////////////
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

/////////////////////////////////////////////////////////////////
// \brief Tablica logiczna dla algorytmow 
// sterujacych ruchami przeciwnikow
// '0' -> domyslne pole, mozliwy ruch dla wszystkich
// '-' -> pole zablokowane dla ruchu
// '2' -> teleport do 3
// '3' -> teleport do 2
// '9' -> pole 'neutralne', nie korzystaja z niego zadne algorytmy
// '?' -> skrzyzowanie na ktorym przeciwnik podejmuje decyzje o ruchu
/////////////////////////////////////////////////////////////////
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

extern sf::Font font;
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
extern bool czy_wlaczona;
extern bool gra_aktywna;
extern int stan_gry;
extern int typ_menu;
extern punkty_boost boost[4];
extern punkty punkt[242];