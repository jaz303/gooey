#ifndef __GOOEY_SIZE_HPP__
#define __GOOEY_SIZE_HPP__

namespace gooey {

class Size {
public:
    Size() : width(0), height(0) {}
    Size(float width_, float height_) : width(width_), height(height_) {}
    Size(const Size& that) : width(that.width), height(that.height) {}

    Size& operator=(const Size& that) {
        width = that.width;
        height = that.height;
        return *this;
    }

    bool isZero() const {
        return width == 0 && height == 0;
    }

    float width, height;
};

std::ostream& operator<<(std::ostream& os, Size& s);

}

#endif