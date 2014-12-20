#include <iostream>
#include <SDL2/SDL.h>

#include "gooey/gooey.hpp"

using namespace std;
using namespace gooey;

int main() {

    if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        cout << "failed to init SDL: " << SDL_GetError() << endl;
        return 1;
    } else {
        atexit(SDL_Quit);
    }

    SDL_Window *window = SDL_CreateWindow("Gooey Test", 50, 50, 1024, 768, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    WindowManager *wm = new WindowManager(window, renderer);

    Window *win = wm->createRootWindow();

    bool running = true;
    while (running) {

        SDL_Event evt;
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_WINDOWEVENT) {
                if (evt.window.event == SDL_WINDOWEVENT_CLOSE) {
                    cout << "close window requested..." << endl;
                    running = false;
                    break;
                }
            } else {
                // dispatch to wm
            }
        }



        wm->render();

        SDL_Delay(1000 / 60);

    }

    return 0;

}