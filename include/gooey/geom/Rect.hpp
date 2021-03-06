#ifndef __GOOEY_RECT_HPP__
#define __GOOEY_RECT_HPP__

#include <SDL2/SDL.h>
#include "gooey/geom/Point.hpp"
#include "gooey/geom/Size.hpp"

namespace gooey {

class Rect {
public:

    Rect()
            : origin(Point(0, 0)), size(Size(0, 0))
    {}

    Rect(Size size_)
            : origin(Point(0, 0)), size(size_)
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
        offset->x = x - origin.x;
        offset->y = y - origin.y;
        return offset->x > 0
                && offset->x < size.width
                && offset->y > 0
                && offset->y < size.height;
    }

    Point offsetOf(Point p) const {
        return Point(p.x - origin.x, p.y - origin.y);
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

std::ostream& operator<<(std::ostream& os, Rect& p);

}

#endif