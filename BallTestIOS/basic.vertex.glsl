attribute vec4 Position;
attribute vec4 VertexColor;
attribute vec2 TextureCoordinates;

varying lowp vec4 DestinationColor;
varying lowp vec2 DestinationTexture;

uniform mat4 Projection;
uniform mat4 Model;


void main(void) {
    DestinationColor = VertexColor;
    DestinationTexture = TextureCoordinates;
    gl_Position = Projection * Model * Position;
}

