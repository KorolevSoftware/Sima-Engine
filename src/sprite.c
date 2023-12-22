#pragma once

#include "mesh.h"
#include "sprite.h"
#include <stdlib.h>
#include "texture.h"

struct Sprite {
	struct Mesh* mesh;
    struct Texture* texture;
};

static struct Sprite* Create(const unsigned char* texture_data, size_t width, size_t height, size_t depth) {
    struct Sprite* self = malloc(sizeof(struct Sprite));
    float vertex_data[] = {
        // positions            // colors
        -10.0f,  10.0f, 0.0f,   0.0f, 1.0f,
        10.0f, 10.0f, 0.0f,     1.0f, 1.0f,
        -10.0f, -10.0f, 0.0f,   0.0f, 0.0f,
        10.0f, -10.0f, 0.0f,    1.0f, 0.0f,
    };
    self->mesh = AMesh->Create(4, vertex_data, sizeof(vertex_data));
    self->texture = ATexture->Create(texture_data, width, height, depth);
    return self;
}

static void Releace(struct Sprite* self) {
    ATexture->Releace(self->texture);
    AMesh->Releace(self->mesh);
    free(self);
}

static void Draw(struct Sprite* self) {
    AMesh->Draw(self->mesh);
}

static void Bind(struct Sprite* self, void* binder) {
    ATexture->Bind(self->texture, binder);
    AMesh->Bind(self->mesh, binder);
}

struct ASprite ASprite[1] = {
    Create,
    Bind,
    Releace,
    Draw,
};