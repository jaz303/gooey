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

    inline float x() const { return rect_.origin.x; }
    inline float y() const { return rect_.origin.y; }
    inline float width() const { return rect_.size.width; }
    inline float height() const { return rect_.size.height; }

    virtual void render(DrawingContext *ctx, Rect rect);
    virtual void dispatchEvent(Event *evt);

protected:

    void startTappingEvents();
    void stopTappingEvents();

    Window*         window_;
    Rect            rect_;

};

}

#endif