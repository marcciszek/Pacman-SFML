#include "Game.h"

sf::Clock zegar_ruchu;
sf::Clock zegar_animacji;
sf::Clock zegar_boost;
sf::IntRect klatka_animacji(3, 3, 26, 26);                //startowy kwadrat postaci wycinany z arkusza tekstur

const float predkosc_gracza = 0.0025f;

void PacMan::Ruch_postaci() {

    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    float pozycja_wzgledna_x = ((postac.sprajt.getPosition().x + (postac.sprajt.getTextureRect().width / 2)) - szerokosc_boku) / szerokosc_kratki;          //pozycja horyzontalna na mapie logicznej
    float pozycja_wzgledna_y = ((postac.sprajt.getPosition().y + (postac.sprajt.getTextureRect().height / 2))) / wysokosc_kratki;                           //pozycja wertykalna na mapie logicznej
    float odleglosc_od_kratki_x = pozycja_wzgledna_x - floor(pozycja_wzgledna_x);                                                                           //odleglosc horyzontalna od srodka gracza do krawedzi kratki logicznej
    float odleglosc_od_kratki_y = pozycja_wzgledna_y - floor(pozycja_wzgledna_y);                                                                           //odleglosc wertykalna od srodka gracza do krawedzi kratki logicznej
    //std::cout << pozycja_wzgledna_x << " " << pozycja_wzgledna_y << std::endl;
    //switch ten odpowiedzialny jest za sprawdzenie, czy ostatni kierunek wybrany przez gracza jest mozliwy do realizacji, jesli tak to ustawia odpowiedni kierunek postaci
    
    if (zegar_boost.getElapsedTime().asSeconds() >= 6.0f) {
        boost_aktywny = 0;
        if (czerwony.ucieczka == 1) {
            czerwony.ucieczka = 0;
        }
        if (rozowy.ucieczka == 1) {
            rozowy.ucieczka = 0;
        }
        if (niebieski.ucieczka == 1) {
            niebieski.ucieczka = 0;
        }
        if (pomaranczowy.ucieczka == 1) {
            pomaranczowy.ucieczka = 0;
        }
    }

    switch (this->kierunek_nastepny)
    {
    case PRAWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)                                                                                   //sprawdzenie czy jestesmy na srodku kratki
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '-' and poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] != '9')   //sprawdzenie czy mozliwy jest ruch
            {
            kierunek_aktualny = kierunek_nastepny;                                                                                                                 //ustawienie kierunku postaci na ostatnio wybrany przez gracza
            kierunek_ostatni = kierunek_nastepny;
            }
        }
        break;
    case LEWO:
        if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '-' and poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] != '9')
            {
            kierunek_aktualny = kierunek_nastepny;
            kierunek_ostatni = kierunek_nastepny;
            }
        }
        break;
    case DOL:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '-' and poziom_1[(int)pozycja_wzgledna_y + 1][(int)pozycja_wzgledna_x] != '9')
            {
            kierunek_aktualny = kierunek_nastepny;
            kierunek_ostatni = kierunek_nastepny;
            }
        }
        break;
    case GORA:
        if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
        {
            if (poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '-' and poziom_1[(int)pozycja_wzgledna_y - 1][(int)pozycja_wzgledna_x] != '9')
            {
            kierunek_aktualny = kierunek_nastepny;
            kierunek_ostatni = kierunek_nastepny;
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
                    poprawa_pozycji(odleglosc_od_kratki_x, odleglosc_od_kratki_y);
                }
                else if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x + 1] == '3')                                                                         //sprawdzenie czy gracz jest przed punktem teleportujacym
                {
                    pozycja_rysowania.x = (float)144.994;
                    pozycja_rysowania.y = (float)267.689;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                //przeniesienie gracza na odpowiednie miejsce
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x += (float)0.5;
                    postac.sprajt.setPosition(pozycja_rysowania.x , pozycja_rysowania.y);                                                                               //zmiana pozycji gracza
                    zbieranie_pkt((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);                                                                                    //funkcja zbirajaca punkty
                    Kontakt_z_przeciwnikiem((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                }
            }
            else
            {
                pozycja_rysowania.x += (float)0.5;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);                                                                                    //zmiana pozycji gracza
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
                    kierunek_nastepny = STOP;
                    poprawa_pozycji(odleglosc_od_kratki_x, odleglosc_od_kratki_y);
                }
                else if (poziom_1[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x - 1] == '2')
                {
                    pozycja_rysowania.x = (float)629.015;
                    pozycja_rysowania.y = (float)267.689;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                }
                else if (odleglosc_od_kratki_y >= 0.48f and odleglosc_od_kratki_y <= 0.52f)
                {
                    pozycja_rysowania.x -= (float)0.5;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                    zbieranie_pkt((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                    Kontakt_z_przeciwnikiem((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                }
            }
            else
            {
                pozycja_rysowania.x -= (float)0.5;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
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
                    kierunek_nastepny = STOP;
                    poprawa_pozycji(odleglosc_od_kratki_x, odleglosc_od_kratki_y);
                }
                else if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y += (float)0.5;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                    zbieranie_pkt((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                    Kontakt_z_przeciwnikiem((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                }
            }
            else
            {
                pozycja_rysowania.y += (float)0.5;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
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
                    kierunek_nastepny = STOP;
                    poprawa_pozycji(odleglosc_od_kratki_x, odleglosc_od_kratki_y);
                }
                else if (odleglosc_od_kratki_x >= 0.48f and odleglosc_od_kratki_x <= 0.52f)
                {
                    pozycja_rysowania.y -= (float)0.5;
                    postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
                    zbieranie_pkt((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                    Kontakt_z_przeciwnikiem((int)pozycja_wzgledna_x, (int)pozycja_wzgledna_y);
                }
            }
            else
            {
                pozycja_rysowania.y -= (float)0.5;
                postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
            }
            zegar_ruchu.restart();
        }
        break;
    }
}

void PacMan::Animacja_postaci() {
    if (zegar_animacji.getElapsedTime().asSeconds() >= 0.1f) {
        switch (kierunek_aktualny) {
        case PRAWO:
            klatka_animacji.top = 3;               //koordynaty gornej krawedzi klatki
            if (klatka_animacji.left == 81) {      //sprawdzenie czy animacja doszla do ostatniej klatki
                klatka_animacji.left = 3;          //powrot na pierwsza klatke animacji danego kierunku
            }
            else klatka_animacji.left += 26;       //skok do nastepnej klatki animacji
            break;
        case LEWO:
            klatka_animacji.top = 32;
            if (klatka_animacji.left == 81) {
                klatka_animacji.left = 3;
            }
            else klatka_animacji.left += 26;
            break;
        case GORA:
            klatka_animacji.top = 61;
            if (klatka_animacji.left == 81) {
                klatka_animacji.left = 3;
            }
            else klatka_animacji.left += 26;
            break;
        case DOL:
            klatka_animacji.top = 90;
            if (klatka_animacji.left == 81) {
                klatka_animacji.left = 3;
            }
            else klatka_animacji.left += 26;
            break;
        }
        postac.sprajt.setTextureRect(klatka_animacji);  //ustawienie danej klatki animacji
        zegar_animacji.restart();
    }
}

void PacMan::zbieranie_pkt(int pozycja_x, int pozycja_y) {
    if (poziom_1[pozycja_y][pozycja_x] == '#')
    {
        for (int i = 0; i < 242; i++) {
            if (pozycja_x == punkt[i].pozycja_logiczna.x && pozycja_y == punkt[i].pozycja_logiczna.y) {
                punkt[i].Ustawienie(-100, -100);
                Ilosc_punktow++;
                std::cout << "Punkty: " << Ilosc_punktow << std::endl;
                break;
            }
        }
    }
    else if (poziom_1[pozycja_y][pozycja_x] == 'X')
    {
        for (int i = 0; i < 4; i++) {
            if (pozycja_x == boost[i].pozycja_logiczna.x && pozycja_y == boost[i].pozycja_logiczna.y) {
                boost[i].Ustawienie(-100, -100);
                boost_aktywny = 1;
                czerwony.ucieczka = 1;
                rozowy.ucieczka = 1;
                niebieski.ucieczka = 1;
                pomaranczowy.ucieczka = 1;
                zegar_boost.restart();
                break;
            }
        }
    }
}



void punkty::Ustawienie(int x, int y) {
    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    pozycja_logiczna.x = x;
    pozycja_logiczna.y = y;
    pozycja_wzgledna.x = (float)x * szerokosc_kratki + szerokosc_boku + 0.5f * szerokosc_kratki;
    pozycja_wzgledna.y = (float)y * wysokosc_kratki + 0.5f * wysokosc_kratki;
    punkt.sprajt.setPosition(pozycja_wzgledna.x, pozycja_wzgledna.y);
}

void punkty_boost::Ustawienie(int x, int y) {
    float szerokosc_boku = ((float)rozmiar_gry.x - tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y)) / (float)2;                //szerokosc obszaru miedzy mapa a krawedzia okna
    float szerokosc_kratki = tlo.tekstura.getSize().x * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)28;                                      //szerokosc kratki na mapie logicznej
    float wysokosc_kratki = tlo.tekstura.getSize().y * ((float)rozmiar_gry.y / tlo.tekstura.getSize().y) / (float)31;                                       //wysokosc kratki na mapie logicznej
    pozycja_logiczna.x = x;
    pozycja_logiczna.y = y;
    pozycja_wzgledna.x = (float)x * szerokosc_kratki + szerokosc_boku;
    pozycja_wzgledna.y = (float)y * wysokosc_kratki;
    punkt.sprajt.setPosition(pozycja_wzgledna.x, pozycja_wzgledna.y);
}

void PacMan::poprawa_pozycji(float wzgledna_x, float wzgledna_y)
{
    std::cout << "***************" <<wzgledna_x<<" "<<wzgledna_y<< std::endl;
    if (wzgledna_x >= 0.46f and wzgledna_x < 0.5f)
    {
        pozycja_rysowania.x += 0.2f;
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
        std::cout << "1" << std::endl;
    }
    else if (wzgledna_x > 0.5f and wzgledna_x <= 0.54f)
    {
        pozycja_rysowania.x -= 0.2f;
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
        std::cout << "2" << std::endl;
    }
    if (wzgledna_y >= 0.46f and wzgledna_y < 0.5f)
    {
        pozycja_rysowania.y += 0.2f;
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
        std::cout << "3" << std::endl;
    }
    else if (wzgledna_y > 0.5f and wzgledna_y <= 0.54f)
    {
        pozycja_rysowania.y -= 0.2f;
        postac.sprajt.setPosition(pozycja_rysowania.x, pozycja_rysowania.y);
        std::cout << "4" << std::endl;
    }
}

void PacMan::Kontakt_z_przeciwnikiem(float pozycja_x, float pozycja_y) {

    if (pozycja_x == czerwony.pozycja_ostatniej_zmiany_x && pozycja_y == czerwony.pozycja_ostatniej_zmiany_y)
    {
        if (czerwony.ucieczka == 0)
        {
            stan_gry = 2;
        }
        else if (czerwony.ucieczka == 1)
        {
            czerwony.ucieczka = 2;
        }
    }

    if (pozycja_x == rozowy.pozycja_ostatniej_zmiany_x && pozycja_y == rozowy.pozycja_ostatniej_zmiany_y)
    {
        if (rozowy.ucieczka == 0)
        {
            stan_gry = 2;
        }
        else if (rozowy.ucieczka == 1)
        {
            rozowy.ucieczka = 2;
        }
    }

    if (pozycja_x == niebieski.pozycja_ostatniej_zmiany_x && pozycja_y == niebieski.pozycja_ostatniej_zmiany_y)
    {
        if (niebieski.ucieczka == 0)
        {
            stan_gry = 2;
        }
        else if (niebieski.ucieczka == 1)
        {
            niebieski.ucieczka = 2;
        }
    }

    if (pozycja_x == pomaranczowy.pozycja_ostatniej_zmiany_x && pozycja_y == pomaranczowy.pozycja_ostatniej_zmiany_y)
    {
        if (pomaranczowy.ucieczka == 0)
        {
            stan_gry = 2;
        }
        else if (pomaranczowy.ucieczka == 1)
        {
            pomaranczowy.ucieczka = 2;
        }
    }
}