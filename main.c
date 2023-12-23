//------------------------------------------------------------------------------
//  triangle-sapp.c
//  Simple 2D rendering from vertex buffer.
//------------------------------------------------------------------------------

#include <stdbool.h>
#include "render.h"
#include "sokol_app.h"
#include "sokol_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <game_object.h>
#include "../dependency/cmath/mathc.h"
#define STB_IMAGE_IMPLEMENTATION  
#include "STDImage.h"

const char* game_script =
"264 constant down "
"265 constant up "
"263 constant left "
"262 constant right "

"variable posX "
"variable posY "
"variable posZ "

//": init ; "

": input "
    "get_position posX ! posY ! posZ ! "
    "dup down = if posY @ 1  - posY ! then "
    "dup up = if posY @ 1 + posY ! then "
    "dup left = if posX @ 1 - posX ! then "
    "dup right = if posX @ 1 + posX ! then "
    "posZ @ posY @ posX @ set_position "
    "drop "
" ; ";

struct GameObject* gm;
static struct mat4 project;

const float display_width = 800;
const float display_height = 600;
const float zoom = 1;
const float dpi_ratio = 1;
const float near_z = 0.1;
const float far_z = 100;

static void fixed_zoom(int windows_width, int windows_height) {
    int projected_width = windows_width / (zoom / dpi_ratio);
    int projected_height = windows_height / (zoom / dpi_ratio);
    int xoffset = -(projected_width - display_width) / 2;
    int yoffset = -(projected_height - display_height) / 2;
    mat4_orthoLH(&project, xoffset, xoffset + projected_width, yoffset, yoffset + projected_height, near_z, far_z);
}

static void fixed_auto(int windows_width, int windows_height) {
    float zoom_factor = min(windows_width / display_width, windows_height / display_height) * zoom * dpi_ratio;
    float projected_width = windows_width / (zoom_factor / dpi_ratio);
    float projected_height = windows_height / (zoom_factor / dpi_ratio);
    float xoffset = -(projected_width - display_width) / 2;
    float yoffset = -(projected_height - display_height) / 2;
    mat4_orthoLH(&project, xoffset, xoffset + projected_width, yoffset, yoffset + projected_height, near_z, far_z);
}

static void init(void) {
    ARender->Create();
    fixed_auto(640, 480);
    const char* path = "e:\\Project\\Defold\\defold-games-master\\Galaxy Force\\assets\\png\\boss2.png";
    int sprite_width, sprite_height, sprite_depth;
    uint8_t* bitmapData = stbi_load(path, &sprite_width, &sprite_height, &sprite_depth, 0);
    gm = AGameObject->Create(game_script, bitmapData, sprite_width, sprite_height, sprite_depth);
    AGameObject->SetPosition(gm, (struct vec3) { 800, 600, 50 });
    free(bitmapData);
}

void cleanup(void) {
    AGameObject->Releace(gm);
    ARender->Release();
}

void render(int width, int height) { 
    AGameObject->Bind(gm, ARender->GetBinder());
    ARender->Begin(width, height);  // BEGIN DRAW

    struct mat4 result;

    struct mat4* world = AGameObject->GetWorldMatrix(gm);

    mat4_multiply(&result, &project, world);

    ARender->SetMatrix4x4(&result);
    AGameObject->Draw(gm);

    ARender->End(); // END DRAW
}

void frame(void) {
    render(sapp_width(), sapp_height());
}

void eventa(const sapp_event* ev) {

    if (ev->type == SAPP_EVENTTYPE_RESIZED) {
        fixed_auto(ev->window_width, ev->window_height);
    }

    if (ev->key_code == SAPP_KEYCODE_INVALID) {
        return;
    }
    AGameObject->Input(gm, ev->key_code);
}

sapp_desc sokol_main(int argc, char* argv[]) {
    (void)argc; (void)argv;
    return (sapp_desc) {
        .init_cb = init,
        .frame_cb = frame,
        .cleanup_cb = cleanup,
        .event_cb = eventa,
        .width = 640,
        .height = 480,
        .window_title = "Sima-Engine (sokol-app)",
        .icon.sokol_default = true,
        .logger.func = slog_func,
    };
}