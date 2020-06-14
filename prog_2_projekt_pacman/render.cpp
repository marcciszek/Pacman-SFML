#include "Game.h"

//tworzenie obiektow zawierajacych odpowiednie grafiki (lokalizacja tekstury)
Grafika logo("grafiki/logo.png");
Grafika start("grafiki/start.png");
Grafika tlo("grafiki/plansza_3.png");
sf::Font font;
sf::Text zdobyte_punkty;
PacMan gracz1;
Blinky czerwony;
Pinky rozowy;
Inky niebieski;
Clyde pomaranczowy;
punkty_boost boost[4];                                  //tablica boosterow (pozwalajace zjadac przeciwnikow)
punkty punkt[242];                                      //tablica punktow do zbierania

void Game::Render()                                     // \brief Metoda renderujaca aplikacje
{
    if (!font.loadFromFile("grafiki/FrederickatheGreat-Regular.ttf"))
    {
        std::cerr << "font problem" << std::endl;
    }
    zdobyte_punkty.setFont(font);
    zdobyte_punkty.setFillColor(sf::Color::Red);


    while (this->okno_aplikacji.isOpen()) 
    {
        Event();                                        //Metoda sprawdzajaca zdarzenia w aplikacji (zdarzenia.cpp)
        switch (typ_menu)
        {
        case 1:
            Menu_Render();                              //render okna menu
            break;
        case 2:
            if (gra_aktywna==true and stan_gry == 0)    //render gdy gra trwa
            {
                if (stan_gry == 0)
                {
                    czerwony.Ruch();
                    czerwony.Animacja();
                    rozowy.Ruch();
                    rozowy.Animacja();
                    niebieski.Ruch();
                    niebieski.Animacja();
                    pomaranczowy.Ruch();
                    pomaranczowy.Animacja();
                    gracz1.Ruch_postaci();
                    gracz1.Animacja_postaci();
                }
                 else if (stan_gry == 1)               //przerwanie gdy wygrana
                {
                    std::cout << "wygrana" << std::endl;
                }
                 else if (stan_gry == 2)               //przerwanie gdy przegrana
                {
                    std::cout << "przegrana" << std::endl;
                }
            }
            Game_Render();                              //render okna gry
            break;
        }
        this->okno_aplikacji.display();                 //funkcja wyswietlajaca utworzone wczesniej okno aplikacji
    }
}

void Game::Menu_Render()                                //Metoda renderujaca menu
{
    logo.sprajt.setScale(0.5, 0.5);
    logo.sprajt.setPosition(rozmiar_menu.x / (float)2 - (logo.tekstura.getSize().x / 4), rozmiar_menu.y / (float)10);                                  //ustawienie pozycji na srodku, zalezne od uzytej wczesniej skali
    this->okno_aplikacji.clear(sf::Color::White);
    this->okno_aplikacji.draw(logo.sprajt);
    start.sprajt.setScale(0.5, 0.5);
    start.sprajt.setPosition(rozmiar_menu.x / (float)2 - start.tekstura.getSize().x / 4, rozmiar_menu.y / (float)2 - (start.tekstura.getSize().y / 4)); //ustawienie pozycji na srodku, zalezne od uzytej wczesniej skali
    this->okno_aplikacji.draw(start.sprajt);
}

void Game::Game_Render()                                                    //Metoda renderujaca okno gry
{
    float skala = (float)rozmiar_gry.y / tlo.tekstura.getSize().y;          //przeskalowanie rozmiaru obrazka do rozmiaru okna
    tlo.sprajt.setScale(skala, skala);
    tlo.sprajt.setPosition(rozmiar_gry.x / (float)2 - tlo.tekstura.getSize().x * skala / (float)2, 0);
    this->okno_aplikacji.clear(sf::Color::Blue);
    this->okno_aplikacji.draw(tlo.sprajt);                                  //rysowanie tla

    for (int i = 0; i < 4; i++) {                                           //rysowanie boosterow
        this->okno_aplikacji.draw(boost[i].punkt.sprajt);
    }
    for (int i = 0; i < 242; i++) {                                         //rysowanie punktow
        this->okno_aplikacji.draw(punkt[i].punkt.sprajt);
    }
    this->okno_aplikacji.draw(czerwony.czerwony.sprajt);
    this->okno_aplikacji.draw(rozowy.rozowy.sprajt);
    this->okno_aplikacji.draw(niebieski.niebieski.sprajt);
    this->okno_aplikacji.draw(pomaranczowy.pomaranczowy.sprajt);
    this->okno_aplikacji.draw(gracz1.postac.sprajt);                        //rysowanie gracza

    zdobyte_punkty.setString("Punkty\n"+std::to_string(gracz1.Ilosc_punktow)+"/242");

    this->okno_aplikacji.draw(zdobyte_punkty);

    if (gracz1.kierunek_nastepny != STOP)
    {
        gra_aktywna = true;
    }
    if (gracz1.Ilosc_punktow == 242)
    {
        stan_gry = 1;
    }
}