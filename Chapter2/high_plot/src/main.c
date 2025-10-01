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
    return 1 * exp(- x * x - y * y);
}

double hight_func_exp_deriv(double x, double y, char direction)
{
    if (direction == 'x') return -2 * x * hight_func_exp(x, y);
    if (direction == 'y') return -2 * y * hight_func_exp(x, y);
    return NAN;
}

double hight_func_trig(double x, double y)
{
    return (sin(x) + cos(y)) / 2;
}

double hight_func_trig_deriv(double x, double y, char direction)
{
    if (direction == 'x') return 0.5 * cos(x);
    if (direction == 'y') return -0.5 * sin(y);
    return NAN;
}

double hight_func_inv(double x, double y)
{
    return 1 / (x*x + y*y);
}

double hight_func_inv_deriv(double x, double y, char direction)
{
    if (direction == 'x') return -2 * x * hight_func_inv(x, y);
    if (direction == 'y') return -2 * y * hight_func_inv(x, y);
    return NAN;
}

Hight_plot hight_plot_create_smooth_approximate(double (*hight_func)(double, double), float min_e1_val, float max_e1_val, float min_e2_val, float max_e2_val, float min_func_val, float max_func_val, float func_offset, float min_e1_pos, float max_e1_pos, float min_e2_pos, float max_e2_pos, int num_sample_e1, int num_sample_e2, char *plane, float third_direction_grid_position)
{
    ADL_ASSERT(!strncmp(plane, "XZ", 3) && "other direction are no implemented.");

    Hight_plot hight_plot;

    ada_init_array(Quad, hight_plot.quads);
    ada_init_array(Quad, hight_plot.proj_quads);

    hight_plot.grid      = adl_cartesian_grid_create(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1 - 1, num_sample_e2 - 1, plane, third_direction_grid_position);
    hight_plot.grid_proj = adl_cartesian_grid_create(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1 - 1, num_sample_e2 - 1, plane, third_direction_grid_position);
    hight_plot.min_e1    = min_e1_val;
    hight_plot.min_e2    = min_e2_val;
    hight_plot.max_e1    = max_e1_val;
    hight_plot.max_e2    = max_e2_val;
    hight_plot.de1       = (hight_plot.max_e1 - hight_plot.min_e1) / (hight_plot.grid.num_samples_e1);
    hight_plot.de2       = (hight_plot.max_e2 - hight_plot.min_e2) / (hight_plot.grid.num_samples_e2);

    float de1      = hight_plot.grid.de1;
    float de2      = hight_plot.grid.de2;
    float de1_func = hight_plot.de1;
    float de2_func = hight_plot.de2;

    for (float e1_val = min_e1_pos, e1_val_func = hight_plot.min_e1; e1_val < max_e1_pos - de1; e1_val += de1, e1_val_func += hight_plot.de1) {
        for (float e2_val = min_e2_pos, e2_val_func = hight_plot.min_e2; e2_val < max_e2_pos - de2; e2_val += de2, e2_val_func += hight_plot.de2) {

            Quad quad = {0};

            quad.light_intensity[0] = 1;
            quad.light_intensity[1] = 1;
            quad.light_intensity[2] = 1;
            quad.light_intensity[3] = 1;
            quad.to_draw = 1;
            quad.points[3] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};
            quad.points[2] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[1] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[0] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};

            float step_size = de2_func;
            quad.normals[3].x = -(hight_func(e1_val_func + step_size, e2_val_func) - hight_func(e1_val_func - step_size, e2_val_func)) / (2 * step_size); 
            quad.normals[3].y = -1;
            quad.normals[3].z = -(hight_func(e1_val_func, e2_val_func + step_size) - hight_func(e1_val_func, e2_val_func - step_size)) / (2 * step_size); 
            quad.normals[3] = ae_point_normalize_xyz(quad.normals[3]);
            quad.normals[2].x = -(hight_func(e1_val_func + step_size, e2_val_func + de2_func) - hight_func(e1_val_func - step_size, e2_val_func + de2_func)) / (2 * step_size);
            quad.normals[2].y = -1;
            quad.normals[2].z = -(hight_func(e1_val_func, e2_val_func + de2_func + step_size) - hight_func(e1_val_func, e2_val_func + de2_func - step_size)) / (2 * step_size);
            quad.normals[2] = ae_point_normalize_xyz(quad.normals[2]);
            quad.normals[1].x = -(hight_func(e1_val_func + de1_func + step_size, e2_val_func + de2_func) - hight_func(e1_val_func + de1_func - step_size, e2_val_func + de2_func)) / (2 * step_size);
            quad.normals[1].y = -1;
            quad.normals[1].z = -(hight_func(e1_val_func + de1_func, e2_val_func + de2_func + step_size) - hight_func(e1_val_func + de1_func, e2_val_func + de2_func - step_size)) / (2 * step_size);
            quad.normals[1] = ae_point_normalize_xyz(quad.normals[1]);
            quad.normals[0].x = -(hight_func(e1_val_func + de1_func + step_size, e2_val_func) - hight_func(e1_val_func + de1_func - step_size, e2_val_func)) / (2 * step_size);
            quad.normals[0].y = -1;
            quad.normals[0].z = -(hight_func(e1_val_func + de1_func, e2_val_func + step_size) - hight_func(e1_val_func + de1_func, e2_val_func - step_size)) / (2 * step_size);
            quad.normals[0] = ae_point_normalize_xyz(quad.normals[0]);

            quad.colors[0] = 0xFFFFFFFF;
            quad.colors[1] = 0xFFFFFFFF;
            quad.colors[2] = 0xFFFFFFFF;
            quad.colors[3] = 0xFFFFFFFF;

            ada_appand(Quad, hight_plot.quads, quad);
        }
    }

    return hight_plot;
}

