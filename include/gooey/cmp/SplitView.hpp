#ifndef __GOOEY_SPLITVIEW_HPP__
#define __GOOEY_SPLITVIEW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"

namespace gooey {

class SplitView : public View {

public:
    SplitView(Rect rect);

    virtual void setRect(Rect rect) override;

    void setLeftView(View *view);
    void setRightView(View *view);

    virtual void render(DrawingContext *ctx, Rect invalidRect) override;

    virtual View* findEventTarget(Event *evt) override;

private:

    float splitRatio_;
    View *firstView_;
    View *secondView_;

    void updateChildRects(bool c1, bool c2);

};

}

#endif