/* This code is heavily inspired by the 3D engine of 'OneLoneCoder' in C++.
you can find the source code in:
https://github.com/OneLoneCoder/Javidx9/tree/master/ConsoleGameEngine/BiggerProjects/Engine3D .
featured in this video of his:
https://youtu.be/ih20l3pJoeU?si=CzQ8rjk5ZEOlqEHN. */ 


#ifndef ALMOG_ENGINE_H_
#define ALMOG_ENGINE_H_

#include "./Almog_Dynamic_Array.h"
#include "./Matrix2D.h"
#include "./Almog_Draw_Library.h"

#ifndef ALMOG_STRING_MANIPULATION_IMPLEMENTATION
#define ALMOG_STRING_MANIPULATION_IMPLEMENTATION
#endif
#include "./Almog_String_Manipulation.h"

#ifndef AE_ASSERT
#include <assert.h>
#define AE_ASSERT assert
#endif

#include <math.h>
#include <stdbool.h>
#include <float.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>

#ifndef PI
#define PI M_PI
#endif

#ifndef STL_HEADER_SIZE
#define STL_HEADER_SIZE 80
#endif

#ifndef STL_NUM_SIZE
#define STL_NUM_SIZE 4
#endif

#ifndef STL_SIZE_FOREACH_TRI
#define STL_SIZE_FOREACH_TRI 50
#endif

#ifndef STL_ATTRIBUTE_BITS_SIZE
#define STL_ATTRIBUTE_BITS_SIZE 2
#endif

#ifndef HexARGB_RGBA
#define HexARGB_RGBA(x) ((x)>>(8*2)&0xFF), ((x)>>(8*1)&0xFF), ((x)>>(8*0)&0xFF), ((x)>>(8*3)&0xFF)
#endif
#ifndef HexARGB_RGBA_VAR
#define HexARGB_RGBA_VAR(x) uint8_t r = ((x)>>(8*2)&0xFF); uint8_t g = ((x)>>(8*1)&0xFF); uint8_t b = ((x)>>(8*0)&0xFF); uint8_t a = ((x)>>(8*3)&0xFF)
#endif
#define ARGB_hexARGB(a, r, g, b) 0x01000000*(a) + 0x00010000*(r) + 0x00000100*(g) + 0x00000001*(b)
#ifndef RGB_hexRGB
#define RGB_hexRGB(r, g, b) (int)(0x010000*(int)(r) + 0x000100*(int)(g) + 0x000001*(int)(b))
#endif

#define AE_MAX_POINT_VAL 1e5
#define ae_assert_point_is_valid(p) AE_ASSERT(isfinite(p.x) && isfinite(p.y) && isfinite(p.z) && isfinite(p.w));    \
        AE_ASSERT(p.x > -AE_MAX_POINT_VAL && p.x < AE_MAX_POINT_VAL);                                                                  \
        AE_ASSERT(p.y > -AE_MAX_POINT_VAL && p.y < AE_MAX_POINT_VAL);                                                                  \
        AE_ASSERT(p.z > -AE_MAX_POINT_VAL && p.z < AE_MAX_POINT_VAL);                                                                  \
        AE_ASSERT(p.w > -AE_MAX_POINT_VAL && p.w < AE_MAX_POINT_VAL);
#define ae_assert_tri_is_valid(tri) ae_assert_point_is_valid((tri).points[0]);  \
        ae_assert_point_is_valid((tri).points[1]);                              \
        ae_assert_point_is_valid((tri).points[2])
#define ae_assert_quad_is_valid(quad) ae_assert_point_is_valid((quad).points[0]);   \
        ae_assert_point_is_valid((quad).points[1]);                                 \
        ae_assert_point_is_valid((quad).points[2]);                                 \
        ae_assert_point_is_valid((quad).points[3])


#ifndef TRI_MESH_ARRAY
#define TRI_MESH_ARRAY
typedef struct {
    size_t length;
    size_t capacity;
    Tri_mesh *elements;
} Tri_mesh_array; /* Tri_mesh ada array */
#endif

#ifndef QUAD_MESH_ARRAY
#define QUAD_MESH_ARRAY
typedef struct {
    size_t length;
    size_t capacity;
    Quad_mesh *elements;
} Quad_mesh_array; /* Quad_mesh ada array */
#endif

typedef struct {
    Mat2D init_position;
    Mat2D current_position;
    Mat2D offset_position;
    Mat2D direction;
    float z_near;
    float z_far;
    float fov_deg;
    float aspect_ratio;
    float roll_offset_deg;
    float pitch_offset_deg;
    float yaw_offset_deg;
    Mat2D camera_x;
    Mat2D camera_y;
    Mat2D camera_z;
} Camera;

typedef struct {
    Tri_mesh_array in_world_tri_meshes;
    Tri_mesh_array projected_tri_meshes;
    Tri_mesh_array original_tri_meshes;

    Quad_mesh_array in_world_quad_meshes;
    Quad_mesh_array projected_quad_meshes;
    Quad_mesh_array original_quad_meshes;

    Camera camera;
    Mat2D up_direction;
    Mat2D light_direction;
    Mat2D proj_mat;
    Mat2D view_mat;
} Scene;

Tri ae_create_tri(Point p1, Point p2, Point p3);
void ae_create_copy_of_tri_mesh(Tri_mesh *des, Tri *src_elements, size_t len);
Tri_mesh ae_create_cube_tri_mesh(const size_t len, uint32_t color);

void ae_init_camera(Scene *scene, int window_h, int window_w);
Scene ae_init_scene(int window_h, int window_w);
void ae_reset_camera_pos(Scene *scene);

void ae_point_to_mat2D(Point p, Mat2D m);
Point ae_mat2D_to_point(Mat2D m);
Tri_mesh ae_get_tri_mesh_from_obj_file(char *file_path);
Tri_mesh ae_get_tri_mesh_from_stl_file(char *file_path);
void ae_appand_copy_of_tri_mesh(Tri_mesh_array *mesh_array, Tri_mesh mesh);
Tri_mesh ae_get_tri_mesh_from_quad_mesh(Quad_mesh q_mesh);

void ae_print_points(Curve p);
void ae_print_tri(Tri tri, char *name, size_t padding);
void ae_print_tri_mesh(Tri_mesh mesh, char *name, size_t padding);

void ae_calc_normal_to_tri(Mat2D normal, Tri tri);
void ae_calc_normal_to_quad(Mat2D normal, Quad quad);
void ae_translate_tri_mesh(Tri_mesh mesh, float x, float y, float z);
void ae_rotate_tri_mesh_Euler_xyz(Tri_mesh mesh, float phi_deg, float theta_deg, float psi_deg);
void ae_set_tri_mesh_bounding_box(Tri_mesh mesh, float *x_min, float *x_max, float *y_min, float *y_max, float *z_min, float *z_max);
void ae_set_tri_center_zmin_zmax(Tri *tri);
void ae_normalize_tri_mesh(Tri_mesh mesh);

Point ae_line_itersect_plane(Mat2D plane_p, Mat2D plane_n, Mat2D line_start, Mat2D line_end, float *t);
float signed_dist_point_and_plane(Point p, Mat2D plane_p, Mat2D plane_n);
int ae_tri_clip_with_plane(Tri tri_in, Mat2D plane_p, Mat2D plane_n, Tri *tri_out1, Tri *tri_out2);
int ae_quad_clip_with_plane(Quad quad_in, Mat2D plane_p, Mat2D plane_n, Quad *quad_out);

void ae_set_projection_mat(Mat2D proj_mat,float aspect_ratio, float FOV_deg, float z_near, float z_far);
void ae_set_view_mat(Mat2D view_mat, Camera camera, Mat2D up);
Point ae_project_point_world2screen(Mat2D view_mat, Mat2D proj_mat, Point src, int window_w, int window_h);
Point ae_project_point_world2view(Mat2D view_mat, Point src);
Point ae_project_point_view2screen(Mat2D proj_mat, Point src, int window_w, int window_h);
Tri ae_transform_tri_to_view(Mat2D view_mat, Tri tri);
Quad ae_transform_quad_to_view(Mat2D view_mat, Quad quad);
Tri_mesh ae_project_tri_world2screen(Mat2D proj_mat, Mat2D view_mat, Tri tri, int window_w, int window_h, Mat2D light_direction, Scene *scene);
void ae_project_tri_mesh_world2screen(Mat2D proj_mat, Mat2D view_mat, Tri_mesh *des, Tri_mesh src, int window_w, int window_h, Mat2D light_direction, Scene *scene);
Quad_mesh ae_project_quad_world2screen(Mat2D proj_mat, Mat2D view_mat, Quad quad, int window_w, int window_h, Mat2D light_direction, Scene *scene);
void ae_project_quad_mesh_world2screen(Mat2D proj_mat, Mat2D view_mat, Quad_mesh *des, Quad_mesh src, int window_w, int window_h, Mat2D light_direction, Scene *scene);
void ae_project_grid_world2screen(Mat2D proj_mat, Mat2D view_mat, Grid des, Grid src, int window_w, int window_h);

void ae_swap_tri(Tri *v, int i, int j);
bool ae_compare_tri(Tri t1, Tri t2);
void ae_qsort_tri(Tri *v, int left, int right);
double ae_linear_map(double s, double min_in, double max_in, double min_out, double max_out);
void ae_copy_z_buffer_to_screen(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer);

#endif /* ALMOG_ENGINE_H_ */

#ifdef ALMOG_ENGINE_IMPLEMENTATION
#undef ALMOG_ENGINE_IMPLEMENTATION

#define AE_PRINT_TRI(tri) ae_print_tri(tri, #tri, 0)
#define AE_PRINT_MESH(mesh) ae_print_tri_mesh(mesh, #mesh, 0)

Tri ae_create_tri(Point p1, Point p2, Point p3)
{
    Tri tri;

    tri.points[0] = p1;
    tri.points[1] = p2;
    tri.points[2] = p3;

    return tri;
}

void ae_create_copy_of_tri_mesh(Tri_mesh *des, Tri *src_elements, size_t len)
{
    Tri_mesh temp_des = *des;
    for (size_t i = 0; i < len; i++) {
        ada_appand(Tri, temp_des, src_elements[i]);
    }
    *des = temp_des;
}

