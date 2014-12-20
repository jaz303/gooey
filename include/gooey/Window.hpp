#ifndef __GOOEY_WINDOW_HPP__
#define __GOOEY_WINDOW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"
#include <vector>

namespace gooey {

class Window {

public:
    Window(WindowManager *windowManager);

    Rect rect() const;
    void setRect(Rect rect);

    void addView(View *view);

    void render();

private:

    WindowManager* windowManager_;
    DrawingContext* context_;

    Rect rect_;

    std::vector<View*> views_;

};

}

#endif