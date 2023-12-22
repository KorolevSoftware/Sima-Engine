#pragma once
#include "script.h"
#include <stdlib.h>

struct Script {
    struct forth_state* state;
    struct forth_byte_code* code;
};

static void AddFunction(struct Script* self, const char* name, forth_native_function func) {
    forth_set_function(self->state, name, func);
}

void CallFunction(struct Script* self, const char* name) {
    forth_run_function(self->state, self->code, name);
}

static void DataPush(struct Script* self, int data) {
    forth_data_stack_push(self->state, data);
}

static void DataPop(struct Script* self) {
    return forth_data_stack_pop(self->state);
}


static struct Script* Create(const char* script_text, void* user_data) {
    struct Script* script = malloc(sizeof(struct Script));

    script->code = forth_compile(script_text);
    script->state = forth_make_default_state();

    forth_set_user_data(script->state, user_data);
    forth_run(script->state, script->code);
    return script;
}

static void Releace(struct Script* self) {
    forth_release_byte_code(self->code);
    forth_release_state(self->state);
    free(self);
}

struct AScript AScript[1] = {
    Create,
    AddFunction,
    CallFunction,
    DataPush,
    DataPop,
    Releace,
};