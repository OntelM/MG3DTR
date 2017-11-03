attribute vec3 a_posL, a_normalL, a_binormL, a_tgtL;
attribute vec2 a_uv;
varying vec2 v_uv;


attribute vec3 a_color;
varying vec3 v_color;
uniform mat4 u_MVP;

varying vec3 v_pos;
varying vec3 v_norm;


uniform mat4 Model, View, Projection;



void main()
{
v_color = a_color;
v_uv = a_uv;


v_pos		= (Model * vec4(a_posL, 1.0)).xyz;
v_norm		= (normalize(Model * vec4(a_normalL, 0.0)).xyz);

vec4 posL	= u_MVP * vec4(a_posL, 1.0);

gl_Position = posL;

}

  