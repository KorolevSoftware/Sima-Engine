#include "mesh.h"
#include <stdlib.h>
#include "sokol_gfx.h"

// Mesh public methods

struct Mesh {
    sg_buffer gpu_buffer;
    size_t vertex_count;
};

static struct Mesh* Create(int count, const float* vertices, int vertex_size) {
	struct Mesh* self = malloc(sizeof(struct Mesh));
    self->vertex_count = count;
    self->gpu_buffer = sg_make_buffer(&(sg_buffer_desc) {
        .data = (sg_range){ .ptr = vertices, .size = vertex_size },
        .label = "mesh"
    });
    return self;
}

static void Releace(struct Mesh* self) {
    sg_destroy_buffer(self->gpu_buffer);
    free(self);
}

void Bind(struct Mesh* self, void* binder) {
    sg_bindings* bind = (sg_bindings*)binder;
    bind->vertex_buffers[0] = self->gpu_buffer;
}

static void Draw(struct Mesh* self) {
    sg_draw(0, self->vertex_count, 1);
}

struct AMesh AMesh[1] = {
    Create,
    Bind,
    Releace,
    Draw,
};