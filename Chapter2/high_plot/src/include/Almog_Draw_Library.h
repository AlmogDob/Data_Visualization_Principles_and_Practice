#ifndef ALMOG_DRAW_LIBRARY_H_
#define ALMOG_DRAW_LIBRARY_H_

#include <math.h>
#include <stdint.h>
#include <limits.h>
#include <string.h>
#include <float.h>

#include "./Matrix2D.h"
#include "./Almog_Dynamic_Array.h"

#ifndef ADL_ASSERT
#include <assert.h>
#define ADL_ASSERT assert
#endif

typedef struct {
    float zoom_multiplier;
    float offset_x;
    float offset_y;
    int mouse_x;
    int mouse_y;
} Offset_zoom_param;

#ifndef POINT
#define POINT
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Point ;
#endif

typedef struct {
    uint32_t color;
    size_t length;
    size_t capacity;
    Point *elements;
} Curve;

typedef struct {
    size_t length;
    size_t capacity;
    Curve *elements;
} Curve_ada;

#ifndef TRI
#define TRI
typedef struct {
    Point points[3];
    Point tex_points[3];
    Point center;
    Point normals[3];
    uint32_t colors[3];
    float z_min;
    float z_max;
    bool to_draw;
    float light_intensity;
} Tri;
#endif

#ifndef QUAD
#define QUAD
typedef struct {
    Point points[4];
    Point normal[4];
    uint32_t colors[4];
    bool to_draw;
    float light_intensity;
} Quad;
#endif

#ifndef TRI_MESH
#define TRI_MESH
typedef struct {
    size_t length;
    size_t capacity;
    Tri *elements;
} Tri_mesh; /* Tri ada array */
#endif

#ifndef QUAD_MESH
#define QUAD_MESH
typedef struct {
    size_t length;
    size_t capacity;
    Quad *elements;
} Quad_mesh; /* Quad ada array */
#endif

typedef struct {
    int min_x_pixel;
    int max_x_pixel;
    int min_y_pixel;
    int max_y_pixel;
    float min_x;
    float max_x;
    float min_y;
    float max_y;
    int x_axis_head_size;
    int y_axis_head_size;
    Offset_zoom_param offset_zoom_param;
    Curve_ada src_curve_array;
    Point top_left_position;
    Mat2D_uint32 pixels_mat;
    Mat2D inv_z_buffer_mat;
    uint32_t background_color;
    bool to_draw_axis;
    bool to_draw_max_min_values;
} Figure;

typedef struct {
    Curve_ada curves;
    float min_e1;
    float max_e1;
    float min_e2;
    float max_e2;
    int num_samples_e1;
    int num_samples_e2;
    char plane[3];
} Grid; /* direction: e1, e2 */


#ifndef HexARGB_RGBA
#define HexARGB_RGBA(x) ((x)>>(8*2)&0xFF), ((x)>>(8*1)&0xFF), ((x)>>(8*0)&0xFF), ((x)>>(8*3)&0xFF)
#endif
#ifndef HexARGB_RGB_VAR
#define HexARGB_RGB_VAR(x, r, g, b) r = ((x)>>(8*2)&0xFF); g = ((x)>>(8*1)&0xFF); b = ((x)>>(8*0)&0xFF);
#endif
#ifndef RGB_hexRGB
#define RGB_hexRGB(r, g, b) (int)(0x010000*(int)(r) + 0x000100*(int)(g) + 0x000001*(int)(b))
#endif
#ifndef RGBA_hexARGB
#define RGBA_hexARGB(r, g, b, a) (int)(0x01000000l*(int)(fminf(a, 255)) + 0x010000*(int)(r) + 0x000100*(int)(g) + 0x000001*(int)(b))
#endif



