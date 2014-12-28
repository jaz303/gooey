#ifndef __GOOEY_DRAWINGCONTEXT_HPP__
#define __GOOEY_DRAWINGCONTEXT_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"
#include <SDL2/SDL.h>
#include <cairo/cairo.h>

namespace gooey {

class DrawingContext {

public:
    DrawingContext();
    ~DrawingContext();

    void setSurface(SDL_Surface *surface);

    void setFill(float r, float g, float b);

    void translate(float dx, float dy);
    void scale(float s);
    void scale(float sx, float sy);
    void rotate(float theta);
    void loadIdentity();

    void clear();
    void fillRect(Rect rect);
    void fillRect(float x, float y, float w, float h);

private:

    void teardown();

    SDL_Surface *sdlSurface_;
    cairo_surface_t *cairoSurface_;
    cairo_t *cairo_;
};

}

#endif