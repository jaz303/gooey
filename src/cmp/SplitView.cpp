#include "gooey/cmp/SplitView.hpp"
#include "gooey/DrawingContext.hpp"
#include "gooey/Event.hpp"

using namespace gooey;

SplitView::SplitView(Rect rect)
    : View(rect)
    , vertical_(true)
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

void SplitView::setVertical()
{
    vertical_ = true;
    updateChildRects(true, true);
}

void SplitView::setHorizontal()
{
    vertical_ = false;
    updateChildRects(true, true);
}


void SplitView::setDividerSize(float newDividerSize)
{
    dividerSize_ = newDividerSize;
    updateChildRects(true, true);
}

void SplitView::setDividerPosition(float newDividerPosition)
{
    float referenceDim = vertical_ ? width() : height();
    splitRatio_ = newDividerPosition / (referenceDim - dividerSize());
    if (splitRatio_ < 0) splitRatio_ = 0;
    if (splitRatio_ > 1) splitRatio_ = 1;
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
    float dp = dividerPosition();
    ctx->setFill(0.5f, 0.5f, 0.5f);

    if (vertical_) {
        ctx->fillRect(dp, 0, dividerSize(), height());
    } else {
        ctx->fillRect(0, dp, width(), dividerSize());
    }

    Rect viewRect;

    if (firstView_) {
        if (splitRatio_ > 0) {
            viewRect = firstView_->rect();
            ctx->translate(viewRect.origin.x, viewRect.origin.y);
            firstView_->render(ctx, Rect());
            ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
        }
    } else {
        // TODO(jwf): solid fill
    }

    if (secondView_) {
        if (splitRatio_ < 1) {
            viewRect = secondView_->rect();
            ctx->translate(viewRect.origin.x, viewRect.origin.y);
            secondView_->render(ctx, Rect());
            ctx->translate(-viewRect.origin.x, -viewRect.origin.y);
        }
    } else {
        // TODO(jwf): solid fill
    }

    if (resizing_) {
        ctx->setFill(1.0f, 0.5f, 0.5f, 0.75f);
        if (vertical_) {
            ctx->fillRect(resizeCurrentOffset_, 0.0f, dividerSize(), height());
        } else {
            ctx->fillRect(0.0f, resizeCurrentOffset_, width(), dividerSize());
        }
    }
}

#include <iostream>

View* SplitView::findEventTarget(Event *evt)
{
    auto dp = dividerPosition();
    auto rc = vertical_ ? evt->viewOffset.x : evt->viewOffset.y;

    if (firstView_ && rc < dp) {
        evt->viewOffset = firstView_->rect().offsetOf(evt->viewOffset);
        return firstView_->findEventTarget(evt);
    } else if (secondView_ && rc >= (dp + dividerSize())) {
        evt->viewOffset = secondView_->rect().offsetOf(evt->viewOffset);
        return secondView_->findEventTarget(evt);
    } else {
        return this;
    }
}

void SplitView::dispatchEvent(Event *evt)
{
    float offsetComponent;
    float screenOffsetComponent;
    float maxPosition;

    if (vertical_) {
        offsetComponent = evt->viewOffset.x;
        screenOffsetComponent = evt->screenOffset.x;
        maxPosition = width();
    } else {
        offsetComponent = evt->viewOffset.y;
        screenOffsetComponent = evt->screenOffset.y;
        maxPosition = height();
    }

    switch (evt->type()) {
        case SDL_MOUSEBUTTONDOWN:
        {
            auto dp = dividerPosition();
            if (offsetComponent >= dp && offsetComponent < (dp + dividerSize())) {
                resizing_ = true;
                resizeCurrentOffset_ = dp;
                resizeStartOffset_ = dp;
                resizeScreenStartOffset_ = screenOffsetComponent;
                startTappingEvents();
            }
            break;
        }
        case SDL_MOUSEMOTION:
        {
            if (resizing_) {
                float newOffset = resizeStartOffset_ + (screenOffsetComponent - resizeScreenStartOffset_);
                if (newOffset < 0) newOffset = 0;
                if (newOffset > maxPosition - dividerSize()) newOffset = maxPosition - dividerSize();
                resizeCurrentOffset_ = newOffset;
            }
            break;
        };
        case SDL_MOUSEBUTTONUP:
        {
            if (resizing_) {
                setDividerPosition(resizeCurrentOffset_);
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

    float availableSpace = (vertical_ ? width() : height()) - dividerSize();
    float firstSize = splitRatio_ * availableSpace;
    float secondSize = (1 - splitRatio_) * availableSpace;

    if (c1 && firstView_) {
        if (vertical_) {
            firstView_->setRect(Rect(0, 0, firstSize, height()));
        } else {
            firstView_->setRect(Rect(0, 0, width(), firstSize));
        }

    }

    if (c2 && secondView_) {
        float start = firstSize + dividerSize();
        if (vertical_) {
            secondView_->setRect(Rect(start, 0, secondSize, height()));
        } else {
            secondView_->setRect(Rect(0, start, width(), secondSize));
        }
    }
}