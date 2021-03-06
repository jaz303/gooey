#include "gooey/cmp/Button.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

using namespace gooey;

Button::Button(Rect rect)
    : View(rect)
    , pressed_(false)
{
}

void Button::setLabel(const char *newLabel)
{
    label_ = std::string(newLabel);
}

void Button::setLabel(std::string newLabel)
{
    label_ = newLabel;
}

void Button::render(DrawingContext *ctx, Rect invalidRect)
{
    if (pressed_) {
        ctx->setFill(1.0f, 0.5f, 0.2f);
    } else {
        ctx->setFill(0.5f, 1.0f, 0.2f);
    }

    ctx->fillRect(0, 0, width(), height());

    ctx->setFill(0.0f, 0.0f, 0.0f);

    if (label_.length() > 0) {
        ctx->save();
        ctx->clip(0, 0, width(), height());
        ctx->setFontSize(12.0f);
        ctx->fillTextCentered(label_, width() / 2.0f, height() / 2.0f);
        ctx->restore();
    }
}

void Button::dispatchEvent(Event *evt)
{
    switch (evt->type()) {
        case SDL_MOUSEBUTTONDOWN:
            pressed_ = true;
            startTappingEvents();
            break;
        case SDL_MOUSEBUTTONUP:
            pressed_ = false;
            if (evt->targetView == this) {
                // TODO(jwf): handle click
            }
            stopTappingEvents();
            break;
    }
}
