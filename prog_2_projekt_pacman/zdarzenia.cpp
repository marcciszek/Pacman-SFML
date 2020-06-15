#include "Game.h"

void Game::Event() {
    while (this->okno_aplikacji.pollEvent(zdarzenie))                                                                             //Petla sprawdzenia zdarzen
    {
        if (zdarzenie.type == sf::Event::Closed) {                                                                                //zdarzenie obslugujace zamkniecie okna aplikacji
            this->okno_aplikacji.close();
            czy_wlaczona = false;
        }

        if (zdarzenie.type == sf::Event::MouseButtonPressed && zdarzenie.mouseButton.button == sf::Mouse::Left)                                  //zdarzenie wcisniecia lewego klawisza myszy
        {
            if (start.sprajt.getGlobalBounds().contains(okno_aplikacji.mapPixelToCoords(sf::Mouse::getPosition(okno_aplikacji))) && typ_menu==1) //Sprawdzenie czy jestesmy w menu i czy kursor jest na przycisku start
            {
                this->okno_aplikacji.close();                                                                                                    //zamkniecie menu
                gra.Init(rozmiar_gry.x, rozmiar_gry.y);                                                                                          //otwarcie okna gry
                typ_menu = 2;                                                                                                                    //rozpoczecie gry
                break;
            }
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Right) {                                //zdarzenie wcisniecia prawej strzalki na klawiaturze
            gracz1.kierunek_nastepny = PRAWO;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Left) {                                 //zdarzenie wcisniecia lewej strzalki na klawiaturze
            gracz1.kierunek_nastepny = LEWO;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Up) {                                   //zdarzenie wcisniecia gornej strzalki na klawiaturze
            gracz1.kierunek_nastepny = GORA;
        }
        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Down) {                                 //zdarzenie wcisniecia dolnej strzalki na klawiaturze
            gracz1.kierunek_nastepny = DOL;
        }

        if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Space and (stan_gry==1 or stan_gry==2))  //po zakonczeniu gry, wciasniecei spacji resetuje gre i przywraca menu
        {
            typ_menu = 1;
            stan_gry = 0;
            gra_aktywna = false;
            gracz1.reset();
            czerwony.reset();
            rozowy.reset();
            niebieski.reset();
            pomaranczowy.reset();
            ustawienie_punktow_i_boostow();
        }
    }
}