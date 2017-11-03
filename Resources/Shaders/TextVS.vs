attribute vec2 coord;
attribute vec2 coorduv;
varying vec2 texcoord;

void main(void) {
  gl_Position = vec4(coord.xy, 0, 1);
  texcoord = coorduv;
}