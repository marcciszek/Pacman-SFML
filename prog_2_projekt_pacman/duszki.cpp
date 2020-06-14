#include "game.h"

sf::Clock zegar_ruchu_czerwony;
sf::Clock zegar_ruchu_rozowy;
sf::Clock zegar_ruchu_niebieski;
sf::Clock zegar_ruchu_pomaranczowy;
float predkosc_duszka_cz = 0.003f;
float predkosc_duszka_r = 0.003f;
float predkosc_duszka_n = 0.003f;
float predkosc_duszka_p = 0.003f;

sf::Clock zegar_animacji_czerwony;
sf::Clock zegar_animacji_niebieski;
sf::Clock zegar_animacji_rozowy;
sf::Clock zegar_animacji_pomaranczowy;
sf::IntRect klatka_animacji_czerwony(3, 146, 26, 26);
sf::IntRect klatka_animacji_rozowy(3, 178, 26, 26);
sf::IntRect klatka_animacji_niebieski(3, 210, 26, 26);
sf::IntRect klatka_animacji_pomaranczowy(3, 242, 26, 26);

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
            
        if (ucieczka == 2 and (int)pozycja_wzgledna_x == 14 and (int)pozycja_wzgledna_y == 11)
        {
            ucieczka = 0;
        }

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }    
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?')
        {
            if (ucieczka == 0)
            {
                predkosc_duszka_cz = 0.003f;
                if (czy_wybrac_nowy_kierunek)
                {
                skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
                }
            }
            else if (ucieczka == 1)
            {
                predkosc_duszka_cz = 0.004f;
                if (czy_wybrac_nowy_kierunek)
                {
                skrzyzowanie_losowe(pozycja_wzgledna_x, pozycja_wzgledna_y);
                }
            }
            else if (ucieczka == 2)
            {
                predkosc_duszka_cz = 0.002f;
                if (czy_wybrac_nowy_kierunek)
                {

                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, 14, 11.5);

                }
            }
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
    czy_wybrac_nowy_kierunek = false;
}

void Blinky::skrzyzowanie_losowe(float pozycja_x, float pozycja_y)
{
    bool czy_zmienic_kierunek = true;
    std::random_device ziarno;
    std::mt19937 losowa(ziarno());
    std::uniform_int_distribution<int> losowy_kierunek(0, 3);

    while (czy_zmienic_kierunek)
    {
        int wylosowany_kierunek = losowy_kierunek(losowa);
        switch (wylosowany_kierunek)
        {
        case 0:
            if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' and kierunek_aktualny != DOL))
            {
                kierunek_nastepny = GORA;
                czy_zmienic_kierunek = false;
            }
            break;
        case 1:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' and kierunek_aktualny != PRAWO))
            {
                kierunek_nastepny = LEWO;
                czy_zmienic_kierunek = false;
            }
            break;
        case 2:
            if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' and kierunek_aktualny != GORA))
            {
                kierunek_nastepny = DOL;
                czy_zmienic_kierunek = false;
            }
            break;
        case 3:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' and kierunek_aktualny != LEWO))
        {
            kierunek_nastepny = PRAWO;
            czy_zmienic_kierunek = false;
        }
            break;
        }
    }
    czy_wybrac_nowy_kierunek = false;
}