void adl_draw_point(Mat2D_uint32 screen_mat, int x, int y, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_draw_line(Mat2D_uint32 screen_mat, const float x1_input, const float y1_input, const float x2_input, const float y2_input, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_draw_lines(const Mat2D_uint32 screen_mat, const Point *points, const size_t len, const uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_draw_lines_loop(const Mat2D_uint32 screen_mat, const Point *points, const size_t len, const uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_draw_arrow(Mat2D_uint32 screen_mat, int xs, int ys, int xe, int ye, float head_size, float angle_deg, uint32_t color, Offset_zoom_param offset_zoom_param);

void adl_draw_character(Mat2D_uint32 screen_mat, char c, int width_pixel, int hight_pixel, int x_top_left, int y_top_left, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_draw_sentence(Mat2D_uint32 screen_mat, const char sentence[], size_t len, const int x_top_left, const int y_top_left, const int hight_pixel, const uint32_t color, Offset_zoom_param offset_zoom_param);

void adl_draw_rectangle_min_max(Mat2D_uint32 screen_mat, int min_x, int max_x, int min_y, int max_y, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_rectangle_min_max(Mat2D_uint32 screen_mat, int min_x, int max_x, int min_y, int max_y, uint32_t color, Offset_zoom_param offset_zoom_param);

void adl_draw_quad(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_quad_tri(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, char split_line[], uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_quad(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_quad_interpolate_color_tri(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, char split_line[], Offset_zoom_param offset_zoom_param);
void adl_fill_quad_interpolate_color_mean_value(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, Offset_zoom_param offset_zoom_param);

void adl_draw_circle(Mat2D_uint32 screen_mat, float center_x, float center_y, float r, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_circle(Mat2D_uint32 screen_mat, float center_x, float center_y, float r, uint32_t color, Offset_zoom_param offset_zoom_param);

void adl_draw_tri(Mat2D_uint32 screen_mat, Tri tri, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_tri_scanline_rasterizer(Mat2D_uint32 screen_mat, Tri tri, Offset_zoom_param offset_zoom_param);
void adl_fill_tri_Pinedas_rasterizer(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Tri tri, float light_intensity, Offset_zoom_param offset_zoom_param);
void adl_fill_tri_Pinedas_rasterizer_interpolate_color(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Tri tri, float light_intensity, Offset_zoom_param offset_zoom_param);

void adl_draw_mesh(Mat2D_uint32 screen_mat, Tri_mesh mesh, uint32_t color, Offset_zoom_param offset_zoom_param);
void adl_fill_mesh_scanline_rasterizer(Mat2D_uint32 screen_mat, Tri_mesh mesh, Offset_zoom_param offset_zoom_param);
void adl_fill_mesh_Pinedas_rasterizer(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer_mat, Tri_mesh mesh, Offset_zoom_param offset_zoom_param);

float adl_linear_map(float s, float min_in, float max_in, float min_out, float max_out);
void adl_quad2tris(Quad quad, Tri *tri1, Tri *tri2, char split_line[]);
void adl_linear_sRGB_to_okLab(uint32_t hex_ARGB, float *L, float *a, float *b);
void adl_okLab_to_linear_sRGB(float L, float a, float b, uint32_t *hex_ARGB);
void adl_linear_sRGB_to_okLch(uint32_t hex_ARGB, float *L, float *c, float *h_deg);
void adl_okLch_to_linear_sRGB(float L, float c, float h_deg, uint32_t *hex_ARGB);
void adl_interpolate_ARGBcolor_on_okLch(uint32_t color1, uint32_t color2, float t, float num_of_rotations, uint32_t *color_out);

Figure adl_alloc_figure(size_t rows, size_t cols, Point top_left_position);
void adl_copy_figure_to_screen(Mat2D_uint32 screen_mat, Figure figure);
void adl_draw_axis_on_figure(Figure *figure);
void adl_draw_max_min_values_on_figure(Figure figure);
void adl_add_curve_to_figure(Figure *figure, Point *src_points, size_t src_len, uint32_t color);
void adl_plot_curves_on_figure(Figure figure);
void adl_interp_scalar_2D_on_figure(Figure figure, double *x_2Dmat, double *y_2Dmat, double *scalar_2Dmat, int ni, int nj, char color_scale[], float num_of_rotations);

Grid adl_create_square_grid(float min_e1, float max_e1, float min_e2, float max_e2, int num_samples_e1, int num_samples_e2, char plane[], float third_direction_position);
void adl_draw_grid(Mat2D_uint32 screen_mat, Grid grid, uint32_t color, Offset_zoom_param offset_zoom_param);

#endif /*ALMOG_RENDER_SHAPES_H_*/

#ifdef ALMOG_DRAW_LIBRARY_IMPLEMENTATION
#undef ALMOG_DRAW_LIBRARY_IMPLEMENTATION

#define RED_hexARGB    0xFFFF0000
#define GREEN_hexARGB  0xFF00FF00
#define BLUE_hexARGB   0xFF0000FF
#define PURPLE_hexARGB 0xFFFF00FF
#define CYAN_hexARGB   0xFF00FFFF
#define YELLOW_hexARGB 0xFFFFFF00

#define edge_cross_point(a1, b, a2, p) (b.x-a1.x)*(p.y-a2.y)-(b.y-a1.y)*(p.x-a2.x)
#define is_top_edge(x, y) (y == 0 && x > 0)
#define is_left_edge(x, y) (y < 0)
#define is_top_left(ps, pe) (is_top_edge(pe.x-ps.x, pe.y-ps.y) || is_left_edge(pe.x-ps.x, pe.y-ps.y))

#define ADL_MAX_POINT_VAL 1e5
#define adl_assert_point_is_valid(p) ADL_ASSERT(isfinite(p.x) && isfinite(p.y) && isfinite(p.z) && isfinite(p.w))
#define adl_assert_tri_is_valid(tri) adl_assert_point_is_valid(tri.points[0]); \
        adl_assert_point_is_valid(tri.points[1]);                              \
        adl_assert_point_is_valid(tri.points[2])

#define ADL_FIGURE_PADDING_PRECENTAGE 20
#define ADL_MAX_FIGURE_PADDING 70
#define ADL_MIN_FIGURE_PADDING 20
#define ADL_MAX_HEAD_SIZE 15
#define ADL_FIGURE_HEAD_ANGLE_DEG 30
#define ADL_FIGURE_AXIS_COLOR 0x0

#define ADL_MAX_CHARACTER_OFFSET 10
#define ADL_MIN_CHARACTER_OFFSET 5
#define ADL_MAX_SENTENCE_LEN 256
#define ADL_MAX_ZOOM 1e3

#define ADL_DEFAULT_OFFSET_ZOOM (Offset_zoom_param){1,0,0,0,0}
#define adl_offset_zoom_point(p, window_w, window_h, offset_zoom_param)                                             \
    (p).x = ((p).x - (window_w)/2 + offset_zoom_param.offset_x) * offset_zoom_param.zoom_multiplier + (window_w)/2; \
    (p).y = ((p).y - (window_h)/2 + offset_zoom_param.offset_y) * offset_zoom_param.zoom_multiplier + (window_h)/2

/* default values should be: 
zoom_multiplier = 1;
offset_x = 0;
offset_y = 0; */
void adl_draw_point(Mat2D_uint32 screen_mat, int x, int y, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    float window_w = (float)screen_mat.cols;
    float window_h = (float)screen_mat.rows;

    x = (x - window_w/2 + offset_zoom_param.offset_x) * offset_zoom_param.zoom_multiplier + window_w/2;
    y = (y - window_h/2 + offset_zoom_param.offset_y) * offset_zoom_param.zoom_multiplier + window_h/2;

    if ((x < (int)screen_mat.cols && y < (int)screen_mat.rows) && (x >= 0 && y >= 0)) { /* point is in screen */
        MAT2D_AT_UINT32(screen_mat, y, x) = color;
    }
}

void adl_draw_line(Mat2D_uint32 screen_mat, const float x1_input, const float y1_input, const float x2_input, const float y2_input, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    /* This function is inspired by the Olive.c function developed by 'Tsoding' on his YouTube channel. You can fined the video in this link: https://youtu.be/LmQKZmQh1ZQ?list=PLpM-Dvs8t0Va-Gb0Dp4d9t8yvNFHaKH6N&t=4683. */

    float window_w = (float)screen_mat.cols;
    float window_h = (float)screen_mat.rows;

    int x1 = (x1_input - window_w/2 + offset_zoom_param.offset_x) * offset_zoom_param.zoom_multiplier + window_w/2;
    int x2 = (x2_input - window_w/2 + offset_zoom_param.offset_x) * offset_zoom_param.zoom_multiplier + window_w/2;
    int y1 = (y1_input - window_h/2 + offset_zoom_param.offset_y) * offset_zoom_param.zoom_multiplier + window_h/2;
    int y2 = (y2_input - window_h/2 + offset_zoom_param.offset_y) * offset_zoom_param.zoom_multiplier + window_h/2;

    ADL_ASSERT((int)fabsf(fabsf((float)x2) - fabsf((float)x1)) < ADL_MAX_POINT_VAL);
    ADL_ASSERT((int)fabsf(fabsf((float)y2) - fabsf((float)y1)) < ADL_MAX_POINT_VAL);

    int x = x1;
    int y = y1;
    int dx, dy;

    adl_draw_point(screen_mat, x, y, color, (Offset_zoom_param){1,0,0,0,0});

    dx = x2 - x1;
    dy = y2 - y1;

    ADL_ASSERT(dy > INT_MIN && dy < INT_MAX);
    ADL_ASSERT(dx > INT_MIN && dx < INT_MAX);

    if (0 == dx && 0 == dy) return;
    if (0 == dx) {
        while (x != x2 || y != y2) {
            if (dy > 0) {
                y++;
            }
            if (dy < 0) {
                y--;
            }
            adl_draw_point(screen_mat, x, y, color, (Offset_zoom_param){1,0,0,0,0});
        }
        return;
    }
    if (0 == dy) {
        while (x != x2 || y != y2) {
            if (dx > 0) {
                x++;
            }
            if (dx < 0) {
                x--;
            }
            adl_draw_point(screen_mat, x, y, color, (Offset_zoom_param){1,0,0,0,0});
        }
        return;
    }

    /* float m = (float)dy / dx */
    int b = y1 - dy * x1 / dx;

    if (x1 > x2) {
        int temp_x = x1;
        x1 = x2;
        x2 = temp_x;
    }
    for (x = x1; x < x2; x++) {
        int sy1 = dy * x / dx + b;
        int sy2 = dy * (x + 1) / dx + b;
        if (sy1 > sy2) {
            int temp_y = sy1;
            sy1 = sy2;
            sy2 = temp_y;
        }
        for (y = sy1; y <= sy2; y++) {
            adl_draw_point(screen_mat, x, y, color, (Offset_zoom_param){1,0,0,0,0});
        }
    }

}

void adl_draw_lines(const Mat2D_uint32 screen_mat, const Point *points, const size_t len, const uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (size_t i = 0; i < len-1; i++) {
        adl_draw_line(screen_mat, points[i].x, points[i].y, points[i+1].x, points[i+1].y, color, offset_zoom_param);
    }
}

void adl_draw_lines_loop(const Mat2D_uint32 screen_mat, const Point *points, const size_t len, const uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (size_t i = 0; i < len-1; i++) {
        adl_draw_line(screen_mat, points[i].x, points[i].y, points[i+1].x, points[i+1].y, color, offset_zoom_param);
    }
    adl_draw_line(screen_mat, points[len-1].x, points[len-1].y, points[0].x, points[0].y, color, offset_zoom_param);
}

/* This function is a bit complicated and expansive but this is what I could come up with */
void adl_draw_arrow(Mat2D_uint32 screen_mat, int xs, int ys, int xe, int ye, float head_size, float angle_deg, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    Mat2D pe = mat2D_alloc(3, 1);
    mat2D_fill(pe, 0);
    MAT2D_AT(pe, 0, 0) = xe;
    MAT2D_AT(pe, 1, 0) = ye;
    Mat2D v1 = mat2D_alloc(3, 1);
    mat2D_fill(v1, 0);
    Mat2D v2 = mat2D_alloc(3, 1);
    mat2D_fill(v2, 0);
    Mat2D temp_v = mat2D_alloc(3, 1);
    mat2D_fill(temp_v, 0);
    Mat2D DCM_p = mat2D_alloc(3, 3);
    mat2D_fill(DCM_p, 0);
    mat2D_set_rot_mat_z(DCM_p, angle_deg);
    Mat2D DCM_m = mat2D_alloc(3, 3);
    mat2D_fill(DCM_m, 0);
    mat2D_set_rot_mat_z(DCM_m, -angle_deg);

    int x_center = xs*head_size + xe*(1-head_size);
    int y_center = ys*head_size + ye*(1-head_size);

    MAT2D_AT(v1, 0, 0) = x_center;
    MAT2D_AT(v1, 1, 0) = y_center;
    mat2D_copy(v2, v1);

    /* v1 */
    mat2D_copy(temp_v, v1);
    mat2D_sub(temp_v, pe);
    mat2D_fill(v1, 0);
    mat2D_dot(v1, DCM_p, temp_v);
    mat2D_add(v1, pe);

    /* v2 */
    mat2D_copy(temp_v, v2);
    mat2D_sub(temp_v, pe);
    mat2D_fill(v2, 0);
    mat2D_dot(v2, DCM_m, temp_v);
    mat2D_add(v2, pe);

    adl_draw_line(screen_mat, MAT2D_AT(v1, 0, 0), MAT2D_AT(v1, 1, 0), xe, ye, color, offset_zoom_param);
    adl_draw_line(screen_mat, MAT2D_AT(v2, 0, 0), MAT2D_AT(v2, 1, 0), xe, ye, color, offset_zoom_param);
    adl_draw_line(screen_mat, xs, ys, xe, ye, color, offset_zoom_param);

    mat2D_free(pe);
    mat2D_free(v1);
    mat2D_free(v2);
    mat2D_free(temp_v);
    mat2D_free(DCM_p);
    mat2D_free(DCM_m);
}

void adl_draw_character(Mat2D_uint32 screen_mat, char c, int width_pixel, int hight_pixel, int x_top_left, int y_top_left, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    switch (c)
    {
    case 'a':
    case 'A':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel/2, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/6, y_top_left+2*hight_pixel/3, x_top_left+5*width_pixel/6, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        break;
    case 'b':
    case 'B':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/3, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'c':
    case 'C':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'd':
    case 'D':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left, y_top_left, color, offset_zoom_param);
        break;
    case 'e':
    case 'E':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/2, color, offset_zoom_param);
        break;
    case 'f':
    case 'F':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/2, color, offset_zoom_param);
        break;
    case 'g':
    case 'G':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/2, x_top_left+width_pixel/2, y_top_left+hight_pixel/2, color, offset_zoom_param);
        break;
    case 'h':
    case 'H':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/2, color, offset_zoom_param);
        break;
    case 'i':
    case 'I':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'j':
    case 'J':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+2*width_pixel/3, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left+hight_pixel, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel/6, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        break;
    case 'k':
    case 'K':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    case 'l':
    case 'L':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'm':
    case 'M':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'n':
    case 'N':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    case 'o':
    case 'O':
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        break;
    case 'p':
    case 'P':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/3, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left, y_top_left+hight_pixel/2, color, offset_zoom_param);
        break;
    case 'q':
    case 'Q':
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'r':
    case 'R':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/3, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 's':
    case 'S':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/3, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        break;
    case 't':
    case 'T':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'u':
    case 'U':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    case 'v':
    case 'V':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    case 'w':
    case 'W':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel/2, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    case 'x':
    case 'X':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    case 'y':
    case 'Y':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left+hight_pixel/2, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case 'z':
    case 'Z':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case '.':
        adl_fill_rectangle_min_max(screen_mat, x_top_left+width_pixel/6, x_top_left+width_pixel/3, y_top_left+5*hight_pixel/6, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case ':':
        adl_fill_rectangle_min_max(screen_mat, x_top_left+width_pixel/6, x_top_left+width_pixel/3, y_top_left+5*hight_pixel/6, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_fill_rectangle_min_max(screen_mat, x_top_left+width_pixel/6, x_top_left+width_pixel/3, y_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        break;
    case '0':
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        break;
    case '1':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left+width_pixel/2, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case '2':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/3, x_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case '3':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/3, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        break;
    case '4':
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+2*hight_pixel/3, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        break;
    case '5':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left, y_top_left+hight_pixel/2, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        break;
    case '6':
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, x_top_left, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        break;
    case '7':
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case '8':
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/3, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/3, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);

        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, x_top_left, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+2*hight_pixel/3, x_top_left, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+2*hight_pixel/3, color, offset_zoom_param);
        break;
    case '9':
        adl_draw_line(screen_mat, x_top_left, y_top_left+5*hight_pixel/6, x_top_left+width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+5*hight_pixel/6, x_top_left+width_pixel, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel, y_top_left+hight_pixel/6, x_top_left+2*width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left, x_top_left+width_pixel/3, y_top_left, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left, x_top_left, y_top_left+hight_pixel/6, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/6, x_top_left, y_top_left+hight_pixel/3, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/3, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/3, y_top_left+hight_pixel/2, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+2*width_pixel/3, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/3, color, offset_zoom_param);
        break;
    case '-':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/2, color, offset_zoom_param);
        break;
    case '+':
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel/2, x_top_left+width_pixel, y_top_left+hight_pixel/2, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left+width_pixel/2, y_top_left, x_top_left+width_pixel/2, y_top_left+hight_pixel, color, offset_zoom_param);
        break;
    case ' ':
        break;
    default:
        adl_draw_rectangle_min_max(screen_mat, x_top_left, x_top_left+width_pixel, y_top_left, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left, x_top_left+width_pixel, y_top_left+hight_pixel, color, offset_zoom_param);
        adl_draw_line(screen_mat, x_top_left, y_top_left+hight_pixel, x_top_left+width_pixel, y_top_left, color, offset_zoom_param);
        break;
    }
}

void adl_draw_sentence(Mat2D_uint32 screen_mat, const char sentence[], size_t len, const int x_top_left, const int y_top_left, const int hight_pixel, const uint32_t color, Offset_zoom_param offset_zoom_param)
{
    int character_width_pixel = hight_pixel/2;
    int current_x_top_left = x_top_left;
    int character_x_offset = (int)fmaxf(fminf(ADL_MAX_CHARACTER_OFFSET, character_width_pixel / 5), ADL_MIN_CHARACTER_OFFSET);

    for (size_t char_index = 0; char_index < len; char_index++) {
        adl_draw_character(screen_mat, sentence[char_index], character_width_pixel, hight_pixel, current_x_top_left, y_top_left, color, offset_zoom_param);
        current_x_top_left += character_width_pixel + character_x_offset;
    }

}

void adl_draw_rectangle_min_max(Mat2D_uint32 screen_mat, int min_x, int max_x, int min_y, int max_y, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    adl_draw_line(screen_mat, min_x, min_y, max_x, min_y, color, offset_zoom_param);
    adl_draw_line(screen_mat, min_x, max_y, max_x, max_y, color, offset_zoom_param);
    adl_draw_line(screen_mat, min_x, min_y, min_x, max_y, color, offset_zoom_param);
    adl_draw_line(screen_mat, max_x, min_y, max_x, max_y, color, offset_zoom_param);
}

void adl_fill_rectangle_min_max(Mat2D_uint32 screen_mat, int min_x, int max_x, int min_y, int max_y, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (int y = min_y; y <= max_y; y++) {
        adl_draw_line(screen_mat, min_x, y, max_x, y, color, offset_zoom_param);
    }
}

void adl_draw_quad(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    (void)inv_z_buffer;
    adl_draw_lines_loop(screen_mat, quad.points, 4, color, offset_zoom_param);
}

void adl_fill_quad_tri(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, char split_line[], uint32_t color, Offset_zoom_param offset_zoom_param)
{
    Tri tri1 = {0}, tri2 = {0};
    adl_quad2tris(quad, &tri1, &tri2, split_line);
    for (int i = 0; i < 3; i++) {
        tri1.colors[i] = color;
        tri2.colors[i] = color;
    }

    adl_fill_tri_Pinedas_rasterizer(screen_mat, inv_z_buffer, tri1, tri1.light_intensity, offset_zoom_param);
    adl_fill_tri_Pinedas_rasterizer(screen_mat, inv_z_buffer, tri2, tri2.light_intensity, offset_zoom_param);
}

void adl_fill_quad(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    Point p0 = quad.points[0];
    Point p1 = quad.points[1];
    Point p2 = quad.points[2];
    Point p3 = quad.points[3];

    int x_min = fminf(p0.x, fminf(p1.x, fminf(p2.x, p3.x)));
    int x_max = fmaxf(p0.x, fmaxf(p1.x, fmaxf(p2.x, p3.x)));
    int y_min = fminf(p0.y, fminf(p1.y, fminf(p2.y, p3.y)));
    int y_max = fmaxf(p0.y, fmaxf(p1.y, fmaxf(p2.y, p3.y)));

    if (x_min < 0) x_min = 0;
    if (y_min < 0) y_min = 0;
    if (x_max >= (int)screen_mat.cols) x_max = (int)screen_mat.cols - 1;
    if (y_max >= (int)screen_mat.rows) y_max = (int)screen_mat.rows - 1;

    float w = edge_cross_point(p0, p1, p1, p2) + edge_cross_point(p2, p3, p3, p0);
    if (w < 0) return;
    if (w < 1e-6) {
        adl_draw_quad(screen_mat, inv_z_buffer, quad, color, offset_zoom_param);
        return;
    }

    adl_draw_quad(screen_mat, inv_z_buffer, quad, color, offset_zoom_param);
    adl_draw_rectangle_min_max(screen_mat, x_min, x_max, y_min, y_max, color, offset_zoom_param);

    /* fill conventions */
    int bias0 = is_top_left(p0, p1) ? 0 : -1;
    int bias1 = is_top_left(p1, p2) ? 0 : -1;
    int bias2 = is_top_left(p2, p3) ? 0 : -1;
    int bias3 = is_top_left(p3, p0) ? 0 : -1;

    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            Point p = {.x = x, .y = y, .z = 0};

            float w0 = edge_cross_point(p0, p1, p0, p) + bias0;
            float w1 = edge_cross_point(p1, p2, p1, p) + bias1;
            float w2 = edge_cross_point(p2, p3, p2, p) + bias2;
            float w3 = edge_cross_point(p3, p0, p3, p) + bias3;

            float alpha = fabs(w1 / (w0 + w1 + w2 + w3));
            float beta  = fabs(w2 / (w0 + w1 + w2 + w3));
            float gamma = fabs(w3 / (w0 + w1 + w2 + w3));
            float delta = fabs(w0 / (w0 + w1 + w2 + w3));

            if (w0 * w >= 0 && w1 * w >= 0 &&  w2 * w >= 0 && w3 * w >= 0) {
                int r, b, g;
                HexARGB_RGB_VAR(color, r, g, b);
                float rf = r * quad.light_intensity;
                float gf = g * quad.light_intensity;
                float bf = b * quad.light_intensity;
                uint8_t r8 = (uint8_t)fmaxf(0, fminf(255, rf));
                uint8_t g8 = (uint8_t)fmaxf(0, fminf(255, gf));
                uint8_t b8 = (uint8_t)fmaxf(0, fminf(255, bf));

                double inv_w = alpha * (1.0f / p0.w) + beta  * (1.0f / p1.w) + gamma * (1.0f / p2.w) + delta * (1.0f / p3.w);
                double z_over_w = alpha * (p0.z / p0.w) + beta  * (p1.z / p1.w) + gamma * (p2.z / p2.w) + delta * (p3.z / p3.w);
                double inv_z = inv_w / z_over_w;

                if (inv_z >= MAT2D_AT(inv_z_buffer, y, x)) {
                    adl_draw_point(screen_mat, x, y, RGB_hexRGB(r8, g8, b8), offset_zoom_param);
                    MAT2D_AT(inv_z_buffer, y, x) = inv_z;
                }
            }
        }
    }
}

/* Since the function filles by triangles, there are some artifacts */
void adl_fill_quad_interpolate_color_tri(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, char split_line[], Offset_zoom_param offset_zoom_param)
{
    Tri tri1 = {0}, tri2 = {0};
    // adl_quad2tris(quad, &tri1, &tri2, "02");
    adl_quad2tris(quad, &tri1, &tri2, split_line);

    adl_fill_tri_Pinedas_rasterizer_interpolate_color(screen_mat, inv_z_buffer, tri1, tri1.light_intensity, offset_zoom_param);
    adl_fill_tri_Pinedas_rasterizer_interpolate_color(screen_mat, inv_z_buffer, tri2, tri2.light_intensity, offset_zoom_param);
}

/* This function works correctly but there is a lot of calculation for every pixel. */
void adl_fill_quad_interpolate_color_mean_value(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Quad quad, Offset_zoom_param offset_zoom_param)
{
    Point p0 = quad.points[0];
    Point p1 = quad.points[1];
    Point p2 = quad.points[2];
    Point p3 = quad.points[3];

    int x_min = fminf(p0.x, fminf(p1.x, fminf(p2.x, p3.x)));
    int x_max = fmaxf(p0.x, fmaxf(p1.x, fmaxf(p2.x, p3.x)));
    int y_min = fminf(p0.y, fminf(p1.y, fminf(p2.y, p3.y)));
    int y_max = fmaxf(p0.y, fmaxf(p1.y, fmaxf(p2.y, p3.y)));

    if (x_min < 0) x_min = 0;
    if (y_min < 0) y_min = 0;
    if (x_max >= (int)screen_mat.cols) x_max = (int)screen_mat.cols - 1;
    if (y_max >= (int)screen_mat.rows) y_max = (int)screen_mat.rows - 1;

    float w = edge_cross_point(p0, p1, p1, p2) + edge_cross_point(p2, p3, p3, p0);
    if (w < 0) {
        return;
    }
    if (w < 1e-6) {
        adl_draw_quad(screen_mat, inv_z_buffer, quad, quad.colors[0], offset_zoom_param);
        return;
    }

    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            Point p = {.x = x, .y = y, .z = 0};

            bool in_01 = edge_cross_point(p0, p1, p0, p) >= 0;
            bool in_12 = edge_cross_point(p1, p2, p1, p) >= 0;
            bool in_23 = edge_cross_point(p2, p3, p2, p) >= 0;
            bool in_30 = edge_cross_point(p3, p0, p3, p) >= 0;

            /* https://www.mn.uio.no/math/english/people/aca/michaelf/papers/mv3d.pdf. */
            float size_p_to_p0 = sqrt((p0.x - p.x)*(p0.x - p.x) + (p0.y - p.y)*(p0.y - p.y));
            float size_p_to_p1 = sqrt((p1.x - p.x)*(p1.x - p.x) + (p1.y - p.y)*(p1.y - p.y));
            float size_p_to_p2 = sqrt((p2.x - p.x)*(p2.x - p.x) + (p2.y - p.y)*(p2.y - p.y));
            float size_p_to_p3 = sqrt((p3.x - p.x)*(p3.x - p.x) + (p3.y - p.y)*(p3.y - p.y));

            float theta_3 = acosf(((p3.x - p.x) * (p0.x - p.x) + (p3.y - p.y) * (p0.y - p.y)) / (size_p_to_p3 * size_p_to_p0));
            float theta_0 = acosf(((p0.x - p.x) * (p1.x - p.x) + (p0.y - p.y) * (p1.y - p.y)) / (size_p_to_p0 * size_p_to_p1));
            float theta_1 = acosf(((p1.x - p.x) * (p2.x - p.x) + (p1.y - p.y) * (p2.y - p.y)) / (size_p_to_p1 * size_p_to_p2));
            float theta_2 = acosf(((p2.x - p.x) * (p3.x - p.x) + (p2.y - p.y) * (p3.y - p.y)) / (size_p_to_p2 * size_p_to_p3));

            float w0 = (tanf(theta_3 / 2) + tanf(theta_0 / 2)) / size_p_to_p0;
            float w1 = (tanf(theta_0 / 2) + tanf(theta_1 / 2)) / size_p_to_p1;
            float w2 = (tanf(theta_1 / 2) + tanf(theta_2 / 2)) / size_p_to_p2;
            float w3 = (tanf(theta_2 / 2) + tanf(theta_3 / 2)) / size_p_to_p3;

            float alpha = w0 / (w0 + w1 + w2 + w3);
            float beta  = w1 / (w0 + w1 + w2 + w3);
            float gamma = w2 / (w0 + w1 + w2 + w3);
            float delta = w3 / (w0 + w1 + w2 + w3);

            if (in_01 && in_12 &&  in_23 && in_30) {
                int r0, b0, g0;
                int r1, b1, g1;
                int r2, b2, g2;
                int r3, b3, g3;
                HexARGB_RGB_VAR(quad.colors[0], r0, g0, b0);
                HexARGB_RGB_VAR(quad.colors[1], r1, g1, b1);
                HexARGB_RGB_VAR(quad.colors[2], r2, g2, b2);
                HexARGB_RGB_VAR(quad.colors[3], r3, g3, b3);
                
                uint8_t current_r = r0*alpha + r1*beta + r2*gamma + r3*delta;
                uint8_t current_g = g0*alpha + g1*beta + g2*gamma + g3*delta;
                uint8_t current_b = b0*alpha + b1*beta + b2*gamma + b3*delta;

                float rf = current_r * quad.light_intensity;
                float gf = current_g * quad.light_intensity;
                float bf = current_b * quad.light_intensity;
                uint8_t r8 = (uint8_t)fmaxf(0, fminf(255, rf));
                uint8_t g8 = (uint8_t)fmaxf(0, fminf(255, gf));
                uint8_t b8 = (uint8_t)fmaxf(0, fminf(255, bf));

                double inv_w = alpha * (1.0f / p0.w) + beta  * (1.0f / p1.w) + gamma * (1.0f / p2.w) + delta * (1.0f / p3.w);
                double z_over_w = alpha * (p0.z / p0.w) + beta  * (p1.z / p1.w) + gamma * (p2.z / p2.w) + delta * (p3.z / p3.w);
                double inv_z = inv_w / z_over_w;

                if (inv_z >= MAT2D_AT(inv_z_buffer, y, x)) {
                    adl_draw_point(screen_mat, x, y, RGB_hexRGB(r8, g8, b8), offset_zoom_param);
                    MAT2D_AT(inv_z_buffer, y, x) = inv_z;
                }
            }
        }
    }
}

