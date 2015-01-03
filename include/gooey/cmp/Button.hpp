#ifndef __GOOEY_BUTTON_HPP__
#define __GOOEY_BUTTON_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"
#include <string>

namespace gooey {

class Button : public View {

public:
    Button(Rect rect);

    void setLabel(const char *newLabel);
    void setLabel(std::string newLabel);

    void render(DrawingContext *ctx, Rect invalidRect);

    virtual void dispatchEvent(Event *evt) override;

private:

    bool pressed_;
    std::string label_;

};

}

#endif