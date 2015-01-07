#include "gooey/cmp/Knob.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

#include <cmath>
#include <iostream>

using namespace gooey;

Knob::Knob(Rect rect)
    : View(rect)
    , minValue_(0.0f)
    , maxValue_(100.0f)
    , value_(0.0f)
    , adjusting_(false)
{
}

void Knob::render(DrawingContext *ctx, Rect invalidRect)
{
    float cx = width() * 0.5f;
    float cy = height() * 0.5f;
    float r  = (cx < cy ? cx : cy) - 2.0f;

    ctx->save();
    ctx->translate(cx, cy);

    ctx->beginPath();
    ctx->setStroke(1.0f, 0.0f, 0.0f);
    ctx->setLineWidth(3.0f);
    ctx->arc(0, 0, r, 3 * M_PI_4, M_PI_4);
    ctx->stroke();

    ctx->beginPath();

    float referenceValue;
    if (adjusting_) {
        referenceValue = adjustValue_;
        ctx->setStroke(1.0f, 1.0f, 1.0f);
    } else {
        referenceValue = value_;
        ctx->setStroke(0.0f, 0.0f, 0.0f);
    }

    float ratio = ((referenceValue - minValue_) / (maxValue_ - minValue_)) * 1.5f * M_PI;

    ctx->rotate((3 * M_PI_4) + ratio);
    ctx->moveTo(0, 0);
    ctx->lineTo(r + 1, 0);
    ctx->stroke();

    ctx->restore();
}

void Knob::dispatchEvent(Event *evt)
{
    switch (evt->type()) {
        case SDL_MOUSEBUTTONDOWN:
            adjusting_ = true;
            adjustValue_ = value_;
            adjustStartOffset_ = evt->screenOffset.x;
            adjustCenter_ = evt->targetCenterScreen();
            startTappingEvents();
            break;
        case SDL_MOUSEMOTION:
        {
            float angle = atan2f(
                    -(evt->screenOffset.x - adjustCenter_.x),
                    evt->screenOffset.y - adjustCenter_.y
            );

            float adjustRatio = 0.0f;

            // TODO(jwf): this can probably be improved
            if (angle >= 0) {
                angle -= M_PI_4;
                if (angle < 0) {
                    angle = 0;
                }
                adjustRatio = (angle / (M_PI * 0.75f)) * 0.5f;
            } else if (angle < 0) {
                angle += M_PI_4;
                if (angle > 0) {
                    angle = 0;
                }
                adjustRatio = 1 - (-angle / (M_PI * 0.75)) * 0.5f;
            }

            adjustValue_ = minValue_ + (adjustRatio * maxValue_);

            break;
        };
        case SDL_MOUSEBUTTONUP:
            adjusting_ = false;
            setValue(adjustValue_);
            stopTappingEvents();
            break;
    }
}
