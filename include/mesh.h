#pragma once

struct Mesh;

struct AMesh {
    struct Mesh* (*Create) (int count, const float* vertices, int vertex_size);
    void (*Bind)(struct Mesh* self, void* binder);
    void (*Releace) (struct Mesh* self);
    void (*Draw) (struct Mesh* self);
};

extern struct AMesh AMesh[1];