Tri_mesh ae_create_cube_tri_mesh(const size_t len, uint32_t color)
{
    Tri_mesh cube;

    ada_init_array(Tri, cube);

    Tri tri1 = { /* south */
        .points[0].x = 0,
        .points[0].y = 0,
        .points[0].z = 0,

        .points[1].x = 0,
        .points[1].y = len,
        .points[1].z = 0,

        .points[2].x = len,
        .points[2].y = len,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri1);
    Tri tri2 = {
        .points[0].x = len,
        .points[0].y = len,
        .points[0].z = 0,

        .points[1].x = len,
        .points[1].y = 0,
        .points[1].z = 0,

        .points[2].x = 0,
        .points[2].y = 0,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri2);
    Tri tri3 = { /* north */
        .points[0].x = len,
        .points[0].y = 0,
        .points[0].z = len,

        .points[1].x = len,
        .points[1].y = len,
        .points[1].z = len,

        .points[2].x = 0,
        .points[2].y = len,
        .points[2].z = len,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri3);
    Tri tri4 = {
        .points[0].x = len,
        .points[0].y = 0,
        .points[0].z = len,

        .points[1].x = 0,
        .points[1].y = len,
        .points[1].z = len,

        .points[2].x = 0,
        .points[2].y = 0,
        .points[2].z = len,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri4);
    Tri tri5 = { /* east */
        .points[0].x = len,
        .points[0].y = 0,
        .points[0].z = 0,

        .points[1].x = len,
        .points[1].y = len,
        .points[1].z = 0,

        .points[2].x = len,
        .points[2].y = len,
        .points[2].z = len,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri5);
    Tri tri6 = {
        .points[0].x = len,
        .points[0].y = 0,
        .points[0].z = 0,

        .points[1].x = len,
        .points[1].y = len,
        .points[1].z = len,

        .points[2].x = len,
        .points[2].y = 0,
        .points[2].z = len,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri6);
    Tri tri7 = { /* west */
        .points[0].x = 0,
        .points[0].y = 0,
        .points[0].z = len,

        .points[1].x = 0,
        .points[1].y = len,
        .points[1].z = len,

        .points[2].x = 0,
        .points[2].y = len,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri7);
    Tri tri8 = {
        .points[0].x = 0,
        .points[0].y = 0,
        .points[0].z = len,

        .points[1].x = 0,
        .points[1].y = len,
        .points[1].z = 0,

        .points[2].x = 0,
        .points[2].y = 0,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri8);
    Tri tri9 = { /* top */
        .points[0].x = 0,
        .points[0].y = len,
        .points[0].z = 0,

        .points[1].x = 0,
        .points[1].y = len,
        .points[1].z = len,

        .points[2].x = len,
        .points[2].y = len,
        .points[2].z = len,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri9);
    Tri tri10 = {
        .points[0].x = 0,
        .points[0].y = len,
        .points[0].z = 0,

        .points[1].x = len,
        .points[1].y = len,
        .points[1].z = len,

        .points[2].x = len,
        .points[2].y = len,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri10);
    Tri tri11 = { /* bottom */
        .points[0].x = len,
        .points[0].y = 0,
        .points[0].z = len,

        .points[1].x = 0,
        .points[1].y = 0,
        .points[1].z = len,

        .points[2].x = 0,
        .points[2].y = 0,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri11);
    Tri tri12 = {
        .points[0].x = len,
        .points[0].y = 0,
        .points[0].z = len,

        .points[1].x = 0,
        .points[1].y = 0,
        .points[1].z = 0,

        .points[2].x = len,
        .points[2].y = 0,
        .points[2].z = 0,
        .to_draw = true,
        .colors = {color, color, color},
    };
    ada_appand(Tri, cube, tri12);
    
    return cube;
}

void ae_init_camera(Scene *scene, int window_h, int window_w)
{
    scene->camera.z_near       = 0.1;
    scene->camera.z_far        = 1000;
    scene->camera.fov_deg      = 60;
    scene->camera.aspect_ratio = (float)window_h / (float)window_w;

    scene->camera.init_position = mat2D_alloc(3, 1);
    mat2D_fill(scene->camera.init_position, 0);
    MAT2D_AT(scene->camera.init_position, 2, 0) = -4;

    scene->camera.current_position = mat2D_alloc(3, 1);
    mat2D_copy(scene->camera.current_position, scene->camera.init_position);

    scene->camera.offset_position = mat2D_alloc(3, 1);
    mat2D_fill(scene->camera.offset_position, 0);

    scene->camera.roll_offset_deg = 0;
    scene->camera.pitch_offset_deg = 0;
    scene->camera.yaw_offset_deg = 0;

    scene->camera.direction = mat2D_alloc(3, 1);
    mat2D_fill(scene->camera.direction, 0);
    MAT2D_AT(scene->camera.direction, 2, 0) = 1;

    scene->camera.camera_x = mat2D_alloc(3, 1);
    mat2D_fill(scene->camera.camera_x, 0);
    MAT2D_AT(scene->camera.camera_x, 0, 0) = 1;
    
    scene->camera.camera_y = mat2D_alloc(3, 1);
    mat2D_fill(scene->camera.camera_y, 0);
    MAT2D_AT(scene->camera.camera_y, 1, 0) = 1;

    scene->camera.camera_z = mat2D_alloc(3, 1);
    mat2D_fill(scene->camera.camera_z, 0);
    MAT2D_AT(scene->camera.camera_z, 2, 0) = 1;
}

Scene ae_init_scene(int window_h, int window_w)
{
    Scene scene;
    ae_init_camera(&(scene), window_h, window_w);

    scene.up_direction = mat2D_alloc(3, 1);
    mat2D_fill(scene.up_direction, 0);
    MAT2D_AT(scene.up_direction, 1, 0) = 1;

    scene.light_direction = mat2D_alloc(3, 1);
    mat2D_fill(scene.light_direction, 0);
    MAT2D_AT(scene.light_direction, 1, 0) = -1;
    MAT2D_AT(scene.light_direction, 2, 0) = -1;
    mat2D_normalize(scene.light_direction);

    scene.proj_mat = mat2D_alloc(4, 4);
    ae_set_projection_mat(scene.proj_mat, scene.camera.aspect_ratio, scene.camera.fov_deg, scene.camera.z_near, scene.camera.z_far);

    scene.view_mat = mat2D_alloc(4, 4);
    ae_set_view_mat(scene.view_mat, scene.camera, scene.up_direction);

    return scene;
}

void ae_reset_camera_pos(Scene *scene)
{
    scene->camera.roll_offset_deg = 0;
    scene->camera.pitch_offset_deg = 0;
    scene->camera.yaw_offset_deg = 0;

    mat2D_fill(scene->camera.offset_position, 0);

    mat2D_fill(scene->camera.camera_x, 0);
    MAT2D_AT(scene->camera.camera_x, 0, 0) = 1;
    mat2D_fill(scene->camera.camera_y, 0);
    MAT2D_AT(scene->camera.camera_y, 1, 0) = 1;
    mat2D_fill(scene->camera.camera_z, 0);
    MAT2D_AT(scene->camera.camera_z, 2, 0) = 1;

    mat2D_copy(scene->camera.current_position, scene->camera.init_position);
}


void ae_point_to_mat2D(Point p, Mat2D m)
{
    MATRIX2D_ASSERT((3 == m.rows && 1 == m.cols) || (1 == m.rows && 3 == m.cols));
    
    if (3 == m.rows) {
        MAT2D_AT(m, 0, 0) = p.x;
        MAT2D_AT(m, 1, 0) = p.y;
        MAT2D_AT(m, 2, 0) = p.z;
    }
    if (3 == m.cols) {
        MAT2D_AT(m, 0, 0) = p.x;
        MAT2D_AT(m, 0, 1) = p.y;
        MAT2D_AT(m, 0, 2) = p.z;
    }
}

Point ae_mat2D_to_point(Mat2D m)
{
    Point res = {.x = MAT2D_AT(m, 0, 0), .y = MAT2D_AT(m, 1, 0), .z = MAT2D_AT(m, 2, 0)};
    return res;
}

Tri_mesh ae_get_mesh_from_file(char *file_path)
{
    char file_extention[MAX_LEN_LINE], temp_word[MAX_LEN_LINE];

    strncpy(file_extention, file_path, MAX_LEN_LINE);

    int num_of_dots;
    while ((num_of_dots = asm_str_in_str(file_extention, ".")) >= 1) {
        asm_get_word_and_cut(temp_word, file_extention, '.');
    }

    if (!(!strncmp(file_extention, "obj", 3) || !strncmp(file_extention, "STL", 3) || !strncmp(file_extention, "stl", 3))) {
        fprintf(stderr, "%s:%d: [Error] unsupported file format: '%s'\n", __FILE__, __LINE__, file_path);
        exit(1);
    }

    if (!strncmp(file_extention, "STL", 3) || !strncmp(file_extention, "stl", 3)) {
        return ae_get_tri_mesh_from_stl_file(file_path);
    } else if (!strncmp(file_extention, "obj", 3)) {
        return ae_get_tri_mesh_from_obj_file(file_path);
    }
    
    Tri_mesh null_mesh = {0};
    return null_mesh;
}

