#include "gooey/cmp/Button.hpp"

#include "gooey/DrawingContext.hpp"

using namespace gooey;

Button::Button(Rect rect)
        : View(rect)
{

}

void Button::render(DrawingContext *ctx, Rect rect)
{
    ctx->setFill(1.0f, 0.5f, 0.2f);
    ctx->fillRect(rect);
}