void adl_draw_circle(Mat2D_uint32 screen_mat, float center_x, float center_y, float r, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (int dy = -r; dy <= r; dy++) {
        for (int dx = -r; dx <= r; dx ++) {
            float diff = dx * dx + dy * dy - r * r;
            if (diff < 0 && diff > -r*2) {
                adl_draw_point(screen_mat, center_x + dx, center_y + dy, color, offset_zoom_param);
            }
        }
    }
}

void adl_fill_circle(Mat2D_uint32 screen_mat, float center_x, float center_y, float r, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (int dy = -r; dy <= r; dy++) {
        for (int dx = -r; dx <= r; dx ++) {
            float diff = dx * dx + dy * dy - r * r;
            if (diff < 0) {
                adl_draw_point(screen_mat, center_x + dx, center_y + dy, color, offset_zoom_param);
            }
        }
    }
}

void adl_draw_tri(Mat2D_uint32 screen_mat, Tri tri, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    adl_draw_line(screen_mat, tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, color, offset_zoom_param);
    adl_draw_line(screen_mat, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, color, offset_zoom_param);
    adl_draw_line(screen_mat, tri.points[2].x, tri.points[2].y, tri.points[0].x, tri.points[0].y, color, offset_zoom_param);

    // adl_draw_arrow(screen_mat, tri.points[0].x, tri.points[0].y, tri.points[1].x, tri.points[1].y, 0.3, 22, color);
    // adl_draw_arrow(screen_mat, tri.points[1].x, tri.points[1].y, tri.points[2].x, tri.points[2].y, 0.3, 22, color);
    // adl_draw_arrow(screen_mat, tri.points[2].x, tri.points[2].y, tri.points[0].x, tri.points[0].y, 0.3, 22, color);
}