Tri_mesh ae_get_tri_mesh_from_obj_file(char *file_path)
{
    char current_line[MAX_LEN_LINE], current_word[MAX_LEN_LINE], current_num_str[MAX_LEN_LINE];
    char file_name[MAX_LEN_LINE], file_extention[MAX_LEN_LINE], mesh_name[MAX_LEN_LINE];
    int texture_warning_was_printed = 0;

    strncpy(file_name, file_path, MAX_LEN_LINE);
    strncpy(file_extention, file_name, MAX_LEN_LINE);

    /* check if file is an obj file*/
    asm_get_word_and_cut(file_name, file_extention, '.');
    asm_get_word_and_cut(file_name, file_extention, '.');
    if (strncmp(file_extention, ".obj", MAX_LEN_LINE)) {
        fprintf(stderr, "%s:%d: [Error] unsupported file format: '%s'\n", __FILE__, __LINE__, file_name);
        exit(1);
    }

    strncpy(mesh_name, file_name, MAX_LEN_LINE);
    while(asm_length(mesh_name)) {
        asm_get_word_and_cut(current_word, mesh_name, '/');
    }

    strncpy(mesh_name, current_word, MAX_LEN_LINE);

    strncpy(current_word, ".", MAX_LEN_LINE);
    strncat(file_name, ".obj", MAX_LEN_LINE/2);
    strncat(current_word, file_name, MAX_LEN_LINE/2);

    FILE *fp_input = fopen(current_word, "rt");
    if (fp_input == NULL) {
        fprintf(stderr, "%s:%d: [Error] failed to open input file: '%s', %s\n", __FILE__, __LINE__, current_word, strerror(errno));
        exit(1);
    }

    // strncpy(output_file_name, "./build/", MAX_LEN_LINE);
    // strncat(output_file_name, mesh_name, MAX_LEN_LINE/2);
    // strncat(output_file_name, ".c", MAX_LEN_LINE/2);
    // FILE *fp_output = fopen(output_file_name, "wt");
    // if (fp_input == NULL) {
    //     fprintf(stderr, "%s:%d: [Error] failed to open output file: '%s'. %s\n", __FILE__, __LINE__, output_file_name, strerror(errno));
    //     exit(1);
    // }

    /* parsing data from file */
    Curve points = {0};
    ada_init_array(Point, points);
    Tri_mesh mesh;
    ada_init_array(Tri, mesh);

    int line_len;

    while ((line_len = asm_get_line(fp_input, current_line)) != -1) {
        asm_get_next_word_from_line(current_word, current_line, ' ');
        if (!strncmp(current_word, "v", 1)) {
            Point p;
            asm_get_word_and_cut(current_word, current_line, ' ');
            asm_get_word_and_cut(current_word, current_line, ' ');
            p.x = atof(current_word);
            asm_get_word_and_cut(current_word, current_line, ' ');
            p.y = atof(current_word);
            asm_get_word_and_cut(current_word, current_line, ' ');
            p.z = atof(current_word);
            // printf("current word: %s\n", current_word);
            ada_appand(Point, points, p);
            // break;
        }
        if (!strncmp(current_word, "f", 1)) {
            Tri tri1 = {0}, tri2 = {0};

            // printf("line: %s\nword: %s, %d\n", current_line, current_word, atoi(current_word));
            asm_get_word_and_cut(current_word, current_line, ' ');
            // printf("line: %s\nword: %s, %d\n", current_line, current_word, atoi(current_word));

            int number_of_spaces = asm_str_in_str(current_line, " ");
            // printf("%d\n", number_of_spaces);
            // exit(1);
            if (!(number_of_spaces == 3 || number_of_spaces == 4 || number_of_spaces == 5)) {
                fprintf(stderr, "%s:%d: [Error] there is unsupported number of vertices for a face: %d\n", __FILE__, __LINE__, number_of_spaces);
                exit(1);
            }
            if (number_of_spaces == 3) {
                /* there are 3 vertices for the face. */
                asm_get_word_and_cut(current_word, current_line, ' ');
                // printf("line: %s\nword: %s, %d\n", current_line, current_word, atoi(current_word));
                int number_of_backslash = asm_str_in_str(current_word, "/");
                if (number_of_backslash == 0) {
                    tri1.points[0] = points.elements[atoi(current_word)-1];
                    asm_get_word_and_cut(current_word, current_line, ' ');
                    tri1.points[1] = points.elements[atoi(current_word)-1];
                    asm_get_word_and_cut(current_word, current_line, ' ');
                    tri1.points[2] = points.elements[atoi(current_word)-1];
                }
                if (number_of_backslash == 2) {
                    if (!texture_warning_was_printed) {
                        fprintf(stderr, "%s:%d [Warning] texture and normals data ignored of file at - '%s'\n", __FILE__, __LINE__, file_path);
                        texture_warning_was_printed = 1;
                    }

                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri1.points[0] = points.elements[atoi(current_num_str)-1];

                    asm_get_word_and_cut(current_word, current_line, ' ');
                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri1.points[1] = points.elements[atoi(current_num_str)-1];

                    asm_get_word_and_cut(current_word, current_line, ' ');
                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri1.points[2] = points.elements[atoi(current_num_str)-1];
                }

                tri1.to_draw = true;
                tri1.light_intensity = 1;
                tri1.center.x = (tri1.points[0].x + tri1.points[1].x + tri1.points[2].x) / 3;
                tri1.center.y = (tri1.points[0].y + tri1.points[1].y + tri1.points[2].y) / 3;
                tri1.center.z = (tri1.points[0].z + tri1.points[1].z + tri1.points[2].z) / 3;
                tri1.z_min = fmin(tri1.points[0].z, fmin(tri1.points[1].z, tri1.points[2].z));
                tri1.z_max = fmax(tri1.points[0].z, fmax(tri1.points[1].z, tri1.points[2].z));
                tri1.colors[0] = 0xFFFFFFFF;
                tri1.colors[1] = 0xFFFFFFFF;
                tri1.colors[2] = 0xFFFFFFFF;

                ada_appand(Tri, mesh, tri1);
                // AE_PRINT_TRI(tri1);
            } else if (number_of_spaces == 5 || number_of_spaces == 4) {
                /* there are 4 vertices for the face. */
                /* sometimes there is a space in the end */
                asm_get_word_and_cut(current_word, current_line, ' ');
                // printf("line: %s\nword: %s, %d\n", current_line, current_word, atoi(current_word));
                int number_of_backslash = asm_str_in_str(current_word, "/");
                if (number_of_backslash == 0) {
                    tri1.points[0] = points.elements[atoi(current_word)-1];
                    asm_get_word_and_cut(current_word, current_line, ' ');
                    tri1.points[1] = points.elements[atoi(current_word)-1];
                    asm_get_word_and_cut(current_word, current_line, ' ');
                    tri1.points[2] = points.elements[atoi(current_word)-1];
                }
                if (number_of_backslash == 2 || number_of_backslash == 1) {
                    if (!texture_warning_was_printed) {
                        fprintf(stderr, "%s:%d [Warning] texture and normals data ignored of file at - '%s'\n", __FILE__, __LINE__, file_path);
                        texture_warning_was_printed = 1;
                    }

                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri1.points[0] = points.elements[atoi(current_num_str)-1];
                    tri2.points[2] = points.elements[atoi(current_num_str)-1];

                    asm_get_word_and_cut(current_word, current_line, ' ');
                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri1.points[1] = points.elements[atoi(current_num_str)-1];

                    asm_get_word_and_cut(current_word, current_line, ' ');
                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri1.points[2] = points.elements[atoi(current_num_str)-1];
                    tri2.points[0] = points.elements[atoi(current_num_str)-1];

                    asm_get_word_and_cut(current_word, current_line, ' ');
                    asm_get_word_and_cut(current_num_str, current_word, '/');
                    // printf("line: %s\nword: %s\nnum str: %s, %d\n", current_line, current_word, current_num_str, atoi(current_num_str));
                    tri2.points[1] = points.elements[atoi(current_num_str)-1];
                }

                tri1.to_draw = true;
                tri1.light_intensity = 1;
                tri1.center.x = (tri1.points[0].x + tri1.points[1].x + tri1.points[2].x) / 3;
                tri1.center.y = (tri1.points[0].y + tri1.points[1].y + tri1.points[2].y) / 3;
                tri1.center.z = (tri1.points[0].z + tri1.points[1].z + tri1.points[2].z) / 3;
                tri1.z_min = fmin(tri1.points[0].z, fmin(tri1.points[1].z, tri1.points[2].z));
                tri1.z_max = fmax(tri1.points[0].z, fmax(tri1.points[1].z, tri1.points[2].z));
                tri1.colors[0] = 0xFFFFFFFF;
                tri1.colors[1] = 0xFFFFFFFF;
                tri1.colors[2] = 0xFFFFFFFF;

                tri2.to_draw = true;
                tri2.light_intensity = 1;
                tri2.center.x = (tri2.points[0].x + tri2.points[1].x + tri2.points[2].x) / 3;
                tri2.center.y = (tri2.points[0].y + tri2.points[1].y + tri2.points[2].y) / 3;
                tri2.center.z = (tri2.points[0].z + tri2.points[1].z + tri2.points[2].z) / 3;
                tri2.z_min = fmin(tri2.points[0].z, fmin(tri2.points[1].z, tri2.points[2].z));
                tri2.z_max = fmax(tri2.points[0].z, fmax(tri2.points[1].z, tri2.points[2].z));
                tri2.colors[0] = 0xFFFFFFFF;
                tri2.colors[1] = 0xFFFFFFFF;
                tri2.colors[2] = 0xFFFFFFFF;

                ada_appand(Tri, mesh, tri1);
                ada_appand(Tri, mesh, tri2);
                // AE_PRINT_TRI(tri1);
                // AE_PRINT_TRI(tri2);
            }
            // exit(2);
        }
    }
    
    return mesh;
}

Tri_mesh ae_get_tri_mesh_from_stl_file(char *file_path)
{
    FILE *file;
    file = fopen(file_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "%s:%d: [Error] failed to open input file: '%s', %s\n", __FILE__, __LINE__, file_path, strerror(errno));
        exit(1);
    }

    char header[STL_HEADER_SIZE];
    fread(header, STL_HEADER_SIZE, 1, file);
    // dprintSTRING(header);

    uint32_t num_of_tri;
    fread(&num_of_tri, STL_NUM_SIZE, 1, file);
    // dprintINT(num_of_tri);

    Tri_mesh mesh;
    ada_init_array(Tri, mesh);
    for (size_t i = 0; i < num_of_tri; i++) {
        Tri temp_tri = {0};

        fread(&(temp_tri.normals[0].x), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.normals[0].y), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.normals[0].z), STL_NUM_SIZE, 1, file);

        temp_tri.normals[1] = temp_tri.normals[0];
        temp_tri.normals[2] = temp_tri.normals[0];

        fread(&(temp_tri.points[0].x), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.points[0].y), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.points[0].z), STL_NUM_SIZE, 1, file);

        fread(&(temp_tri.points[1].x), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.points[1].y), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.points[1].z), STL_NUM_SIZE, 1, file);
        
        fread(&(temp_tri.points[2].x), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.points[2].y), STL_NUM_SIZE, 1, file);
        fread(&(temp_tri.points[2].z), STL_NUM_SIZE, 1, file);

        fseek(file, STL_ATTRIBUTE_BITS_SIZE, SEEK_CUR);

        temp_tri.to_draw = true;
        temp_tri.light_intensity = 1;
        temp_tri.center.x = (temp_tri.points[0].x + temp_tri.points[1].x + temp_tri.points[2].x) / 3;
        temp_tri.center.y = (temp_tri.points[0].y + temp_tri.points[1].y + temp_tri.points[2].y) / 3;
        temp_tri.center.z = (temp_tri.points[0].z + temp_tri.points[1].z + temp_tri.points[2].z) / 3;
        temp_tri.z_min = fmin(temp_tri.points[0].z, fmin(temp_tri.points[1].z, temp_tri.points[2].z));
        temp_tri.z_max = fmax(temp_tri.points[0].z, fmax(temp_tri.points[1].z, temp_tri.points[2].z));
        temp_tri.colors[0] = 0xFFFFFFFF;
        temp_tri.colors[1] = 0xFFFFFFFF;
        temp_tri.colors[2] = 0xFFFFFFFF;

        ada_appand(Tri, mesh, temp_tri);
    }

    return mesh;
}

void ae_appand_copy_of_tri_mesh(Tri_mesh_array *mesh_array, Tri_mesh mesh)
{
    Tri_mesh_array temp_mesh_array = *mesh_array;
    Tri_mesh temp_mesh;
    ada_init_array(Tri, temp_mesh);
    for (size_t i = 0; i < mesh.length; i++) {
        ada_appand(Tri, temp_mesh, mesh.elements[i]);
    }
    ada_appand(Tri_mesh, temp_mesh_array, temp_mesh);

    *mesh_array = temp_mesh_array;
}

