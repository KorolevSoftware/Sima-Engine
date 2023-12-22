#include "texture.h"
#include <stdlib.h>
#include "sokol_gfx.h"

// Mesh public methods

struct Texture {
    sg_image gpu_image;
    sg_sampler sampler;
};

static struct Texture* Create(const unsigned char* texture_data, size_t width, size_t height, size_t depth) {
	struct Texture* self = malloc(sizeof(struct Texture));

    self->gpu_image = sg_make_image(&(sg_image_desc) {
        .width = width,
        .height = height,
        .data.subimage[0][0] = (sg_range){ .ptr = texture_data, .size = width * height * depth },
        .label = "sprite_texture"
    });

    self->sampler = sg_make_sampler(&(sg_sampler_desc) {
        .label = "sprite_texture_sampler"
    });
        
    return self;
}

static void Releace(struct Texture* self) {
    sg_destroy_image(self->gpu_image);
    sg_destroy_sampler(self->sampler);
    free(self);
}

static void Bind(struct Texture* self, void* binder) {
    sg_bindings* bind = (sg_bindings*)binder;
    bind->fs.images[0] = self->gpu_image;
    bind->fs.samplers[0] = self->sampler;
}

struct ATexture ATexture[1] = {
    Create,
    Bind,
    Releace,
};