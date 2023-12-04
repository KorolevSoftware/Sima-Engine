//------------------------------------------------------------------------------
//  triangle-sapp.c
//  Simple 2D rendering from vertex buffer.
//------------------------------------------------------------------------------
#include "mesh.h"

#define SOKOL_D3D11
#define SOKOL_IMPL
#include "sokol_app.h"
#include "sokol_gfx.h"
#include "sokol_log.h"
#include "sokol_glue.h"
#include "shaders/triangle-sapp.glsl.h"

//#include "SDL2/SDL.h"

// application state
static struct {
    sg_pass_action pass_action;
    struct mesh* mesh;
} state;

static void init(void) {
    sg_setup(&(sg_desc) {
        .context = sapp_sgcontext(),
        .logger.func = slog_func,
    });

    // a vertex buffer with 3 vertices
    float vertices[] = {
        // positions            // colors
         0.0f,  0.5f, 0.5f,     1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, 0.5f,     0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f,     0.0f, 0.0f, 1.0f, 1.0f
    };

    // create shader from code-generated sg_shader_desc
    sg_shader shd = sg_make_shader(triangle_shader_desc(sg_query_backend()));
    
    // create a pipeline object (default render states are fine for triangle)
    sg_pipeline pip = sg_make_pipeline(&(sg_pipeline_desc) {
        .shader = shd,
            // if the vertex layout doesn't have gaps, don't need to provide strides and offsets
        .layout = {
            .attrs = {
                        [ATTR_vs_position].format = SG_VERTEXFORMAT_FLOAT3,
                        [ATTR_vs_color0].format = SG_VERTEXFORMAT_FLOAT4
                     }
        },
        .label = "triangle-pipeline"
    });
    state.mesh = create_mesh(pip, vertices, sizeof(vertices));
    // a pass action to clear framebuffer to black
    state.pass_action = (sg_pass_action) {
        .colors[0] = {.load_action = SG_LOADACTION_CLEAR, .clear_value = {0.0f, 0.0f, 0.0f, 1.0f } }
    };
}

void frame(void) {
    //sg_begin_pass();
    sg_begin_default_pass(&state.pass_action, sapp_width(), sapp_height());
    draw_mesh(state.mesh);
    //__dbgui_draw();
    sg_end_pass();
    sg_commit();
}

void cleanup(void) {
    //__dbgui_shutdown();
    sg_shutdown();
}


//int main(int argc, char* argv[]) {
//    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
//        //std::cerr << "Failed to init SDL: " << SDL_GetError() << "\n";
//        return -1;
//    }
//    SDL_Window* window = SDL_CreateWindow("SDL2 + DX12",
//        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
//        SDL_WINDOW_RESIZABLE);
//
//    SDL_RenderGetD3D11Device
//    //SDL_GetRendererInfo
//
//}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc) {
        .init_cb = init,
            .frame_cb = frame,
            .cleanup_cb = cleanup,
            .event_cb = NULL,
            .width = 640,
            .height = 480,
            .window_title = "Triangle (sokol-app)",
            .icon.sokol_default = true,
            .logger.func = slog_func,
    };
}