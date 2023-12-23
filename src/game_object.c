#pragma once

#include "game_object.h"
#include <stdlib.h>
#include "sprite.h"
#include "script.h"
#include <string.h>
#include "forth_embed.h"

static struct mat4 world_matrix;

struct GameObject {
    struct Sprite* sprite;
    struct Script* script;
    struct vec3 position;
    struct vec3 rotation;
};


static struct vec3 get_position(struct GameObject* self) {
    return self->position;
}

static void set_position(struct GameObject* self, struct vec3 position) {
    self->position = position;
}

static void get_position_forth(struct forth_state* fs) {
    struct GameObject* self = (struct GameObject*)forth_get_user_data(fs);
    forth_data_stack_push(fs, (int)self->position.z);
    forth_data_stack_push(fs, (int)self->position.y);
    forth_data_stack_push(fs, (int)self->position.x);
}

static void set_position_forth(struct forth_state* fs) {
    struct GameObject* self = (struct GameObject*)forth_get_user_data(fs);

    float posX = forth_data_stack_pop(fs);
    float posY = forth_data_stack_pop(fs);
    float posZ = forth_data_stack_pop(fs);

    set_position(self, (struct vec3){ posX, posY, posZ });
}

static struct GameObject* Create(const char* script_text, const unsigned char* texture_data, size_t width, size_t height, size_t depth) {
    struct GameObject* new_gm = malloc(sizeof(struct GameObject));
    memset(new_gm, 0, sizeof(struct GameObject));

    if (script_text) {
        new_gm->script = AScript->Create(script_text, new_gm);
        AScript->AddFunction(new_gm->script, "set_position", set_position_forth);
        AScript->AddFunction(new_gm->script, "get_position", get_position_forth);
        AScript->CallFunction(new_gm->script, "init");
    }
    if (texture_data) {
        new_gm->sprite = ASprite->Create(texture_data, width, height, depth);
    }
    return new_gm;
}

static void Update(struct GameObject* self) {

}

static void Input(struct GameObject* self, int key) {
    AScript->DataPush(self->script, key);
    AScript->CallFunction(self->script, "input");
}

static float* GetWorldMatrix(const struct GameObject* self) {
    struct mat4 position;
    struct mat4 rotation;

    mat4_identity(&position);

    mat4_translation(&world_matrix, &position, &self->position);

    return &world_matrix;
}

static void Bind(struct GameObject* self, void* binder) {
    ASprite->Bind(self->sprite, binder);
}

static void Releace(struct GameObject* self) {
    if (self->script) { // release script
        AScript->Releace(self->script);
    }

    if (self->sprite) { // release sprite
        ASprite->Releace(self->sprite);
    }

    free(self);
}

static void Draw(struct GameObject* self) {
    if (self->sprite) {
        ASprite->Draw(self->sprite);
    }
}

struct AGameObject AGameObject[1] = {
    Create,
    Update,
    Input,
    Releace,
    Bind,
    Draw,
    GetWorldMatrix,
    set_position,
};