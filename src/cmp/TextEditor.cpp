#include "gooey/cmp/TextEditor.hpp"
#include "gooey/DrawingContext.hpp"

#include <SDL/SDL_image.h>

#include <iostream>
#include <string.h>

using namespace gooey;

TextEditor::TextEditor(Rect rect)
        : View(rect)
{
    font_ = IMG_Load("res/font10x10.png");
    charWidth_ = 10;
    charHeight_ = 10;
}

TextEditor::~TextEditor()
{
    SDL_FreeSurface(font_);
}

void TextEditor::render(DrawingContext *ctx, Rect invalidRect)
{
    // Bypass cairo and grab a reference to the target SDL surface and
    // calculate the position of this widget's top-left corner on this
    // surface. It is assumed that display is not scaled, i.e. width()
    // and height() correspond directly to pixel sizes.
    target_ = ctx->sdlSurface();
    topLeft_ = ctx->viewToSurface(Point(0, 0));

    topLeft_.x = floorf(topLeft_.x);
    topLeft_.y = floorf(topLeft_.y);

    SDL_Rect rect;
    rect.x = (int) topLeft_.x;
    rect.y = (int) topLeft_.y;
    rect.w = (int) width();
    rect.h = (int) height();

    SDL_SetClipRect(target_, &rect);
    SDL_FillRect(target_, &rect, 0xFF000000);

    const char *str1 = "10 PRINT \"HELLO WORLD\"";
    const char *str2 = "20 GOTO 10";
    drawText(5, 5, str1, strlen(str1), 0xFF0000);
    drawText(5, 15, str2, strlen(str2), 0xFFFF00);

    drawText(300, 5, str1, strlen(str1), 0xFF00FF);

    drawCursor(100, 100, 0xFFFF0000);


    SDL_SetClipRect(target_, 0);
}

void TextEditor::drawText(int x, int y, const char *str, size_t len, uint32_t color) {
    SDL_SetSurfaceColorMod(font_, color >> 16, color >> 8, color >> 0);
    int xpos = topLeft_.x + x;
    int ypos = topLeft_.y + y;
    for (int i = 0; i < len; ++i) {
        drawChar(xpos, ypos, str[i]);
        xpos += charWidth_;
    }
    SDL_SetSurfaceColorMod(font_, 0xFF, 0xFF, 0xFF);
}

void TextEditor::drawChar(int x, int y, char ch) {
    SDL_Rect src = {
        (ch & 0x0F) * charWidth_,
        (ch >> 4) * charHeight_,
        charWidth_,
        charHeight_
    };
    SDL_Rect dest = { x, y, charWidth_, charHeight_ };
    SDL_BlitSurface(font_, &src, target_, &dest);
}

void TextEditor::drawCursor(int x, int y, uint32_t color) {
    x = topLeft_.x + x;
    y = topLeft_.y + y;
    SDL_Rect cursorRect = { x, y, charWidth_, charHeight_ };
    SDL_FillRect(target_, &cursorRect, color);
}