Hight_plot hight_plot_create_smooth(double (*hight_func)(double, double), double (*hight_func_deriv)(double, double, char), float min_e1_val, float max_e1_val, float min_e2_val, float max_e2_val, float min_func_val, float max_func_val, float func_offset, float min_e1_pos, float max_e1_pos, float min_e2_pos, float max_e2_pos, int num_sample_e1, int num_sample_e2, char *plane, float third_direction_grid_position)
{
    ADL_ASSERT(!strncmp(plane, "XZ", 3) && "other direction are no implemented.");

    Hight_plot hight_plot;

    ada_init_array(Quad, hight_plot.quads);
    ada_init_array(Quad, hight_plot.proj_quads);

    hight_plot.grid      = adl_cartesian_grid_create(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1 - 1, num_sample_e2 - 1, plane, third_direction_grid_position);
    hight_plot.grid_proj = adl_cartesian_grid_create(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1 - 1, num_sample_e2 - 1, plane, third_direction_grid_position);
    hight_plot.min_e1    = min_e1_val;
    hight_plot.min_e2    = min_e2_val;
    hight_plot.max_e1    = max_e1_val;
    hight_plot.max_e2    = max_e2_val;
    hight_plot.de1       = (hight_plot.max_e1 - hight_plot.min_e1) / (hight_plot.grid.num_samples_e1);
    hight_plot.de2       = (hight_plot.max_e2 - hight_plot.min_e2) / (hight_plot.grid.num_samples_e2);

    float de1      = hight_plot.grid.de1;
    float de2      = hight_plot.grid.de2;
    float de1_func = hight_plot.de1;
    float de2_func = hight_plot.de2;

    for (float e1_val = min_e1_pos, e1_val_func = hight_plot.min_e1; e1_val < max_e1_pos - de1; e1_val += de1, e1_val_func += hight_plot.de1) {
        for (float e2_val = min_e2_pos, e2_val_func = hight_plot.min_e2; e2_val < max_e2_pos - de2; e2_val += de2, e2_val_func += hight_plot.de2) {

            Quad quad = {0};

            quad.light_intensity[0] = 1;
            quad.light_intensity[1] = 1;
            quad.light_intensity[2] = 1;
            quad.light_intensity[3] = 1;
            quad.to_draw = 1;
            quad.points[3] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};
            quad.points[2] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[1] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[0] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};

            quad.normals[3].x = -hight_func_deriv(e1_val_func, e2_val_func, 'x'); 
            quad.normals[3].y = -1;
            quad.normals[3].z = -hight_func_deriv(e1_val_func, e2_val_func, 'y'); 
            quad.normals[3] = ae_point_normalize_xyz(quad.normals[3]);
            quad.normals[2].x = -hight_func_deriv(e1_val_func, e2_val_func + de2_func, 'x');
            quad.normals[2].y = -1;
            quad.normals[2].z = -hight_func_deriv(e1_val_func, e2_val_func + de2_func, 'y');
            quad.normals[2] = ae_point_normalize_xyz(quad.normals[2]);
            quad.normals[1].x = -hight_func_deriv(e1_val_func + de1_func, e2_val_func + de2_func, 'x');
            quad.normals[1].y = -1;
            quad.normals[1].z = -hight_func_deriv(e1_val_func + de1_func, e2_val_func + de2_func, 'y');
            quad.normals[1] = ae_point_normalize_xyz(quad.normals[1]);
            quad.normals[0].x = -hight_func_deriv(e1_val_func + de1_func, e2_val_func, 'x');
            quad.normals[0].y = -1;
            quad.normals[0].z = -hight_func_deriv(e1_val_func + de1_func, e2_val_func, 'y');
            quad.normals[0] = ae_point_normalize_xyz(quad.normals[0]);

            quad.colors[0] = 0xFFFFFFFF;
            quad.colors[1] = 0xFFFFFFFF;
            quad.colors[2] = 0xFFFFFFFF;
            quad.colors[3] = 0xFFFFFFFF;

            ada_appand(Quad, hight_plot.quads, quad);
        }
    }

    return hight_plot;
}

