#ifndef __GOOEY_POINT_HPP__
#define __GOOEY_POINT_HPP__

namespace gooey {

class Point {
public:
    Point() : x(0), y(0) {}
    Point(float x_, float y_) : x(x_), y(y_) {}
    Point(const Point& that) : x(that.x), y(that.y) {}

    Point& operator=(const Point& that) {
        x = that.x;
        y = that.y;
        return *this;
    }

    bool isZero() {
        return x == 0 && y == 0;
    }

    float x, y;
};

}

#endif