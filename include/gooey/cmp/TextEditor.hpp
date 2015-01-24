#ifndef __GOOEY_TEXT_EDITOR_HPP__
#define __GOOEY_TEXT_EDITOR_HPP__

#include "gooey/fwd.hpp"
#include "gooey/View.hpp"
#include "gooey/geom/Rect.hpp"
#include <string>

namespace gooey {

class TextEditor : public View {

public:
    TextEditor(Rect rect);
    virtual ~TextEditor();

    void render(DrawingContext *ctx, Rect invalidRect);

private:

	void drawText(int x, int y, const char *str, size_t len, uint32_t color);
	void drawChar(int x, int y, char ch);
	void drawCursor(int x, int y, uint32_t color);

	SDL_Surface*	font_;
	int 			charWidth_;
	int 			charHeight_;

	// transients
	SDL_Surface* 	target_;
	Point 			topLeft_;

};

}

#endif