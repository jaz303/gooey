#ifndef __GOOEY_WINDOW_HPP__
#define __GOOEY_WINDOW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"
#include "gooey/DrawingContext.hpp"
#include <vector>
#include <SDL2/SDL.h>

namespace gooey {

class Window {

public:
    Window(WindowManager *windowManager);
    ~Window();

    Rect rect() const;

    /*
     * NOTE: rect will be rounded to integral origin/size
     */
    void setRect(Rect rect);

    void addView(View *view);

    void render();
    SDL_Surface* sdlSurface() { return sdlSurface_; }

private:

    WindowManager       *windowManager_;
    DrawingContext      context_;
    SDL_Surface         *sdlSurface_;
    Rect                rect_;
    std::vector<View*>  views_;

};

}

#endif