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

typedef struct {
    Grid grid;
    Grid grid_proj;
    Quad_mesh quads;
    Quad_mesh proj_quads;
    Tri_mesh quads_in_tri;
    Tri_mesh proj_quads_tri;
} Hight_plot;

Hight_plot hight_plot;
void setup(game_state_t *game_state)
{
    game_state->to_limit_fps = 0;

    ada_init_array(Quad, hight_plot.quads);
    ada_init_array(Quad, hight_plot.proj_quads);
    ada_init_array(Tri, hight_plot.proj_quads_tri);

    hight_plot.quads_in_tri = ae_get_tri_mesh_from_quad_mesh(hight_plot.quads);

    hight_plot.grid      = adl_create_cartesian_grid(-2.0, 2.0, -2.0, 2.0, 25, 25, "XZ", 0);
    hight_plot.grid_proj = adl_create_cartesian_grid(-2.0, 2.0, -2.0, 2.0, 25, 25, "XZ", 0);

    float de1 = hight_plot.grid.de1;
    float de2 = hight_plot.grid.de2;

    for (float e1_val = hight_plot.grid.min_e1; e1_val < hight_plot.grid.max_e1; e1_val += de1) {
        for (float e2_val = hight_plot.grid.min_e2; e2_val < hight_plot.grid.max_e2; e2_val += de2) {

            Quad quad = {0};

            quad.light_intensity = 1;
            quad.to_draw = 1;
            quad.points[3] = (Point){e1_val      , -0.4 - 3*expf(-(e1_val)*(e1_val)         - (e2_val)*(e2_val))        , e2_val      , 0};
            quad.points[2] = (Point){e1_val      , -0.4 - 3*expf(-(e1_val)*(e1_val)         - (e2_val+de2)*(e2_val+de2)), e2_val + de2, 0};
            quad.points[1] = (Point){e1_val + de1, -0.4 - 3*expf(-(e1_val+de1)*(e1_val+de1) - (e2_val+de2)*(e2_val+de2)), e2_val + de2, 0};
            quad.points[0] = (Point){e1_val + de1, -0.4 - 3*expf(-(e1_val+de1)*(e1_val+de1) - (e2_val)*(e2_val))        , e2_val      , 0};

            quad.colors[0] = 0xFFFFFFFF;
            quad.colors[1] = 0xFFFFFFFF;
            quad.colors[2] = 0xFFFFFFFF;
            quad.colors[3] = 0xFFFFFFFF;


            ada_appand(Quad, hight_plot.quads, quad);
        }
    }

    hight_plot.quads_in_tri = ae_get_tri_mesh_from_quad_mesh(hight_plot.quads);

}


void update(game_state_t *game_state)
{
    ae_set_projection_mat(game_state->scene.proj_mat, game_state->scene.camera.aspect_ratio, game_state->scene.camera.fov_deg, game_state->scene.camera.z_near, game_state->scene.camera.z_far);
    ae_set_view_mat(game_state->scene.view_mat, game_state->scene.camera, game_state->scene.up_direction);

    ae_project_tri_mesh_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, &(hight_plot.proj_quads_tri), hight_plot.quads_in_tri, game_state->window_w, game_state->window_h, game_state->scene.light_direction, &(game_state->scene));
    ae_project_quad_mesh_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, &(hight_plot.proj_quads), hight_plot.quads, game_state->window_w, game_state->window_h, game_state->scene.light_direction, &(game_state->scene));
    ae_project_grid_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, hight_plot.grid_proj, hight_plot.grid, game_state->window_w, game_state->window_h);
}

void render(game_state_t *game_state)
{
    adl_draw_grid(game_state->window_pixels_mat, hight_plot.grid_proj, 0xFFFFFF, ADL_DEFAULT_OFFSET_ZOOM);

    // adl_fill_quad_mesh(game_state->window_pixels_mat, game_state->inv_z_buffer_mat, hight_plot.proj_quads, 0xFFFFFFFF, ADL_DEFAULT_OFFSET_ZOOM);
    adl_fill_tri_mesh_Pinedas_rasterizer(game_state->window_pixels_mat, game_state->inv_z_buffer_mat, hight_plot.proj_quads_tri, ADL_DEFAULT_OFFSET_ZOOM);


    hight_plot.proj_quads_tri.length = 0;
    hight_plot.proj_quads.length = 0;

}