Tri_mesh ae_get_tri_mesh_from_quad_mesh(Quad_mesh q_mesh)
{
    Tri_mesh t_mesh;
    ada_init_array(Tri, t_mesh);

    for (size_t q_index = 0; q_index < q_mesh.length; q_index++) {
        Quad current_q = q_mesh.elements[q_index];
        Tri temp_t = {.light_intensity = current_q.light_intensity, .to_draw = current_q.to_draw};

        temp_t.points[0] = current_q.points[0];
        temp_t.colors[0] = current_q.colors[0];
        temp_t.normals[0] = current_q.normal[0];
        temp_t.points[1] = current_q.points[1];
        temp_t.colors[1] = current_q.colors[1];
        temp_t.normals[1] = current_q.normal[1];
        temp_t.points[2] = current_q.points[2];
        temp_t.colors[2] = current_q.colors[2];
        temp_t.normals[2] = current_q.normal[2];

        ada_appand(Tri, t_mesh, temp_t);

        temp_t.points[0] = current_q.points[2];
        temp_t.colors[0] = current_q.colors[2];
        temp_t.normals[0] = current_q.normal[2];
        temp_t.points[1] = current_q.points[3];
        temp_t.colors[1] = current_q.colors[3];
        temp_t.normals[1] = current_q.normal[3];
        temp_t.points[2] = current_q.points[0];
        temp_t.colors[2] = current_q.colors[0];
        temp_t.normals[2] = current_q.normal[0];

        ada_appand(Tri, t_mesh, temp_t);
    }

    return t_mesh;
}

void ae_print_points(Curve p)
{
    for (size_t i = 0; i < p.length; i++) {
        printf("point %3zu: (%5f, %5f, %5f)\n", i, p.elements[i].x, p.elements[i].y, p.elements[i].z);
    }
}

void ae_print_tri(Tri tri, char *name, size_t padding)
{
    printf("%*s%s:\n", (int) padding, "", name);
    printf("%*s    (%f, %f, %f)\n%*s    (%f, %f, %f)\n%*s    (%f, %f, %f)\n", (int) padding, "", tri.points[0].x, tri.points[0].y, tri.points[0].z, (int) padding, "", tri.points[1].x, tri.points[1].y, tri.points[1].z, (int) padding, "", tri.points[2].x, tri.points[2].y, tri.points[2].z);
    printf("%*s    draw? %d\n", (int)padding, "", tri.to_draw);
}

void ae_print_tri_mesh(Tri_mesh mesh, char *name, size_t padding)
{
    char tri_name[256];
    printf("%*s%s:\n", (int) padding, "", name);
    for (size_t i = 0; i < mesh.length; i++) {
        snprintf(tri_name, 256, "tri %zu", i);
        ae_print_tri(mesh.elements[i], tri_name, 4);
    }
}

void ae_calc_normal_to_tri(Mat2D normal, Tri tri)
{
    AE_ASSERT(3 == normal.rows && 1 == normal.cols);
    ae_assert_tri_is_valid(tri);

    Mat2D a = mat2D_alloc(3, 1);
    Mat2D b = mat2D_alloc(3, 1);
    Mat2D c = mat2D_alloc(3, 1);

    ae_point_to_mat2D(tri.points[0], a);
    ae_point_to_mat2D(tri.points[1], b);
    ae_point_to_mat2D(tri.points[2], c);

    mat2D_sub(b, a);
    mat2D_sub(c, a);

    mat2D_cross(normal, b, c);

    mat2D_mult(normal, 1/mat2D_calc_norma(normal));

    mat2D_free(a);
    mat2D_free(b);
    mat2D_free(c);
}

void ae_calc_normal_to_quad(Mat2D normal, Quad quad)
{
    AE_ASSERT(3 == normal.rows && 1 == normal.cols);
    ae_assert_quad_is_valid(quad);

    Mat2D a = mat2D_alloc(3, 1);
    Mat2D b = mat2D_alloc(3, 1);
    Mat2D c = mat2D_alloc(3, 1);

    ae_point_to_mat2D(quad.points[0], a);
    ae_point_to_mat2D(quad.points[1], b);
    ae_point_to_mat2D(quad.points[2], c);

    mat2D_sub(b, a);
    mat2D_sub(c, a);

    mat2D_cross(normal, b, c);

    mat2D_mult(normal, 1/mat2D_calc_norma(normal));

    mat2D_free(a);
    mat2D_free(b);
    mat2D_free(c);
}

void ae_translate_tri_mesh(Tri_mesh mesh, float x, float y, float z)
{
    for (size_t i = 0; i < mesh.length; i++) {
        for (int j = 0; j < 3; j++) {
            mesh.elements[i].points[j].x += x;
            mesh.elements[i].points[j].y += y;
            mesh.elements[i].points[j].z += z;
        }
    }
}

/* phi around x, theta around y, psi around z.
DCM = Cz*Cy*Cx */
void ae_rotate_tri_mesh_Euler_xyz(Tri_mesh mesh, float phi_deg, float theta_deg, float psi_deg)
{
    Mat2D RotZ = mat2D_alloc(3,3);
    mat2D_set_rot_mat_z(RotZ, psi_deg);
    Mat2D RotY = mat2D_alloc(3,3);
    mat2D_set_rot_mat_y(RotY, theta_deg);
    Mat2D RotX = mat2D_alloc(3,3);
    mat2D_set_rot_mat_x(RotX, phi_deg);
    Mat2D DCM = mat2D_alloc(3,3);
    // mat2D_fill(DCM,0);
    Mat2D temp = mat2D_alloc(3,3);
    // mat2D_fill(temp,0);
    mat2D_dot(temp, RotY, RotZ);
    mat2D_dot(DCM, RotX, temp); /* I have a DCM */

    Mat2D src_point_mat = mat2D_alloc(3,1);
    Mat2D des_point_mat = mat2D_alloc(3,1);

    for (size_t i = 0; i < mesh.length; i++) {
        for (int j = 0; j < 3; j++) {
            // mat2D_fill(src_point_mat, 0);
            // mat2D_fill(des_point_mat, 0);
            Point des;
            Point src = mesh.elements[i].points[j];

            MAT2D_AT(src_point_mat, 0, 0) = src.x;
            MAT2D_AT(src_point_mat, 1, 0) = src.y;
            MAT2D_AT(src_point_mat, 2, 0) = src.z;

            mat2D_dot(des_point_mat, DCM, src_point_mat);

            des.x = MAT2D_AT(des_point_mat, 0, 0);
            des.y = MAT2D_AT(des_point_mat, 1, 0);
            des.z = MAT2D_AT(des_point_mat, 2, 0);

            mesh.elements[i].points[j] = des;
        }
    }

    mat2D_free(RotZ);
    mat2D_free(RotY);
    mat2D_free(RotX);
    mat2D_free(DCM);
    mat2D_free(src_point_mat);
    mat2D_free(des_point_mat);
}

void ae_set_tri_mesh_bounding_box(Tri_mesh mesh, float *x_min, float *x_max, float *y_min, float *y_max, float *z_min, float *z_max)
{
    float xmin = FLT_MAX, xmax = FLT_MIN;
    float ymin = FLT_MAX, ymax = FLT_MIN;
    float zmin = FLT_MAX, zmax = FLT_MIN;

    float x, y, z;

    for (size_t t = 0; t < mesh.length; t++) {
        for (size_t p = 0; p < 3; p++) {
            x = mesh.elements[t].points[p].x;
            y = mesh.elements[t].points[p].y;
            z = mesh.elements[t].points[p].z;
            if (x > xmax) xmax = x;
            if (x < xmin) xmin = x;
            if (y > ymax) ymax = y;
            if (y < ymin) ymin = y;
            if (z > zmax) zmax = z;
            if (z < zmin) zmin = z;
        }
    }
    *x_min = xmin;
    *x_max = xmax; 
    *y_min = ymin;
    *y_max = ymax;
    *z_min = zmin;
    *z_max = zmax;
}

void ae_set_tri_center_zmin_zmax(Tri *tri)
{
    ae_assert_tri_is_valid(*tri);
    tri->center.x = (tri->points[0].x + tri->points[1].x + tri->points[2].x) / 3;
    tri->center.y = (tri->points[0].y + tri->points[1].y + tri->points[2].y) / 3;
    tri->center.z = (tri->points[0].z + tri->points[1].z + tri->points[2].z) / 3;
    tri->z_min = fmin(tri->points[0].z, fmin(tri->points[1].z, tri->points[2].z));
    tri->z_max = fmax(tri->points[0].z, fmax(tri->points[1].z, tri->points[2].z));
}

/* normalize all the points in between -1 and 1. the origin is in the center of the body. */
void ae_normalize_tri_mesh(Tri_mesh mesh)
{
    float xmax, xmin, ymax, ymin, zmax, zmin;
    ae_set_tri_mesh_bounding_box(mesh, &xmin, &xmax, &ymin, &ymax, &zmin, &zmax);

    for (size_t t = 0; t < mesh.length; t++) {
        for (size_t p = 0; p < 3; p++) {
            float x, y, z;
            x = mesh.elements[t].points[p].x;
            y = mesh.elements[t].points[p].y;
            z = mesh.elements[t].points[p].z;

            float xdiff = xmax-xmin;
            float ydiff = ymax-ymin;
            float zdiff = zmax-zmin;
            float max_diff = fmax(xdiff, fmax(ydiff, zdiff));
            float xfactor = xdiff/max_diff;
            float yfactor = ydiff/max_diff;
            float zfactor = zdiff/max_diff;

            x = (((x - xmin) / (xdiff)) * 2 - 1) * xfactor;
            y = (((y - ymin) / (ydiff)) * 2 - 1) * yfactor;
            z = (((z - zmin) / (zdiff)) * 2 - 1) * zfactor;

            // ae_set_tri_center_zmin_zmax(&(mesh.elements[t]));

            mesh.elements[t].points[p].x = x;
            mesh.elements[t].points[p].y = y;
            mesh.elements[t].points[p].z = z;
        }
    }
}

Point ae_line_itersect_plane(Mat2D plane_p, Mat2D plane_n, Mat2D line_start, Mat2D line_end, float *t)
{
    mat2D_normalize(plane_n);
    float plane_d = - mat2D_dot_product(plane_n, plane_p);
    float ad = mat2D_dot_product(line_start, plane_n);
    float bd = mat2D_dot_product(line_end, plane_n);
    *t  = (- plane_d - ad) / (bd - ad);
    mat2D_sub(line_end, line_start);
    Mat2D line_start_to_end = line_end;
    mat2D_mult(line_start_to_end, *t);
    Mat2D line_to_intersection = line_start_to_end;
    
    Mat2D intersection_p = mat2D_alloc(3, 1);
    mat2D_fill(intersection_p, 0);
    mat2D_add(intersection_p, line_start);
    mat2D_add(intersection_p, line_to_intersection);

    Point ans_p = ae_mat2D_to_point(intersection_p);

    mat2D_free(intersection_p);

    return ans_p;
}

