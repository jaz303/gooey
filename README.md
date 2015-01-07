# gooey

UI library for SDL/cairo.

Current status: unfinished & useless

Not sure what direction this is going to take.

## Screenshot

![gooey screenshot](gooey.png)

This shows a toolbar, various buttons, panels and vertical split view.

## References

Cairo docs: http://cairographics.org/documentation/

## TODO

### Next Up

  - [x] Event capturing e.g. for handling clicks/drags
  - [x] Decide how coordinate system should work for nested views
  - [x] Panel (background color, subviews)
  - [x] Split view - groundwork
  - [x] Split view - drag-resize 
  - [x] Use clipping when rendering containers
  - [x] Text rendering spike
  - [x] Label
  - [x] SDL container view
  - [x] Knob
  - [ ] Slider
  - [ ] Layout manager for toolbar
  

This leaves: text inputs, check boxes, radio buttons, floating windows, key windows

### Deferred

  - [ ] Use HW accelerated rendering (i.e. `SDL_Renderer`)
  - [ ] SDLSurfaceView should support scaling in addition to clipping
  - [ ] Migrate from cairo's "toy" text API

## General Deficiencies

  - Raw pointers are used liberally. They should be replaced with smart pointers.
  - No consideration has yet been given whatsoever to setting the cursor.
  
## Thoughts

  - Should explore whether to make event-tapping 2-tiered, i.e. `WindowManager` taps events to `Window` then `Window` taps events to `View`. The same approach should be adopted for key events, when we have them.
  
## Limitations

  - Assumes ARGB32