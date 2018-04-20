#include "main.h"

int main(int argc, char *argv[])

{

    delay=16;

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