/* This works but there are some artifacts */
void adl_fill_tri_scanline_rasterizer(Mat2D_uint32 screen_mat, Tri tri, Offset_zoom_param offset_zoom_param)
{
    /* This function follows the rasterizer of 'Pikuma' shown in his YouTube video. You can fine the video in this link: https://youtu.be/k5wtuKWmV48. */
    /* arranging the points according to y value */
    Point p0 = tri.points[0];
    Point p1 = tri.points[1];
    Point p2 = tri.points[2];
    if (p1.y > p0.y) {
        Point temp = p1;
        p1 = p0;
        p0 = temp;
    }
    if (p2.y > p1.y) {
        Point temp = p2;
        p2 = p1;
        p1 = temp;
        if (p1.y > p0.y) {
            Point temp = p1;
            p1 = p0;
            p0 = temp;
        }
    }
    if (p2.y > p0.y) {
        Point temp = p2;
        p2 = p0;
        p0 = temp;
    }

    /* finding max and min x */
    int x_max = fmax(p0.x, fmax(p1.x, p2.x));
    int x_min = fmin(p0.x, fmin(p1.x, p2.x));

    if (p0.x == p1.x && p1.x == p2.x) {
        adl_draw_tri(screen_mat, tri, tri.colors[0], offset_zoom_param);
        return;
    }

    /* The rasterization */
    float m01 = (p0.y - p1.y) / (p0.x - p1.x);
    float b01 = p0.y - m01 * p0.x;
    float m02 = (p0.y - p2.y) / (p0.x - p2.x);
    float b02 = p0.y - m02 * p0.x;
    float m12 = (p1.y - p2.y) / (p1.x - p2.x);
    float b12 = p1.y - m12 * p1.x;

    float epsilon = 1e-3;
    int gap = 15;
    // printf("m01: %f, m02: %f, m12: %f\n", m01, m02, m12);
    if (fabs(m02) < epsilon || fabs(m12) < epsilon || fabs(m01) < epsilon) return;
    for (int y = (int)p2.y; y < (int)p1.y; y++)
    {
        float x02 = (y - b02) / m02;
        float x12 = (y - b12) / m12;
        if (x02 <= x_min-gap || x02 >= x_max+gap) continue;
        if (x12 <= x_min-gap || x12 >= x_max+gap) continue;
        if (fabs(p0.x - p2.x) - fabs(p0.x - x02) < 0) continue;
        if (fabs(p1.x - p2.x) - fabs(p1.x - x12) < 0) continue;
        adl_draw_line(screen_mat, x02, y, x12, y, tri.colors[0], offset_zoom_param);
        // printf("x02: %d, x12: %d, y: %d\n", (int)x02, (int)x12, (int)y);
    }
    for (int y = (int)p1.y; y <= (int)p0.y; y++) {
        float x01 = (y - b01) / m01;
        float x02 = (y - b02) / m02;
        if (x01 <= x_min-gap || x01 >= x_max+gap) continue;
        if (x02 <= x_min-gap || x02 >= x_max+gap) continue;
        if (fabs(p1.x - p0.x) - fabs(p1.x - x01) < 0) continue;
        if (fabs(p0.x - p2.x) - fabs(p0.x - x02) < 0) continue;
        adl_draw_line(screen_mat, x02, y, x01, y, tri.colors[0], offset_zoom_param);
    }
}