/* signed distance from point to plane */
float signed_dist_point_and_plane(Point p, Mat2D plane_p, Mat2D plane_n)
{
    ae_assert_point_is_valid(p);

    // mat2D_normalize(plane_n);
    // Mat2D p_mat2D = mat2D_alloc(3, 1);
    // ae_point_to_mat2D(p, p_mat2D);

    // float res = mat2D_dot_product(plane_n, p_mat2D) - mat2D_dot_product(plane_n, plane_p); 

    float res = MAT2D_AT(plane_n, 0, 0) * p.x + MAT2D_AT(plane_n, 1, 0) * p.y + MAT2D_AT(plane_n, 2, 0) * p.z - (MAT2D_AT(plane_n, 0, 0) * MAT2D_AT(plane_p, 0, 0) + MAT2D_AT(plane_n, 1, 0) * MAT2D_AT(plane_p, 1, 0) + MAT2D_AT(plane_n, 2, 0) * MAT2D_AT(plane_p, 2, 0)); 

    // mat2D_free(p_mat2D);

    return res;
}

/* returns number of inside triangles
return -1 on error */
int ae_tri_clip_with_plane(Tri tri_in, Mat2D plane_p, Mat2D plane_n, Tri *tri_out1, Tri *tri_out2)
{
    ae_assert_tri_is_valid(tri_in);

    mat2D_normalize(plane_n);

    /* if the signed distance is positive, the point lies on the "inside" of the plane */
    Point inside_points[3];
    Point outside_points[3];
    int inside_points_count = 0;
    int outside_points_count = 0;
    Point tex_inside_points[3];
    Point tex_outside_points[3];
    int tex_inside_points_count = 0;
    int tex_outside_points_count = 0;
    
    /* calc signed distance of each point of tri_in */
    float d0 = signed_dist_point_and_plane(tri_in.points[0], plane_p, plane_n);
    float d1 = signed_dist_point_and_plane(tri_in.points[1], plane_p, plane_n);
    float d2 = signed_dist_point_and_plane(tri_in.points[2], plane_p, plane_n);
    float t;

    // float epsilon = 1e-3;
    float epsilon = 0;
    if (d0 >= epsilon) {
        inside_points[inside_points_count++] = tri_in.points[0];
        tex_inside_points[tex_inside_points_count++] = tri_in.tex_points[0];
    } else {
        outside_points[outside_points_count++] = tri_in.points[0];
        tex_outside_points[tex_outside_points_count++] = tri_in.tex_points[0];
    }
    if (d1 >= epsilon) {
        inside_points[inside_points_count++] = tri_in.points[1];
        tex_inside_points[tex_inside_points_count++] = tri_in.tex_points[1];
    } else {
        outside_points[outside_points_count++] = tri_in.points[1];
        tex_outside_points[tex_outside_points_count++] = tri_in.tex_points[1];
    }
    if (d2 >= epsilon) {
        inside_points[inside_points_count++] = tri_in.points[2];
        tex_inside_points[tex_inside_points_count++] = tri_in.tex_points[2];
    } else {
        outside_points[outside_points_count++] = tri_in.points[2];
        tex_outside_points[tex_outside_points_count++] = tri_in.tex_points[2];
    }

    /* classifying the triangle points */
    if (inside_points_count == 0) {
        return 0;
    } else if (inside_points_count == 3) {
        *tri_out1 = tri_in;
        return 1;
    } else if (inside_points_count == 1 && outside_points_count == 2) {
        Mat2D line_start = mat2D_alloc(3, 1);
        Mat2D line_end   = mat2D_alloc(3, 1);

        *tri_out1 = tri_in;
        
        (*tri_out1).points[0] = inside_points[0];
        (*tri_out1).tex_points[0] = tex_inside_points[0];

        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[0], line_end);
        (*tri_out1).points[1] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*tri_out1).points[1].w = t * (outside_points[0].w - inside_points[0].w) + inside_points[0].w;
        (*tri_out1).tex_points[1].x = t * (tex_outside_points[0].x - tex_inside_points[0].x) + tex_inside_points[0].x;
        (*tri_out1).tex_points[1].y = t * (tex_outside_points[0].y - tex_inside_points[0].y) + tex_inside_points[0].y;

        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[1], line_end);
        (*tri_out1).points[2] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*tri_out1).points[2].w = t * (outside_points[1].w - inside_points[0].w) + inside_points[0].w;
        (*tri_out1).tex_points[2].x = t * (tex_outside_points[1].x - tex_inside_points[0].x) + tex_inside_points[0].x;
        (*tri_out1).tex_points[2].y = t * (tex_outside_points[1].y - tex_inside_points[0].y) + tex_inside_points[0].y;

        mat2D_free(line_start);
        mat2D_free(line_end);

        ae_assert_tri_is_valid(*tri_out1);

        return 1;
    } else if (inside_points_count == 2 && outside_points_count == 1) {
        Mat2D line_start = mat2D_alloc(3, 1);
        Mat2D line_end   = mat2D_alloc(3, 1);
        
        *tri_out1 = tri_in;
        *tri_out2 = tri_in;

        (*tri_out1).points[0] = inside_points[0];
        (*tri_out1).tex_points[0] = tex_inside_points[0];
        (*tri_out1).points[1] = inside_points[1];
        (*tri_out1).tex_points[1] = tex_inside_points[1];
        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[0], line_end);
        (*tri_out1).points[2] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*tri_out1).points[2].w = t * (outside_points[0].w - inside_points[0].w) + inside_points[0].w;
        (*tri_out1).tex_points[2].x = t * (tex_outside_points[0].x - tex_inside_points[0].x) + tex_inside_points[0].x;
        (*tri_out1).tex_points[2].y = t * (tex_outside_points[0].y - tex_inside_points[0].y) + tex_inside_points[0].y;

        (*tri_out2).points[0] = inside_points[1];
        (*tri_out2).tex_points[0] = tex_inside_points[1];
        ae_point_to_mat2D(inside_points[1], line_start);
        ae_point_to_mat2D(outside_points[0], line_end);
        (*tri_out2).points[1] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*tri_out2).points[1].w = t * (outside_points[0].w - inside_points[1].w) + inside_points[1].w;
        (*tri_out2).tex_points[1].x = t * (tex_outside_points[0].x - tex_inside_points[1].x) + tex_inside_points[1].x;
        (*tri_out2).tex_points[1].y = t * (tex_outside_points[0].y - tex_inside_points[1].y) + tex_inside_points[1].y;
        (*tri_out2).points[2] = (*tri_out1).points[2];
        (*tri_out2).tex_points[2] = (*tri_out1).tex_points[2];

        mat2D_free(line_start);
        mat2D_free(line_end);

        ae_assert_tri_is_valid(*tri_out1);
        ae_assert_tri_is_valid(*tri_out2);

        return 2;
    }
    return -1;
}

/* returns number of inside quads
return -1 on error */
int ae_quad_clip_with_plane(Quad quad_in, Mat2D plane_p, Mat2D plane_n, Quad *quad_out)
{
    ae_assert_quad_is_valid(quad_in);

    mat2D_normalize(plane_n);

    /* if the signed distance is positive, the point lies on the "inside" of the plane */
    Point inside_points[4];
    Point outside_points[4];
    int inside_points_count = 0;
    int outside_points_count = 0;
    
    /* calc signed distance of each point of tri_in */
    float d0 = signed_dist_point_and_plane(quad_in.points[0], plane_p, plane_n);
    float d1 = signed_dist_point_and_plane(quad_in.points[1], plane_p, plane_n);
    float d2 = signed_dist_point_and_plane(quad_in.points[2], plane_p, plane_n);
    float d3 = signed_dist_point_and_plane(quad_in.points[3], plane_p, plane_n);
    float t;

    // float epsilon = 1e-3;
    float epsilon = 0;
    if (d0 >= epsilon) {
        inside_points[inside_points_count++] = quad_in.points[0];
    } else {
        outside_points[outside_points_count++] = quad_in.points[0];
    }
    if (d1 >= epsilon) {
        inside_points[inside_points_count++] = quad_in.points[1];
    } else {
        outside_points[outside_points_count++] = quad_in.points[1];
    }
    if (d2 >= epsilon) {
        inside_points[inside_points_count++] = quad_in.points[2];
    } else {
        outside_points[outside_points_count++] = quad_in.points[2];
    }
    if (d3 >= epsilon) {
        inside_points[inside_points_count++] = quad_in.points[3];
    } else {
        outside_points[outside_points_count++] = quad_in.points[3];
    }

    /* classifying the triangle points */
    if (inside_points_count == 0) {
        return 0;
    } else if (inside_points_count == 4) {
        *quad_out = quad_in;
        return 1;
    } else if (inside_points_count == 1 && outside_points_count == 3) {
        Mat2D line_start = mat2D_alloc(3, 1);
        Mat2D line_end   = mat2D_alloc(3, 1);

        *quad_out = quad_in;        

        (*quad_out).points[0] = inside_points[0];

        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[0], line_end);
        (*quad_out).points[1] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*quad_out).points[1].w = t * (outside_points[0].w - inside_points[0].w) + inside_points[0].w;

        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[1], line_end);
        (*quad_out).points[2] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*quad_out).points[2].w = t * (outside_points[1].w - inside_points[0].w) + inside_points[0].w;

        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[2], line_end);
        (*quad_out).points[3] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*quad_out).points[3].w = t * (outside_points[2].w - inside_points[0].w) + inside_points[0].w;

        mat2D_free(line_start);
        mat2D_free(line_end);

        ae_assert_quad_is_valid(*quad_out);

        return 1;
    } else if (inside_points_count == 2 && outside_points_count == 2) {
        Mat2D line_start = mat2D_alloc(3, 1);
        Mat2D line_end   = mat2D_alloc(3, 1);
        
        *quad_out = quad_in;

        (*quad_out).points[0] = inside_points[0];
        (*quad_out).points[1] = inside_points[1];
        ae_point_to_mat2D(inside_points[1], line_start);
        ae_point_to_mat2D(outside_points[0], line_end);
        (*quad_out).points[2] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*quad_out).points[2].w = t * (outside_points[0].w - inside_points[1].w) + inside_points[1].w;

        ae_point_to_mat2D(inside_points[0], line_start);
        ae_point_to_mat2D(outside_points[1], line_end);
        (*quad_out).points[3] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*quad_out).points[3].w = t * (outside_points[1].w - inside_points[0].w) + inside_points[0].w;

        mat2D_free(line_start);
        mat2D_free(line_end);

        ae_assert_quad_is_valid(*quad_out);

        return 1;
    } else if (inside_points_count == 3 && outside_points_count == 1) {
        Mat2D line_start = mat2D_alloc(3, 1);
        Mat2D line_end   = mat2D_alloc(3, 1);
        
        *quad_out = quad_in;

        (*quad_out).points[0] = inside_points[0];
        (*quad_out).points[1] = inside_points[1];
        (*quad_out).points[2] = inside_points[2];
        ae_point_to_mat2D(inside_points[2], line_start);
        ae_point_to_mat2D(outside_points[0], line_end);
        (*quad_out).points[3] = ae_line_itersect_plane(plane_p, plane_n, line_start, line_end, &t);
        (*quad_out).points[3].w = t * (outside_points[0].w - inside_points[2].w) + inside_points[2].w;

        mat2D_free(line_start);
        mat2D_free(line_end);

        ae_assert_quad_is_valid(*quad_out);

        return 1;
    }
    return -1;
}

