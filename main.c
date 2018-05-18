#include "main.h"

int main(int argc, char *argv[])

{

    delay=(int*)malloc(sizeof(int));
    *delay=8;
    angle = 0;

    init();

    render();

    for (;;) {

        input();

        if (update()) {

            gameover();

        }

        render();

        SDL_Delay(*delay * 10);

    }

    return 0;

}
