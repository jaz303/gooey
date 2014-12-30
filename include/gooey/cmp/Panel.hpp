#ifndef __GOOEY_PANEL_HPP__
#define __GOOEY_PANEL_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"

#include <vector>

namespace gooey {

class Panel : public View {

public:
    Panel(Rect rect);

    void addSubView(View *subView);

    virtual void render(DrawingContext *ctx, Rect invalidRect) override;

    virtual View* findEventTarget(Event *evt) override;

private:

    std::vector<View*> subViews_;

};

}

#endif