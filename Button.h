#include <SDL2/SDL.h>

struct Button;
typedef struct Button Button;

Button CreateButton (int x, int y, int w, int h, char string_[50]);
void DrawButton(SDL_Renderer* renderer, Button* button);