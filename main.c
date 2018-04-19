#include "main.h"


int main(int argc, char *argv[])

{

    init();

    render();

    for (;;) {

        input();

        if (update()) {

            gameover();

        }

        render();

        SDL_Delay(delay * 10);

    }

    return 0;

}
