#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Matrix2D.h"
#include <stdlib.h>
#include <stdint.h>
#include "Almog_Engine.h"

#ifndef WINDOW_WIDTH
#define WINDOW_WIDTH (16 * 80)
#endif

#ifndef WINDOW_HEIGHT
#define WINDOW_HEIGHT (9 * 80)
#endif

#ifndef FPS
#define FPS 100
#endif

#ifndef FRAME_TARGET_TIME
#define FRAME_TARGET_TIME (1000 / FPS)
#endif

#define dprintSTRING(expr) printf(#expr " = %s\n", expr)
#define dprintCHAR(expr) printf(#expr " = %c\n", expr)
#define dprintINT(expr) printf(#expr " = %d\n", expr)
#define dprintD(expr) printf(#expr " = %g\n", expr)
#define dprintSIZE_T(expr) printf(#expr " = %zu\n", expr)

#ifndef PI
    #ifndef __USE_MISC
    #define __USE_MISC
    #endif
    #include <math.h>
    #define PI M_PI
#endif

typedef struct {
    int game_is_running;
    float delta_time;
    float elapsed_time;
    float const_fps;
    float fps;
    float frame_target_time;
    int to_render;
    int to_update;
    size_t previous_frame_time;
    int left_button_pressed;
    int to_limit_fps;
    int to_clear_renderer;

    int space_bar_was_pressed;
    int w_was_pressed;
    int s_was_pressed;
    int a_was_pressed;
    int d_was_pressed;
    int e_was_pressed;
    int q_was_pressed;

    SDL_Window *window;
    int window_w;
    int window_h;
    SDL_Renderer *renderer;

    SDL_Surface *window_surface;
    SDL_Texture *window_texture;

    Mat2D_uint32 window_pixels_mat;
    Mat2D inv_z_buffer_mat;
    
    Scene scene;
} game_state_t;

int initialize_window(game_state_t *game_state);
void setup_window(game_state_t *game_state);
void process_input_window(game_state_t *game_state);
void update_window(game_state_t *game_state);
void render_window(game_state_t *game_state);
void destroy_window(game_state_t *game_state);
void fix_framerate(game_state_t *game_state);
void setup(game_state_t *game_state);
void update(game_state_t *game_state);
void render(game_state_t *game_state);

void check_window_mat_size(game_state_t *game_state);
void copy_mat_to_surface_RGB(game_state_t *game_state);

int main()
{
    game_state_t game_state;

    game_state.game_is_running = 0;
    game_state.delta_time = 0;
    game_state.elapsed_time = 0;
    game_state.const_fps = FPS;
    game_state.fps = 0;
    game_state.frame_target_time = FRAME_TARGET_TIME;

    game_state.space_bar_was_pressed = 0;
    game_state.w_was_pressed = 0;
    game_state.s_was_pressed = 0;
    game_state.a_was_pressed = 0;
    game_state.d_was_pressed = 0;
    game_state.e_was_pressed = 0;
    game_state.q_was_pressed = 0;

    game_state.to_render = 1;
    game_state.to_update = 1;
    game_state.previous_frame_time = 0;
    game_state.left_button_pressed = 0;
    game_state.to_limit_fps = 1;
    game_state.to_clear_renderer = 1;
    game_state.window = NULL;
    game_state.window_w = WINDOW_WIDTH;
    game_state.window_h = WINDOW_HEIGHT;
    game_state.renderer = NULL;

    game_state.game_is_running = !initialize_window(&game_state);

    setup_window(&game_state);

    while (game_state.game_is_running) {
        process_input_window(&game_state);
        if (game_state.to_update) {
            update_window(&game_state);
        }
        if (game_state.to_render) {
            render_window(&game_state);
        }
        
    }
    destroy_window(&game_state);

    return 0;
}

