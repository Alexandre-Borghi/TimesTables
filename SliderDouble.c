#include "SliderDouble.h"
#include "App.h"

static float map(float val, float min, float max, float nextMin, float nextMax)
{
    return (((val - min) / (max - min)) * (nextMax - nextMin)) + nextMin;
}

static float constrain(float val, float min, float max)
{
    val = val < min ? min : val;
    val = val > max ? max : val;

    return val;
}

void CreateSliderDouble(
    SliderDouble* s,
    int x, int y, int w, int h, 
    double minVal_, double maxVal_, double* value_,
    SDL_Color barColor_,
    SDL_Color fillColor_, SDL_Color hoverColor_, SDL_Color pressColor_
    )
{
    s->minVal = minVal_;
    s->maxVal = maxVal_;
    s->value = value_;

    s->bar.x = x;
    s->bar.y = y;
    s->bar.w = w;
    s->bar.h = h;

    s->handle.w = h;
    s->handle.h = 2 * h;
    s->handle.x = map(*s->value, s->minVal, s->maxVal, x, x + s->bar.w);
    s->handle.y = y - s->handle.h / 4;

    s->barColor = barColor_;

    s->handleColor = fillColor_;
    s->hoverColor = hoverColor_;
    s->pressColor = pressColor_;

    s->isHovered = 0;
    s->isPressed = 0;
    s->callCallback = 0;
}

void DrawSlider(App* app, SliderDouble* slider)
{
    slider->handle.x = (double)constrain(map(*slider->value, slider->minVal, slider->maxVal, slider->bar.x - slider->handle.w / 2, slider->bar.x + slider->bar.w - slider->handle.w / 2), slider->bar.x - slider->handle.w / 2, slider->bar.x + slider->bar.w - slider->handle.w / 2);

    SDL_Color* bc = &(slider->barColor);
    SDL_Color* fc = &(slider->handleColor);
    SDL_Color* hc = &(slider->hoverColor);
    SDL_Color* pc = &(slider->pressColor);

    SDL_SetRenderDrawColor(app->renderer, bc->r, bc->g, bc->b, bc->a);
    SDL_RenderFillRect(app->renderer, &slider->bar);

    if (slider->isPressed == 1)
    {
        SDL_SetRenderDrawColor(app->renderer, pc->r, pc->g, pc->b, pc->a);
    }
    else if (slider->isHovered == 1)
    {
        SDL_SetRenderDrawColor(app->renderer, hc->r, hc->g, hc->b, hc->a);
    }
    else
    {
        SDL_SetRenderDrawColor(app->renderer, fc->r, fc->g, fc->b, fc->a);
    }

    SDL_RenderFillRect(app->renderer, &slider->handle);
}

static int IsPointInRect(Sint32 x, Sint32 y, SDL_Rect* rect)
{
    if (x > rect->x && x < rect->x + rect->w && y > rect->y && y < rect->y + rect->h)
        return 1;
    
    return 0;
}

void EventSlider (SliderDouble* slider, SDL_Event* e)
{
    // Slider hovered

    if (e->type == SDL_MOUSEMOTION && IsPointInRect(e->motion.x, e->motion.y, &(slider->handle)) == 1)
    {
        slider->isHovered = 1;
    }
    else if (e->type == SDL_MOUSEMOTION)
    {
        slider->isHovered = 0;
    }    

    // Slider clicked

    if (e->type == SDL_MOUSEBUTTONDOWN && slider->isHovered == 1)
    {
        slider->isPressed = 1;
    }

    if (e->type == SDL_MOUSEBUTTONUP && slider->isHovered == 1)
    {
        slider->isPressed = 0;
        slider->callCallback = 1;
    }
    else if (e->type == SDL_MOUSEBUTTONUP)
    {
        slider->isPressed = 0;
    }

    // Slider dragged

    if (e->type == SDL_MOUSEMOTION && slider->isPressed == 1)
    {
        slider->handle.x = constrain(e->motion.x, slider->bar.x - slider->handle.w / 2, slider->bar.x + slider->bar.w - slider->handle.w / 2);
        *slider->value = map(slider->handle.x + slider->handle.w / 2, slider->bar.x, slider->bar.x + slider->bar.w, slider->minVal, slider->maxVal);
    }
}