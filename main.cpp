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
    win->setRect(Rect(50, 50, 640, 500));

    Panel *p1 = new Panel(Rect(10, 10, 620, 60));
    win->addView(p1);

    SplitView *sp1 = new SplitView(Rect(10, 80, 620, 410));
    win->addView(sp1);

    Panel *p2 = new Panel(Rect());
    sp1->setLeftView(p2);

    Button *b3 = new Button(Rect(10, 10, 50, 50));
    b3->setLabel("button 3");

    Button *b4 = new Button(Rect(-40, 100, 100, 50));
    b4->setLabel("button 4");

    p2->addSubView(b3);
    p2->addSubView(b4);

    Panel *p3 = new Panel(Rect());
    sp1->setRightView(p3);

    Button *b1 = new Button(Rect(10, 10, 200, 40));
    b1->setLabel("button 1");

    Button *b2 = new Button(Rect(220, 10, 70, 40));
    b2->setLabel("button 2");

    p1->addSubView(b1);
    p1->addSubView(b2);
//
//    win->addView(b1);
//    win->addView(b2);

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