int initialize_window(game_state_t *game_state)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        fprintf(stderr, "%s:%d: [Error] initializing SDL.\n", __FILE__, __LINE__);
        return -1;
    }

    game_state->window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              game_state->window_w,
                              game_state->window_h,
                              SDL_WINDOW_RESIZABLE
                              );
    if (!game_state->window) {
        fprintf(stderr, "%s:%d: [Error] creating SDL window.\n", __FILE__, __LINE__);
        return -1;
    }

    game_state->renderer = SDL_CreateRenderer(game_state->window, -1, 0);
    if (!game_state->renderer) {
        fprintf(stderr, "%s:%d: [Error] creating SDL renderer.\n", __FILE__, __LINE__);
        return -1;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "%s:%d: [Error] initializing SDL_ttf.\n", __FILE__, __LINE__);
        return -1;
    }

    return 0;
}

void setup_window(game_state_t *game_state)
{

    game_state->window_surface = SDL_GetWindowSurface(game_state->window);

    game_state->window_pixels_mat = mat2D_alloc_uint32(game_state->window_h, game_state->window_w);
    game_state->inv_z_buffer_mat = mat2D_alloc(game_state->window_h, game_state->window_w);

    game_state->scene = ae_init_scene(game_state->window_h, game_state->window_w);

    /*-----------------------------------*/

    setup(game_state);

}

void process_input_window(game_state_t *game_state)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                game_state->game_is_running = 0;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game_state->game_is_running = 0;
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    if (!game_state->space_bar_was_pressed) {
                        game_state->to_render = 0;
                        game_state->to_update = 0;
                        game_state->space_bar_was_pressed = 1;
                        break;
                    }
                    if (game_state->space_bar_was_pressed) {
                        game_state->to_render = 1;
                        game_state->to_update = 1;
                        game_state->previous_frame_time = SDL_GetTicks();
                        game_state->space_bar_was_pressed = 0;
                        break;
                    }
                }
                if (event.key.keysym.sym == SDLK_w) {
                    MAT2D_AT(game_state->scene.camera.offset_position, 1, 0) -= 0.05;
                }
                if (event.key.keysym.sym == SDLK_s) {
                    MAT2D_AT(game_state->scene.camera.offset_position, 1, 0) += 0.05;
                }
                if (event.key.keysym.sym == SDLK_d) {
                    MAT2D_AT(game_state->scene.camera.offset_position, 0, 0) += 0.05;
                }
                if (event.key.keysym.sym == SDLK_a) {
                    MAT2D_AT(game_state->scene.camera.offset_position, 0, 0) -= 0.05;
                }
                if (event.key.keysym.sym == SDLK_e) {
                    MAT2D_AT(game_state->scene.camera.offset_position, 2, 0) += 0.05;
                }
                if (event.key.keysym.sym == SDLK_q) {
                    MAT2D_AT(game_state->scene.camera.offset_position, 2, 0) -= 0.05;
                }
                if (event.key.keysym.sym == SDLK_LEFT) {
                    game_state->scene.camera.pitch_offset_deg -= 1;
                }
                if (event.key.keysym.sym == SDLK_RIGHT) {
                    game_state->scene.camera.pitch_offset_deg += 1;
                }
                if (event.key.keysym.sym == SDLK_UP) {
                    game_state->scene.camera.roll_offset_deg += 1;
                    if (game_state->scene.camera.roll_offset_deg > 89) {
                        game_state->scene.camera.roll_offset_deg = 89;
                    }
                }
                if (event.key.keysym.sym == SDLK_DOWN) {
                    game_state->scene.camera.roll_offset_deg -= 1;
                    if (game_state->scene.camera.roll_offset_deg < -89) {
                        game_state->scene.camera.roll_offset_deg = -89;
                    }
                }
                if (event.key.keysym.sym == SDLK_r) {
                    ae_reset_camera_pos(&(game_state->scene));
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    game_state->left_button_pressed = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    game_state->left_button_pressed = 0;
                }
                break;
        }
    }
}

