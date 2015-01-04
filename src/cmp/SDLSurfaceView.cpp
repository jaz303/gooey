#include "gooey/cmp/SDLSurfaceView.hpp"
#include "gooey/DrawingContext.hpp"

using namespace gooey;

SDLSurfaceView::SDLSurfaceView(Rect rect)
    : View(rect)
    , surface_(0)
    , cairoSurface_(0)
    , surfaceIsAdopted_(false)
{
}

SDLSurfaceView::~SDLSurfaceView()
{
    setSurface(0);
}

SDL_Surface* SDLSurfaceView::surface() const
{
    return surface_;
}

void SDLSurfaceView::setSurface(SDL_Surface *newSurface, bool adopt)
{
    if (cairoSurface_) {
        cairo_surface_destroy(cairoSurface_);
        cairoSurface_ = 0;
    }

    if (surface_) {
        if (surfaceIsAdopted_) {
            SDL_FreeSurface(surface_);
        }
        surface_ = 0;
        surfaceIsAdopted_ = false;
    }

    if (newSurface) {
        surface_ = newSurface;
        surfaceIsAdopted_ = adopt;
        // TODO(jwf): helper function for creating cairo surface from SDL surface
        cairoSurface_ = cairo_image_surface_create_for_data(
                (unsigned char*)surface_->pixels,
                CAIRO_FORMAT_ARGB32,
                surface_->w,
                surface_->h,
                surface_->pitch
        );
    }
}

void SDLSurfaceView::adoptSurface()
{
    if (surface_) {
        surfaceIsAdopted_ = true;
    }
}

void SDLSurfaceView::render(DrawingContext *ctx, Rect invalidRect)
{
    if (!surface_) {
        return;
    }

    float sx, sy, sw, sh;
    float dx, dy, dw, dh;

    float widthDelta = surface_->w - width();

    if (widthDelta < 0) {
        sx = 0;
        sw = surface_->w;
        dx = (width() * 0.5f) - (sw * 0.5f);
        dw = sw;
    } else {
        dx = 0;
        dw = sw = width();
        sx = widthDelta * 0.5f;
    }

    float heightDelta = surface_->h - height();

    if (heightDelta < 0) {
        sy = 0;
        sh = surface_->h;
        dy = (height() * 0.5f) - (sh * 0.5f);
        dh = sh;
    } else {
        dy = 0;
        dh = sh = height();
        sy = heightDelta * 0.5f;
    }

    if (dw == 0 || dh == 0) {
        return;
    }

    ctx->drawSurface(cairoSurface_, sx, sy, sw, sh, dx, dy, dw, dh);
}