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

"0 posX ! "
"0 posY ! "

": input "
    "dup down = if posY @ 1  - posY ! then "
    "dup up = if posY @ 1 + posY ! then "
    "dup left = if posX @ 1 - posX ! then "
    "dup right = if posX @ 1 + posX ! then "
    "99 posY @ posX @ set_poition "
    "drop "
" ; ";

struct GameObject* gm;
static struct mat4 project;

static void init(void) {
    ARender->Create();
    mat4_orthoLH(&project, 0.0f, 40.0f, 0.0f, 30.0f, 0.1f, 100.0f);
    const char* path = "e:\\Project\\Defold\\defold-games-master\\Galaxy Force\\assets\\png\\boss2.png";
    int sprite_width, sprite_height, sprite_depth;
    uint8_t* bitmapData = stbi_load(path, &sprite_width, &sprite_height, &sprite_depth, 0);
    gm = AGameObject->Create(game_script, bitmapData, sprite_width, sprite_height, sprite_depth);
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
    if (ev->key_code == SAPP_KEYCODE_INVALID || ev->type !=  SAPP_EVENTTYPE_KEY_DOWN) {
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