#ifndef __GOOEY_KNOB_HPP__
#define __GOOEY_KNOB_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"
#include <string>

// TODO(jwf): stepping/rounding
// TODO(jwf): angular motion
// TODO(jwf): configurable motion
// TODO(jwf): configurable sensitivity

namespace gooey {

class Knob : public View {

public:
    Knob(Rect rect);

    float minValue() const { return minValue_; }
    float maxValue() const { return maxValue_; }
    float value() const { return value_; }

    void setMinValue(float newMinValue) {
        minValue_ = newMinValue;
        if (minValue_ > maxValue_) {
            minValue_ = maxValue_;
        }
    }

    void setMaxValue(float newMaxValue) {
        maxValue_ = newMaxValue;
        if (maxValue_ < minValue_) {
            maxValue_ = minValue_;
        }
    }

    void setValue(float newValue) {
        value_ = newValue;
        if (value_ < minValue_) value_ = minValue_;
        if (value_ > maxValue_) value_ = maxValue_;
    }

    void render(DrawingContext *ctx, Rect invalidRect);

    virtual void dispatchEvent(Event *evt) override;

private:

    float minValue_;
    float maxValue_;
    float value_;

    bool adjusting_;
    float adjustValue_;
    float adjustStartOffset_;

    Point adjustCenter_;

};

}

#endif