void Blinky::Animacja() {
    if (zegar_animacji_czerwony.getElapsedTime().asSeconds() >= 0.1f) {
        switch (ucieczka) {
        case 0:
            switch (kierunek_aktualny) {
            case PRAWO:
                klatka_animacji_czerwony.top = 146;               //koordynaty gornej krawedzi klatki
                if (klatka_animacji_czerwony.left != 3 && klatka_animacji_czerwony.left != 35) {
                    klatka_animacji_czerwony.left = 3;
                }
                if (klatka_animacji_czerwony.left == 35) {      //sprawdzenie czy animacja doszla do ostatniej klatki
                    klatka_animacji_czerwony.left = 3;          //powrot na pierwsza klatke animacji danego kierunku
                }
                else klatka_animacji_czerwony.left = 35;       //skok do nastepnej klatki animacji
                break;
            case LEWO:
                klatka_animacji_czerwony.top = 146;
                if (klatka_animacji_czerwony.left != 131 && klatka_animacji_czerwony.left != 163) {
                    klatka_animacji_czerwony.left = 131;
                }
                if (klatka_animacji_czerwony.left == 163) {
                    klatka_animacji_czerwony.left = 131;
                }
                else klatka_animacji_czerwony.left = 163;
                break;
            case GORA:
                klatka_animacji_czerwony.top = 146;
                if (klatka_animacji_czerwony.left != 195 && klatka_animacji_czerwony.left != 227) {
                    klatka_animacji_czerwony.left = 195;
                }
                if (klatka_animacji_czerwony.left == 227) {
                    klatka_animacji_czerwony.left = 195;
                }
                else klatka_animacji_czerwony.left = 227;
                break;
            case DOL:
                klatka_animacji_czerwony.top = 146;
                if (klatka_animacji_czerwony.left != 67 && klatka_animacji_czerwony.left != 99) {
                    klatka_animacji_czerwony.left = 67;
                }
                if (klatka_animacji_czerwony.left == 99) {
                    klatka_animacji_czerwony.left = 67;
                }
                else klatka_animacji_czerwony.left = 99;
                break;
            }
            czerwony.sprajt.setTextureRect(klatka_animacji_czerwony);
            zegar_animacji_czerwony.restart();
            break;
        case 1:
            klatka_animacji_czerwony.top = 306;
            if (klatka_animacji_czerwony.left != 3 && klatka_animacji_czerwony.left != 35) {
                klatka_animacji_czerwony.left = 3;
            }
            if (klatka_animacji_czerwony.left == 35) {
                klatka_animacji_czerwony.left = 3;
            }
            else klatka_animacji_czerwony.left += 32;
            czerwony.sprajt.setTextureRect(klatka_animacji_czerwony);
            zegar_animacji_czerwony.restart();
            break;
        case 2:
            break;
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

        if (ucieczka == 2 and (int)pozycja_wzgledna_x == 14 and (int)pozycja_wzgledna_y == 11)
        {
            ucieczka = 0;
        }

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?')
        {
            if (ucieczka == 0)
            {
                predkosc_duszka_r = 0.003f;
                if (czy_wybrac_nowy_kierunek)
                {
                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
                }
            }
            else if (ucieczka == 1)
            {
                predkosc_duszka_r = 0.004f;
                if (czy_wybrac_nowy_kierunek)
                {
                    skrzyzowanie_losowe(pozycja_wzgledna_x, pozycja_wzgledna_y);
                }
            }
            else if (ucieczka == 2)
            {
                predkosc_duszka_r = 0.002f;
                if (czy_wybrac_nowy_kierunek)
                {

                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, 14, 11.5);

                }
            }
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
            kierunek_nastepny = GORA;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO

        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x - 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x - 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x - 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x - 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y));
            kierunek_nastepny = LEWO;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
        if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_gracza_przesunieta_x) * abs(pozycja_x - pozycja_gracza_przesunieta_x) + abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y) * abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_gracza_przesunieta_x) * abs(pozycja_x - pozycja_gracza_przesunieta_x) + abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y) * abs((pozycja_y + 1) - pozycja_gracza_przesunieta_y));
            kierunek_nastepny = DOL;
        }
    }
    if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
        if (najmniejsza_odleglosc > sqrt(abs((pozycja_x + 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x + 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y))) {
            najmniejsza_odleglosc = sqrt(abs((pozycja_x + 1) - pozycja_gracza_przesunieta_x) * abs(pozycja_x + 1 - pozycja_gracza_przesunieta_x) + abs(pozycja_y - pozycja_gracza_przesunieta_y) * abs(pozycja_y - pozycja_gracza_przesunieta_y));
            kierunek_nastepny = PRAWO;
        }
    }
    czy_wybrac_nowy_kierunek = false;
}

void Pinky::skrzyzowanie_losowe(float pozycja_x, float pozycja_y)
{
    bool czy_zmienic_kierunek = true;
    std::random_device ziarno;
    std::mt19937 losowa(ziarno());
    std::uniform_int_distribution<int> losowy_kierunek(0, 3);

    while (czy_zmienic_kierunek)
    {
        int wylosowany_kierunek = losowy_kierunek(losowa);
        switch (wylosowany_kierunek)
        {
        case 0:
            if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' and kierunek_aktualny != DOL))
            {
                kierunek_nastepny = GORA;
                czy_zmienic_kierunek = false;
            }
            break;
        case 1:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' and kierunek_aktualny != PRAWO))
            {
                kierunek_nastepny = LEWO;
                czy_zmienic_kierunek = false;
            }
            break;
        case 2:
            if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' and kierunek_aktualny != GORA))
            {
                kierunek_nastepny = DOL;
                czy_zmienic_kierunek = false;
            }
            break;
        case 3:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' and kierunek_aktualny != LEWO))
            {
                kierunek_nastepny = PRAWO;
                czy_zmienic_kierunek = false;
            }
            break;
        }
    }
    czy_wybrac_nowy_kierunek = false;
}

