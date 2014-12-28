#include "gooey/DrawingContext.hpp"

#include <iostream>

using namespace gooey;

DrawingContext::DrawingContext()
        : sdlSurface_(0), cairoSurface_(0), cairo_(0)
{
}

void DrawingContext::setSurface(SDL_Surface *surface)
{
    teardown();

    sdlSurface_ = surface;
    if (sdlSurface_) {
        cairoSurface_ = cairo_image_surface_create_for_data(
                (unsigned char*)surface->pixels,
                CAIRO_FORMAT_ARGB32,
                surface->w,
                surface->h,
                surface->pitch
        );
        cairo_ = cairo_create(cairoSurface_);
    }
}

DrawingContext::~DrawingContext()
{
    teardown();
}

void DrawingContext::setFill(float r, float g, float b)
{
    cairo_set_source_rgb(cairo_, r, g, b);
}

void DrawingContext::translate(float dx, float dy)
{
    cairo_translate(cairo_, dx, dy);
}

void DrawingContext::scale(float s)
{
    cairo_scale(cairo_, s, s);
}

void DrawingContext::scale(float sx, float sy)
{
    cairo_scale(cairo_, sx, sy);
}

void DrawingContext::rotate(float theta)
{
    cairo_rotate(cairo_, theta);
}

void DrawingContext::loadIdentity()
{
    cairo_identity_matrix(cairo_);
}

void DrawingContext::clear()
{
    cairo_paint(cairo_);
}

void DrawingContext::fillRect(Rect rect)
{
    cairo_rectangle(cairo_, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    cairo_fill(cairo_);
}

void DrawingContext::fillRect(float x, float y, float w, float h)
{
    cairo_rectangle(cairo_, x, y, w, h);
    cairo_fill(cairo_);
}

void DrawingContext::teardown()
{
    if (sdlSurface_) {
        sdlSurface_ = 0;
    }
    if (cairo_) {
        cairo_destroy(cairo_);
        cairo_ = 0;
    }
    if (cairoSurface_) {
        cairo_surface_destroy(cairoSurface_);
        cairoSurface_ = 0;
    }
}