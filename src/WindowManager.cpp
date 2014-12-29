#include <gooey/Event.hpp>
#include <gooey/View.hpp>
#include "gooey/WindowManager.hpp"

#include "gooey/geom/Rect.hpp"
#include "gooey/Window.hpp"

using namespace gooey;

WindowManager::WindowManager(SDL_Window *window, SDL_Renderer *renderer)
    : window_(window)
    , renderer_(renderer)
    , rootWindow_(0)
    , tappedView_(0)
{
    sdlWindowDidResize();
}

bool WindowManager::dispatchEvent(Event *evt)
{
    if (tappedView_) {
        if (evt->isSpatial()) {
            Window *window = tappedView_->window();
            window->rect().contains(evt->screenOffset, &evt->windowOffset);
            tappedView_->rect().contains(evt->windowOffset, &evt->viewOffset);
        }
        tappedView_->dispatchEvent(evt);
        return true;
    }

    if (evt->isSpatial()) {
        for (auto iter = windows_.rbegin(); iter != windows_.rend(); ++iter) {
            Window *window = *iter;
            if (window->rect().contains(evt->screenOffset, &evt->windowOffset)) {
                window->dispatchEvent(evt);
                return true;
            }
        }
    }
    // TODO(jwf): dispatch keyboard event when we have key windows
    return false;
}

#include <iostream>

void WindowManager::render()
{
//    SDL_SetRenderTarget(renderer_, NULL);
//    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
//    SDL_RenderClear(renderer_);

    for (auto window : windows_) {
        window->render();
    }

    for (auto window : windows_) {

        Rect windowRect = window->rect();

        SDL_Rect srcRect;
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = (int) windowRect.size.width;
        srcRect.h = (int) windowRect.size.height;

        SDL_Rect dstRect;
        dstRect.x = (int) windowRect.origin.x;
        dstRect.y = (int) windowRect.origin.y;
        dstRect.w = (int) windowRect.size.width;
        dstRect.h = (int) windowRect.size.height;

        SDL_BlitSurface(
                window->sdlSurface(),
                &srcRect,
                SDL_GetWindowSurface(window_),
                &dstRect
        );

    }

    SDL_UpdateWindowSurface(window_);

    //SDL_RenderPresent(renderer_);
}

Window* WindowManager::createRootWindow()
{
    if (!rootWindow_) {
        rootWindow_ = new Window(this);
        rootWindow_->setRect(rect_);
        windows_.push_back(rootWindow_);
    }
    return rootWindow_;
}

void WindowManager::sdlWindowDidResize()
{
    int w, h;
    SDL_GetWindowSize(window_, &w, &h);
    rect_ = Rect(0, 0, w, h);
    if (rootWindow_) {
        rootWindow_->setRect(rect_);
    }
}

void WindowManager::installEventTapToView(View *view)
{
    if (tappedView_ != 0) {
        // TODO(jwf): report error/crash horribly
    } else {
        tappedView_ = view;
    }
}

void WindowManager::uninstallEventTapToView(View *view)
{
    if (tappedView_ != view) {
        // TODO(jwf): report error/crash horribly
    } else {
        tappedView_ = 0;
    }
}