void Pinky::Animacja() {
    if (zegar_animacji_rozowy.getElapsedTime().asSeconds() >= 0.1f) {
        switch (ucieczka) {
        case 0:
            switch (kierunek_aktualny) {
            case PRAWO:
                klatka_animacji_rozowy.top = 178;               //koordynaty gornej krawedzi klatki
                if (klatka_animacji_rozowy.left != 3 && klatka_animacji_rozowy.left != 35) {
                    klatka_animacji_rozowy.left = 3;
                }
                if (klatka_animacji_rozowy.left == 35) {      //sprawdzenie czy animacja doszla do ostatniej klatki
                    klatka_animacji_rozowy.left = 3;          //powrot na pierwsza klatke animacji danego kierunku
                }
                else klatka_animacji_rozowy.left = 35;       //skok do nastepnej klatki animacji
                break;
            case LEWO:
                klatka_animacji_rozowy.top = 178;
                if (klatka_animacji_rozowy.left != 131 && klatka_animacji_rozowy.left != 163) {
                    klatka_animacji_rozowy.left = 131;
                }
                if (klatka_animacji_rozowy.left == 163) {
                    klatka_animacji_rozowy.left = 131;
                }
                else klatka_animacji_rozowy.left = 163;
                break;
            case GORA:
                klatka_animacji_rozowy.top = 178;
                if (klatka_animacji_rozowy.left != 195 && klatka_animacji_rozowy.left != 227) {
                    klatka_animacji_rozowy.left = 195;
                }
                if (klatka_animacji_rozowy.left == 227) {
                    klatka_animacji_rozowy.left = 195;
                }
                else klatka_animacji_rozowy.left = 227;
                break;
            case DOL:
                klatka_animacji_rozowy.top = 178;
                if (klatka_animacji_rozowy.left != 67 && klatka_animacji_rozowy.left != 99) {
                    klatka_animacji_rozowy.left = 67;
                }
                if (klatka_animacji_rozowy.left == 99) {
                    klatka_animacji_rozowy.left = 67;
                }
                else klatka_animacji_rozowy.left = 99;
                break;
            }
            rozowy.sprajt.setTextureRect(klatka_animacji_rozowy);
            zegar_animacji_rozowy.restart();
            break;
        case 1:
            klatka_animacji_czerwony.top = 306;
            if (klatka_animacji_czerwony.left != 3 && klatka_animacji_czerwony.left != 35) {
                klatka_animacji_czerwony.left = 3;
            }
            if (klatka_animacji_czerwony.left == 35) {
                klatka_animacji_czerwony.left = 3;
            }
            else klatka_animacji_czerwony.left += 32;
            rozowy.sprajt.setTextureRect(klatka_animacji_czerwony);
            zegar_animacji_rozowy.restart();
            break;
        case 2:
            break;
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

        if (ucieczka == 2 and (int)pozycja_wzgledna_x == 14 and (int)pozycja_wzgledna_y == 11)
        {
            ucieczka = 0;
        }

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?')
        {
            if (ucieczka == 0)
            {
                predkosc_duszka_n = 0.003f;
                if (czy_wybrac_nowy_kierunek)
                {
                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
                }
            }
            else if (ucieczka == 1)
            {
                predkosc_duszka_n = 0.004f;
                if (czy_wybrac_nowy_kierunek)
                {
                    skrzyzowanie_losowe(pozycja_wzgledna_x, pozycja_wzgledna_y);
                }
            }
            else if (ucieczka == 2)
            {
                predkosc_duszka_n = 0.002f;
                if (czy_wybrac_nowy_kierunek)
                {

                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, 14, 11.5);

                }
            }
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
    float pozycja_czerwonego_x = (float)czerwony.pozycja_ostatniej_zmiany_x;
    float pozycja_czerownego_y = (float)czerwony.pozycja_ostatniej_zmiany_y;

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
    czy_wybrac_nowy_kierunek = false;
}

void Inky::skrzyzowanie_losowe(float pozycja_x, float pozycja_y)
{
    bool czy_zmienic_kierunek = true;
    std::random_device ziarno;
    std::mt19937 losowa(ziarno());
    std::uniform_int_distribution<int> losowy_kierunek(0, 3);

    while (czy_zmienic_kierunek)
    {
        int wylosowany_kierunek = losowy_kierunek(losowa);
        switch (wylosowany_kierunek)
        {
        case 0:
            if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' and kierunek_aktualny != DOL))
            {
                kierunek_nastepny = GORA;
                czy_zmienic_kierunek = false;
            }
            break;
        case 1:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' and kierunek_aktualny != PRAWO))
            {
                kierunek_nastepny = LEWO;
                czy_zmienic_kierunek = false;
            }
            break;
        case 2:
            if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' and kierunek_aktualny != GORA))
            {
                kierunek_nastepny = DOL;
                czy_zmienic_kierunek = false;
            }
            break;
        case 3:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' and kierunek_aktualny != LEWO))
            {
                kierunek_nastepny = PRAWO;
                czy_zmienic_kierunek = false;
            }
            break;
        }
    }
    czy_wybrac_nowy_kierunek = false;
}

void Inky::Animacja() {
    if (zegar_animacji_niebieski.getElapsedTime().asSeconds() >= 0.1f) {
        switch (ucieczka) {
        case 0:
            switch (kierunek_aktualny) {
            case PRAWO:
                klatka_animacji_niebieski.top = 210;               //koordynaty gornej krawedzi klatki
                if (klatka_animacji_niebieski.left != 3 && klatka_animacji_niebieski.left != 35) {
                    klatka_animacji_niebieski.left = 3;
                }
                if (klatka_animacji_niebieski.left == 35) {      //sprawdzenie czy animacja doszla do ostatniej klatki
                    klatka_animacji_niebieski.left = 3;          //powrot na pierwsza klatke animacji danego kierunku
                }
                else klatka_animacji_niebieski.left = 35;       //skok do nastepnej klatki animacji
                break;
            case LEWO:
                klatka_animacji_niebieski.top = 210;
                if (klatka_animacji_niebieski.left != 131 && klatka_animacji_niebieski.left != 163) {
                    klatka_animacji_niebieski.left = 131;
                }
                if (klatka_animacji_niebieski.left == 163) {
                    klatka_animacji_niebieski.left = 131;
                }
                else klatka_animacji_niebieski.left = 163;
                break;
            case GORA:
                klatka_animacji_niebieski.top = 210;
                if (klatka_animacji_niebieski.left != 195 && klatka_animacji_niebieski.left != 227) {
                    klatka_animacji_niebieski.left = 195;
                }
                if (klatka_animacji_niebieski.left == 227) {
                    klatka_animacji_niebieski.left = 195;
                }
                else klatka_animacji_niebieski.left = 227;
                break;
            case DOL:
                klatka_animacji_niebieski.top = 210;
                if (klatka_animacji_niebieski.left != 67 && klatka_animacji_niebieski.left != 99) {
                    klatka_animacji_niebieski.left = 67;
                }
                if (klatka_animacji_niebieski.left == 99) {
                    klatka_animacji_niebieski.left = 67;
                }
                else klatka_animacji_niebieski.left = 99;
                break;
            }
            niebieski.sprajt.setTextureRect(klatka_animacji_niebieski);
            zegar_animacji_niebieski.restart();
            break;
        case 1:
            klatka_animacji_niebieski.top = 306;
            if (klatka_animacji_niebieski.left != 3 && klatka_animacji_niebieski.left != 35) {
                klatka_animacji_niebieski.left = 3;
            }
            if (klatka_animacji_niebieski.left == 35) {
                klatka_animacji_niebieski.left = 3;
            }
            else klatka_animacji_niebieski.left += 32;
            niebieski.sprajt.setTextureRect(klatka_animacji_niebieski);
            zegar_animacji_niebieski.restart();
            break;
        case 2:
            break;
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

        if (ucieczka == 2 and (int)pozycja_wzgledna_x == 14 and (int)pozycja_wzgledna_y == 11)
        {
            ucieczka = 0;
        }

        if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '0') {
            Sprawdzenie_mozliwosci_ruchu(pozycja_wzgledna_x, pozycja_wzgledna_y);
        }
        else if (poziom_1_skrzyzowania[(int)pozycja_wzgledna_y][(int)pozycja_wzgledna_x] == '?')
        {
            if (ucieczka == 0)
            {
                predkosc_duszka_p = 0.003f;
                if (czy_wybrac_nowy_kierunek)
                {
                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, pozycja_wzgledna_x_gracza, pozycja_wzgledna_y_gracza);
                }
            }
            else if (ucieczka == 1)
            {
                predkosc_duszka_p = 0.004f;
                if (czy_wybrac_nowy_kierunek)
                {
                    skrzyzowanie_losowe(pozycja_wzgledna_x, pozycja_wzgledna_y);
                }
            }
            else if (ucieczka == 2)
            {
                predkosc_duszka_p = 0.002f;
                if (czy_wybrac_nowy_kierunek)
                {

                    skrzyzowanie(pozycja_wzgledna_x, pozycja_wzgledna_y, 14, 11.5);

                }
            }
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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
                czy_wybrac_nowy_kierunek = true;
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

    float odleglosc_od_gracza = sqrt(abs(pozycja_x - pozycja_x_gracz) * abs(pozycja_x - pozycja_x_gracz) + abs(pozycja_y - pozycja_y_gracz) * abs(pozycja_y - pozycja_y_gracz));

    //Odleglosci dla kazdego kierunku 0-GORA 1-LEWO 2-DOL 3-PRAWO
    float najmniejsza_odleglosc = std::numeric_limits<float>::max();
    //std::cout << najmniejsza_odleglosc << std::endl;

    if (odleglosc_od_gracza >= 8) {     //DROGA DO GRACZA
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
    else {      //DROGA DO ROGU
        if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '?') and kierunek_aktualny != DOL) {           //GORA
            if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_rog.x) * abs(pozycja_x - pozycja_rog.x) + abs((pozycja_y - 1) - pozycja_rog.y) * abs((pozycja_y - 1) - pozycja_rog.y))) {
                najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_rog.x) * abs(pozycja_x - pozycja_rog.x) + abs((pozycja_y - 1) - pozycja_rog.y) * abs((pozycja_y - 1) - pozycja_rog.y));
                //std::cout << "GORA: " << najmniejsza_odleglosc << std::endl;
                kierunek_nastepny = GORA;
            }
        }
        if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '?') and kierunek_aktualny != PRAWO) {           //LEWO

            if (najmniejsza_odleglosc > sqrt(abs((pozycja_x - 1) - pozycja_rog.x) * abs(pozycja_x - 1 - pozycja_rog.x) + abs(pozycja_y - pozycja_rog.y) * abs(pozycja_y - pozycja_rog.y))) {
                najmniejsza_odleglosc = sqrt(abs((pozycja_x - 1) - pozycja_rog.x) * abs(pozycja_x - 1 - pozycja_rog.x) + abs(pozycja_y - pozycja_rog.y) * abs(pozycja_y - pozycja_rog.y));
                //std::cout << "LEWO: " << najmniejsza_odleglosc << std::endl;
                kierunek_nastepny = LEWO;
            }
        }
        if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' || poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '?') and kierunek_aktualny != GORA) {           //DOL
            if (najmniejsza_odleglosc > sqrt(abs(pozycja_x - pozycja_rog.x) * abs(pozycja_x - pozycja_rog.x) + abs((pozycja_y + 1) - pozycja_rog.y) * abs((pozycja_y + 1) - pozycja_rog.y))) {
                najmniejsza_odleglosc = sqrt(abs(pozycja_x - pozycja_rog.x) * abs(pozycja_x - pozycja_rog.x) + abs((pozycja_y + 1) - pozycja_rog.y) * abs((pozycja_y + 1) - pozycja_rog.y));
                //std::cout << "DOL: " << najmniejsza_odleglosc << std::endl;
                kierunek_nastepny = DOL;
            }
        }
        if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' || poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '?') and kierunek_aktualny != LEWO) {             //PRAWO
            if (najmniejsza_odleglosc > sqrt(abs((pozycja_x + 1) - pozycja_rog.x) * abs(pozycja_x + 1 - pozycja_rog.x) + abs(pozycja_y - pozycja_rog.y) * abs(pozycja_y - pozycja_rog.y))) {
                najmniejsza_odleglosc = sqrt(abs((pozycja_x + 1) - pozycja_rog.x) * abs(pozycja_x + 1 - pozycja_rog.x) + abs(pozycja_y - pozycja_rog.y) * abs(pozycja_y - pozycja_rog.y));
                //std::cout << "PRAWO: " << najmniejsza_odleglosc << std::endl;
                kierunek_nastepny = PRAWO;
            }
        }
    }
    czy_wybrac_nowy_kierunek = false;
}

