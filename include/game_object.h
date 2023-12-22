#pragma once

struct GameObject;

struct AGameObject {
    struct GameObject* (*Create) (const char* script_text, const unsigned char* texture_data, size_t width, size_t height, size_t depth);
    void (*Update) (struct GameObject* self);
    void (*Input) (struct GameObject* self, int key);
    void (*Releace) (struct GameObject* self);
    void (*Bind) (struct GameObject* self, void* binder);
    void (*Draw) (struct GameObject* self);
    float* (*GetWorldMatrix)(const struct GameObject* self);
};

extern struct AGameObject AGameObject[1];