#include "gooey/Window.hpp"
#include "gooey/View.hpp"

#include <gooey/WindowManager.hpp>
#include <gooey/DrawingContext.hpp>

#include <cmath>
#include <iostream>

using namespace gooey;

Window::Window(WindowManager *windowManager)
    : windowManager_(windowManager)
    , sdlSurface_(0)
{
    setRect(Rect(0, 0, 100, 100));
}

Window::~Window()
{
    if (sdlSurface_) {
        SDL_FreeSurface(sdlSurface_);
    }
}

Rect Window::rect() const
{
    return rect_;
}

void Window::setRect(Rect rect)
{
    rect.size.width = ceilf(rect.size.width);
    rect.size.height = ceilf(rect.size.height);

    rect_ = rect;

    if (sdlSurface_ == 0
            || rect.size.width > sdlSurface_->w
            || rect.size.height > sdlSurface_->h) {

        if (sdlSurface_ != 0) {
            SDL_FreeSurface(sdlSurface_);
            sdlSurface_ = 0;
        }

        sdlSurface_ = SDL_CreateRGBSurface(
                0,
                (int)rect.size.width, (int)rect.size.height,
                32,
                0x00FF0000,
                0x0000FF00,
                0x000000FF,
                0xFF000000
        );

        context_.setSurface(sdlSurface_);

    }
}

void Window::addView(View *view)
{
    views_.push_back(view);
}

void Window::render()
{
    // TODO(jwf): clip rendering?

    context_.setFill(1.0, 0, 1.0);
    context_.clear();

    for (auto view : views_) {
//        Rect viewRect = view->rect().offset(rect_.origin);
        view->render(&context_, view->rect());
    }
}