/* This function is the function for rasterization */
void adl_fill_tri_Pinedas_rasterizer(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Tri tri, float light_intensity, Offset_zoom_param offset_zoom_param)
{
    /* This function follows the rasterizer of 'Pikuma' shown in his YouTube video. You can fine the video in this link: https://youtu.be/k5wtuKWmV48. */

    Point p0, p1, p2;
    p0 = tri.points[0];
    p1 = tri.points[1];
    p2 = tri.points[2];

    /* finding bounding box */
    int x_min = fmin(p0.x, fmin(p1.x, p2.x));
    int x_max = fmax(p0.x, fmax(p1.x, p2.x));
    int y_min = fmin(p0.y, fmin(p1.y, p2.y));
    int y_max = fmax(p0.y, fmax(p1.y, p2.y));

    /* Clamp to screen bounds */
    if (x_min < 0) x_min = 0;
    if (y_min < 0) y_min = 0;
    if (x_max >= (int)screen_mat.cols) x_max = screen_mat.cols - 1;
    if (y_max >= (int)screen_mat.rows) y_max = screen_mat.rows - 1;

    /* draw only outline of the tri if there is no area */
    float w = edge_cross_point(p0, p1, p1, p2);
    if (fabsf(w) < 1e-6) {
        adl_draw_tri(screen_mat, tri, tri.colors[0], offset_zoom_param);
        return;
    }
    // if (w < 0) { /* don't draw negative triangles */
    //     return;
    // }
    MATRIX2D_ASSERT(fabsf(w) > 1e-6 && "triangle has area");
    // MATRIX2D_ASSERT(w > 0 && "triangle is inverted");

    /* fill conventions */
    int bias0 = is_top_left(p0, p1) ? 0 : -1;
    int bias1 = is_top_left(p1, p2) ? 0 : -1;
    int bias2 = is_top_left(p2, p0) ? 0 : -1;

    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            Point p = {.x = x, .y = y, .z = 0};

            float w0 = edge_cross_point(p0, p1, p0, p) + bias0;
            float w1 = edge_cross_point(p1, p2, p1, p) + bias1;
            float w2 = edge_cross_point(p2, p0, p2, p) + bias2;

            float alpha = fabs(w1 / w);
            float beta  = fabs(w2 / w);
            float gamma = fabs(w0 / w);

            if (w0 * w >= 0 && w1 * w >= 0 &&  w2 * w >= 0) {
                int r, b, g;
                HexARGB_RGB_VAR(tri.colors[0], r, g, b);
                float rf = r * light_intensity;
                float gf = g * light_intensity;
                float bf = b * light_intensity;
                uint8_t r8 = (uint8_t)fmaxf(0, fminf(255, rf));
                uint8_t g8 = (uint8_t)fmaxf(0, fminf(255, gf));
                uint8_t b8 = (uint8_t)fmaxf(0, fminf(255, bf));

                double inv_w = alpha * (1.0 / p0.w) + beta  * (1.0 / p1.w) + gamma * (1.0 / p2.w);
                double z_over_w = alpha * (p0.z / p0.w) + beta  * (p1.z / p1.w) + gamma * (p2.z / p2.w);
                double inv_z = inv_w / z_over_w;

                if (inv_z >= MAT2D_AT(inv_z_buffer, y, x)) {
                    adl_draw_point(screen_mat, x, y, RGB_hexRGB(r8, g8, b8), offset_zoom_param);
                    MAT2D_AT(inv_z_buffer, y, x) = inv_z;
                }
            }
        }
    }
}

void adl_fill_tri_Pinedas_rasterizer_interpolate_color(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer, Tri tri, float light_intensity, Offset_zoom_param offset_zoom_param)
{
    /* This function follows the rasterizer of 'Pikuma' shown in his YouTube video. You can fine the video in this link: https://youtu.be/k5wtuKWmV48. */

    Point p0, p1, p2;
    p0 = tri.points[0];
    p1 = tri.points[1];
    p2 = tri.points[2];

    float w = edge_cross_point(p0, p1, p1, p2);
    MATRIX2D_ASSERT(w != 0 && "triangle has area");

    /* fill conventions */
    int bias0 = is_top_left(p0, p1) ? 0 : -1;
    int bias1 = is_top_left(p1, p2) ? 0 : -1;
    int bias2 = is_top_left(p2, p0) ? 0 : -1;

    /* finding bounding box */
    int x_min = fmin(p0.x, fmin(p1.x, p2.x));
    int x_max = fmax(p0.x, fmax(p1.x, p2.x));
    int y_min = fmin(p0.y, fmin(p1.y, p2.y));
    int y_max = fmax(p0.y, fmax(p1.y, p2.y));
    // printf("xmin: %d, xmax: %d || ymin: %d, ymax: %d\n", x_min, x_max, y_min, y_max);

    /* Clamp to screen bounds */
    if (x_min < 0) x_min = 0;
    if (y_min < 0) y_min = 0;
    if (x_max >= (int)screen_mat.cols) x_max = screen_mat.cols - 1;
    if (y_max >= (int)screen_mat.rows) y_max = screen_mat.rows - 1;

    for (int y = y_min; y <= y_max; y++) {
        for (int x = x_min; x <= x_max; x++) {
            // adl_draw_point(screen_mat, x, y, color);
            Point p = {.x = x, .y = y, .z = 0};

            float w0 = edge_cross_point(p0, p1, p0, p) + bias0;
            float w1 = edge_cross_point(p1, p2, p1, p) + bias1;
            float w2 = edge_cross_point(p2, p0, p2, p) + bias2;

            float alpha = fabs(w1 / w);
            float beta  = fabs(w2 / w);
            float gamma = fabs(w0 / w);
            // printf("alpha: %5f, beta: %5f, gamma: %5f\n", alpha, beta, gamma);

            if (w0 * w >= 0 && w1 * w >= 0 &&  w2 * w >= 0) {
                int r0, b0, g0;
                int r1, b1, g1;
                int r2, b2, g2;
                HexARGB_RGB_VAR(tri.colors[0], r0, g0, b0);
                HexARGB_RGB_VAR(tri.colors[1], r1, g1, b1);
                HexARGB_RGB_VAR(tri.colors[2], r2, g2, b2);
                
                uint8_t current_r = r0*alpha + r1*beta + r2*gamma;
                uint8_t current_g = g0*alpha + g1*beta + g2*gamma;
                uint8_t current_b = b0*alpha + b1*beta + b2*gamma;

                float rf = current_r * light_intensity;
                float gf = current_g * light_intensity;
                float bf = current_b * light_intensity;
                uint8_t r8 = (uint8_t)fmaxf(0, fminf(255, rf));
                uint8_t g8 = (uint8_t)fmaxf(0, fminf(255, gf));
                uint8_t b8 = (uint8_t)fmaxf(0, fminf(255, bf));

                double inv_w = alpha * (1.0 / p0.w) + beta  * (1.0 / p1.w) + gamma * (1.0 / p2.w);
                double z_over_w = alpha * (p0.z / p0.w) + beta  * (p1.z / p1.w) + gamma * (p2.z / p2.w);
                double inv_z = inv_w / z_over_w;

                if (inv_z >= MAT2D_AT(inv_z_buffer, y, x)) {
                    adl_draw_point(screen_mat, x, y, RGB_hexRGB(r8, g8, b8), offset_zoom_param);
                    MAT2D_AT(inv_z_buffer, y, x) = inv_z;
                }
            }
        }
    }
}

void adl_draw_mesh(Mat2D_uint32 screen_mat, Tri_mesh mesh, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (size_t i = 0; i < mesh.length; i++) {
        Tri tri = mesh.elements[i];
        if (tri.to_draw) {
            adl_draw_tri(screen_mat, tri, color, offset_zoom_param);
        }
    }
}

void adl_fill_mesh_scanline_rasterizer(Mat2D_uint32 screen_mat, Tri_mesh mesh, Offset_zoom_param offset_zoom_param)
{
    for (size_t i = 0; i < mesh.length; i++) {
        Tri tri = mesh.elements[i];
        if (tri.to_draw) {
            adl_fill_tri_scanline_rasterizer(screen_mat, tri, offset_zoom_param);
        }
    }
}

void adl_fill_mesh_Pinedas_rasterizer(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer_mat, Tri_mesh mesh, Offset_zoom_param offset_zoom_param)
{
    for (size_t i = 0; i < mesh.length; i++) {
        Tri tri = mesh.elements[i];
        /* Reject invalid triangles */
        adl_assert_tri_is_valid(tri);

        if (!tri.to_draw) continue;

        adl_fill_tri_Pinedas_rasterizer(screen_mat, inv_z_buffer_mat, tri, tri.light_intensity, offset_zoom_param);
    }
}

float adl_linear_map(float s, float min_in, float max_in, float min_out, float max_out)
{
    return (min_out + ((s-min_in)*(max_out-min_out))/(max_in-min_in));
}

void adl_quad2tris(Quad quad, Tri *tri1, Tri *tri2, char split_line[])
{
    if (!strncmp(split_line, "02", 2)) {
        tri1->points[0] = quad.points[0];
        tri1->points[1] = quad.points[1];
        tri1->points[2] = quad.points[2];
        tri1->to_draw = quad.to_draw;
        tri1->light_intensity = quad.light_intensity;
        tri1->colors[0] = quad.colors[0];
        tri1->colors[1] = quad.colors[1];
        tri1->colors[2] = quad.colors[2];

        tri2->points[0] = quad.points[2];
        tri2->points[1] = quad.points[3];
        tri2->points[2] = quad.points[0];
        tri2->to_draw = quad.to_draw;
        tri2->light_intensity = quad.light_intensity;
        tri2->colors[0] = quad.colors[2];
        tri2->colors[1] = quad.colors[3];
        tri2->colors[2] = quad.colors[0];
    } else if (!strncmp(split_line, "13", 2)) {
        tri1->points[0] = quad.points[1];
        tri1->points[1] = quad.points[2];
        tri1->points[2] = quad.points[3];
        tri1->to_draw = quad.to_draw;
        tri1->light_intensity = quad.light_intensity;
        tri1->colors[0] = quad.colors[1];
        tri1->colors[1] = quad.colors[2];
        tri1->colors[2] = quad.colors[3];

        tri2->points[0] = quad.points[3];
        tri2->points[1] = quad.points[0];
        tri2->points[2] = quad.points[1];
        tri2->to_draw = quad.to_draw;
        tri2->light_intensity = quad.light_intensity;
        tri2->colors[0] = quad.colors[3];
        tri2->colors[1] = quad.colors[0];
        tri2->colors[2] = quad.colors[1];
    }
}

