#pragma once

struct Render;

struct ARender {
    void (*Create) (void);
    void (*Release) (void);
    void (*Begin) (int width, int height);
    void* (*GetBinder) ();
    void (*End) (void);
    void (*SetUniform4f)(float* data);
    void (*SetMatrix4x4)(float* data);
};

extern struct ARender ARender[1];