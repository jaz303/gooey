#ifndef __GOOEY_DRAWINGCONTEXT_HPP__
#define __GOOEY_DRAWINGCONTEXT_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"
#include <SDL2/SDL.h>

namespace gooey {

class DrawingContext {

public:
    DrawingContext(SDL_Renderer *renderer);

    void setFill(float r, float g, float b);

    void fillRect(Rect rect);
    void fillRect(float x, float y, float w, float h);

private:

    SDL_Renderer *renderer_;

};

}

#endif