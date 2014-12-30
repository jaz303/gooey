#include "gooey/cmp/SplitView.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

using namespace gooey;

SplitView::SplitView(Rect rect)
    : View(rect)
    , dividerWidth_(10)
    , splitRatio_(0.33333f)
    , firstView_(0)
    , secondView_(0)
{
}

void SplitView::setRect(Rect rect)
{
    View::setRect(rect);
    updateChildRects(true, true);
}

void SplitView::setDividerWidth(float newDividerWidth)
{
    dividerWidth_ = newDividerWidth;
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
    // NOTE(jwf): this is a little bodge to prevent the superview's
    // background color haloing the divider. we just make the divider
    // a pixel wider at each side to fully obscure the background
    // color.
    float dp = dividerPosition();
    ctx->setFill(0.5f, 0.5f, 0.5f);
    ctx->fillRect(dp - 1.0f, 0, dividerWidth() + 2.0f, height());

    Rect viewRect;

    if (firstView_) {
        viewRect = firstView_->rect();
        ctx->translate(viewRect.origin.x, viewRect.origin.y);
        firstView_->render(ctx, Rect());
        ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
    } else {
        // TODO(jwf): solid fill
    }

    if (secondView_) {
        viewRect = secondView_->rect();
        ctx->translate(viewRect.origin.x, viewRect.origin.y);
        secondView_->render(ctx, Rect());
        ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
    } else {
        // TODO(jwf): solid fill
    }
}

#include <iostream>

View* SplitView::findEventTarget(Event *evt)
{
    auto dp = dividerPosition();

    if (firstView_ && evt->viewOffset.x < dp) {
        evt->viewOffset = firstView_->rect().offsetOf(evt->viewOffset);
        return firstView_->findEventTarget(evt);
    } else if (secondView_ && evt->viewOffset.x >= (dp + dividerWidth())) {
        evt->viewOffset = secondView_->rect().offsetOf(evt->viewOffset);
        return secondView_->findEventTarget(evt);
    } else {
        return this;
    }
}

void SplitView::updateChildRects(bool c1, bool c2)
{
    // TODO(jwf): handle case where not enough space

    float dp = dividerPosition();

    if (c1 && firstView_) {
        firstView_->setRect(Rect(0, 0, dp, height()));
    }

    if (c2 && secondView_) {
        float left = dp + dividerWidth();
        secondView_->setRect(Rect(left, 0, width() - left, height()));
    }
}