#include "game.h"

sf::Clock zegar_ruchu_czerwony;
sf::Clock zegar_ruchu_rozowy;
sf::Clock zegar_ruchu_niebieski;
sf::Clock zegar_ruchu_pomaranczowy;
float predkosc_duszka_cz = 0.0025f;
float predkosc_duszka_r = 0.0025f;
float predkosc_duszka_n = 0.0025f;
float predkosc_duszka_p = 0.0025f;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Blinky - czerwony - sciga gracza
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Blinky::Ruch() {
    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((czerwony.sprajt.getPosition().x + (czerwony.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((czerwony.sprajt.getPosition().y + (czerwony.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);
    float pozycja_wzgledna_x_gracza = ((gracz1.postac.sprajt.getPosition().x + (gracz1.postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y_gracza = ((gracz1.postac.sprajt.getPosition().y + (gracz1.postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej

    //std::cout << odleglosc_od_kratki_x <<" "<< odleglosc_od_kratki_y <<" "<< pozycja_wzgledna_x <<" "<< pozycja_wzgledna_y << std::endl;

    if ((int)pozycja_wzgledna_x != pozycja_ostatniej_zmiany_x or (int)pozycja_wzgledna_y != pozycja_ostatniej_zmiany_y){
            
        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }    
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?') {
            skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
        }
    }
    switch (this->kierunek_nastepny)
    {
    case PRAWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)                                                                                   //sprawdzenie czy jestesmy na srodku kratki
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '-')   //sprawdzenie czy mozliwy jest ruch
            {
                kierunek_aktualny = kierunek_nastepny;                                                                                                                 //ustawienie kierunku postaci na ostatnio wybrany przez gracza
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case LEWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case DOL:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case GORA:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    }

    switch (this->kierunek_aktualny) {
    case PRAWO:
        if (zegar_ruchu_czerwony.getElapsedTime().asSeconds() >= predkosc_duszka_cz)
        {
            if (odleglosc_od_kratki_x >= 0.5f)                                                                                                                          //sprawdzenie czy gracz jest w polowie kratki
            {
                if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '3')                                                                         //sprawdzenie czy gracz jest przed punktem teleportujacym
                {
                    pozycja_rysowania.x = (float)144.994;
                    pozycja_rysowania.y = (float)267.689;
                    czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                //przeniesienie gracza na odpowiednie miejsce
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x += (float)0.5;
                    czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                               //zmiana pozycji gracza
                }
            }
            else
            {
                pozycja_rysowania.x += (float)0.5;
                czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                    //zmiana pozycji gracza
            }
            zegar_ruchu_czerwony.restart();
        }
        break;
    case LEWO:
        if (zegar_ruchu_czerwony.getElapsedTime().asSeconds() >= predkosc_duszka_cz)
        {
            if (odleglosc_od_kratki_x <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '2')
                {
                    pozycja_rysowania.x = (float)629.015;
                    pozycja_rysowania.y = (float)267.689;
                    czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x -= (float)0.5;
                    czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.x -= (float)0.5;
                czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_czerwony.restart();
        }
        break;
    case DOL:
        if (zegar_ruchu_czerwony.getElapsedTime().asSeconds() >= predkosc_duszka_cz)
        {
            if (odleglosc_od_kratki_y >= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y += (float)0.5;
                    czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y += (float)0.5;
                czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_czerwony.restart();
        }
        break;
    case GORA:
        if (zegar_ruchu_czerwony.getElapsedTime().asSeconds() >= predkosc_duszka_cz)
        {
            if (odleglosc_od_kratki_y <= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y -= (float)0.5;
                    czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y -= (float)0.5;
                czerwony.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_czerwony.restart();
        }
        break;
    }
}

void Blinky::Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y) {
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        //std::cout << "GORA" << std::endl;
        kierunek_nastepny = GORA;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO
        //std::cout << "LEWO" << std::endl;
        kierunek_nastepny = LEWO;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        //std::cout << "DOL" << std::endl;
        kierunek_nastepny = DOL;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        //std::cout << "PRAWO" << std::endl;
        kierunek_nastepny = PRAWO;
    }
}

void Blinky::skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz) {
    //Odleglosci dla kazdego kierunku 0-GORA 1-LEWO 2-DOL 3-PRAWO
    float najmniejsza_odleglosc = std::numeric_limits<float>::max();
    //std::cout << najmniejsza_odleglosc << std::endl;
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y - 1) - pozycja_y_gracz) * abs((pozycja_y - 1) - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y - 1) - pozycja_y_gracz) * abs((pozycja_y - 1) - pozycja_y_gracz));
            //std::cout << "GORA: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = GORA;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO
        
        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x - 1) - pozycja_x_gracz) * abs(pozycja_x - 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x - 1) - pozycja_x_gracz) * abs(pozycja_x - 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz));
            //std::cout << "LEWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = LEWO;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        if(najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y + 1) - pozycja_y_gracz) * abs((pozycja_y + 1) - pozycja_y_gracz))){
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y + 1) - pozycja_y_gracz) * abs((pozycja_y + 1) - pozycja_y_gracz));
            //std::cout << "DOL: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = DOL;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x + 1) - pozycja_x_gracz) * abs(pozycja_x + 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x + 1) - pozycja_x_gracz) * abs(pozycja_x + 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz));
            //std::cout << "PRAWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = PRAWO;
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Pinky - rozowy - blokuje droge
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Pinky::Ruch() {
    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((rozowy.sprajt.getPosition().x + (rozowy.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((rozowy.sprajt.getPosition().y + (rozowy.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);
    float pozycja_wzgledna_x_gracza = ((gracz1.postac.sprajt.getPosition().x + (gracz1.postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y_gracza = ((gracz1.postac.sprajt.getPosition().y + (gracz1.postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej

    //std::cout << odleglosc_od_kratki_x <<" "<< odleglosc_od_kratki_y <<" "<< pozycja_wzgledna_x <<" "<< pozycja_wzgledna_y << std::endl;
    //std::cout << kierunek_aktualny << " " << kierunek_nastepny << std::endl;

    if ((int)pozycja_wzgledna_x != pozycja_ostatniej_zmiany_x or (int)pozycja_wzgledna_y != pozycja_ostatniej_zmiany_y) {

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?') {
            skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
        }
    }
    switch (this->kierunek_nastepny)
    {
    case PRAWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)                                                                                   //sprawdzenie czy jestesmy na srodku kratki
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '-')   //sprawdzenie czy mozliwy jest ruch
            {
                kierunek_aktualny = kierunek_nastepny;                                                                                                                 //ustawienie kierunku postaci na ostatnio wybrany przez gracza
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case LEWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case DOL:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case GORA:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    }

    switch (this->kierunek_aktualny) {
    case PRAWO:
        if (zegar_ruchu_rozowy.getElapsedTime().asSeconds() >= predkosc_duszka_r)
        {
            if (odleglosc_od_kratki_x >= 0.5f)                                                                                                                          //sprawdzenie czy gracz jest w polowie kratki
            {
                if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '3')                                                                         //sprawdzenie czy gracz jest przed punktem teleportujacym
                {
                    pozycja_rysowania.x = (float)144.994;
                    pozycja_rysowania.y = (float)267.689;
                    rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                //przeniesienie gracza na odpowiednie miejsce
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x += (float)0.5;
                    rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                               //zmiana pozycji gracza
                }
            }
            else
            {
                pozycja_rysowania.x += (float)0.5;
                rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                    //zmiana pozycji gracza
            }
            zegar_ruchu_rozowy.restart();
        }
        break;
    case LEWO:
        if (zegar_ruchu_rozowy.getElapsedTime().asSeconds() >= predkosc_duszka_r)
        {
            if (odleglosc_od_kratki_x <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '2')
                {
                    pozycja_rysowania.x = (float)629.015;
                    pozycja_rysowania.y = (float)267.689;
                    rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x -= (float)0.5;
                    rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.x -= (float)0.5;
                rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_rozowy.restart();
        }
        break;
    case DOL:
        if (zegar_ruchu_rozowy.getElapsedTime().asSeconds() >= predkosc_duszka_r)
        {
            if (odleglosc_od_kratki_y >= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y += (float)0.5;
                    rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y += (float)0.5;
                rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_rozowy.restart();
        }
        break;
    case GORA:
        if (zegar_ruchu_rozowy.getElapsedTime().asSeconds() >= predkosc_duszka_r)
        {
            if (odleglosc_od_kratki_y <= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y -= (float)0.5;
                    rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y -= (float)0.5;
                rozowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_rozowy.restart();
        }
        break;
    }
}

void Pinky::Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y) {
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        //std::cout << "GORA" << std::endl;
        kierunek_nastepny = GORA;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO
        //std::cout << "LEWO" << std::endl;
        kierunek_nastepny = LEWO;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        //std::cout << "DOL" << std::endl;
        kierunek_nastepny = DOL;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        //std::cout << "PRAWO" << std::endl;
        kierunek_nastepny = PRAWO;
    }
}

void Pinky::skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz) {
    float pozycja_gracza_przesunieta_x;
    float pozycja_gracza_przesunieta_y;
    
    switch (gracz1.kierunek_ostatni)
    {
    case STOP:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz;
    case PRAWO:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz + 4;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz;
        //std::cout << "**prawo " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y << " " << pozycja_x_gracz<< " " << pozycja_y_gracz<< std::endl;
        break;
    case LEWO:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz - 4;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz;
        //std::cout << "**lewo " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y <<" "<< pozycja_x_gracz <<" "<< pozycja_y_gracz << std::endl;
        break;
    case DOL:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz + 4;
        //std::cout << "**dol " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y << " " << pozycja_x_gracz << " " << pozycja_y_gracz << std::endl;
        break;
    case GORA:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz - 4;
        //std::cout << "**gora " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y << " " << pozycja_x_gracz << " " << pozycja_y_gracz << std::endl;
        break;
    }
    //Odleglosci dla kazdego kierunku 0-GORA 1-LEWO 2-DOL 3-PRAWO
    float najmniejsza_odleglosc = std::numeric_limits<float>::max();

    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_gracza_przesunieta_x) * abs(pozycja_x - pozycja_gracza_przesunieta_x) + abs((pozycja_y - 1) - pozycja_gracza_przesunieta_y) * abs((pozycja_y - 1) - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_gracza_przesunieta_x) * abs(pozycja_x - pozycja_gracza_przesunieta_x) + abs((pozycja_y - 1) - pozycja_gracza_przesunieta_y) * abs((pozycja_y - 1) - pozycja_gracza_przesunieta_y));
            std::cout << "GORA: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = GORA;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO

        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x - 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x - 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x - 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x - 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y));
            std::cout << "LEWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = LEWO;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_gracza_przesunieta_x) * abs(pozycja_x - pozycja_gracza_przesunieta_x) + abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y) * abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_gracza_przesunieta_x) * abs(pozycja_x - pozycja_gracza_przesunieta_x) + abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y) * abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y));
            std::cout << "DOL: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = DOL;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x + 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x + 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x + 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x + 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y));
            std::cout << "PRAWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = PRAWO;
        }
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Inky - niebieski - dwie kratki od pacmana jest punktem symetrii, odbicie wzgledenm tego punktu pozycji ducha czerwonego
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




void Inky::Ruch() {
    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((niebieski.sprajt.getPosition().x + (niebieski.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((niebieski.sprajt.getPosition().y + (niebieski.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);
    float pozycja_wzgledna_x_gracza = ((gracz1.postac.sprajt.getPosition().x + (gracz1.postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y_gracza = ((gracz1.postac.sprajt.getPosition().y + (gracz1.postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej

    if (start == false and gracz1.Ilosc_punktow > 5)
    {
        kierunek_aktualny = PRAWO;
        start = true;
    }

    if ((int)pozycja_wzgledna_x != pozycja_ostatniej_zmiany_x or (int)pozycja_wzgledna_y != pozycja_ostatniej_zmiany_y) {

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?') {
            skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
        }
    }
    switch (this->kierunek_nastepny)
    {
    case PRAWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)                                                                                   //sprawdzenie czy jestesmy na srodku kratki
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '-')   //sprawdzenie czy mozliwy jest ruch
            {
                kierunek_aktualny = kierunek_nastepny;                                                                                                                 //ustawienie kierunku postaci na ostatnio wybrany przez gracza
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case LEWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case DOL:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case GORA:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    }

    switch (this->kierunek_aktualny) {
    case PRAWO:
        if (zegar_ruchu_niebieski.getElapsedTime().asSeconds() >= predkosc_duszka_n)
        {
            if (odleglosc_od_kratki_x >= 0.5f)                                                                                                                          //sprawdzenie czy gracz jest w polowie kratki
            {
                if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '3')                                                                         //sprawdzenie czy gracz jest przed punktem teleportujacym
                {
                    pozycja_rysowania.x = (float)144.994;
                    pozycja_rysowania.y = (float)267.689;
                    niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                //przeniesienie gracza na odpowiednie miejsce
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x += (float)0.5;
                    niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                               //zmiana pozycji gracza
                }
            }
            else
            {
                pozycja_rysowania.x += (float)0.5;
                niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                    //zmiana pozycji gracza
            }
            zegar_ruchu_niebieski.restart();
        }
        break;
    case LEWO:
        if (zegar_ruchu_niebieski.getElapsedTime().asSeconds() >= predkosc_duszka_n)
        {
            if (odleglosc_od_kratki_x <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '2')
                {
                    pozycja_rysowania.x = (float)629.015;
                    pozycja_rysowania.y = (float)267.689;
                    niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x -= (float)0.5;
                    niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.x -= (float)0.5;
                niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_niebieski.restart();
        }
        break;
    case DOL:
        if (zegar_ruchu_niebieski.getElapsedTime().asSeconds() >= predkosc_duszka_n)
        {
            if (odleglosc_od_kratki_y >= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y += (float)0.5;
                    niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y += (float)0.5;
                niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_niebieski.restart();
        }
        break;
    case GORA:
        if (zegar_ruchu_niebieski.getElapsedTime().asSeconds() >= predkosc_duszka_n)
        {
            if (odleglosc_od_kratki_y <= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y -= (float)0.5;
                    niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y -= (float)0.5;
                niebieski.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_niebieski.restart();
        }
        break;
    }
}

void Inky::Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y) {
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        //std::cout << "GORA" << std::endl;
        kierunek_nastepny = GORA;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO
        //std::cout << "LEWO" << std::endl;
        kierunek_nastepny = LEWO;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        //std::cout << "DOL" << std::endl;
        kierunek_nastepny = DOL;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        //std::cout << "PRAWO" << std::endl;
        kierunek_nastepny = PRAWO;
    }
}

void Inky::skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz) {
    float pozycja_gracza_przesunieta_x;
    float pozycja_gracza_przesunieta_y;
    float pozycja_czerwonego_x = czerwony.pozycja_ostatniej_zmiany_x;
    float pozycja_czerownego_y = czerwony.pozycja_ostatniej_zmiany_y;

    switch (gracz1.kierunek_ostatni)
    {
    case STOP:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz;
    case PRAWO:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz + 2;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz;
        //std::cout << "**prawo " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y << " " << pozycja_x_gracz<< " " << pozycja_y_gracz<< std::endl;
        break;
    case LEWO:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz - 2;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz;
        //std::cout << "**lewo " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y <<" "<< pozycja_x_gracz <<" "<< pozycja_y_gracz << std::endl;
        break;
    case DOL:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz + 2;
        //std::cout << "**dol " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y << " " << pozycja_x_gracz << " " << pozycja_y_gracz << std::endl;
        break;
    case GORA:
        pozycja_gracza_przesunieta_x = pozycja_x_gracz;
        pozycja_gracza_przesunieta_y = pozycja_y_gracz - 2;
        //std::cout << "**gora " << pozycja_gracza_przesunieta_x << " " << pozycja_gracza_przesunieta_y << " " << pozycja_x_gracz << " " << pozycja_y_gracz << std::endl;
        break;
    }

    float dlugosc_wektora_x = czerwony.pozycja_ostatniej_zmiany_x - pozycja_gracza_przesunieta_x;
    float dlugosc_wektora_y = czerwony.pozycja_ostatniej_zmiany_y - pozycja_gracza_przesunieta_y;

    float cel_x = pozycja_gracza_przesunieta_x + dlugosc_wektora_x;
    float cel_y = pozycja_gracza_przesunieta_y + dlugosc_wektora_y;

    //Odleglosci dla kazdego kierunku 0-GORA 1-LEWO 2-DOL 3-PRAWO
    float najmniejsza_odleglosc = std::numeric_limits<float>::max();
    //std::cout << najmniejsza_odleglosc << std::endl;
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - cel_x) * abs(pozycja_x - cel_x) + abs((pozycja_y - 1) - cel_y) * abs((pozycja_y - 1) - cel_y))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - cel_x) * abs(pozycja_x - cel_x) + abs((pozycja_y - 1) - cel_y) * abs((pozycja_y - 1) - cel_y));
            //std::cout << "GORA: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = GORA;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO

        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x - 1) - cel_x) * abs(pozycja_x - 1 - cel_x) + abs(pozycja_y - cel_y) * abs(pozycja_y - cel_y))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x - 1) - cel_x) * abs(pozycja_x - 1 - cel_x) + abs(pozycja_y - cel_y) * abs(pozycja_y - cel_y));
            //std::cout << "LEWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = LEWO;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - cel_x) * abs(pozycja_x - cel_x) + abs((pozycja_y + 1) - cel_y) * abs((pozycja_y + 1) - cel_y))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - cel_x) * abs(pozycja_x - cel_x) + abs((pozycja_y + 1) - cel_y) * abs((pozycja_y + 1) - cel_y));
            //std::cout << "DOL: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = DOL;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x + 1) - cel_x) * abs(pozycja_x + 1 - cel_x) + abs(pozycja_y - cel_y) * abs(pozycja_y - cel_y))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x + 1) - cel_x) * abs(pozycja_x + 1 - cel_x) + abs(pozycja_y - cel_y) * abs(pozycja_y - cel_y));
            //std::cout << "PRAWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = PRAWO;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Clyde - pomaranczowy - goni na odleglosc 8 kratek, potem ucieka do swojego rogu
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void Clyde::Ruch() {
    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((pomaranczowy.sprajt.getPosition().x + (pomaranczowy.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((pomaranczowy.sprajt.getPosition().y + (pomaranczowy.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);
    float pozycja_wzgledna_x_gracza = ((gracz1.postac.sprajt.getPosition().x + (gracz1.postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y_gracza = ((gracz1.postac.sprajt.getPosition().y + (gracz1.postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej

    //std::cout << odleglosc_od_kratki_x <<" "<< odleglosc_od_kratki_y <<" "<< pozycja_wzgledna_x <<" "<< pozycja_wzgledna_y << std::endl;

    if (start == false and gracz1.Ilosc_punktow > 10)
    {
        kierunek_aktualny = LEWO;
        start = true;
    }

    if ((int)pozycja_wzgledna_x != pozycja_ostatniej_zmiany_x or (int)pozycja_wzgledna_y != pozycja_ostatniej_zmiany_y) {

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?') {
            skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
        }
    }
    switch (this->kierunek_nastepny)
    {
    case PRAWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)                                                                                   //sprawdzenie czy jestesmy na srodku kratki
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '-')   //sprawdzenie czy mozliwy jest ruch
            {
                kierunek_aktualny = kierunek_nastepny;                                                                                                                 //ustawienie kierunku postaci na ostatnio wybrany przez gracza
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case LEWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case DOL:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    case GORA:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '-')
            {
                kierunek_aktualny = kierunek_nastepny;
                pozycja_ostatniej_zmiany_x = (int)pozycja_wzgledna_x;
                pozycja_ostatniej_zmiany_y = (int)pozycja_wzgledna_y;
            }
        }
        break;
    }

    switch (this->kierunek_aktualny) {
    case PRAWO:
        if (zegar_ruchu_pomaranczowy.getElapsedTime().asSeconds() >= predkosc_duszka_p)
        {
            if (odleglosc_od_kratki_x >= 0.5f)                                                                                                                          //sprawdzenie czy gracz jest w polowie kratki
            {
                if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '3')                                                                         //sprawdzenie czy gracz jest przed punktem teleportujacym
                {
                    pozycja_rysowania.x = (float)144.994;
                    pozycja_rysowania.y = (float)267.689;
                    pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                //przeniesienie gracza na odpowiednie miejsce
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x += (float)0.5;
                    pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                               //zmiana pozycji gracza
                }
            }
            else
            {
                pozycja_rysowania.x += (float)0.5;
                pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                    //zmiana pozycji gracza
            }
            zegar_ruchu_pomaranczowy.restart();
        }
        break;
    case LEWO:
        if (zegar_ruchu_pomaranczowy.getElapsedTime().asSeconds() >= predkosc_duszka_p)
        {
            if (odleglosc_od_kratki_x <= 0.5)
            {
                if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '2')
                {
                    pozycja_rysowania.x = (float)629.015;
                    pozycja_rysowania.y = (float)267.689;
                    pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x -= (float)0.5;
                    pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.x -= (float)0.5;
                pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_pomaranczowy.restart();
        }
        break;
    case DOL:
        if (zegar_ruchu_pomaranczowy.getElapsedTime().asSeconds() >= predkosc_duszka_p)
        {
            if (odleglosc_od_kratki_y >= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y += (float)0.5;
                    pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y += (float)0.5;
                pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_pomaranczowy.restart();
        }
        break;
    case GORA:
        if (zegar_ruchu_pomaranczowy.getElapsedTime().asSeconds() >= predkosc_duszka_p)
        {
            if (odleglosc_od_kratki_y <= 0.5)
            {
                if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y -= (float)0.5;
                    pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
            }
            else
            {
                pozycja_rysowania.y -= (float)0.5;
                pomaranczowy.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu_pomaranczowy.restart();
        }
        break;
    }
}

void Clyde::Sprawdzenie_mozliwosci_ruchu(float pozycja_x, float pozycja_y) {
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        //std::cout << "GORA" << std::endl;
        kierunek_nastepny = GORA;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO
        //std::cout << "LEWO" << std::endl;
        kierunek_nastepny = LEWO;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        //std::cout << "DOL" << std::endl;
        kierunek_nastepny = DOL;
    }
    else if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        //std::cout << "PRAWO" << std::endl;
        kierunek_nastepny = PRAWO;
    }
}

void Clyde::skrzyzowanie(float pozycja_x, float pozycja_y, float pozycja_x_gracz, float pozycja_y_gracz) {
    //Odleglosci dla kazdego kierunku 0-GORA 1-LEWO 2-DOL 3-PRAWO
    float najmniejsza_odleglosc = std::numeric_limits<float>::max();
    //std::cout << najmniejsza_odleglosc << std::endl;
    if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y - 1) - pozycja_y_gracz) * abs((pozycja_y - 1) - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y - 1) - pozycja_y_gracz) * abs((pozycja_y - 1) - pozycja_y_gracz));
            //std::cout << "GORA: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = GORA;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO

        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x - 1) - pozycja_x_gracz) * abs(pozycja_x - 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x - 1) - pozycja_x_gracz) * abs(pozycja_x - 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz));
            //std::cout << "LEWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = LEWO;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y + 1) - pozycja_y_gracz) * abs((pozycja_y + 1) - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs((pozycja_y + 1) - pozycja_y_gracz) * abs((pozycja_y + 1) - pozycja_y_gracz));
            //std::cout << "DOL: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = DOL;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x + 1) - pozycja_x_gracz) * abs(pozycja_x + 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x + 1) - pozycja_x_gracz) * abs(pozycja_x + 1 - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz));
            //std::cout << "PRAWO: " << najmniejsza_odleglosc << std::endl;
            kierunek_nastepny = PRAWO;
        }
    }
}