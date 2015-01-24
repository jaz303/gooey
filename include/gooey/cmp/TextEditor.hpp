#ifndef __GOOEY_TEXT_EDITOR_HPP__
#define __GOOEY_TEXT_EDITOR_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"
#include <string>

namespace gooey {

class TextEditor : public View {

public:
    TextEditor(Rect rect);

    void render(DrawingContext *ctx, Rect invalidRect);

private:

};

}

#endif