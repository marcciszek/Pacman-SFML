#include "Game.h"


int typ_menu = 1;                               //Zmienna przelacznika typu menu -> 1: MENU; 2: GRA;
bool czy_wlaczona = true;                       //Zmienna odpowiedzialna za dzialanie calego programu
bool gra_aktywna = false;                       //zmienna ktora aktywuje gre po pierwszym ruchu gracza
int stan_gry = 0;                               //domyslnie 0, 1 to wygrana, 2 to przegrana
rozmiar_okna rozmiar_menu = { 800,600 };
rozmiar_okna rozmiar_gry = { 800, 600 };
Game gra;                                        //Obiekt klasy Game -> definicja w pliku "Game.h" -> okno okna gry
Game menu;                                       //Obiekt klasy Game -> definicja w pliku "Game.h" -> okno menu glownego


int main()
{
    if (!font.loadFromFile("grafiki/FrederickatheGreat-Regular.ttf"))     //zaladowanie czcionki ze sprawdzeniem poprawnosci
    {
        std::cerr << "font problem" << std::endl;
    }
    menu.Init(rozmiar_menu.x, rozmiar_menu.y);                            //Inicjalizacja okienka menu -> (float x, float y) -> x: szerokosc okna; y: wysokosc okna;

    while (czy_wlaczona) {                                                //Petla glowna programu
        switch (typ_menu) {                                               //Przelacznik typu okna -> 1: MENU; 2: GRA;
        case 1:
            menu.Render();                                                //uruchomienie funkcji odopwiedzialnej za obsluge menu
            break;
        case 2:
            gra.Render();                                                 //uruchomienie funkcji odpowiedzialnej za obsluge gry
            break;
        }
    }
}
