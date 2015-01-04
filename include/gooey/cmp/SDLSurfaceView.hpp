#ifndef __GOOEY_SDLSURFACEVIEW_HPP__
#define __GOOEY_SDLSURFACEVIEW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"
#include <string>
#include <cairo/cairo.h>

namespace gooey {

class SDLSurfaceView : public View {

public:
    SDLSurfaceView(Rect rect);
    ~SDLSurfaceView();

    SDL_Surface* surface() const;
    void setSurface(SDL_Surface *newSurface, bool adopt = false);
    void adoptSurface();

    void render(DrawingContext *ctx, Rect invalidRect);

private:

    SDL_Surface *surface_;
    cairo_surface_t *cairoSurface_;
    bool surfaceIsAdopted_;

};

}

#endif