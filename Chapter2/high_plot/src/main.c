#define SETUP
#define UPDATE
#define RENDER
#include "./include/display.c"
#define MATRIX2D_IMPLEMENTATION
#include "./include/Matrix2D.h"
#define ALMOG_DRAW_LIBRARY_IMPLEMENTATION
#include "./include/Almog_Draw_Library.h"
#define ALMOG_ENGINE_IMPLEMENTATION
#include "./include/Almog_Engine.h"

void setup(game_state_t *game_state)
{
    game_state->to_limit_fps = 0;

}

void update(game_state_t *game_state)
{

}

void render(game_state_t *game_state)
{

}
