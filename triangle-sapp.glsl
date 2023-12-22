@vs vs
uniform vs_params {
    mat4 mvp;
};

in vec4 position;
in vec2 texcoord0;

out vec2 uv;

void main() {
    gl_Position = mvp * position;
    uv = texcoord0;
}
@end

@fs fs
uniform texture2D tex;
uniform sampler smp;

in vec2 uv;

out vec4 frag_color;

void main() {
    frag_color = texture(sampler2D(tex, smp), uv);
}
@end

@program sprite vs fs
