#include "gooey/View.hpp"
#include "gooey/Event.hpp"
#include "gooey/Window.hpp"
#include "gooey/WindowManager.hpp"
#include <SDL2/SDL.h>

using namespace gooey;

View::View(Rect rect)
    : rect_(rect)
{

}

Window* View::window() const
{
    return window_;
}

void View::setWindow(Window *window)
{
    window_ = window;
}

Rect View::rect() const
{
    return rect_;
}

void View::render(DrawingContext *ctx, Rect rect)
{
}

void View::dispatchEvent(Event *evt)
{
}

//
// Protected

void View::startTappingEvents()
{
    window()->windowManager()->installEventTapToView(this);
}

void View::stopTappingEvents()
{
    window()->windowManager()->uninstallEventTapToView(this);
}