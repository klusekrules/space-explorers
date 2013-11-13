uniform sampler2D texture;
uniform mediump float time;

void main(void)
{
	 // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
    gl_FragColor = gl_Color * pixel * (sin( time ) * 0.5 + 0.5);
}