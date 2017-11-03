attribute vec3 a_posL, a_normalL;
varying vec3 v_posL;


attribute vec2 a_uv, a_uvt;
varying vec2 v_uv, v_uvt;

attribute vec3 a_color;
varying vec3 v_color;
uniform mat4 u_MVP;
uniform float nrCel;

uniform vec3 u_height;

uniform sampler2D u_Terrain_blend_map;

uniform mat4 Model;

varying vec3 v_pos;
varying vec3 v_norm;

void main()
{

v_color = a_color;
v_uv = a_uv;
v_uvt = a_uvt;

vec3 vBlendMap = (texture2D(u_Terrain_blend_map, v_uvt)).rgb;
vec3 posLNew = a_posL;
posLNew.y += vBlendMap.r * u_height.r + vBlendMap.g * u_height.g + vBlendMap.b * u_height.b;

v_pos = (Model * vec4(a_posL, 1.0)).xyz;
v_norm = normalize(Model * vec4(a_normalL, 0.0)).xyz;


vec4 posL = u_MVP * vec4(posLNew, 1.0);





gl_Position = posL;

}
   