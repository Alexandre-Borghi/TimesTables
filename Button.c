#include "Button.h"

struct Button
{
    int x;
    int y;
    int w;
    int h;

    char string[50];
};

Button CreateButton (int x_, int y_, int w_, int h_, char string_[50])
{
    Button t;
    t.x = x_;
    t.y = y_;
    t.w = w_;
    t.h = h_;

    strcpy(t.string, string_);
}