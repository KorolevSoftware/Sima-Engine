#include "mesh.h"
#include <stdlib.h>
#include <string.h>

struct mesh {
	sg_bindings bind;
    sg_pipeline pipeline;
};

struct mesh* create_mesh(sg_pipeline pipeline, const float* vertices, int size) {
	struct mesh* new_mesh = malloc(sizeof(struct mesh));
    memset(new_mesh, 0, sizeof(struct mesh));
    new_mesh->pipeline = pipeline;

	new_mesh->bind.vertex_buffers[0] = sg_make_buffer(&(sg_buffer_desc) {
        .data = (sg_range){ vertices, size },
        .label = "mesh"
    });
    return new_mesh;
}

void releace_mesh(struct mesh* from_release) {
    //sg_destroy_buffer() -- todo destroy
}

void draw_mesh(struct mesh* mesh) {
    sg_apply_pipeline(mesh->pipeline);
    sg_apply_bindings(&mesh->bind);
    sg_draw(0, 3, 1);
}
