#ifndef __GOOEY_RECT_HPP__
#define __GOOEY_RECT_HPP__

#include <SDL2/SDL.h>
#include "gooey/geom/Point.hpp"
#include "gooey/geom/Size.hpp"

namespace gooey {

class Rect {
public:

    Rect()
            : origin(Point()), size(Size())
    {}

    Rect(Size size_)
            : origin(Point()), size(size_)
    {}

    Rect(float x, float y, float width, float height)
            : origin(Point(x,y)), size(Size(width, height))
    {}

    Rect(const Rect& that)
            : origin(that.origin), size(that.size)
    {}

    Rect& operator=(const Rect& that) {
        origin = that.origin;
        size = that.size;
        return *this;
    }

    bool isZero() const { return origin.isZero() && size.isZero(); }

    //

    Rect offset(Point p) const {
        return offset(p.x, p.y);
    }

    Rect offset(float x, float y) const {
        return Rect(origin.x + x, origin.y + y, size.width, size.height);
    }

    //
    //

    inline float left() const   { return origin.x; }
    inline float right() const  { return origin.x + size.width; }
    inline float top() const    { return origin.y; }
    inline float bottom() const { return origin.y + size.height; }

    //
    // Containment

    bool contains(const Point p) const {
        return contains(p.x, p.y);
    }

    bool contains(const Point p, Point *offset) const {
        return contains(p.x, p.y, offset);
    }

    bool contains(float x, float y) const {
        return x >= left() && x < right() && y >= top() && y < bottom();
    }

    bool contains(float x, float y, Point *offset) const {
        float dx = x - origin.x;
        float dy = y - origin.y;
        if (dx > 0 && dx < size.width && dy > 0 && dy < size.height) {
            offset->x = dx;
            offset->y = dy;
            return true;
        } else {
            return false;
        }
    }

    //
    // SDL interop

    SDL_Rect toSDLRect() const {
        SDL_Rect out;
        out.x = (int)origin.x;
        out.y = (int)origin.y;
        out.w = (int)size.width;
        out.h = (int)size.height;
        return out;
    }

    void fillSDLRect(SDL_Rect *rect) const {
        rect->x = (int)origin.x;
        rect->y = (int)origin.y;
        rect->w = (int)size.width;
        rect->h = (int)size.height;
    }

    Point origin;
    Size size;
};

}

#endif