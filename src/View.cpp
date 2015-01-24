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

View::~View()
{
}

void View::setWindow(Window *window)
{
    window_ = window;
}

void View::setRect(Rect rect)
{
    rect_ = rect;
}

void View::render(DrawingContext *ctx, Rect invalidRect)
{
}

View* View::findEventTarget(Event *evt)
{
    return this;
}

void View::dispatchEvent(Event *evt)
{
}

void View::dispatchKeyEvent(Event *evt)
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
