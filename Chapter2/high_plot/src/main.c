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
    float min_e1;
    float max_e1;
    float de1;
    float min_e2;
    float max_e2;
    float de2;
} Hight_plot;

double hight_func_exp(double x, double y)
{
    return 3 * exp(- x * x - y * y);
}

double hight_func_trig(double x, double y)
{
    return (sin(x) + cos(y)) / 2;
}

Hight_plot hight_plot_create(double (*hight_func)(double, double), float min_e1_val, float max_e1_val, float min_e2_val, float max_e2_val, float min_func_val, float max_func_val, float func_offset, float min_e1_pos, float max_e1_pos, float min_e2_pos, float max_e2_pos, int num_sample_e1, int num_sample_e2, char *plane, float third_direction_grid_position)
{
    ADL_ASSERT(!strncmp(plane, "XZ", 3) && "other direction are no implemented.");

    Hight_plot hight_plot;

    ada_init_array(Quad, hight_plot.quads);
    ada_init_array(Quad, hight_plot.proj_quads);

    hight_plot.grid      = adl_create_cartesian_grid(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1, num_sample_e2, plane, third_direction_grid_position);
    hight_plot.grid_proj = adl_create_cartesian_grid(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1, num_sample_e2, plane, third_direction_grid_position);
    hight_plot.min_e1    = min_e1_val;
    hight_plot.min_e2    = min_e2_val;
    hight_plot.max_e1    = max_e1_val;
    hight_plot.max_e2    = max_e2_val;
    hight_plot.de1       = (hight_plot.max_e1 - hight_plot.min_e1) / hight_plot.grid.num_samples_e1;
    hight_plot.de2       = (hight_plot.max_e2 - hight_plot.min_e2) / hight_plot.grid.num_samples_e2;

    float de1 = hight_plot.grid.de1;
    float de2 = hight_plot.grid.de2;

    for (float e1_val = hight_plot.grid.min_e1, e1_val_func = hight_plot.min_e1; e1_val < hight_plot.grid.max_e1; e1_val += hight_plot.grid.de1, e1_val_func += hight_plot.de1) {
        for (float e2_val = hight_plot.grid.min_e2, e2_val_func = hight_plot.min_e2; e2_val < hight_plot.grid.max_e2; e2_val += hight_plot.grid.de2, e2_val_func += hight_plot.de2) {

            Quad quad = {0};

            quad.light_intensity = 1;
            quad.to_draw = 1;
            quad.points[3] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};
            quad.points[2] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[1] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[0] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};

            quad.colors[0] = 0xFFFFFFFF;
            quad.colors[1] = 0xFFFFFFFF;
            quad.colors[2] = 0xFFFFFFFF;
            quad.colors[3] = 0xFFFFFFFF;

            ae_quad_set_normals(&quad);

            ada_appand(Quad, hight_plot.quads, quad);
        }
    }

    return hight_plot;
}

Hight_plot hight_plot;
void setup(game_state_t *game_state)
{
    game_state->to_limit_fps = 0;

    // hight_plot = hight_plot_create(hight_func_trig, 0 , 6*PI, 0 , 6*PI, -1, 0, 1.1, -2, 2, -2, 2, 100, 100, "XZ", 1);
    hight_plot = hight_plot_create(hight_func_exp , -2, 2   , -2, 2   , 0 , 3, 1.1, -2, 2, -2, 2, 25, 25, "XZ", 1);

}


void update(game_state_t *game_state)
{
    ae_set_projection_mat(game_state->scene.proj_mat, game_state->scene.camera.aspect_ratio, game_state->scene.camera.fov_deg, game_state->scene.camera.z_near, game_state->scene.camera.z_far);
    ae_set_view_mat(game_state->scene.view_mat, game_state->scene.camera, game_state->scene.up_direction);

    ae_project_quad_mesh_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, &(hight_plot.proj_quads), hight_plot.quads, game_state->window_w, game_state->window_h, game_state->scene.light_direction, &(game_state->scene));
    ae_project_grid_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, hight_plot.grid_proj, hight_plot.grid, game_state->window_w, game_state->window_h, &(game_state->scene));
}

void render(game_state_t *game_state)
{
    adl_draw_grid(game_state->window_pixels_mat, hight_plot.grid_proj, 0xFFFFFF, ADL_DEFAULT_OFFSET_ZOOM);

    adl_fill_quad_mesh(game_state->window_pixels_mat, game_state->inv_z_buffer_mat, hight_plot.proj_quads, 0xFFFFFFFF, ADL_DEFAULT_OFFSET_ZOOM);
    // adl_draw_quad_mesh(game_state->window_pixels_mat, game_state->inv_z_buffer_mat, hight_plot.proj_quads, 0x0, ADL_DEFAULT_OFFSET_ZOOM);


    hight_plot.proj_quads.length = 0;

}
