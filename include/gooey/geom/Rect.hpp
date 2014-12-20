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

    bool isZero() { return origin.isZero() && size.isZero(); }

    //

    Rect offset(Point p) {
        return offset(p.x, p.y);
    }

    Rect offset(float x, float y) {
        return Rect(origin.x + x, origin.y + y, size.width, size.height);
    }

    //
    //

    inline float left()     { return origin.x; }
    inline float right()    { return origin.x + size.width; }
    inline float top()      { return origin.y; }
    inline float bottom()   { return origin.y + size.height; }

    //
    // Containment

    bool contains(const Point p) {
        return contains(p.x, p.y);
    }

    bool contains(const Point p, Point &offset) {
        return contains(p.x, p.y, offset);
    }

    bool contains(float x, float y) {
        return x >= left() && x < right() && y >= top() && y < bottom();
    }

    bool contains(float x, float y, Point& offset) {
        float dx = x - origin.x;
        float dy = y - origin.y;
        if (dx > 0 && dx < size.width && dy > 0 && dy < size.height) {
            offset.x = dx;
            offset.y = dy;
            return true;
        } else {
            return false;
        }
    }

    //
    // SDL interop

    SDL_Rect toSDLRect() {
        SDL_Rect out;
        out.x = (int)origin.x;
        out.y = (int)origin.y;
        out.w = (int)size.width;
        out.h = (int)size.height;
        return out;
    }

    void fillSDLRect(SDL_Rect *rect) {
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