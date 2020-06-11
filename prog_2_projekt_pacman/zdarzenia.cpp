#include "Game.h"

void Game::Event() {
    while (this->okno_aplikacji.pollEvent(zdarzenie))                   //Petla sprawdzenia zdarzen
    {
        if (zdarzenie.type == sf::Event::Closed) {                      //Sprawdzenie typu zdarzenia -> zamkniecie okienka
            this->okno_aplikacji.close();                               //Funkcja zamykajaca okno
            czy_wlaczona = false;
        }

        if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)        //Lewy przycisk myszy wcisniety
        {
            if (start.sprajt.getGlobalBounds().contains(okno_aplikacji.mapPixelToCoords(sf::Mouse::getPosition(okno_aplikacji))) && typ_menu==1) //Kursor w obrebie przycisku start i aktualnie wyswietlane jest menu
            {
                gra.Init(rozmiar_gry.x, rozmiar_gry.y);                                                                                 //Inicjalizacja gry
                typ_menu = 2;                                                                                       //Zmiana typu menu na 2: GRA;
                this->okno_aplikacji.close();                                                                       //Zamkniecie okna konsoli
                break;
            }
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right) {
            gracz1.kierunek_aktualny = PRAWO;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left) {
            gracz1.kierunek_aktualny = LEWO;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up) {
            gracz1.kierunek_aktualny = GORA;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down) {
            gracz1.kierunek_aktualny = DOL;
        }
    }
}