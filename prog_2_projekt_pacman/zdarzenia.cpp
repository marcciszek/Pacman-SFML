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
                this->okno_aplikacji.close();
                break;
            }
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right) {
            gracz1.kierunek_nastepny = PRAWO;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left) {
            gracz1.kierunek_nastepny = LEWO;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up) {
            gracz1.kierunek_nastepny = GORA;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down) {
            gracz1.kierunek_nastepny = DOL;
        }

        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Space and (stan_gry==1 or stan_gry==2))
        {

            typ_menu = 1;
            stan_gry = 0;
            gra_aktywna = false;
        }
    }
}