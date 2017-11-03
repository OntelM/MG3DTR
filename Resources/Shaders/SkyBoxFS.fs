precision mediump float;

uniform samplerCube t_texture_0;
varying vec3 v_coord;

void main()
{	
	gl_FragColor = textureCube(t_texture_0, v_coord);
	//gl_FragColor = vec4(v_coord, 1.0);

}