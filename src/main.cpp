
#include "controller.h"
#include "game.h"
#include "renderer.h"


int main()
{
    renderer rndrr;
    controller cntrllr;
    game g;
    g.run(cntrllr, rndrr);
}
