#ifndef __GOOEY_BUTTON_HPP__
#define __GOOEY_BUTTON_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"

namespace gooey {

class Button : public View {

public:
    Button(Rect rect);

    void render(DrawingContext *ctx, Rect invalidRect);

    virtual void dispatchEvent(Event *evt) override;

private:

    bool pressed_;

};

}

#endif