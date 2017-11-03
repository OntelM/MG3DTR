precision mediump float;

varying vec3 v_color;
uniform sampler2D t_texture_0, t_texture_1, t_texture_2;
uniform float u_Time;
uniform float u_DispMax;

varying vec2 v_uv;

varying vec3 v_pos;
uniform float u_r, u_R;
uniform vec3 u_colorFog;
uniform vec3 u_cam;

void main()
{	
	vec2 disp = texture2D(t_texture_2, vec2(v_uv.x, v_uv.y + u_Time)).rg;
	vec2 v_uv_displaced = v_uv + normalize((2.0 * disp) - 1.0) * u_DispMax;
	vec4 c_alpha = texture2D(t_texture_1, vec2(v_uv.x, v_uv.y));
	vec4 c_fire = texture2D(t_texture_0, v_uv_displaced);
	if(c_fire.a < 0.7){
		discard;
	}
	vec4 c_final = c_fire * vec4(1.0,1.0,1.0,c_alpha);

	


	float dist = distance(v_pos, u_cam);

	float alpha = clamp((dist - u_r)/(u_R - u_r),0.0,1.0);


	vec4 newColor = alpha * vec4(u_colorFog,1.0) + (1.0 - alpha) * c_final;


	gl_FragColor = newColor;


	

	//gl_FragColor = texture2D(u_texture, v_uv) * texture2D(u_firemask, v_uv) * texture2D(u_dispmap, v_uv);
	//gl_FragColor = vec4(v_uv.x, v_uv.y, 0.0, 1.0);
	//gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}