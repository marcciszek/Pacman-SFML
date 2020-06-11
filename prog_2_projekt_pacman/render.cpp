#include "Game.h"

//tworzenie obiektow zawierajacych odpowiednie grafiki (lokalizacja tekstury)
Grafika logo("grafiki/logo.png");
Grafika start("grafiki/start.png");
Grafika tlo("grafiki/plansza_3.png");
PacMan gracz1;
//Grafika opcje("grafika/opcje.png");

void Game::Render()                                     // \brief Metoda renderujaca aplikacje
{
    while (this->okno_aplikacji.isOpen()) 
    {
        
        Event();                                        //Metoda sprawdzajaca zdarzenia w aplikacji (zdarzenia.cpp)
        switch (typ_menu)
        {
        case 1:
            Menu_Render();                              //render okna menu
            break;
        case 2:
            gracz1.Ruch_postaci();
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
}//czy this potrzebne?

void Game::Game_Render()                                                    //Metoda renderujaca okno gry
{
    float skala = (float)rozmiar_gry.y / tlo.tekstura.getSize().y;          //przeskalowanie rozmiaru obrazka do rozmiaru okna
    tlo.sprajt.setScale(skala, skala);
    tlo.sprajt.setPosition(rozmiar_gry.x / (float)2 - tlo.tekstura.getSize().x * skala / (float)2, 0);
    this->okno_aplikacji.clear(sf::Color::Blue);
    this->okno_aplikacji.draw(tlo.sprajt);
    this->okno_aplikacji.draw(gracz1.postac.sprajt);
}