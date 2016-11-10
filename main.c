#include "graphic.h"
#include "game.h"
#include "menu.h"

//Define

#define tailleFenetreX 1472
#define tailleFenetreY 768

int main(int argc, char *argv[])
{
    CreateWindow(tailleFenetreX, tailleFenetreY, "Game");
    menu leMenu;
    leMenu.Init();

    while (!KeyGet(SDLK_ESCAPE) && !StickGetClick(0, 7))
    {
        leMenu.Draw();
        RefreshScreen();
    }

    return 0;
}
