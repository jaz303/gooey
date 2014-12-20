#include "gooey/DrawingContext.hpp"

using namespace gooey;

DrawingContext::DrawingContext(SDL_Renderer *renderer)
    : renderer_(renderer)
{

}

#include <iostream>

void DrawingContext::setFill(float r, float g, float b)
{
    SDL_SetRenderDrawColor(
            renderer_,
            (Uint8)(r * 255.0),
            (Uint8)(g * 255.0),
            (Uint8)(b * 255.0),
            255
    );
}

void DrawingContext::fillRect(Rect rect)
{
    SDL_Rect sRect;
    rect.fillSDLRect(&sRect);
    SDL_RenderFillRect(renderer_, &sRect);
}

void DrawingContext::fillRect(float x, float y, float w, float h)
{
    SDL_Rect sRect = { (int)x, (int)y, (int)w, (int)h };
    SDL_RenderFillRect(renderer_, &sRect);
}