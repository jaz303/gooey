#ifndef __GOOEY_VIEW_HPP__
#define __GOOEY_VIEW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"

namespace gooey {

class View {

public:
    View(Rect rect);

    Window* window() const;
    void setWindow(Window *window);

    Rect rect() const;

    virtual void render(DrawingContext *ctx, Rect rect);

private:

    Window*         window_;
    Rect            rect_;

};

}

#endif