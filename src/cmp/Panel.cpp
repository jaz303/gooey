#include "gooey/cmp/Panel.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

using namespace gooey;

Panel::Panel(Rect rect)
        : View(rect)
{
}

void Panel::addSubView(View *subView)
{
    subView->setWindow(window());
    subViews_.push_back(subView);
}

void Panel::render(DrawingContext *ctx, Rect invalidRect)
{
    ctx->setFill(0.0f, 0.0f, 1.0f);
    ctx->fillRect(0, 0, width(), height());

    ctx->save();
    ctx->clip(0, 0, width(), height());

    for (auto view : subViews_) {
        auto viewRect = view->rect();
        ctx->translate(viewRect.origin.x, viewRect.origin.y);
        view->render(ctx, Rect());
        ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
    }

    ctx->restore();
}

#include <iostream>

View* Panel::findEventTarget(Event *evt)
{
    for (auto iter = subViews_.rbegin(); iter != subViews_.rend(); ++iter) {
        View *view = *iter;
        if (view->rect().contains(evt->viewOffset)) {
            evt->viewOffset = view->rect().offsetOf(evt->viewOffset);
            return view->findEventTarget(evt);
        }
    }
    return this;
}