void Clyde::skrzyzowanie_losowe(float pozycja_x, float pozycja_y)
{
    bool czy_zmienic_kierunek = true;
    std::random_device ziarno;
    std::mt19937 losowa(ziarno());
    std::uniform_int_distribution<int> losowy_kierunek(0, 3);

    while (czy_zmienic_kierunek)
    {
        int wylosowany_kierunek = losowy_kierunek(losowa);
        switch (wylosowany_kierunek)
        {
        case 0:
            if ((poziom_1_skrzyzowania[(int)pozycja_y - 1][(int)pozycja_x] == '0' and kierunek_aktualny != DOL))
            {
                kierunek_nastepny = GORA;
                czy_zmienic_kierunek = false;
            }
            break;
        case 1:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x - 1] == '0' and kierunek_aktualny != PRAWO))
            {
                kierunek_nastepny = LEWO;
                czy_zmienic_kierunek = false;
            }
            break;
        case 2:
            if ((poziom_1_skrzyzowania[(int)pozycja_y + 1][(int)pozycja_x] == '0' and kierunek_aktualny != GORA))
            {
                kierunek_nastepny = DOL;
                czy_zmienic_kierunek = false;
            }
            break;
        case 3:
            if ((poziom_1_skrzyzowania[(int)pozycja_y][(int)pozycja_x + 1] == '0' and kierunek_aktualny != LEWO))
            {
                kierunek_nastepny = PRAWO;
                czy_zmienic_kierunek = false;
            }
            break;
        }
    }
    czy_wybrac_nowy_kierunek = false;
}

