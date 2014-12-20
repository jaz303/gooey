#include "gooey/WindowManager.hpp"

#include "gooey/geom/Rect.hpp"
#include "gooey/Window.hpp"

using namespace gooey;

WindowManager::WindowManager(SDL_Window *window, SDL_Renderer *renderer)
    : window_(window)
    , renderer_(renderer)
{
    int w, h;
    SDL_GetWindowSize(window_, &w, &h);
    rect_ = Rect(0, 0, w, h);
}

WindowManager::WindowManager(SDL_Window *window, SDL_Renderer *renderer, Rect rect)
    : window_(window)
    , renderer_(renderer)
    , rect_(rect)
{

}

void WindowManager::render()
{
    SDL_SetRenderTarget(renderer_, NULL);
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
    SDL_RenderClear(renderer_);

    for (auto window : windows_) {
        window->render();
    }

    SDL_RenderPresent(renderer_);
}

Window* WindowManager::createRootWindow()
{
    auto rootWindow = new Window(this);
    rootWindow->setRect(rect_);
    windows_.push_back(rootWindow);
    return rootWindow;
}
