#ifndef __GOOEY_SPLITVIEW_HPP__
#define __GOOEY_SPLITVIEW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"

// TODO(jwf): support horizontal and vertical orientation

namespace gooey {

class SplitView : public View {

public:
    SplitView(Rect rect);

    virtual void setRect(Rect rect) override;

    inline float dividerSize() const { return dividerSize_; }
    void setDividerSize(float newDividerSize);

    void setLeftView(View *view);
    void setRightView(View *view);

    virtual void render(DrawingContext *ctx, Rect invalidRect) override;

    virtual View* findEventTarget(Event *evt) override;
    virtual void dispatchEvent(Event *evt) override;

private:

    float dividerSize_;
    float splitRatio_;
    View *firstView_;
    View *secondView_;
    bool resizing_;

    void updateChildRects(bool c1, bool c2);

    inline float dividerPosition() const {
        float dividerMidPoint = width() * splitRatio_;
        float dividerLeft = dividerMidPoint - (dividerSize_ * 0.5f);
        return dividerLeft;
    }

};

}

#endif