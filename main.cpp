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

    SDL_Window *window = SDL_CreateWindow("Gooey Test", 50, 50, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    //SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
   // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    WindowManager *wm = new WindowManager(window, 0);

    Window *win = wm->createRootWindow();
    win->setRect(Rect(50, 50, 300, 300));

    Button *b1 = new Button(Rect(10, 10, 200, 60));
    Button *b2 = new Button(Rect(100, 100, 150, 50));

    win->addView(b1);
    win->addView(b2);

    bool running = true;
    while (running) {
        Event evt;

        while (SDL_PollEvent(&evt.sdl)) {
            evt.init();

            if (evt.sdl.type == SDL_WINDOWEVENT) {
                if (evt.sdl.window.event == SDL_WINDOWEVENT_CLOSE) {
                    cout << "close window requested..." << endl;
                    running = false;
                    break;
                } else if (evt.sdl.window.event == SDL_WINDOWEVENT_RESIZED) {
                    wm->sdlWindowDidResize();
                    break;
                }
            } else if (!wm->dispatchEvent(&evt)) {
                // event wasn't handled by the window manager
            }
        }

        wm->render();

        SDL_Delay(1000 / 60);

    }

    return 0;

}