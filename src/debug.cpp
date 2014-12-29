#include "gooey/gooey.hpp"

#include <iostream>

namespace gooey {

std::ostream &operator<<(std::ostream &os, Point &p) {
    os << '<' << p.x << ',' << p.y << '>';
    return os;
}

}