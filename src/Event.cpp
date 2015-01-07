#include "gooey/Event.hpp"
#include "gooey/View.hpp"

using namespace gooey;

Point Event::targetTopLeftScreen() const {
    if (!targetView) return Point();
    return Point(
            screenOffset.x - viewOffset.x,
            screenOffset.y - viewOffset.y);
}

Point Event::targetCenterScreen() const {
    if (!targetView) return Point();
    return Point(
            screenOffset.x - viewOffset.x + targetView->width() * 0.5f,
            screenOffset.y - viewOffset.y + targetView->height() * 0.5f
    );
}