void ae_set_projection_mat(Mat2D proj_mat,float aspect_ratio, float FOV_deg, float z_near, float z_far)
{
    AE_ASSERT(4 == proj_mat.cols); 
    AE_ASSERT(4 == proj_mat.rows); 
    AE_ASSERT(FOV_deg && "FOV needs to bee bigger then zero");

    mat2D_fill(proj_mat, 0);

    float field_of_view = 1.0f / tanf(0.5f * FOV_deg * PI / 180);
    float z_normalization = z_far / (z_far - z_near);

    MAT2D_AT(proj_mat, 0, 0) = aspect_ratio * field_of_view;
    MAT2D_AT(proj_mat, 1, 1) = field_of_view;
    MAT2D_AT(proj_mat, 2, 2) = z_normalization;
    MAT2D_AT(proj_mat, 2, 3) = 1;
    MAT2D_AT(proj_mat, 3, 2) = - z_normalization * z_near;
}

void ae_set_view_mat(Mat2D view_mat, Camera camera, Mat2D up)
{
    Mat2D DCM = mat2D_alloc(3,3);
    Mat2D DCM_trans = mat2D_alloc(3,3);
    mat2D_set_DCM_zyx(DCM, camera.yaw_offset_deg, camera.pitch_offset_deg, camera.roll_offset_deg);
    mat2D_transpose(DCM_trans, DCM);

    Mat2D temp_vec = mat2D_alloc(3, 1);
    Mat2D camera_direction = mat2D_alloc(3, 1);

    /* rotating camera_direction */
    mat2D_dot(camera_direction, DCM_trans, camera.direction);

    /* calc new forward direction */
    Mat2D new_forward = mat2D_alloc(3, 1);
    mat2D_copy(new_forward, camera_direction);
    mat2D_mult(new_forward, 1.0 / mat2D_calc_norma(new_forward));

    /* calc new up direction */
    mat2D_copy(temp_vec, new_forward);
    mat2D_mult(temp_vec, mat2D_dot_product(up, new_forward));
    Mat2D new_up = mat2D_alloc(3, 1);
    mat2D_copy(new_up, up);
    mat2D_sub(new_up, temp_vec);
    mat2D_mult(new_up, 1.0 / mat2D_calc_norma(new_up));

    /* calc new right direction */
    Mat2D new_right = mat2D_alloc(3, 1);
    mat2D_cross(new_right, new_up, new_forward);
    mat2D_mult(new_right, 1.0 / mat2D_calc_norma(new_right));

    mat2D_copy(camera.camera_x, new_right);
    mat2D_copy(camera.camera_y, new_up);
    mat2D_copy(camera.camera_z, new_forward);

    /* adding offset to init_position */
    // mat2D_add(camera_pos, camera.offset_position);

    mat2D_copy(temp_vec, camera.camera_x);
    mat2D_mult(temp_vec, MAT2D_AT(camera.offset_position, 0, 0));
    mat2D_add(camera.current_position, temp_vec);
    mat2D_copy(temp_vec, camera.camera_y);
    mat2D_mult(temp_vec, MAT2D_AT(camera.offset_position, 1, 0));
    mat2D_add(camera.current_position, temp_vec);
    mat2D_copy(temp_vec, camera.camera_z);
    mat2D_mult(temp_vec, MAT2D_AT(camera.offset_position, 2, 0));
    mat2D_add(camera.current_position, temp_vec);

    mat2D_fill(camera.offset_position, 0);

    MAT2D_AT(view_mat, 0, 0) = MAT2D_AT(new_right, 0, 0);
    MAT2D_AT(view_mat, 0, 1) = MAT2D_AT(new_up, 0, 0);
    MAT2D_AT(view_mat, 0, 2) = MAT2D_AT(new_forward, 0, 0);
    MAT2D_AT(view_mat, 0, 3) = 0;
    MAT2D_AT(view_mat, 1, 0) = MAT2D_AT(new_right, 1, 0);
    MAT2D_AT(view_mat, 1, 1) = MAT2D_AT(new_up, 1, 0);
    MAT2D_AT(view_mat, 1, 2) = MAT2D_AT(new_forward, 1, 0);
    MAT2D_AT(view_mat, 1, 3) = 0;
    MAT2D_AT(view_mat, 2, 0) = MAT2D_AT(new_right, 2, 0);
    MAT2D_AT(view_mat, 2, 1) = MAT2D_AT(new_up, 2, 0);
    MAT2D_AT(view_mat, 2, 2) = MAT2D_AT(new_forward, 2, 0);
    MAT2D_AT(view_mat, 2, 3) = 0;
    MAT2D_AT(view_mat, 3, 0) = - mat2D_dot_product(camera.current_position, new_right);
    MAT2D_AT(view_mat, 3, 1) = - mat2D_dot_product(camera.current_position, new_up);
    MAT2D_AT(view_mat, 3, 2) = - mat2D_dot_product(camera.current_position, new_forward);
    MAT2D_AT(view_mat, 3, 3) = 1;


    mat2D_free(temp_vec);
    mat2D_free(new_forward);
    mat2D_free(new_up);
    mat2D_free(new_right);
    mat2D_free(DCM);
    mat2D_free(DCM_trans);
}

Point ae_project_point_world2screen(Mat2D view_mat, Mat2D proj_mat, Point src, int window_w, int window_h)
{
    Point view_point = ae_project_point_world2view(view_mat, src);
    Point screen_point = ae_project_point_view2screen(proj_mat, view_point, window_w, window_h);

    return screen_point;
}

Point ae_project_point_world2view(Mat2D view_mat, Point src)
{
    ae_assert_point_is_valid(src);

    Mat2D src_point_mat = mat2D_alloc(1,4);
    Mat2D des_point_mat = mat2D_alloc(1,4);

    Point des_point = {0};

    MAT2D_AT(src_point_mat, 0, 0) = src.x;
    MAT2D_AT(src_point_mat, 0, 1) = src.y;
    MAT2D_AT(src_point_mat, 0, 2) = src.z;
    MAT2D_AT(src_point_mat, 0, 3) = 1;

    mat2D_dot(des_point_mat, src_point_mat, view_mat);

    double w = MAT2D_AT(des_point_mat, 0, 3);
    AE_ASSERT(w == 1);
    des_point.x = MAT2D_AT(des_point_mat, 0, 0) / w;
    des_point.y = MAT2D_AT(des_point_mat, 0, 1) / w;
    des_point.z = MAT2D_AT(des_point_mat, 0, 2) / w;
    des_point.w = w;

    mat2D_free(src_point_mat);
    mat2D_free(des_point_mat);

    return des_point;

}

Point ae_project_point_view2screen(Mat2D proj_mat, Point src, int window_w, int window_h)
{
    ae_assert_point_is_valid(src);

    Mat2D src_point_mat = mat2D_alloc(1,4);
    Mat2D des_point_mat = mat2D_alloc(1,4);
    Point des;

    MAT2D_AT(src_point_mat, 0, 0) = src.x;
    MAT2D_AT(src_point_mat, 0, 1) = src.y;
    MAT2D_AT(src_point_mat, 0, 2) = src.z;
    MAT2D_AT(src_point_mat, 0, 3) = 1;

    mat2D_dot(des_point_mat, src_point_mat, proj_mat);

    double w = MAT2D_AT(des_point_mat, 0, 3);
    if (fabs(w) > 1e-3) {
        des.x = MAT2D_AT(des_point_mat, 0, 0) / w;
        des.y = MAT2D_AT(des_point_mat, 0, 1) / w;
        des.z = MAT2D_AT(des_point_mat, 0, 2) / w;
        des.w = w;
    } else {
        // des.x = MAT2D_AT(des_point_mat, 0, 0);
        // des.y = MAT2D_AT(des_point_mat, 0, 1);
        // des.z = MAT2D_AT(des_point_mat, 0, 2);
        // des.w = 1;

        des.x = 0;
        des.y = 0;
        des.z = 0;
        des.w = 1;
    }

    mat2D_free(src_point_mat);
    mat2D_free(des_point_mat);


    /* scale into view */
    des.x += 1;
    des.y += 1;

    des.x *= 0.5f * window_w;
    des.y *= 0.5f * window_h;

    return des;
}

Tri ae_transform_tri_to_view(Mat2D view_mat, Tri tri)
{
    ae_assert_tri_is_valid(tri);

    Mat2D src_point_mat = mat2D_alloc(1,4);
    Mat2D des_point_mat = mat2D_alloc(1,4);

    Tri des_tri = tri;

    for (int i = 0; i < 3; i++) {
        MAT2D_AT(src_point_mat, 0, 0) = tri.points[i].x;
        MAT2D_AT(src_point_mat, 0, 1) = tri.points[i].y;
        MAT2D_AT(src_point_mat, 0, 2) = tri.points[i].z;
        MAT2D_AT(src_point_mat, 0, 3) = 1;

        mat2D_dot(des_point_mat, src_point_mat, view_mat);

        double w = MAT2D_AT(des_point_mat, 0, 3);
        AE_ASSERT(w == 1);
        des_tri.points[i].x = MAT2D_AT(des_point_mat, 0, 0) / w;
        des_tri.points[i].y = MAT2D_AT(des_point_mat, 0, 1) / w;
        des_tri.points[i].z = MAT2D_AT(des_point_mat, 0, 2) / w;
        des_tri.points[i].w = w;
    }

    mat2D_free(src_point_mat);
    mat2D_free(des_point_mat);

    ae_assert_tri_is_valid(des_tri);

    return des_tri;
}

Quad ae_transform_quad_to_view(Mat2D view_mat, Quad quad)
{
    ae_assert_quad_is_valid(quad);

    Mat2D src_point_mat = mat2D_alloc(1,4);
    Mat2D des_point_mat = mat2D_alloc(1,4);

    Quad des_quad = quad;

    for (int i = 0; i < 4; i++) {
        MAT2D_AT(src_point_mat, 0, 0) = quad.points[i].x;
        MAT2D_AT(src_point_mat, 0, 1) = quad.points[i].y;
        MAT2D_AT(src_point_mat, 0, 2) = quad.points[i].z;
        MAT2D_AT(src_point_mat, 0, 3) = 1;

        mat2D_dot(des_point_mat, src_point_mat, view_mat);

        double w = MAT2D_AT(des_point_mat, 0, 3);
        AE_ASSERT(w == 1);
        des_quad.points[i].x = MAT2D_AT(des_point_mat, 0, 0) / w;
        des_quad.points[i].y = MAT2D_AT(des_point_mat, 0, 1) / w;
        des_quad.points[i].z = MAT2D_AT(des_point_mat, 0, 2) / w;
        des_quad.points[i].w = w;
    }

    mat2D_free(src_point_mat);
    mat2D_free(des_point_mat);

    ae_assert_quad_is_valid(des_quad);

    return des_quad;
}

