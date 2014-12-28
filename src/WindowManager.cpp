#include "gooey/WindowManager.hpp"

#include "gooey/geom/Rect.hpp"
#include "gooey/Window.hpp"

using namespace gooey;

WindowManager::WindowManager(SDL_Window *window, SDL_Renderer *renderer)
    : window_(window)
    , renderer_(renderer)
{
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    rect_ = Rect(0, 0, w, h);
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
    auto rootWindow = new Window(this);
    rootWindow->setRect(rect_);
    windows_.push_back(rootWindow);
    return rootWindow;
}