void update_window(game_state_t *game_state)
{
    SDL_GetWindowSize(game_state->window, &(game_state->window_w), &(game_state->window_h));

    fix_framerate(game_state);
    game_state->elapsed_time += game_state->delta_time;
    game_state->fps = 1.0f / game_state->delta_time;
    game_state->frame_target_time = 1000/game_state->const_fps;

    char fps_count[100];
    if (!game_state->to_limit_fps) {
        sprintf(fps_count, "dt = %5.02f [ms]", game_state->delta_time*1000);
    } else {
        sprintf(fps_count, "FPS = %5.2f", game_state->fps);
    }

    if (game_state->elapsed_time*10-(int)(game_state->elapsed_time*10) < 0.1) {
        SDL_SetWindowTitle(game_state->window, fps_count);
    }

    check_window_mat_size(game_state);

    /*----------------------------------------------------------------------------*/

    update(game_state);

}

void render_window(game_state_t *game_state)
{
    if (game_state->to_clear_renderer) {
        // SDL_SetRenderDrawColor(game_state->renderer, HexARGB_RGBA(0xFF181818));
        // SDL_RenderClear(game_state->renderer);
        // mat2D_fill(game_state->window_pixels_mat, 0x181818);
        memset(game_state->window_pixels_mat.elements, 0x20, sizeof(uint32_t) * game_state->window_pixels_mat.rows * game_state->window_pixels_mat.cols);
        /* not using mat2D_fill but using memset because it is way faster, so the buffer needs to be of 1/z */
        memset(game_state->inv_z_buffer_mat.elements, 0x0, sizeof(double) * game_state->inv_z_buffer_mat.rows * game_state->inv_z_buffer_mat.cols);
    }
    /*------------------------------------------------------------------------*/

    render(game_state);

    /*------------------------------------------------------------------------*/

    copy_mat_to_surface_RGB(game_state);
    SDL_UpdateWindowSurface(game_state->window);

}

void destroy_window(game_state_t *game_state)
{
    mat2D_free_uint32(game_state->window_pixels_mat);

    if (!game_state->window_surface) SDL_FreeSurface(game_state->window_surface);
    if (!game_state->window_texture) SDL_DestroyTexture(game_state->window_texture);

    SDL_DestroyRenderer(game_state->renderer);
    SDL_DestroyWindow(game_state->window);

    SDL_Quit();

    (void)game_state;
}

void fix_framerate(game_state_t *game_state)
{
    int time_ellapsed = SDL_GetTicks() - game_state->previous_frame_time;
    int time_to_wait = game_state->frame_target_time - time_ellapsed;
    if (time_to_wait > 0 && time_to_wait < game_state->frame_target_time) {
        if (game_state->to_limit_fps) {
            SDL_Delay(time_to_wait);
        }
    }
    game_state->delta_time = (SDL_GetTicks() - game_state->previous_frame_time) / 1000.0f;
    game_state->previous_frame_time = SDL_GetTicks();
}

#ifndef SETUP
#define SETUP
void setup(game_state_t *game_state) { (void)game_state; }
#endif

#ifndef UPDATE
#define UPDATE
void update(game_state_t *game_state) { (void)game_state; }
#endif

#ifndef RENDER
#define RENDER
void render(game_state_t *game_state) { (void)game_state; }
#endif

void check_window_mat_size(game_state_t *game_state)
{
    if (game_state->window_h != (int)game_state->window_pixels_mat.rows || game_state->window_w != (int)game_state->window_pixels_mat.cols) {
        mat2D_free_uint32(game_state->window_pixels_mat);
        mat2D_free(game_state->inv_z_buffer_mat);
        SDL_FreeSurface(game_state->window_surface);

        game_state->window_pixels_mat = mat2D_alloc_uint32(game_state->window_h, game_state->window_w);
        game_state->inv_z_buffer_mat = mat2D_alloc(game_state->window_h, game_state->window_w);
        game_state->scene.camera.aspect_ratio = (float)(game_state->window_h) / (float)(game_state->window_w);

        game_state->window_surface = SDL_GetWindowSurface(game_state->window);
    }
}

void copy_mat_to_surface_RGB(game_state_t *game_state)
{
    SDL_LockSurface(game_state->window_surface);

    memcpy(game_state->window_surface->pixels, game_state->window_pixels_mat.elements, sizeof(uint32_t) * game_state->window_pixels_mat.rows * game_state->window_pixels_mat.cols);

    SDL_UnlockSurface(game_state->window_surface);
}


