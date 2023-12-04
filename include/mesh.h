#pragma once

#include "sokol_gfx.h"

struct mesh* create_mesh(sg_pipeline pipeline, const float* vertices, int vertex_count);
void releace_mesh(struct mesh* from_release);
void draw_mesh(struct mesh* mesh);