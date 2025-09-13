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

Quad_mesh quads;
Tri_mesh quads_in_tri;
Tri_mesh proj_quads_tri;
void setup(game_state_t *game_state)
{
    game_state->to_limit_fps = 0;

    ada_init_array(Quad, quads);
    ada_init_array(Tri, proj_quads_tri);

    Quad quad = {0};

    quad.points[3] = (Point){1  , 1 , 2, 1};
    quad.points[2] = (Point){3  , 2 , 2, 1};
    quad.points[1] = (Point){2  , 2.5 , 2, 1};
    quad.points[0] = (Point){0.5, 2 , 2, 1};
    quad.to_draw = true;
    quad.light_intensity = 1;
    quad.colors[0] = 0xFFFFFF;
    quad.colors[1] = 0x0000FF;
    quad.colors[2] = 0x00FF00;
    quad.colors[3] = 0xFF0000;

    ada_appand(Quad, quads, quad);

    quads_in_tri = ae_get_tri_mesh_from_quad_mesh(quads);
}


void update(game_state_t *game_state)
{
    ae_set_projection_mat(game_state->scene.proj_mat, game_state->scene.camera.aspect_ratio, game_state->scene.camera.fov_deg, game_state->scene.camera.z_near, game_state->scene.camera.z_far);
    ae_set_view_mat(game_state->scene.view_mat, game_state->scene.camera, game_state->scene.up_direction);

    ae_project_tri_mesh_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, &proj_quads_tri, quads_in_tri, game_state->window_w, game_state->window_h, game_state->scene.light_direction, &(game_state->scene));
}

void render(game_state_t *game_state)
{
        adl_fill_mesh_Pinedas_rasterizer_interpolate_color(game_state->window_pixels_mat, game_state->inv_z_buffer_mat, proj_quads_tri, ADL_DEFAULT_OFFSET_ZOOM);

        proj_quads_tri.length = 0;

}
