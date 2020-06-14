#include "Game.h"

//tworzenie obiektow zawierajacych odpowiednie grafiki (lokalizacja tekstury)
Grafika logo("grafiki/logo.png");
Grafika start("grafiki/start.png");
Grafika tlo("grafiki/plansza_3.png");
sf::Font font;
sf::Text zdobyte_punkty;
sf::Text komunikat;
PacMan gracz1;
Blinky czerwony;
Pinky rozowy;
Inky niebieski;
Clyde pomaranczowy;
punkty_boost boost[4];                                  //tablica boosterow (pozwalajace zjadac przeciwnikow)
punkty punkt[242];                                      //tablica punktow do zbierania

void Game::Render()                                     // \brief Metoda renderujaca aplikacje
{
    zdobyte_punkty.setFont(font);
    komunikat.setFont(font);
    zdobyte_punkty.setFillColor(sf::Color::Red);

    int nr_boost = 0;                                                     //licznik boosterow
    int nr_pkt = 0;                                                       //licznik punktow
    for (int x = 1; x < 30; x++) {
        for (int y = 1; y < 27; y++) {
            if (poziom_1[x][y] == 'X') {
                boost[nr_boost].Ustawienie(y, x);                         //ustawienie boosterow
                nr_boost++;
            }
            if (poziom_1[x][y] == '#') {
                punkt[nr_pkt].Ustawienie(y, x);                           //ustawienie punktow
                nr_pkt++;
            }
        }
    }

    while (this->okno_aplikacji.isOpen()) 
    {
        Event();                                         //Metoda sprawdzajaca zdarzenia w aplikacji (zdarzenia.cpp)
        switch (typ_menu)
        {
        case 1:
            Menu_Render();                               //render okna menu
            break;
        case 2:
            if (gra_aktywna==true)                       //gra ruszy dopiero gdy gracz wykona ruch
            {
                if (stan_gry == 0)                       //gra normalnie dziala
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
            }
            Game_Render();                              //render okna gry w zaleznosci od stanu gry
            warunki_pomocnicze();                       //sprawdzanie warunkow rozpoczecia i wygrania gry
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
    
    if (stan_gry == 0)                                                      //stan gdy gra dziala normalnie
    {
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
    }
    else if (stan_gry == 1)                                                 //stan gdy gracz wygral
    {
        okno_aplikacji.clear(sf::Color::White);
        komunikat.setFillColor(sf::Color::Green);
        komunikat.setString("Wygrana!\nnacisnij spacje aby kontynuowac...");
        okno_aplikacji.draw(komunikat);
    }
    else if (stan_gry == 2)                                                 //stan gdy gracz przegral
    {
        okno_aplikacji.clear(sf::Color::White);
        komunikat.setFillColor(sf::Color::Red);
        komunikat.setString("Przegrana\nnacisnij spacje aby kontynuowac...");
        okno_aplikacji.draw(komunikat);
    }

}

void Game::warunki_pomocnicze()
{
    if (gracz1.kierunek_nastepny != STOP)                                   //oczekiwanie, az gracz ruszy
    {
        gra_aktywna = true;
    }
    if (gracz1.Ilosc_punktow == 242)                                        //sprawdzenie czy gracz zebral wszystkie punkty
    {
        stan_gry = 1;
    }
}