void Clyde::Animacja() {
    if (zegar_animacji_pomaranczowy.getElapsedTime().asSeconds() >= 0.1f) {
        switch (ucieczka) {
        case 0:
            switch (kierunek_aktualny) {
            case PRAWO:
                klatka_animacji_pomaranczowy.top = 242;               //koordynaty gornej krawedzi klatki
                if (klatka_animacji_pomaranczowy.left != 3 && klatka_animacji_pomaranczowy.left != 35) {
                    klatka_animacji_pomaranczowy.left = 3;
                }
                if (klatka_animacji_pomaranczowy.left == 35) {      //sprawdzenie czy animacja doszla do ostatniej klatki
                    klatka_animacji_pomaranczowy.left = 3;          //powrot na pierwsza klatke animacji danego kierunku
                }
                else klatka_animacji_pomaranczowy.left = 35;       //skok do nastepnej klatki animacji
                break;
            case LEWO:
                klatka_animacji_pomaranczowy.top = 242;
                if (klatka_animacji_pomaranczowy.left != 131 && klatka_animacji_pomaranczowy.left != 163) {
                    klatka_animacji_pomaranczowy.left = 131;
                }
                if (klatka_animacji_pomaranczowy.left == 163) {
                    klatka_animacji_pomaranczowy.left = 131;
                }
                else klatka_animacji_pomaranczowy.left = 163;
                break;
            case GORA:
                klatka_animacji_pomaranczowy.top = 242;
                if (klatka_animacji_pomaranczowy.left != 195 && klatka_animacji_pomaranczowy.left != 227) {
                    klatka_animacji_pomaranczowy.left = 195;
                }
                if (klatka_animacji_pomaranczowy.left == 227) {
                    klatka_animacji_pomaranczowy.left = 195;
                }
                else klatka_animacji_pomaranczowy.left = 227;
                break;
            case DOL:
                klatka_animacji_pomaranczowy.top = 242;
                if (klatka_animacji_pomaranczowy.left != 67 && klatka_animacji_pomaranczowy.left != 99) {
                    klatka_animacji_pomaranczowy.left = 67;
                }
                if (klatka_animacji_pomaranczowy.left == 99) {
                    klatka_animacji_pomaranczowy.left = 67;
                }
                else klatka_animacji_pomaranczowy.left = 99;
                break;
            }
            pomaranczowy.sprajt.setTextureRect(klatka_animacji_pomaranczowy);
            zegar_animacji_pomaranczowy.restart();
            break;
        case 1:
            klatka_animacji_pomaranczowy.top = 306;
            if (klatka_animacji_pomaranczowy.left != 3 && klatka_animacji_pomaranczowy.left != 35) {
                klatka_animacji_pomaranczowy.left = 3;
            }
            if (klatka_animacji_pomaranczowy.left == 35) {
                klatka_animacji_pomaranczowy.left = 3;
            }
            else klatka_animacji_pomaranczowy.left += 32;
            pomaranczowy.sprajt.setTextureRect(klatka_animacji_pomaranczowy);
            zegar_animacji_pomaranczowy.restart();
            break;
        case 2:
            break;
        }
    }
}