/* L:   0  -> 1
   a: -0.5 -> 0.5
   b: -0.5 -> 0.5 */
void adl_linear_sRGB_to_okLab(uint32_t hex_ARGB, float *L, float *a, float *b)
{
    /* https://bottosson.github.io/posts/oklab/
       https://en.wikipedia.org/wiki/Oklab_color_space */
    int R_255, G_255, B_255;
    HexARGB_RGB_VAR(hex_ARGB, R_255, G_255, B_255);

    float R = R_255;
    float G = G_255;
    float B = B_255;

    float l = 0.4122214705f * R + 0.5363325363f * G + 0.0514459929f * B;
    float m = 0.2119034982f * R + 0.6806995451f * G + 0.1073969566f * B;
    float s = 0.0883024619f * R + 0.2817188376f * G + 0.6299787005f * B;

    float l_ = cbrtf(l);
    float m_ = cbrtf(m);
    float s_ = cbrtf(s);

    *L = 0.2104542553f * l_ + 0.7936177850f * m_ - 0.0040720468f * s_;
    *a = 1.9779984951f * l_ - 2.4285922050f * m_ + 0.4505937099f * s_;
    *b = 0.0259040371f * l_ + 0.7827717662f * m_ - 0.8086757660f * s_;

}

/* L:   0  -> 1
   a: -0.5 -> 0.5
   b: -0.5 -> 0.5 */
void adl_okLab_to_linear_sRGB(float L, float a, float b, uint32_t *hex_ARGB)
{
    /* https://bottosson.github.io/posts/oklab/
       https://en.wikipedia.org/wiki/Oklab_color_space */

    float l_ = L + 0.3963377774f * a + 0.2158037573f * b;
    float m_ = L - 0.1055613458f * a - 0.0638541728f * b;
    float s_ = L - 0.0894841775f * a - 1.2914855480f * b;

    float l = l_ * l_ * l_;
    float m = m_ * m_ * m_;
    float s = s_ * s_ * s_;

    float R = + 4.0767416621f * l - 3.3077115913f * m + 0.2309699292f * s;
    float G = - 1.2684380046f * l + 2.6097574011f * m - 0.3413193965f * s;
    float B = - 0.0041960863f * l - 0.7034186147f * m + 1.7076147010f * s;

    R = fmaxf(fminf(R, 255), 0);
    G = fmaxf(fminf(G, 255), 0);
    B = fmaxf(fminf(B, 255), 0);

    *hex_ARGB = RGBA_hexARGB(R, G, B, 0xFF);
}

void adl_linear_sRGB_to_okLch(uint32_t hex_ARGB, float *L, float *c, float *h_deg)
{
    float a, b;
    adl_linear_sRGB_to_okLab(hex_ARGB, L, &a, &b);

    *c = sqrtf(a * a + b * b);
    *h_deg = atan2f(b, a) * 180 / PI;
}

void adl_okLch_to_linear_sRGB(float L, float c, float h_deg, uint32_t *hex_ARGB)
{
    h_deg = fmodf((h_deg + 360), 360);
    float a = c * cosf(h_deg * PI / 180);
    float b = c * sinf(h_deg * PI / 180);
    adl_okLab_to_linear_sRGB(L, a, b, hex_ARGB);
}

void adl_interpolate_ARGBcolor_on_okLch(uint32_t color1, uint32_t color2, float t, float num_of_rotations, uint32_t *color_out)
{
    float L_1, c_1, h_1;
    float L_2, c_2, h_2;
    adl_linear_sRGB_to_okLch(color1, &L_1, &c_1, &h_1);
    adl_linear_sRGB_to_okLch(color2, &L_2, &c_2, &h_2);
    h_2 = h_2 + 360 * num_of_rotations;

    float L, c, h;
    L = L_1 * (1 - t) + L_2 * (t);
    c = c_1 * (1 - t) + c_2 * (t);
    h = h_1 * (1 - t) + h_2 * (t);
    adl_okLch_to_linear_sRGB(L, c, h, color_out);
}

Figure adl_alloc_figure(size_t rows, size_t cols, Point top_left_position)
{
    ADL_ASSERT(rows && cols);
    adl_assert_point_is_valid(top_left_position);

    Figure figure = {0};
    figure.pixels_mat = mat2D_alloc_uint32(rows, cols);
    figure.inv_z_buffer_mat = mat2D_alloc(rows, cols);
    memset(figure.inv_z_buffer_mat.elements, 0x0, sizeof(double) * figure.inv_z_buffer_mat.rows * figure.inv_z_buffer_mat.cols);
    ada_init_array(Curve, figure.src_curve_array);

    figure.top_left_position = top_left_position;

    int max_i    = (int)(figure.pixels_mat.rows);
    int max_j    = (int)(figure.pixels_mat.cols);
    int offset_i = (int)fminf(figure.pixels_mat.rows * ADL_FIGURE_PADDING_PRECENTAGE / 100.0f, ADL_MAX_FIGURE_PADDING);
    int offset_j = (int)fminf(figure.pixels_mat.cols * ADL_FIGURE_PADDING_PRECENTAGE / 100.0f, ADL_MAX_FIGURE_PADDING);

    figure.min_x_pixel = offset_j;
    figure.max_x_pixel = max_j - offset_j;
    figure.min_y_pixel = offset_i;
    figure.max_y_pixel = max_i - offset_i;

    figure.min_x = + FLT_MAX;
    figure.max_x = - FLT_MAX;
    figure.min_y = + FLT_MAX;
    figure.max_y = - FLT_MAX;

    figure.offset_zoom_param = ADL_DEFAULT_OFFSET_ZOOM;

    return figure;
}

void adl_copy_figure_to_screen(Mat2D_uint32 screen_mat, Figure figure)
{
    for (size_t i = 0; i < figure.pixels_mat.rows; i++) {
        for (size_t j = 0; j < figure.pixels_mat.cols; j++) {
            int offset_i = figure.top_left_position.y;
            int offset_j = figure.top_left_position.x;
            
            adl_draw_point(screen_mat, offset_j+j, offset_i+i, MAT2D_AT_UINT32(figure.pixels_mat, i, j), (Offset_zoom_param){1,0,0,0,0});
        }
    }
}

void adl_draw_axis_on_figure(Figure *figure)
{
    int max_i    = (int)(figure->pixels_mat.rows);
    int max_j    = (int)(figure->pixels_mat.cols);
    int offset_i = (int)fmaxf(fminf(figure->pixels_mat.rows * ADL_FIGURE_PADDING_PRECENTAGE / 100.0f, ADL_MAX_FIGURE_PADDING), ADL_MIN_FIGURE_PADDING);
    int offset_j = (int)fmaxf(fminf(figure->pixels_mat.cols * ADL_FIGURE_PADDING_PRECENTAGE / 100.0f, ADL_MAX_FIGURE_PADDING), ADL_MIN_FIGURE_PADDING);

    int arrow_head_size_x = (int)fminf(ADL_MAX_HEAD_SIZE, ADL_FIGURE_PADDING_PRECENTAGE / 100.0f * (max_j - 2 * offset_j));
    int arrow_head_size_y = (int)fminf(ADL_MAX_HEAD_SIZE, ADL_FIGURE_PADDING_PRECENTAGE / 100.0f * (max_i - 2 * offset_i));

    adl_draw_arrow(figure->pixels_mat, figure->min_x_pixel, figure->max_y_pixel, figure->max_x_pixel, figure->max_y_pixel, (float)arrow_head_size_x / (max_j-2*offset_j), ADL_FIGURE_HEAD_ANGLE_DEG, 0, figure->offset_zoom_param);
    adl_draw_arrow(figure->pixels_mat, figure->min_x_pixel, figure->max_y_pixel, figure->min_x_pixel, figure->min_y_pixel, (float)arrow_head_size_y / (max_i-2*offset_i), ADL_FIGURE_HEAD_ANGLE_DEG, 0, figure->offset_zoom_param);
    // adl_draw_rectangle_min_max(figure->pixels_mat, figure->min_x_pixel, figure->max_x_pixel, figure->min_y_pixel, figure->max_y_pixel, 0);

    figure->x_axis_head_size = arrow_head_size_x;
    figure->y_axis_head_size = arrow_head_size_y;
}

