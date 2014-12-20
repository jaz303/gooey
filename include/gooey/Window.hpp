#pragma once

#include "gooey/gooey.hpp"
#include "gooey/geom/Rect.hpp"

namespace gooey {

class Window {

public:
    Window(WindowManager *windowManager);

    Rect rect() const;
    void setRect(Rect rect);

    void render();

private:

    WindowManager* windowManager_;

    Rect rect_;

};

}