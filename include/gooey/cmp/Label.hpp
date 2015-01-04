#ifndef __GOOEY_LABEL_HPP__
#define __GOOEY_LABEL_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"
#include <string>

namespace gooey {

class Label : public View {

public:
    Label(Rect rect);

    void setLabel(const char *newLabel);
    void setLabel(std::string newLabel);

    void render(DrawingContext *ctx, Rect invalidRect);

private:

    std::string label_;

};

}

#endif