void adl_draw_max_min_values_on_figure(Figure figure)
{
    char x_min_sentence[256];
    char x_max_sentence[256];
    snprintf(x_min_sentence, 256, "%g", figure.min_x);
    snprintf(x_max_sentence, 256, "%g", figure.max_x);

    int x_sentence_hight_pixel = (figure.pixels_mat.rows - figure.max_y_pixel - ADL_MIN_CHARACTER_OFFSET * 3);
    int x_min_char_width_pixel = x_sentence_hight_pixel / 2;
    int x_max_char_width_pixel = x_sentence_hight_pixel / 2;

    int x_min_sentence_width_pixel = (int)fminf((figure.max_x_pixel - figure.min_x_pixel)/2, (x_min_char_width_pixel + ADL_MAX_CHARACTER_OFFSET)*strlen(x_min_sentence));
    x_min_char_width_pixel = x_min_sentence_width_pixel / strlen(x_min_sentence) - ADL_MIN_CHARACTER_OFFSET;

    int x_max_sentence_width_pixel = (int)fminf((figure.max_x_pixel - figure.min_x_pixel)/2, (x_max_char_width_pixel + ADL_MAX_CHARACTER_OFFSET)*strlen(x_max_sentence)) - figure.x_axis_head_size;
    x_max_char_width_pixel = (x_max_sentence_width_pixel + figure.x_axis_head_size) / strlen(x_max_sentence) - ADL_MIN_CHARACTER_OFFSET;

    int x_min_sentence_hight_pixel = (int)fminf(x_min_char_width_pixel * 2, x_sentence_hight_pixel);
    int x_max_sentence_hight_pixel = (int)fminf(x_max_char_width_pixel * 2, x_sentence_hight_pixel);

    x_min_sentence_hight_pixel = (int)fminf(x_min_sentence_hight_pixel, x_max_sentence_hight_pixel);
    x_max_sentence_hight_pixel = x_min_sentence_hight_pixel;

    int x_max_x_top_left = figure.max_x_pixel - strlen(x_max_sentence) * (x_max_sentence_hight_pixel / 2 + ADL_MIN_CHARACTER_OFFSET) - figure.x_axis_head_size;

    adl_draw_sentence(figure.pixels_mat, x_min_sentence, strlen(x_min_sentence), figure.min_x_pixel, figure.max_y_pixel+ADL_MIN_CHARACTER_OFFSET*2, x_min_sentence_hight_pixel, 0, figure.offset_zoom_param);
    adl_draw_sentence(figure.pixels_mat, x_max_sentence, strlen(x_max_sentence), x_max_x_top_left, figure.max_y_pixel+ADL_MIN_CHARACTER_OFFSET*2, x_max_sentence_hight_pixel, 0, figure.offset_zoom_param);
    
    char y_min_sentence[256];
    char y_max_sentence[256];
    snprintf(y_min_sentence, 256, "%g", figure.min_y);
    snprintf(y_max_sentence, 256, "%g", figure.max_y);

    int y_sentence_width_pixel = figure.min_x_pixel - ADL_MAX_CHARACTER_OFFSET - figure.y_axis_head_size;
    int y_max_char_width_pixel = y_sentence_width_pixel;
    y_max_char_width_pixel /= strlen(y_max_sentence);
    int y_max_sentence_hight_pixel = y_max_char_width_pixel * 2;

    int y_min_char_width_pixel = y_sentence_width_pixel;
    y_min_char_width_pixel /= strlen(y_min_sentence);
    int y_min_sentence_hight_pixel = y_min_char_width_pixel * 2;

    y_min_sentence_hight_pixel = (int)fmaxf(fminf(y_min_sentence_hight_pixel, y_max_sentence_hight_pixel), 1);
    y_max_sentence_hight_pixel = y_min_sentence_hight_pixel;

    adl_draw_sentence(figure.pixels_mat, y_max_sentence, strlen(y_max_sentence), ADL_MAX_CHARACTER_OFFSET/2, figure.min_y_pixel, y_max_sentence_hight_pixel, 0, figure.offset_zoom_param);
    adl_draw_sentence(figure.pixels_mat, y_min_sentence, strlen(y_min_sentence), ADL_MAX_CHARACTER_OFFSET/2, figure.max_y_pixel-y_min_sentence_hight_pixel, y_min_sentence_hight_pixel, 0, figure.offset_zoom_param);
}


void adl_add_curve_to_figure(Figure *figure, Point *src_points, size_t src_len, uint32_t color)
{
    Curve src_points_ada;
    ada_init_array(Point, src_points_ada);
    src_points_ada.color = color;

    for (size_t i = 0; i < src_len; i++) {
        Point current_point = src_points[i];
        if (current_point.x > figure->max_x) {
            figure->max_x = current_point.x;
        }
        if (current_point.y > figure->max_y) {
            figure->max_y = current_point.y;
        }
        if (current_point.x < figure->min_x) {
            figure->min_x = current_point.x;
        }
        if (current_point.y < figure->min_y) {
            figure->min_y = current_point.y;
        }
        ada_appand(Point, src_points_ada, current_point);
    }
    
    ada_appand(Curve, figure->src_curve_array, src_points_ada);
}

void adl_plot_curves_on_figure(Figure figure)
{
    mat2D_fill_uint32(figure.pixels_mat, figure.background_color);
    memset(figure.inv_z_buffer_mat.elements, 0x0, sizeof(double) * figure.inv_z_buffer_mat.rows * figure.inv_z_buffer_mat.cols);
    if (figure.to_draw_axis) adl_draw_axis_on_figure(&figure);

    for (size_t curve_index = 0; curve_index < figure.src_curve_array.length; curve_index++) {
        size_t src_len = figure.src_curve_array.elements[curve_index].length;
        Point *src_points = figure.src_curve_array.elements[curve_index].elements;
        for (size_t i = 0; i < src_len-1; i++) {
            Point src_start = src_points[i];
            Point src_end   = src_points[i+1];
            Point des_start = {0};
            Point des_end = {0};

            des_start.x = adl_linear_map(src_start.x, figure.min_x, figure.max_x, figure.min_x_pixel, figure.max_x_pixel);
            des_start.y = ((figure.max_y_pixel + figure.min_y_pixel) - adl_linear_map(src_start.y, figure.min_y, figure.max_y, figure.min_y_pixel, figure.max_y_pixel));

            des_end.x = adl_linear_map(src_end.x, figure.min_x, figure.max_x, figure.min_x_pixel, figure.max_x_pixel);
            des_end.y = ((figure.max_y_pixel + figure.min_y_pixel) - adl_linear_map(src_end.y, figure.min_y, figure.max_y, figure.min_y_pixel, figure.max_y_pixel));

            adl_draw_line(figure.pixels_mat, des_start.x, des_start.y, des_end.x, des_end.y, figure.src_curve_array.elements[curve_index].color, figure.offset_zoom_param);
        }
    }

    if (figure.to_draw_max_min_values) {
        char x_min_sentence[256];
        char x_max_sentence[256];
        snprintf(x_min_sentence, 256, "%g", figure.min_x);
        snprintf(x_max_sentence, 256, "%g", figure.max_x);

        int x_sentence_hight_pixel = (figure.pixels_mat.rows - figure.max_y_pixel - ADL_MIN_CHARACTER_OFFSET * 3);
        int x_min_char_width_pixel = x_sentence_hight_pixel / 2;
        int x_max_char_width_pixel = x_sentence_hight_pixel / 2;

        int x_min_sentence_width_pixel = (int)fminf((figure.max_x_pixel - figure.min_x_pixel)/2, (x_min_char_width_pixel + ADL_MAX_CHARACTER_OFFSET)*strlen(x_min_sentence));
        x_min_char_width_pixel = x_min_sentence_width_pixel / strlen(x_min_sentence) - ADL_MIN_CHARACTER_OFFSET;

        int x_max_sentence_width_pixel = (int)fminf((figure.max_x_pixel - figure.min_x_pixel)/2, (x_max_char_width_pixel + ADL_MAX_CHARACTER_OFFSET)*strlen(x_max_sentence)) - figure.x_axis_head_size;
        x_max_char_width_pixel = (x_max_sentence_width_pixel + figure.x_axis_head_size) / strlen(x_max_sentence) - ADL_MIN_CHARACTER_OFFSET;

        int x_min_sentence_hight_pixel = (int)fminf(x_min_char_width_pixel * 2, x_sentence_hight_pixel);
        int x_max_sentence_hight_pixel = (int)fminf(x_max_char_width_pixel * 2, x_sentence_hight_pixel);

        x_min_sentence_hight_pixel = (int)fminf(x_min_sentence_hight_pixel, x_max_sentence_hight_pixel);
        x_max_sentence_hight_pixel = x_min_sentence_hight_pixel;

        int x_max_x_top_left = figure.max_x_pixel - strlen(x_max_sentence) * (x_max_sentence_hight_pixel / 2 + ADL_MIN_CHARACTER_OFFSET) - figure.x_axis_head_size;

        adl_draw_sentence(figure.pixels_mat, x_min_sentence, strlen(x_min_sentence), figure.min_x_pixel, figure.max_y_pixel+ADL_MIN_CHARACTER_OFFSET*2, x_min_sentence_hight_pixel, 0, figure.offset_zoom_param);
        adl_draw_sentence(figure.pixels_mat, x_max_sentence, strlen(x_max_sentence), x_max_x_top_left, figure.max_y_pixel+ADL_MIN_CHARACTER_OFFSET*2, x_max_sentence_hight_pixel, 0, figure.offset_zoom_param);
        
        char y_min_sentence[256];
        char y_max_sentence[256];
        snprintf(y_min_sentence, 256, "%g", figure.min_y);
        snprintf(y_max_sentence, 256, "%g", figure.max_y);

        int y_sentence_width_pixel = figure.min_x_pixel - ADL_MAX_CHARACTER_OFFSET - figure.y_axis_head_size;
        int y_max_char_width_pixel = y_sentence_width_pixel;
        y_max_char_width_pixel /= strlen(y_max_sentence);
        int y_max_sentence_hight_pixel = y_max_char_width_pixel * 2;

        int y_min_char_width_pixel = y_sentence_width_pixel;
        y_min_char_width_pixel /= strlen(y_min_sentence);
        int y_min_sentence_hight_pixel = y_min_char_width_pixel * 2;

        y_min_sentence_hight_pixel = (int)fmaxf(fminf(y_min_sentence_hight_pixel, y_max_sentence_hight_pixel), 1);
        y_max_sentence_hight_pixel = y_min_sentence_hight_pixel;

        adl_draw_sentence(figure.pixels_mat, y_max_sentence, strlen(y_max_sentence), ADL_MAX_CHARACTER_OFFSET/2, figure.min_y_pixel, y_max_sentence_hight_pixel, 0, figure.offset_zoom_param);
        adl_draw_sentence(figure.pixels_mat, y_min_sentence, strlen(y_min_sentence), ADL_MAX_CHARACTER_OFFSET/2, figure.max_y_pixel-y_min_sentence_hight_pixel, y_min_sentence_hight_pixel, 0, figure.offset_zoom_param);
    }
}

