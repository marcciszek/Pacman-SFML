#include "Game.h"

sf::Clock zegar_ruchu;

const float predkosc_gracza = 0.001f;

void PacMan::Ruch_postaci() {

    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((postac.sprajt.getPosition().x + (postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((postac.sprajt.getPosition().y + (postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);                                                                           //odleglosc wertykalna od srodka gracza do krawedzi kratki logicznej

    //switch ten odpowiedzialny jest za sprawdzenie, czy ostatni kierunek wybrany przez gracza jest mozliwy do realizacji, jesli tak to ustawia odpowiedni kierunek postaci
    switch (this->kierunek_nastepny)
    {
    case PRAWO:
        if (odleglosc_od_kratki_y >= 0.495f and odleglosc_od_kratki_y <= 0.505f)                                                                                   //sprawdzenie czy jestesmy na srodku kratki
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '-' and poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '9')   //sprawdzenie czy mozliwy jest ruch
            {
            kierunek_aktualny = kierunek_nastepny;                                                                                                                 //ustawienie kierunku postaci na ostatnio wybrany przez gracza
            }
        }
        break;
    case LEWO:
        if (odleglosc_od_kratki_y >= 0.495f and odleglosc_od_kratki_y <= 0.505f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '-' and poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '9')
            {
            kierunek_aktualny = kierunek_nastepny;
            }
        }
        break;
    case DOL:
        if (odleglosc_od_kratki_x >= 0.495f and odleglosc_od_kratki_x <= 0.505f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '-' and poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '9')
            {
            kierunek_aktualny = kierunek_nastepny;
            }
        }
        break;
    case GORA:
        if (odleglosc_od_kratki_x >= 0.495f and odleglosc_od_kratki_x <= 0.505f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '-' and poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '9')
            {
            kierunek_aktualny = kierunek_nastepny;
            }
        }
        break;
    }
    //switch ktory realzuje przesuwanie sie postaci
    switch (this->kierunek_aktualny) {
    case PRAWO:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_x >= 0.5f)                                                                                                                          //sprawdzenie czy gracz jest w polowie kratki
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '-' || poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '9')     //Sprawdzenie mozliwosciu ruchu
                {
                    kierunek_aktualny = STOP;                                                                                                                           //zatrzymanie gracza jesli nie moze poruszac sie dalej w zadanym kierunku
                    kierunek_nastepny = STOP;
                }
                else if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '3')
                {
                    //std::cout << "prawo " << pozycja_rysowania.x << " " << pozycja_rysowania.y << std::endl;
                    pozycja_rysowania.x = 144.994;
                    pozycja_rysowania.y = 267.689;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.49f and odleglosc_od_kratki_y <= 0.51f)
                {
                    pozycja_rysowania.x += 0.2;                                                                                                                         //
                    postac.sprajt.setPosition(pozycja_rysowania.x , pozycja_rysowania.y);                                                                               //zmiana pozycji gracza
                }
            }
            else
            {
                pozycja_rysowania.x += 0.2;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                    //zmiana pozycji gracza
            }
            zegar_ruchu.restart();
        }
        std::cout << kierunek_aktualny <<" "<<kierunek_nastepny<< " " << pozycja_wzgledna_x << " " << pozycja_wzgledna_y << " " << odleglosc_od_kratki_x << " " << odleglosc_od_kratki_y << std::endl;
        break;
    case LEWO:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_x <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '-' || poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '9')
                {
                    kierunek_aktualny = STOP;
                    kierunek_nastepny = STOP;
                }
                else if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '2')
                {
                    //std::cout << "lewo " << pozycja_rysowania.x <<" "<< pozycja_rysowania.y << std::endl;
                    //postac.sprajt.setPosition(629.015, 267.689);
                    pozycja_rysowania.x = 629.015;
                    pozycja_rysowania.y = 267.689;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.49f and odleglosc_od_kratki_y <= 0.51f)
                {
                    pozycja_rysowania.x -= 0.2;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.x -= 0.2;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        std::cout << kierunek_aktualny << " " << kierunek_nastepny << " " << pozycja_wzgledna_x << " " << pozycja_wzgledna_y << " " << odleglosc_od_kratki_x << " " << odleglosc_od_kratki_y << std::endl;
        break;
    case DOL:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_y >= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] == '-' || poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] == '9')
                {
                    kierunek_aktualny = STOP;
                    kierunek_nastepny = STOP;
                }
                else if (odleglosc_od_kratki_x >= 0.49f and odleglosc_od_kratki_x <= 0.51f)
                {
                    pozycja_rysowania.y += 0.2;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y += 0.2;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        std::cout << kierunek_aktualny << " " << kierunek_nastepny << " " << pozycja_wzgledna_x << " " << pozycja_wzgledna_y << " " << odleglosc_od_kratki_x << " " << odleglosc_od_kratki_y << std::endl;
        break;
    case GORA:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_y <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] == '-' || poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] == '9')
                {
                    kierunek_aktualny = STOP;
                    kierunek_nastepny = STOP;
                }
                else if (odleglosc_od_kratki_x >= 0.49f and odleglosc_od_kratki_x <= 0.51f)
                {
                    pozycja_rysowania.y -= 0.2;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y -= 0.2;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        std::cout << kierunek_aktualny << " " << kierunek_nastepny << " " << pozycja_wzgledna_x << " " << pozycja_wzgledna_y << " " << odleglosc_od_kratki_x << " " << odleglosc_od_kratki_y << std::endl;
        break;
    }
}