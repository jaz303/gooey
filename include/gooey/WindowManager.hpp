#ifndef __GOOEY_WINDOWMANAGER_HPP__
#define __GOOEY_WINDOWMANAGER_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"
#include <SDL2/SDL.h>
#include <vector>

namespace gooey {

class WindowManager {

public:
    WindowManager(SDL_Window *window, SDL_Renderer *renderer);

    void render();

    inline SDL_Window* sdlWindow() const { return window_; }
    inline SDL_Renderer* sdlRenderer() const { return renderer_; }

    bool dispatchEvent(Event *evt);

    Window* createRootWindow();

    /*
     * Call this method if the SDL window is resized
     */
    void sdlWindowDidResize();

private:
    SDL_Window              *window_;
    SDL_Renderer            *renderer_;
    Rect                    rect_;

    std::vector<Window*>    windows_;
    Window                  *rootWindow_;

};

}

#endif