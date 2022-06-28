#version 330
uniform sampler2D Texture;

varying lowp vec4 DestinationColor;
varying lowp vec2 DestinationTexture;

void main(void) {
    gl_FragColor = texture2D(Texture, DestinationTexture) * DestinationColor;
}

