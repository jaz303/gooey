#include "gooey/Window.hpp"

#include <SDL2/SDL.h>

using namespace gooey;

Window::Window(WindowManager *windowManager)
    : windowManager_(windowManager)
{

}

Rect Window::rect() const
{
    return rect_;
}

void Window::setRect(Rect rect)
{
    rect_ = rect;
}

void Window::render()
{
    SDL_Rect rect;
    rect.x = rect_.origin.x;
    rect.y = rect_.origin.y;
    rect.w = rect_.size.width;
    rect.h = rect_.size.height;

    SDL_SetRenderDrawColor(windowManager_->sdlRenderer(), 128, 0, 0, 255);
    SDL_RenderFillRect(windowManager_->sdlRenderer(), &rect);
}