Hight_plot hight_plot_create_discrete(double (*hight_func)(double, double), float min_e1_val, float max_e1_val, float min_e2_val, float max_e2_val, float min_func_val, float max_func_val, float func_offset, float min_e1_pos, float max_e1_pos, float min_e2_pos, float max_e2_pos, int num_sample_e1, int num_sample_e2, char *plane, float third_direction_grid_position)
{
    ADL_ASSERT(!strncmp(plane, "XZ", 3) && "other direction are no implemented.");

    Hight_plot hight_plot;

    ada_init_array(Quad, hight_plot.quads);
    ada_init_array(Quad, hight_plot.proj_quads);

    hight_plot.grid      = adl_cartesian_grid_create(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1 - 1, num_sample_e2 - 1, plane, third_direction_grid_position);
    hight_plot.grid_proj = adl_cartesian_grid_create(min_e1_pos, max_e1_pos, min_e2_pos, max_e2_pos, num_sample_e1 - 1, num_sample_e2 - 1, plane, third_direction_grid_position);
    hight_plot.min_e1    = min_e1_val;
    hight_plot.min_e2    = min_e2_val;
    hight_plot.max_e1    = max_e1_val;
    hight_plot.max_e2    = max_e2_val;
    hight_plot.de1       = (hight_plot.max_e1 - hight_plot.min_e1) / (hight_plot.grid.num_samples_e1);
    hight_plot.de2       = (hight_plot.max_e2 - hight_plot.min_e2) / (hight_plot.grid.num_samples_e2);

    float de1      = hight_plot.grid.de1;
    float de2      = hight_plot.grid.de2;

    for (float e1_val = min_e1_pos, e1_val_func = hight_plot.min_e1; e1_val < max_e1_pos - de1; e1_val += de1, e1_val_func += hight_plot.de1) {
        for (float e2_val = min_e2_pos, e2_val_func = hight_plot.min_e2; e2_val < max_e2_pos - de2; e2_val += de2, e2_val_func += hight_plot.de2) {

            Quad quad = {0};

            quad.light_intensity[0] = 1;
            quad.light_intensity[1] = 1;
            quad.light_intensity[2] = 1;
            quad.light_intensity[3] = 1;
            quad.to_draw = 1;
            quad.points[3] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};
            quad.points[2] = (Point){e1_val      , third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func               , e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[1] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func+hight_plot.de2), max_func_val), min_func_val), e2_val + de2, 1};
            quad.points[0] = (Point){e1_val + de1, third_direction_grid_position - func_offset - fmaxf(fminf(hight_func(e1_val_func+hight_plot.de1, e2_val_func               ), max_func_val), min_func_val), e2_val      , 1};

            ae_quad_set_normals(&(quad));

            quad.colors[0] = 0xFFFFFFFF;
            quad.colors[1] = 0xFFFFFFFF;
            quad.colors[2] = 0xFFFFFFFF;
            quad.colors[3] = 0xFFFFFFFF;

            ada_appand(Quad, hight_plot.quads, quad);
        }
    }

    return hight_plot;
}

/* TODO: add lighting model as described in Pg. 29 */

Hight_plot hight_plot;
void setup(game_state_t *game_state)
{
    game_state->to_limit_fps = 0;

    hight_plot = hight_plot_create_smooth(hight_func_exp, hight_func_exp_deriv, -1, 1   , -1, 1   , 0 , 3, 0.1, -0.5, 0.5, -0.5, 0.5, 30, 30, "XZ", 1);
    // hight_plot = hight_plot_create_discrete(hight_func_exp, -1, 1   , -1, 1   , 0 , 3, 0.1, -0.5, 0.5, -0.5, 0.5, 30, 30, "XZ", 1);
    // hight_plot = hight_plot_create_smooth_approximate(hight_func_exp, -1, 1   , -1, 1   , 0 , 3, 0.1, -0.5, 0.5, -0.5, 0.5, 30, 30, "XZ", 1);

}

void update(game_state_t *game_state)
{
    ae_projection_mat_set(game_state->scene.proj_mat, game_state->scene.camera.aspect_ratio, game_state->scene.camera.fov_deg, game_state->scene.camera.z_near, game_state->scene.camera.z_far);
    ae_view_mat_set(game_state->scene.view_mat, game_state->scene.camera, game_state->scene.up_direction);

    ae_quad_mesh_project_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, &(hight_plot.proj_quads), hight_plot.quads, game_state->window_w, game_state->window_h, &(game_state->scene), AE_LIGHTING_SMOOTH);
    ae_grid_project_world2screen(game_state->scene.proj_mat, game_state->scene.view_mat, hight_plot.grid_proj, hight_plot.grid, game_state->window_w, game_state->window_h, &(game_state->scene));
}

void render(game_state_t *game_state)
{
    adl_grid_draw(game_state->window_pixels_mat, hight_plot.grid_proj, 0xFFFFFF, ADL_DEFAULT_OFFSET_ZOOM);

    adl_quad_mesh_fill_interpolate_normal(game_state->window_pixels_mat, game_state->inv_z_buffer_mat, hight_plot.proj_quads, RGB_hexRGB(0.3*255, 0.8*255, 0.37*255), ADL_DEFAULT_OFFSET_ZOOM);

    hight_plot.proj_quads.length = 0;

}
