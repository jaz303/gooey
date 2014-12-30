#include "gooey/gooey.hpp"

#include <iostream>

namespace gooey {

std::ostream &operator<<(std::ostream &os, Point &p) {
    os << '<' << p.x << ',' << p.y << '>';
    return os;
}

std::ostream &operator<<(std::ostream &os, Size &s) {
    os << '<' << s.width << 'x' << s.height << '>';
    return os;
}

std::ostream &operator<<(std::ostream &os, Rect &r) {
    os << "<Rect origin=" << r.origin << " size=" << r.size << ">";
    return os;
}

}