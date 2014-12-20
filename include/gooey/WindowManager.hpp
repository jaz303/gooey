#pragma once

#include "gooey/gooey.hpp"
#include <vector>

namespace gooey {

class WindowManager {

public:
    WindowManager(SDL_Window *window, SDL_Renderer *renderer);
    WindowManager(SDL_Window *window, SDL_Renderer *renderer, Rect rect);

    void render();

    inline SDL_Window* sdlWindow() const { return window_; }
    inline SDL_Renderer* sdlRenderer() const { return renderer_; }

    Window* createRootWindow();

private:
    SDL_Window              *window_;
    SDL_Renderer            *renderer_;
    Rect                    rect_;

    std::vector<Window*>    windows_;

};

}