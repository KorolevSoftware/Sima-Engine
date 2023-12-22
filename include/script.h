#pragma once

#include "forth_embed.h"

struct Script;

struct AScript {
    struct Script* (*Create) (const char* script_text, void* user_data);
    void (*AddFunction) (struct Script* self, const char* name, forth_native_function func);
    void (*CallFunction) (struct Script* self, const char* name);
    void (*DataPush) (struct Script* self, int data);
    void (*DataPop) (struct Script* self);
    void (*Releace) (struct Script* self);
};

extern struct AScript AScript[1];