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


Grid grid;
Grid grid_proj;
void setup(game_state_t *game_state)
{
    game_state->to_limit_fps = 0;

    grid      = adl_create_square_grid(-2, 2, -1, 1, 40, 40, "XZ", 1);
    grid_proj = adl_create_square_grid(-2, 2, -1, 1, 40, 40, "XZ", 1);

}


void update(game_state_t *game_state)
{
    ae_set_projection_mat(game_state->scene.proj_mat, game_state->scene.camera.aspect_ratio, game_state->scene.camera.fov_deg, game_state->scene.camera.z_near, game_state->scene.camera.z_far);
    ae_set_view_mat(game_state->scene.view_mat, game_state->scene.camera, game_state->scene.up_direction);

    ae_project_grid_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, grid_proj, grid, game_state->window_w, game_state->window_h);
}

void render(game_state_t *game_state)
{
    adl_draw_grid(game_state->window_pixels_mat, grid_proj, 0xFFFFFF, ADL_DEFAULT_OFFSET_ZOOM);

}
