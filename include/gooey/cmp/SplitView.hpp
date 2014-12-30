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

    inline float dividerWidth() const { return dividerWidth_; }
    void setDividerWidth(float newDividerWidth);

    void setLeftView(View *view);
    void setRightView(View *view);

    virtual void render(DrawingContext *ctx, Rect invalidRect) override;

    virtual View* findEventTarget(Event *evt) override;

private:

    float dividerWidth_;
    float splitRatio_;
    View *firstView_;
    View *secondView_;

    void updateChildRects(bool c1, bool c2);

    inline float dividerPosition() const {
        float dividerMidPoint = width() * splitRatio_;
        float dividerLeft = dividerMidPoint - (dividerWidth_ * 0.5f);
        return dividerLeft;
    }

};

}

#endif