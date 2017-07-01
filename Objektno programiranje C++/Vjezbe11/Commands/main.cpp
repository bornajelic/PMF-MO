#include "commands.h"
#include <cstdlib>

// kompilacija (izvan Code::Blocks-a)
// g++ -g -Wall -std=c++11 main.cpp commands.cpp -lsfml-graphics  -lsfml-window  -lsfml-system
int main ( int argc, char *argv[] )
{
    Game game;
    // run uvodi beskonačnu petlju unutar koje se reagira na događaje.
    // Program se zaustavlja kada kada se zatvori prozor.
    game.run();

    return EXIT_SUCCESS;
}