Tri_mesh ae_project_tri_world2screen(Mat2D proj_mat, Mat2D view_mat, Tri tri, int window_w, int window_h, Mat2D light_direction, Scene *scene)
{
    ae_assert_tri_is_valid(tri);

    Mat2D tri_normal = mat2D_alloc(3, 1);
    Mat2D temp_camera2tri = mat2D_alloc(3, 1);
    Mat2D camera2tri = mat2D_alloc(1, 3);
    Mat2D light_directio_traspose = mat2D_alloc(1, 3);
    Mat2D dot_product = mat2D_alloc(1, 1);
    Tri des_tri = tri;

    ae_calc_normal_to_tri(tri_normal, tri);
    ae_point_to_mat2D(tri.points[1], temp_camera2tri);
    mat2D_sub(temp_camera2tri, scene->camera.current_position);
    mat2D_transpose(camera2tri, temp_camera2tri);
    mat2D_transpose(light_directio_traspose, light_direction);

    /* calc lighting intensity of tri */
    MAT2D_AT(dot_product, 0, 0) = MAT2D_AT(light_directio_traspose, 0, 0) * MAT2D_AT(tri_normal, 0, 0) + MAT2D_AT(light_directio_traspose, 0, 1) * MAT2D_AT(tri_normal, 1, 0) + MAT2D_AT(light_directio_traspose, 0, 2) * MAT2D_AT(tri_normal, 2, 0);
    des_tri.light_intensity = MAT2D_AT(dot_product, 0, 0);

    des_tri.light_intensity = fminf(1, des_tri.light_intensity);

    if (des_tri.light_intensity <= 0.4) {
        des_tri.light_intensity = 0.4;
    }

    /* calc if tri is visible to the camera */
    MAT2D_AT(dot_product, 0, 0) = MAT2D_AT(camera2tri, 0, 0) * MAT2D_AT(tri_normal, 0, 0) + MAT2D_AT(camera2tri, 0, 1) * MAT2D_AT(tri_normal, 1, 0) + MAT2D_AT(camera2tri, 0, 2) * MAT2D_AT(tri_normal, 2, 0);
    if (MAT2D_AT(dot_product, 0, 0) < 0) {
        des_tri.to_draw = true;
    } else {
        des_tri.to_draw = false;
    }

    /* transform tri to camera view */
    tri = ae_transform_tri_to_view(view_mat, tri);

    // Tri_mesh temp_tri_array; 
    // ada_init_array(Tri, temp_tri_array);
    // ada_appand(Tri, temp_tri_array, tri);
    /* clip tir */
    Tri clipped_tri1 = {0};
    Tri clipped_tri2 = {0};
    Mat2D z_plane_p = mat2D_alloc(3, 1);
    Mat2D z_plane_n = mat2D_alloc(3, 1);
    mat2D_fill(z_plane_p, 0);
    mat2D_fill(z_plane_n, 0);
    MAT2D_AT(z_plane_p, 2, 0) = scene->camera.z_near+0.01;
    MAT2D_AT(z_plane_n, 2, 0) = 1;

    int num_clipped_tri = ae_tri_clip_with_plane(tri, z_plane_p, z_plane_n, &clipped_tri1, &clipped_tri2);
    Tri_mesh temp_tri_array; 
    ada_init_array(Tri, temp_tri_array);
    if (num_clipped_tri == -1) {
        fprintf(stderr, "%s:%d: [error] problem with clipping triangles\n", __FILE__, __LINE__);
        exit(1);
    } else if (num_clipped_tri == 0) {
        ;
    } else if (num_clipped_tri == 1) {
        ae_assert_tri_is_valid(clipped_tri1);
        ada_appand(Tri, temp_tri_array, clipped_tri1);
    } else if (num_clipped_tri == 2) {
        ae_assert_tri_is_valid(clipped_tri1);
        ae_assert_tri_is_valid(clipped_tri2);
        ada_appand(Tri, temp_tri_array, clipped_tri1);
        ada_appand(Tri, temp_tri_array, clipped_tri2);
    }
    mat2D_free(z_plane_p);
    mat2D_free(z_plane_n);

    for (size_t temp_tri_index = 0; temp_tri_index < temp_tri_array.length; temp_tri_index++) {
        /* project tri to screen */
        for (int i = 0; i < 3; i++) {
            des_tri.points[i] = ae_project_point_view2screen(proj_mat, temp_tri_array.elements[temp_tri_index].points[i], window_w, window_h);

            if (des_tri.points[i].w) {
                des_tri.tex_points[i].x /= des_tri.points[i].w;
                des_tri.tex_points[i].y /= des_tri.points[i].w;
                des_tri.tex_points[i].z /= des_tri.points[i].w;
                des_tri.tex_points[i].w  = des_tri.points[i].w;
            }

        }
        ae_assert_tri_is_valid(des_tri);
        ae_set_tri_center_zmin_zmax(&des_tri);
        temp_tri_array.elements[temp_tri_index] = des_tri;
    }


    mat2D_free(tri_normal);
    mat2D_free(temp_camera2tri);
    mat2D_free(camera2tri);
    mat2D_free(light_directio_traspose);
    mat2D_free(dot_product);

    return temp_tri_array;
}

void ae_project_tri_mesh_world2screen(Mat2D proj_mat, Mat2D view_mat, Tri_mesh *des, Tri_mesh src, int window_w, int window_h, Mat2D light_direction, Scene *scene)
{
    Tri_mesh temp_des = *des;

    size_t i;
    for (i = 0; i < src.length; i++) {
        Tri_mesh temp_tri_array = ae_project_tri_world2screen(proj_mat, view_mat, src.elements[i], window_w, window_h, light_direction, scene);

        for (size_t tri_index = 0; tri_index < temp_tri_array.length; tri_index++) {
            Tri temp_tri = temp_tri_array.elements[tri_index];
            ada_appand(Tri, temp_des, temp_tri);
        }

        free(temp_tri_array.elements);
    }

    /* clip tir */
    int offset = 0;
    Mat2D top_p = mat2D_alloc(3, 1);
    Mat2D top_n = mat2D_alloc(3, 1);
    mat2D_fill(top_p, 0);
    mat2D_fill(top_n, 0);
    MAT2D_AT(top_p, 1, 0) = 0 + offset;
    MAT2D_AT(top_n, 1, 0) = 1;

    Mat2D bottom_p = mat2D_alloc(3, 1);
    Mat2D bottom_n = mat2D_alloc(3, 1);
    mat2D_fill(bottom_p, 0);
    mat2D_fill(bottom_n, 0);
    MAT2D_AT(bottom_p, 1, 0) = window_h - offset;
    MAT2D_AT(bottom_n, 1, 0) = -1;

    Mat2D left_p = mat2D_alloc(3, 1);
    Mat2D left_n = mat2D_alloc(3, 1);
    mat2D_fill(left_p, 0);
    mat2D_fill(left_n, 0);
    MAT2D_AT(left_p, 0, 0) = 0 + offset;
    MAT2D_AT(left_n, 0, 0) = 1;

    Mat2D right_p = mat2D_alloc(3, 1);
    Mat2D right_n = mat2D_alloc(3, 1);
    mat2D_fill(right_p, 0);
    mat2D_fill(right_n, 0);
    MAT2D_AT(right_p, 0, 0) = window_w - offset;
    MAT2D_AT(right_n, 0, 0) = -1;

    for (int plane_number = 0; plane_number < 4; plane_number++) {
        for (int tri_index = 0; tri_index < (int)(temp_des.length); tri_index++) {
            if (temp_des.length == 0) {
                break;
            }
            // if (temp_des.elements[tri_index].to_draw == false) {
            //     ada_remove_unordered(Tri, temp_des, tri_index);
            //     tri_index--;
            //     tri_index = (int)fmaxf((float)tri_index, 0.0f);
            //     continue;
            // }
            Tri clipped_tri1 = {0};
            Tri clipped_tri2 = {0};
            int num_clipped_tri;
            switch (plane_number) {
                case 0:
                    num_clipped_tri = ae_tri_clip_with_plane(temp_des.elements[tri_index], top_p, top_n, &clipped_tri1, &clipped_tri2);
                break;
                case 1:
                    num_clipped_tri = ae_tri_clip_with_plane(temp_des.elements[tri_index], right_p, right_n, &clipped_tri1, &clipped_tri2);
                break;
                case 2:
                    num_clipped_tri = ae_tri_clip_with_plane(temp_des.elements[tri_index], bottom_p, bottom_n, &clipped_tri1, &clipped_tri2);
                break;
                case 3:
                    num_clipped_tri = ae_tri_clip_with_plane(temp_des.elements[tri_index], left_p, left_n, &clipped_tri1, &clipped_tri2);
                break;
            }
            if (num_clipped_tri == -1) {
                fprintf(stderr, "%s:%d: [error] problem with clipping triangles\n", __FILE__, __LINE__);
                exit(1);
            } else if (num_clipped_tri == 0) {
                ada_remove_unordered(Tri, temp_des, tri_index);
                tri_index--;
                tri_index = (int)fmaxf((float)tri_index, 0.0f);
            } else if (num_clipped_tri == 1) {
                ae_assert_tri_is_valid(clipped_tri1);
                temp_des.elements[tri_index] = clipped_tri1;
            } else if (num_clipped_tri == 2) {
                ae_assert_tri_is_valid(clipped_tri1);
                ae_assert_tri_is_valid(clipped_tri2);
                temp_des.elements[tri_index] = clipped_tri1;
                ada_insert_unordered(Tri, temp_des, clipped_tri2, tri_index+1);
            }
        }
    }

    // if (temp_des.length > 2) {
    //     ae_qsort_tri(temp_des.elements, 0, temp_des.length-1);
    // }

    mat2D_free(top_p);
    mat2D_free(top_n);
    mat2D_free(bottom_p);
    mat2D_free(bottom_n);
    mat2D_free(left_p);
    mat2D_free(left_n);
    mat2D_free(right_p);
    mat2D_free(right_n);

    *des = temp_des;
}

