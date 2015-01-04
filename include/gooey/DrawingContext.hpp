#ifndef __GOOEY_DRAWINGCONTEXT_HPP__
#define __GOOEY_DRAWINGCONTEXT_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"
#include <SDL2/SDL.h>
#include <cairo/cairo.h>
#include <string>

namespace gooey {

class DrawingContext {

public:
    DrawingContext();
    ~DrawingContext();

    void setSurface(SDL_Surface *surface);

    void save();
    void restore();

    void clip(Rect rect);
    void clip(float x, float y, float w, float h);

    void clear();

    void translate(float dx, float dy);
    void scale(float s);
    void scale(float sx, float sy);
    void rotate(float theta);
    void loadIdentity();

    void setFill(float r, float g, float b);
    void setFill(float r, float g, float b, float a);

    void fillRect(Rect rect);
    void fillRect(float x, float y, float w, float h);

    void setFontSize(float newFontSize);
    void fillTextCentered(std::string text, float cx, float cy);
    void fillTextVerticallyCentered(std::string text, float cx, float cy);

private:

    void teardown();

    SDL_Surface *sdlSurface_;
    cairo_surface_t *cairoSurface_;
    cairo_t *cairo_;
};

}

#endif