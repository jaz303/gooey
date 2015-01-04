#include "gooey/cmp/Label.hpp"
#include "gooey/DrawingContext.hpp"

using namespace gooey;

Label::Label(Rect rect)
        : View(rect)
{
}

void Label::setLabel(const char *newLabel)
{
    label_ = std::string(newLabel);
}

void Label::setLabel(std::string newLabel)
{
    label_ = newLabel;
}

void Label::render(DrawingContext *ctx, Rect invalidRect)
{
    ctx->setFill(1.0f, 1.0f, 1.0f);

    if (label_.length() > 0) {
        ctx->save();
        ctx->clip(0, 0, width(), height());
        ctx->setFontSize(12.0f);
        ctx->fillTextVerticallyCentered(label_, 0, height() / 2.0f);
        ctx->restore();
    }
}