/* check offset2D. might convert it to a Mat2D */
#define adl_offset2d(i, j, ni) (j) * (ni) + (i)
void adl_interp_scalar_2D_on_figure(Figure figure, double *x_2Dmat, double *y_2Dmat, double *scalar_2Dmat, int ni, int nj, char color_scale[], float num_of_rotations)
{
    mat2D_fill_uint32(figure.pixels_mat, figure.background_color);
    memset(figure.inv_z_buffer_mat.elements, 0x0, sizeof(double) * figure.inv_z_buffer_mat.rows * figure.inv_z_buffer_mat.cols);
    if (figure.to_draw_axis) adl_draw_axis_on_figure(&figure);

    float min_scalar = FLT_MAX; 
    float max_scalar = FLT_MIN; 
    for (int i = 0; i < ni; i++) {
        for (int j = 0; j < nj; j++) {
            float val = scalar_2Dmat[adl_offset2d(i, j, ni)];
            if (val > max_scalar) max_scalar = val;
            if (val < min_scalar) min_scalar = val;
            float current_x = x_2Dmat[adl_offset2d(i, j, ni)];
            float current_y = y_2Dmat[adl_offset2d(i, j, ni)];
            if (current_x > figure.max_x) {
                figure.max_x = current_x;
            }
            if (current_y > figure.max_y) {
                figure.max_y = current_y;
            }
            if (current_x < figure.min_x) {
                figure.min_x = current_x;
            }
            if (current_y < figure.min_y) {
                figure.min_y = current_y;
            }
        }
    }

    float window_w = (float)figure.pixels_mat.cols;
    float window_h = (float)figure.pixels_mat.rows;

    for (int i = 0; i < ni-1; i++) {
        for (int j = 0; j < nj-1; j++) {
            Quad quad = {0};
            quad.light_intensity = 1;
            quad.to_draw = 1;

            quad.points[3].x = x_2Dmat[adl_offset2d(i  , j  , ni)];
            quad.points[3].y = y_2Dmat[adl_offset2d(i  , j  , ni)];
            quad.points[2].x = x_2Dmat[adl_offset2d(i+1, j  , ni)];
            quad.points[2].y = y_2Dmat[adl_offset2d(i+1, j  , ni)];
            quad.points[1].x = x_2Dmat[adl_offset2d(i+1, j+1, ni)];
            quad.points[1].y = y_2Dmat[adl_offset2d(i+1, j+1, ni)];
            quad.points[0].x = x_2Dmat[adl_offset2d(i  , j+1, ni)];
            quad.points[0].y = y_2Dmat[adl_offset2d(i  , j+1, ni)];

            for (int p_index = 0; p_index < 4; p_index++) {
                quad.points[p_index].z = 1;
                quad.points[p_index].w = 1;
                quad.points[p_index].x = adl_linear_map(quad.points[p_index].x, figure.min_x, figure.max_x, figure.min_x_pixel, figure.max_x_pixel);
                quad.points[p_index].y = ((figure.max_y_pixel + figure.min_y_pixel) - adl_linear_map(quad.points[p_index].y, figure.min_y, figure.max_y, figure.min_y_pixel, figure.max_y_pixel));

                adl_offset_zoom_point(quad.points[p_index], window_w, window_h, figure.offset_zoom_param);
            }

            float t3 = adl_linear_map(scalar_2Dmat[adl_offset2d(i  , j  , ni)], min_scalar, max_scalar, 0, 1);
            float t2 = adl_linear_map(scalar_2Dmat[adl_offset2d(i+1, j  , ni)], min_scalar, max_scalar, 0, 1);
            float t1 = adl_linear_map(scalar_2Dmat[adl_offset2d(i+1, j+1, ni)], min_scalar, max_scalar, 0, 1);
            float t0 = adl_linear_map(scalar_2Dmat[adl_offset2d(  i, j+1, ni)], min_scalar, max_scalar, 0, 1);

            /* https://en.wikipedia.org/wiki/Oklab_color_space */
            if (!strcmp(color_scale, "b-c")) {
                uint32_t color = 0, color1 = BLUE_hexARGB, color2 = CYAN_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "b-g")) {
                uint32_t color = 0, color1 = BLUE_hexARGB, color2 = GREEN_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "b-r")) {
                uint32_t color = 0, color1 = BLUE_hexARGB, color2 = RED_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "b-y")) {
                uint32_t color = 0, color1 = BLUE_hexARGB, color2 = YELLOW_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "g-y")) {
                uint32_t color = 0, color1 = GREEN_hexARGB, color2 = YELLOW_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "g-p")) {
                uint32_t color = 0, color1 = GREEN_hexARGB, color2 = PURPLE_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "g-r")) {
                uint32_t color = 0, color1 = GREEN_hexARGB, color2 = RED_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            } else if (!strcmp(color_scale, "r-y")) {
                uint32_t color = 0, color1 = RED_hexARGB, color2 = YELLOW_hexARGB;
                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t0, num_of_rotations, &color);
                quad.colors[0] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t1, num_of_rotations, &color);
                quad.colors[1] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t2, num_of_rotations, &color);
                quad.colors[2] = color;

                adl_interpolate_ARGBcolor_on_okLch(color1, color2, t3, num_of_rotations, &color);
                quad.colors[3] = color;
            }


            adl_fill_quad_interpolate_color_mean_value(figure.pixels_mat, figure.inv_z_buffer_mat, quad, ADL_DEFAULT_OFFSET_ZOOM); 
        }
    }

    if (figure.to_draw_max_min_values) {
        adl_draw_max_min_values_on_figure(figure);
    }

}

Grid adl_create_square_grid(float min_e1, float max_e1, float min_e2, float max_e2, int num_samples_e1, int num_samples_e2, char plane[], float third_direction_position)
{
    Grid grid;
    ada_init_array(Curve, grid.curves);

    grid.min_e1 = min_e1;
    grid.max_e1 = max_e1;
    grid.min_e2 = min_e2;
    grid.max_e2 = max_e2;
    grid.num_samples_e1 = num_samples_e1;
    grid.num_samples_e2 = num_samples_e2;
    strncpy(grid.plane, plane, 2);

    float del_e1 = (max_e1 - min_e1) / num_samples_e1;
    float del_e2 = (max_e2 - min_e2) / num_samples_e2;


    if (!strncmp(plane, "XY", 3)) {
        for (int e1_index = 0; e1_index <= num_samples_e1; e1_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = min_e1 + e1_index * del_e1;
            point_min.y = min_e2;
            point_min.z = third_direction_position;

            point_max.x = min_e1 + e1_index * del_e1;
            point_max.y = max_e2;
            point_max.z = third_direction_position;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
        for (int e2_index = 0; e2_index <= num_samples_e2; e2_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = min_e1;
            point_min.y = min_e2 + e2_index * del_e2;
            point_min.z = third_direction_position;

            point_max.x = max_e1;
            point_max.y = min_e2 + e2_index * del_e2;
            point_max.z = third_direction_position;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
    } else if (!strncmp(plane, "XZ", 3)) {
        for (int e1_index = 0; e1_index <= num_samples_e1; e1_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = min_e1 + e1_index * del_e1;
            point_min.y = third_direction_position;
            point_min.z = min_e2;

            point_max.x = min_e1 + e1_index * del_e1;
            point_max.y = third_direction_position;
            point_max.z = max_e2;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
        for (int e2_index = 0; e2_index <= num_samples_e2; e2_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = min_e1;
            point_min.y = third_direction_position;
            point_min.z = min_e2 + e2_index * del_e2;

            point_max.x = max_e1;
            point_max.y = third_direction_position;
            point_max.z = min_e2 + e2_index * del_e2;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
    } else if (!strncmp(plane, "YZ", 3)) {
        for (int e1_index = 0; e1_index <= num_samples_e1; e1_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = third_direction_position;
            point_min.y = min_e1 + e1_index * del_e1;
            point_min.z = min_e2;

            point_max.x = third_direction_position;
            point_max.y = min_e1 + e1_index * del_e1;
            point_max.z = max_e2;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
        for (int e2_index = 0; e2_index <= num_samples_e2; e2_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = third_direction_position;
            point_min.y = min_e1;
            point_min.z = min_e2 + e2_index * del_e2;

            point_max.x = third_direction_position;
            point_max.y = max_e1;
            point_max.z = min_e2 + e2_index * del_e2;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
    } else if (!strncmp(plane, "ZY", 3)) {
        for (int e1_index = 0; e1_index <= num_samples_e1; e1_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = third_direction_position;
            point_min.y = min_e2;
            point_min.z = min_e1 + e1_index * del_e1;

            point_max.x = third_direction_position;
            point_max.y = max_e2;
            point_max.z = min_e1 + e1_index * del_e1;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
        for (int e2_index = 0; e2_index <= num_samples_e2; e2_index++) {
            Curve curve;
            ada_init_array(Point, curve);
            Point point_max = {0}, point_min = {0};

            point_min.x = third_direction_position;
            point_min.y = min_e2 + e2_index * del_e2;
            point_min.z = min_e1;

            point_max.x = third_direction_position;
            point_max.y = min_e2 + e2_index * del_e2;
            point_max.z = max_e1;

            ada_appand(Point, curve, point_min);
            ada_appand(Point, curve, point_max);

            ada_appand(Curve, grid.curves, curve);
        }
    }

    return grid;
}

void adl_draw_grid(Mat2D_uint32 screen_mat, Grid grid, uint32_t color, Offset_zoom_param offset_zoom_param)
{
    for (size_t curve_index = 0; curve_index < grid.curves.length; curve_index++) {
        adl_draw_lines(screen_mat, grid.curves.elements[curve_index].elements, grid.curves.elements[curve_index].length, color, offset_zoom_param);
    }
}

#endif /*ALMOG_DRAW_LIBRARY_IMPLEMENTATION*/
