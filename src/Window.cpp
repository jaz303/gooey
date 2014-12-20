#include "gooey/Window.hpp"
#include "gooey/View.hpp"

#include <SDL2/SDL.h>
#include <gooey/WindowManager.hpp>
#include <gooey/DrawingContext.hpp>

using namespace gooey;

Window::Window(WindowManager *windowManager)
    : windowManager_(windowManager)
{
    context_ = new DrawingContext(windowManager_->sdlRenderer());
}

Rect Window::rect() const
{
    return rect_;
}

void Window::setRect(Rect rect)
{
    rect_ = rect;
}

void Window::addView(View *view)
{
    views_.push_back(view);
}

void Window::render()
{
    // TODO(jwf): clip rendering?

    for (auto view : views_) {
        Rect viewRect = view->rect().offset(rect_.origin);
        view->render(context_, viewRect);
    }
}