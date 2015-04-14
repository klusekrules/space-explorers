#version 120
uniform sampler2D texture;
uniform float upMargin;
uniform float downMargin;
uniform float zakres;

void main(void)
{
	 // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);

    // multiply it by the color
	if(gl_FragCoord.y > (downMargin - zakres) && gl_FragCoord.y <= downMargin){
		gl_FragColor = gl_Color * pixel * vec4( 1.0, 1.0, 1.0, 1.0 -( ( downMargin - gl_FragCoord.y ) / zakres ) );
	}else{
		if(gl_FragCoord.y < (upMargin + zakres)  && gl_FragCoord.y >= upMargin)
			gl_FragColor = gl_Color * pixel * vec4( 1.0, 1.0, 1.0, 1.0 -( (gl_FragCoord.y - upMargin) / zakres ) );
		else
			gl_FragColor = gl_Color * pixel * vec4( 1.0, 1.0, 1.0, 1.0);
		}
}