varying lowp vec4 DestinationColor;
varying lowp vec2 DestinationTexture;

void main(void) {
    lowp vec2 modifiedTex = DestinationTexture - vec2(.5, .5);
    if ((modifiedTex.x * modifiedTex.x) +
        (modifiedTex.y * modifiedTex.y) < .25)
    {
        gl_FragColor = vec4(DestinationColor);
    } else {
        gl_FragColor = vec4(0,0,0,0);
    }
}

