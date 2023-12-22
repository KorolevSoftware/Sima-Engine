#pragma once
#include <stdint.h>

struct Texture;

struct ATexture {
    struct Texture* (*Create) (const unsigned char* texture_data, size_t width, size_t height, size_t depth);
    void (*Bind)(struct Texture* self, void* binder);
    void (*Releace) (struct Texture* self);
};

extern struct ATexture ATexture[1];