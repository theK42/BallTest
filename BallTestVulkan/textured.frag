#version 450
layout(binding = 1) uniform sampler2D Texture;

layout(location = 0) in vec4 FragColor;
layout(location = 1) in vec2 FragTextureCoords;

layout(location = 0) out vec4 outColor;

void main(void) {
    outColor = texture(Texture, FragTextureCoords) * FragColor;
}

