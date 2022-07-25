#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 ModelMatrix;
    mat4 ProjectionMatrix;
} ubo;

layout(location = 0) in  vec4 Position;
layout(location = 1) in  vec4 VertexColor;
layout(location = 2) in  vec2 TextureCoordinates;

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec2 FragTextureCoords;


void main(void) {
    FragColor = VertexColor;
    FragTextureCoords = TextureCoordinates;

    mat4 fakeModel = transpose(ubo.ModelMatrix);
    gl_Position = ubo.ProjectionMatrix * fakeModel * Position;
}

