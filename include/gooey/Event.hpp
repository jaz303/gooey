#pragma once

#include "gooey/fwd.hpp"
#include "gooey/geom/Point.hpp"
#include <SDL2/SDL.h>

namespace gooey {

struct Event {

    SDL_Event sdl;

    View* targetView;

    /*
     * Offset of event within screen.
     * For gooey's purposes, "screen" is an SDL window.
     * Only valid for isSpatial() events
     */
    Point screenOffset;

    /*
     * Offset of event within target window.
     * Only valid for isSpatial() events where targetView != 0
     */
    Point windowOffset;

    /*
     * Offset of event within target view.
     * Only valid for isSpatial() events where targetView != 0
     */
    Point viewOffset;

    /*
     * Call this method after data is copied into the SDL_Event
     * structure
     */
    void init() {
        targetView = 0;
        if (sdl.type == SDL_MOUSEMOTION) {
            screenOffset.x = sdl.motion.x;
            screenOffset.y = sdl.motion.y;
        } else if (sdl.type == SDL_MOUSEBUTTONDOWN || sdl.type == SDL_MOUSEBUTTONUP) {
            screenOffset.x = sdl.button.x;
            screenOffset.y = sdl.button.y;
        }
    }

    inline int type() const {
        return sdl.type;
    }

    inline bool isSpatial() const {
        return isMouse();
    }

    inline bool isMouse() const {
        return sdl.type == SDL_MOUSEMOTION
                || sdl.type == SDL_MOUSEBUTTONDOWN
                || sdl.type == SDL_MOUSEBUTTONUP;
    }

    inline bool isKeyboard() const {
        return sdl.type == SDL_KEYDOWN
                || sdl.type == SDL_KEYUP;
    }

    Point targetTopLeftScreen() const;
    Point targetCenterScreen() const;

};

}