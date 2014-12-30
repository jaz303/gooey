#include "gooey/cmp/SplitView.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

using namespace gooey;

SplitView::SplitView(Rect rect)
    : View(rect)
    , dividerSize_(10)
    , splitRatio_(0.33333f)
    , firstView_(0)
    , secondView_(0)
    , resizing_(false)
{
}

void SplitView::setRect(Rect rect)
{
    View::setRect(rect);
    updateChildRects(true, true);
}

void SplitView::setDividerSize(float newDividerSize)
{
    dividerSize_ = newDividerSize;
    updateChildRects(true, true);
}

void SplitView::setLeftView(View *view)
{
    if (firstView_) {
        firstView_->setWindow(0);
        firstView_ = 0;
    }
    if (view) {
        view->setWindow(window());
        firstView_ = view;
    }
    updateChildRects(true, false);
}

void SplitView::setRightView(View *view)
{
    if (secondView_) {
        secondView_->setWindow(0);
        secondView_ = 0;
    }
    if (view) {
        view->setWindow(window());
        secondView_ = view;
    }
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
    ctx->fillRect(dp - 1.0f, 0, dividerSize() + 2.0f, height());

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
    } else if (secondView_ && evt->viewOffset.x >= (dp + dividerSize())) {
        evt->viewOffset = secondView_->rect().offsetOf(evt->viewOffset);
        return secondView_->findEventTarget(evt);
    } else {
        return this;
    }
}

void SplitView::dispatchEvent(Event *evt)
{
    switch (evt->type()) {
        case SDL_MOUSEBUTTONDOWN:
        {
            auto dp = dividerPosition();
            if (evt->viewOffset.x >= dp && evt->viewOffset.x < (dp + dividerSize())) {
                std::cout << "mouse down on divider!" << std::endl;
                resizing_ = true;
                startTappingEvents();
                // TODO: stash offsets etc
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (resizing_) {
                std::cout << "do resize stuff!" << std::endl;
            }
            break;
        };
        case SDL_MOUSEBUTTONUP:
        {
            if (resizing_) {
                std::cout << "resize complete!" << std::endl;
                resizing_ = false;
                stopTappingEvents();
            }
            break;
        }
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
        float left = dp + dividerSize();
        secondView_->setRect(Rect(left, 0, width() - left, height()));
    }
}