#version 450
layout(location = 0) in vec4 FragColor;
layout(location = 1) in vec2 FragTextureCoords;

layout(location = 0) out vec4 outColor;

void main(void) {
    vec2 modifiedTex = FragTextureCoords - vec2(.5, .5);
    float insideness = float((modifiedTex.x * modifiedTex.x) +
        (modifiedTex.y * modifiedTex.y) < .25);
    outColor = insideness * vec4(FragColor);
}

