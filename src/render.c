#pragma once

#include "render.h"

#define SOKOL_D3D11
#define SOKOL_IMPL
#include "sokol_gfx.h"
#include "sokol_app.h"
#include "sokol_log.h"
#include "triangle-sapp.glsl.h"
#include "sokol_glue.h"


static struct {
    sg_pass_action pass_action;
    sg_pipeline pipeline;
    sg_bindings bind;
} state;

static void Create(void) {
    // a vertex buffer with 3 vertices
    sg_setup(&(sg_desc) {
        .context = sapp_sgcontext(),
            .logger.func = slog_func,
    });
    
    // create shader from code-generated sg_shader_desc
    sg_shader shd = sg_make_shader(sprite_shader_desc(sg_query_backend()));

    // create a pipeline object (default render states are fine for triangle)
    state.pipeline = sg_make_pipeline(&(sg_pipeline_desc) {
        .shader = shd,
            // if the vertex layout doesn't have gaps, don't need to provide strides and offsets
            .layout = {
                .attrs = {
                            [ATTR_vs_position] .format = SG_VERTEXFORMAT_FLOAT3,
                            [ATTR_vs_texcoord0].format = SG_VERTEXFORMAT_FLOAT2
                         },
        },
            .label = "triangle-pipeline",
            .primitive_type = SG_PRIMITIVETYPE_TRIANGLE_STRIP,
    });
    
    // a pass action to clear framebuffer to black
    state.pass_action = (sg_pass_action){
        .colors[0] = {.load_action = SG_LOADACTION_CLEAR, .clear_value = {0.0f, 0.0f, 0.0f, 1.0f } }
    };
}

static void Release() {
    sg_shutdown();
}

static void Begin(int width, int height) {
    sg_begin_default_pass(&state.pass_action, width, height);
    sg_apply_pipeline(state.pipeline);
    sg_apply_bindings(&state.bind);

}

static void SetUniform4f(float* data) {
  /*  const vs_params_t vs_params;
    memcpy(vs_params.offset, data, sizeof(vs_params.offset));
    sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &SG_RANGE(vs_params));*/
}

static void SetMatrix4x4(float* data) {
    const vs_params_t vs_params;
    memcpy(vs_params.mvp, data, sizeof(vs_params.mvp));
    sg_apply_uniforms(SG_SHADERSTAGE_VS, SLOT_vs_params, &SG_RANGE(vs_params));
}

static void End(void) {
    sg_end_pass();
    sg_commit();
}

static void* GetBinding() {
    return &state.bind;
}

struct ARender ARender[1] = {
    Create,
    Release,
    Begin,
    GetBinding,
    End,
    SetUniform4f,
    SetMatrix4x4,
};