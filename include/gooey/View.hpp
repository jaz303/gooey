#ifndef __GOOEY_VIEW_HPP__
#define __GOOEY_VIEW_HPP__

#include "gooey/fwd.hpp"
#include "gooey/geom/Rect.hpp"

namespace gooey {

class View {

public:
    View(Rect rect);

    inline Window* window() const { return window_; };
    void setWindow(Window *window);

    Rect rect() const;
    virtual void setRect(Rect rect);

    inline float x() const { return rect_.origin.x; }
    inline float y() const { return rect_.origin.y; }
    inline float width() const { return rect_.size.width; }
    inline float height() const { return rect_.size.height; }

    virtual void render(DrawingContext *ctx, Rect invalidRect);

    /*
     * Returns the view, or subview, targeted by the given event.
     *
     * `evt` will have been preprocessed such that its `viewOffset`
     * member contains the correct offset of the event relative to
     * this view's `rect()`. For example, a `viewOffset` of (0,0)
     * indicates that the event took place at the top-left corner
     * of this view.
     *
     * For non-container views, this method should simply return `this`.
     *
     * For container views, this method should return the appropriate
     * subview, taking into account any container-specific functionality
     * (e.g. scrolling, panel visibility). If the event doesn't target
     * a subview (e.g. there was a click on the background of a toolbar
     * rather than an internal button), this method should return `this`.
     * `evt->viewOffset` must be updated such that is correct relative
     * to the returned view.
     */
    virtual View* findEventTarget(Event *evt);
    virtual void dispatchEvent(Event *evt);

protected:

    void startTappingEvents();
    void stopTappingEvents();

    Rect            rect_;

private:

    Window*         window_;

};

}

#endif