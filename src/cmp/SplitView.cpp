#include "gooey/cmp/SplitView.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

static const int DIVIDER_WIDTH = 8;

using namespace gooey;

SplitView::SplitView(Rect rect)
    : View(rect)
    , splitRatio_(0.5f)
    , firstView_(0)
    , secondView_(0)
{
}

void SplitView::setRect(Rect rect)
{
    View::setRect(rect);
    updateChildRects(true, true);
}

void SplitView::setLeftView(View *view)
{
    view->setWindow(window());
    firstView_ = view;
    updateChildRects(true, false);
}

void SplitView::setRightView(View *view)
{
    view->setWindow(window());
    secondView_ = view;
    updateChildRects(false, true);
}

void SplitView::render(DrawingContext *ctx, Rect invalidRect)
{
//    ctx->setFill(0, 1, 1);
//    ctx->fillRect(0, 0, width(), height());

    Rect viewRect;

    if (firstView_) {
        viewRect = firstView_->rect();
        ctx->translate(viewRect.origin.x, viewRect.origin.y);
        firstView_->render(ctx, Rect());
        ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
    }

    if (secondView_) {
        viewRect = secondView_->rect();
        ctx->translate(viewRect.origin.x, viewRect.origin.y);
        secondView_->render(ctx, Rect());
        ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
    }

    // TODO(jwf): draw divider


//    ctx->setFill(0.0f, 0.0f, 1.0f);
//    ctx->fillRect(0, 0, width(), height());
//
//    for (auto view : subViews_) {
//        Rect viewRect = view->rect();
//        ctx->translate(viewRect.origin.x, viewRect.origin.y);
//        view->render(ctx, Rect());
//        ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
//    }
}

#include <iostream>

View* SplitView::findEventTarget(Event *evt)
{
//    for (auto iter = subViews_.rbegin(); iter != subViews_.rend(); ++iter) {
//        View *view = *iter;
//        if (view->rect().contains(evt->viewOffset)) {
//            evt->viewOffset = view->rect().offsetOf(evt->viewOffset);
//            return view;
//        }
//    }
    return this;
}

void SplitView::updateChildRects(bool c1, bool c2)
{
    if (c1 && firstView_) {

    }
    if (c2 && secondView_) {

    }
}