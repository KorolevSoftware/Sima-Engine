#pragma once
#include <stdint.h>

struct Sprite;

struct ASprite {
    struct Sprite* (*Create) (const unsigned char* texture_data, size_t width, size_t height, size_t depth);
    void (*Bind)(struct Sprite* self, void* binder);
    void (*Releace) (struct Sprite* self);
    void (*Draw) (struct Sprite* self);
};

extern struct ASprite ASprite[1];