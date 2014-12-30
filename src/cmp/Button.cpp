#include "gooey/cmp/Button.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

using namespace gooey;

Button::Button(Rect rect)
    : View(rect)
    , pressed_(false)
{
}

void Button::render(DrawingContext *ctx, Rect invalidRect)
{
    if (pressed_) {
        ctx->setFill(1.0f, 0.5f, 0.2f);
    } else {
        ctx->setFill(0.5f, 1.0f, 0.2f);
    }

    ctx->fillRect(0, 0, width(), height());
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
                std::cout << "mouse up inside!" << std::endl;
            }
            std::cout << "so: " << evt->screenOffset << std::endl;
            std::cout << "wo: " << evt->windowOffset << std::endl;
            std::cout << "vo: " << evt->viewOffset << std::endl;
            stopTappingEvents();
            break;
    }
}
