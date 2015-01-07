#include "gooey/DrawingContext.hpp"

#include <iostream>

using namespace gooey;

DrawingContext::DrawingContext()
        : sdlSurface_(0), cairoSurface_(0), cairo_(0)
{
}

DrawingContext::~DrawingContext()
{
    teardown();
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
        // TODO(jwf): should we attempt to maintain any cairo state?
        // (or is it possible to simply rebind the cairo context to
        // a new surface?)
        cairo_ = cairo_create(cairoSurface_);
        cairo_select_font_face(
                cairo_,
                "sans-serif",
                CAIRO_FONT_SLANT_NORMAL,
                CAIRO_FONT_WEIGHT_NORMAL
        );
    }
}

void DrawingContext::save()
{
    cairo_save(cairo_);
}

void DrawingContext::restore()
{
    cairo_restore(cairo_);
}

void DrawingContext::clip(Rect rect)
{
    cairo_rectangle(cairo_, rect.origin.x, rect.origin.y, rect.size.width, rect.size.height);
    cairo_clip(cairo_);
}

void DrawingContext::clip(float x, float y, float w, float h)
{
    cairo_rectangle(cairo_, x, y, w, h);
    cairo_clip(cairo_);
}

void DrawingContext::clear()
{
    cairo_paint(cairo_);
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

void DrawingContext::beginPath()
{
    cairo_new_path(cairo_);
}

void DrawingContext::setFill(float r, float g, float b)
{
    cairo_set_source_rgb(cairo_, r, g, b);
}

void DrawingContext::setFill(float r, float g, float b, float a) {
    cairo_set_source_rgba(cairo_, r, g, b, a);
}

void DrawingContext::setStroke(float r, float g, float b)
{
    cairo_set_source_rgb(cairo_, r, g, b);
}

void DrawingContext::setStroke(float r, float g, float b, float a) {
    cairo_set_source_rgba(cairo_, r, g, b, a);
}

void DrawingContext::setLineWidth(float w) {
    cairo_set_line_width(cairo_, w);
}

void DrawingContext::moveTo(float x, float y) {
    cairo_move_to(cairo_, x, y);
}

void DrawingContext::lineTo(float x, float y) {
    cairo_line_to(cairo_, x, y);
}

void DrawingContext::arc(float cx, float cy, float radius, float angle1, float angle2)
{
    cairo_arc(cairo_, cx, cy, radius, angle1, angle2);
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

void DrawingContext::stroke()
{
    cairo_stroke(cairo_);
}

void DrawingContext::fill()
{
    cairo_fill(cairo_);
}

void DrawingContext::strokeFill()
{
    cairo_stroke_preserve(cairo_);
    cairo_fill(cairo_);
}

void DrawingContext::fillStroke()
{
    cairo_fill_preserve(cairo_);
    cairo_stroke(cairo_);
}

void DrawingContext::setFontSize(float newFontSize)
{
    cairo_set_font_size(cairo_, newFontSize);
}

void DrawingContext::fillTextCentered(std::string text, float cx, float cy)
{
    cairo_text_extents_t extents;
    cairo_text_extents(cairo_, text.c_str(), &extents);
    cairo_move_to(cairo_, cx - extents.width / 2, cy + extents.height / 2);
    cairo_show_text(cairo_, text.c_str());
}

void DrawingContext::fillTextVerticallyCentered(std::string text, float cx, float cy)
{
    cairo_text_extents_t extents;
    cairo_text_extents(cairo_, text.c_str(), &extents);
    cairo_move_to(cairo_, cx, cy + extents.height / 2);
    cairo_show_text(cairo_, text.c_str());
}

void DrawingContext::drawSurface(cairo_surface_t *surface, float sx, float sy, float sw, float sh, float dx, float dy, float dw, float dh)
{
    float imageOffsetX = dx - sx;
    float imageOffsetY = dy - sy;

    cairo_set_source_surface(cairo_, surface, imageOffsetX, imageOffsetY);
    cairo_rectangle(cairo_, dx, dy, dw, dh);
    cairo_fill(cairo_);
}

//
// Private

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