Quad_mesh ae_project_quad_world2screen(Mat2D proj_mat, Mat2D view_mat, Quad quad, int window_w, int window_h, Mat2D light_direction, Scene *scene)
{
    ae_assert_quad_is_valid(quad);

    Mat2D quad_normal = mat2D_alloc(3, 1);
    Mat2D temp_camera2quad = mat2D_alloc(3, 1);
    Mat2D camera2quad = mat2D_alloc(1, 3);
    Mat2D light_directio_traspose = mat2D_alloc(1, 3);
    Mat2D dot_product = mat2D_alloc(1, 1);
    Quad des_quad = quad;

    ae_calc_normal_to_quad(quad_normal, quad);
    ae_point_to_mat2D(quad.points[0], temp_camera2quad);
    mat2D_sub(temp_camera2quad, scene->camera.current_position);
    mat2D_transpose(camera2quad, temp_camera2quad);
    mat2D_transpose(light_directio_traspose, light_direction);

    /* calc lighting intensity of tri */
    MAT2D_AT(dot_product, 0, 0) = MAT2D_AT(light_directio_traspose, 0, 0) * MAT2D_AT(quad_normal, 0, 0) + MAT2D_AT(light_directio_traspose, 0, 1) * MAT2D_AT(quad_normal, 1, 0) + MAT2D_AT(light_directio_traspose, 0, 2) * MAT2D_AT(quad_normal, 2, 0);
    des_quad.light_intensity = MAT2D_AT(dot_product, 0, 0);

    if (des_quad.light_intensity <= 0.1) {
        des_quad.light_intensity = 0.1;
    }

    /* calc if tri is visible to the camera */
    MAT2D_AT(dot_product, 0, 0) = MAT2D_AT(camera2quad, 0, 0) * MAT2D_AT(quad_normal, 0, 0) + MAT2D_AT(camera2quad, 0, 1) * MAT2D_AT(quad_normal, 1, 0) + MAT2D_AT(camera2quad, 0, 2) * MAT2D_AT(quad_normal, 2, 0);
    if (MAT2D_AT(dot_product, 0, 0) < 0) {
        des_quad.to_draw = true;
    } else {
        des_quad.to_draw = false;
    }

    /* transform quad to camera view */
    quad = ae_transform_quad_to_view(view_mat, quad);

    /* clip quad */
    Quad  clipped_quad = {0};
    Mat2D z_plane_p = mat2D_alloc(3, 1);
    Mat2D z_plane_n = mat2D_alloc(3, 1);
    mat2D_fill(z_plane_p, 0);
    mat2D_fill(z_plane_n, 0);
    MAT2D_AT(z_plane_p, 2, 0) = scene->camera.z_near+0.01;
    MAT2D_AT(z_plane_n, 2, 0) = 1;

    int num_clipped_quad = ae_quad_clip_with_plane(quad, z_plane_p, z_plane_n, &clipped_quad);
    Quad_mesh temp_quad_array; 
    ada_init_array(Quad, temp_quad_array);
    if (num_clipped_quad == -1) {
        fprintf(stderr, "%s:%d: [error] problem with clipping quad\n", __FILE__, __LINE__);
        exit(1);
    } else if (num_clipped_quad == 0) {
        ;
    } else if (num_clipped_quad == 1) {
        ae_assert_quad_is_valid(clipped_quad);
        ada_appand(Quad, temp_quad_array, clipped_quad);
    }
    mat2D_free(z_plane_p);
    mat2D_free(z_plane_n);

    for (size_t temp_quad_index = 0; temp_quad_index < temp_quad_array.length; temp_quad_index++) {
        /* project quad to screen */
        for (int i = 0; i < 4; i++) {
            des_quad.points[i] = ae_project_point_view2screen(proj_mat, temp_quad_array.elements[temp_quad_index].points[i], window_w, window_h);

        }
        ae_assert_quad_is_valid(des_quad);
        temp_quad_array.elements[temp_quad_index] = des_quad;
    }


    mat2D_free(quad_normal);
    mat2D_free(temp_camera2quad);
    mat2D_free(camera2quad);
    mat2D_free(light_directio_traspose);
    mat2D_free(dot_product);

    return temp_quad_array;
}

void ae_project_quad_mesh_world2screen(Mat2D proj_mat, Mat2D view_mat, Quad_mesh *des, Quad_mesh src, int window_w, int window_h, Mat2D light_direction, Scene *scene)
{
    Quad_mesh temp_des = *des;

    size_t i;
    for (i = 0; i < src.length; i++) {
        Quad_mesh temp_quad_array = ae_project_quad_world2screen(proj_mat, view_mat, src.elements[i], window_w, window_h, light_direction, scene);

        for (size_t quad_index = 0; quad_index < temp_quad_array.length; quad_index++) {
            Quad temp_quad = temp_quad_array.elements[quad_index];
            ada_appand(Quad, temp_des, temp_quad);
        }

        free(temp_quad_array.elements);
    }


    /* clip quad */
    int offset = 50;
    Mat2D top_p = mat2D_alloc(3, 1);
    Mat2D top_n = mat2D_alloc(3, 1);
    mat2D_fill(top_p, 0);
    mat2D_fill(top_n, 0);
    MAT2D_AT(top_p, 1, 0) = 0 + offset;
    MAT2D_AT(top_n, 1, 0) = 1;

    Mat2D bottom_p = mat2D_alloc(3, 1);
    Mat2D bottom_n = mat2D_alloc(3, 1);
    mat2D_fill(bottom_p, 0);
    mat2D_fill(bottom_n, 0);
    MAT2D_AT(bottom_p, 1, 0) = window_h - offset;
    MAT2D_AT(bottom_n, 1, 0) = -1;

    Mat2D left_p = mat2D_alloc(3, 1);
    Mat2D left_n = mat2D_alloc(3, 1);
    mat2D_fill(left_p, 0);
    mat2D_fill(left_n, 0);
    MAT2D_AT(left_p, 0, 0) = 0 + offset;
    MAT2D_AT(left_n, 0, 0) = 1;

    Mat2D right_p = mat2D_alloc(3, 1);
    Mat2D right_n = mat2D_alloc(3, 1);
    mat2D_fill(right_p, 0);
    mat2D_fill(right_n, 0);
    MAT2D_AT(right_p, 0, 0) = window_w - offset;
    MAT2D_AT(right_n, 0, 0) = -1;

    for (int plane_number = 0; plane_number < 4; plane_number++) {
        for (int quad_index = 0; quad_index < (int)(temp_des.length); quad_index++) {
            if (temp_des.length == 0) {
                break;
            }
            // if (temp_des.elements[quad_index].to_draw == false) {
            //     ada_remove_unordered(Quad, temp_des, quad_index);
            //     quad_index--;
            //     quad_index = (int)fmaxf((float)quad_index, 0.0f);
            //     continue;
            // }
            Quad clipped_quad = {0};
            int num_clipped_quad;
            switch (plane_number) {
                case 0:
                    num_clipped_quad = ae_quad_clip_with_plane(temp_des.elements[quad_index], top_p, top_n, &clipped_quad);
                break;
                case 1:
                    num_clipped_quad = ae_quad_clip_with_plane(temp_des.elements[quad_index], right_p, right_n, &clipped_quad);
                break;
                case 2:
                    num_clipped_quad = ae_quad_clip_with_plane(temp_des.elements[quad_index], bottom_p, bottom_n, &clipped_quad);
                break;
                case 3:
                    num_clipped_quad = ae_quad_clip_with_plane(temp_des.elements[quad_index], left_p, left_n, &clipped_quad);
                break;
            }
            if (num_clipped_quad == -1) {
                fprintf(stderr, "%s:%d: [error] problem with clipping quads\n", __FILE__, __LINE__);
                exit(1);
            } else if (num_clipped_quad == 0) {
                ada_remove_unordered(Quad, temp_des, quad_index);
                quad_index--;
                quad_index = (int)fmaxf((float)quad_index, 0.0f);
            } else if (num_clipped_quad == 1) {
                ae_assert_quad_is_valid(clipped_quad);
                temp_des.elements[quad_index] = clipped_quad;
            }
        }
    }

    mat2D_free(top_p);
    mat2D_free(top_n);
    mat2D_free(bottom_p);
    mat2D_free(bottom_n);
    mat2D_free(left_p);
    mat2D_free(left_n);
    mat2D_free(right_p);
    mat2D_free(right_n);

    *des = temp_des;
}

void ae_project_grid_world2screen(Mat2D proj_mat, Mat2D view_mat, Grid des, Grid src, int window_w, int window_h)
{
    for (size_t curve_index = 0; curve_index < src.curves.length; curve_index++) {
        for (size_t point_index = 0; point_index < src.curves.elements[curve_index].length; point_index++) {
            Point src_point = src.curves.elements[curve_index].elements[point_index];

            Point des_point = ae_project_point_world2screen(view_mat, proj_mat, src_point, window_w, window_h);

            des.curves.elements[curve_index].elements[point_index] = des_point;
        }
    }
}

/* swap: interchange v[i] and v[j] */
void ae_swap_tri(Tri *v, int i, int j)
{
    Tri temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

bool ae_compare_tri(Tri t1, Tri t2)
{
    // int z_min_1 = fmin(t1.points[0].z, fmin(t1.points[1].z, t1.points[2].z));
    // int z_min_2 = fmin(t2.points[0].z, fmin(t2.points[1].z, t2.points[2].z));

    // return z_min_1 > z_min_2;

    // int z_ave_1 = t1.points[0].z + t1.points[1].z + t1.points[2].z;
    // int z_ave_2 = t2.points[0].z + t2.points[1].z + t2.points[2].z;

    // return z_ave_1 > z_ave_2;

    // return t1.center.z > t2.center.z;

    // return t1.z_min > t2.z_min;

    return t1.z_max > t2.z_max;
}

/* qsort: sort v[left]...v[right] int increasing order */
void ae_qsort_tri(Tri *v, int left, int right)
{
    int i, last;

    if (left >= right)                  /* do nothing if array contains */
        return;                         /* fewer than two elements */
    ae_swap_tri(v, left, (left + right) / 2);  /* move partition elem */
    last = left;                        /* to v[0] */
    for (i = left + 1; i <= right; i++) /* partition */
        if (ae_compare_tri(v[i], v[left]))
            ae_swap_tri(v, ++last, i);
    ae_swap_tri(v, left, last); /* restore partition elem */
    ae_qsort_tri(v, left, last - 1);
    ae_qsort_tri(v, last + 1, right);
}

double ae_linear_map(double s, double min_in, double max_in, double min_out, double max_out)
{
    return (min_out + ((s-min_in)*(max_out-min_out))/(max_in-min_in));
}

void ae_copy_z_buffer_to_screen(Mat2D_uint32 screen_mat, Mat2D inv_z_buffer)
{
    double max_inv_z = 0;
    double min_inv_z = DBL_MAX;
    for (size_t i = 0; i < inv_z_buffer.rows; i++) {
        for (size_t j = 0; j < inv_z_buffer.cols; j++) {
            if (MAT2D_AT(inv_z_buffer, i, j) > max_inv_z) {
                max_inv_z = MAT2D_AT(inv_z_buffer, i, j);
            }
            if (MAT2D_AT(inv_z_buffer, i, j) < min_inv_z && MAT2D_AT(inv_z_buffer, i, j) > 0) {
                min_inv_z = MAT2D_AT(inv_z_buffer, i, j);
            }
        }
    }
    for (size_t i = 0; i < inv_z_buffer.rows; i++) {
        for (size_t j = 0; j < inv_z_buffer.cols; j++) {
            double z_fraq = MAT2D_AT(inv_z_buffer, i, j);
            z_fraq = fmax(z_fraq, min_inv_z);
            z_fraq = ae_linear_map(z_fraq, min_inv_z, max_inv_z, 0.1, 1);
            uint32_t color = RGB_hexRGB(0xFF*z_fraq, 0xFF*z_fraq, 0xFF*z_fraq); 
            MAT2D_AT_UINT32(screen_mat, i, j) = color;
        }
    }
}



#endif /* ALMOG_ENGINE_IMPLEMENTATION */ //