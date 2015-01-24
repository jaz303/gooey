#include "gooey/cmp/TextEditor.hpp"
#include "gooey/DrawingContext.hpp"

using namespace gooey;

TextEditor::TextEditor(Rect rect)
        : View(rect)
{
}

void TextEditor::render(DrawingContext *ctx, Rect invalidRect)
{
    ctx->setFill(0.15, 0.18, 0.15);
    ctx->fillRect(0, 0, width(), height());
}
