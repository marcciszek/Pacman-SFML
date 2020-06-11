#include "Game.h"

sf::Clock zegar_ruchu;

const float predkosc_gracza = 0.01;

void PacMan::Ruch_postaci() {

    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((postac.sprajt.getPosition().x + (postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((postac.sprajt.getPosition().y + (postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);                                                                           //odleglosc wertykalna od srodka gracza do krawedzi kratki logicznej


    //osluga poruszania sie w zaleznosci od wybranego kierunku i
    //sprawdzenie mozliwosci poruszania sie gracza po mapie logicznej
    switch (this->kierunek_aktualny) {
    case PRAWO:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_x >= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '-' || poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '9')     //Sprawdzenie mozliwosciu ruchu
                {
                    kierunek_aktualny = STOP;                                                                                                                           //zatrzymanie gracza jesli nie moze poruszac sie dalej w zadanym kierunku
                }
                else
                {
                    postac.sprajt.setPosition(++pozycja_rysowania.x , pozycja_rysowania.y);                                                                             //zmiana pozycji gracza
                }
            }
            else
            {
                postac.sprajt.setPosition(++pozycja_rysowania.x, pozycja_rysowania.y);                                                                                  //zmiana pozycji gracza
            }
            zegar_ruchu.restart();
        }
        break;
    case LEWO:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_x <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '-' || poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '9')
                {
                    kierunek_aktualny = STOP;
                }
                else
                {
                    postac.sprajt.setPosition(--pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                postac.sprajt.setPosition(--pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        break;
    case DOL:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_y >= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] == '-' || poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] == '9')
                {
                    kierunek_aktualny = STOP;
                }
                else
                {
                    postac.sprajt.setPosition(pozycja_rysowania.x, ++pozycja_rysowania.y);
                }
            }
            else
            {
                postac.sprajt.setPosition(pozycja_rysowania.x, ++pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        break;
    case GORA:
        if (zegar_ruchu.getElapsedTime().asSeconds() >= predkosc_gracza)
        {
            if (odleglosc_od_kratki_y <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] == '-' || poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] == '9')
                {
                    kierunek_aktualny = STOP;
                }
                else
                {
                    postac.sprajt.setPosition(pozycja_rysowania.x, --pozycja_rysowania.y);
                }
            }
            else
            {
                postac.sprajt.setPosition(pozycja_rysowania.x, --pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        break;
    }
}