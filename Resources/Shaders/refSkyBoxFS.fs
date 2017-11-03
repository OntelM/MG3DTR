precision mediump float;

varying vec3 v_color;
uniform sampler2D t_texture_0;
uniform samplerCube t_texture_1;
varying vec3 v_norm, v_binorm, v_tgt;

//light-----------------------------
uniform vec3 u_posLight;
uniform vec3 u_ambiental;
uniform vec3 u_diffuseColor;
uniform vec3 u_specularColor;
uniform float u_specCoef;
uniform float u_specPower;
uniform float u_diffCoef;
uniform float u_shininess;
uniform vec3 u_cam; 
uniform vec3 u_ratio;
uniform float u_attenuation;
uniform float u_type;

varying vec2 v_uv;

//fog------------------------------------------------
varying vec3 v_pos;
uniform vec3 u_colorFog;
uniform float u_r, u_R;


void main()
{	
	vec4 color = texture2D(t_texture_0, v_uv);


	if(color.a < 0.7){
		discard;
	}

	vec3 vecLightDirectional	= normalize(-u_posLight);
	vec3 vecLightPoint			= normalize(v_pos - u_posLight);
	vec3 vecLight				= u_type * (vecLightPoint) + (1.0 - u_type) * vecLightDirectional;
	
	
	vec3 toeye		= normalize(u_cam - v_pos);
	vec3 reflec		= normalize(reflect(vecLight, v_norm));
	

	float distPos	= normalize(distance(v_pos, u_posLight));


	float attenuation = 1.0 / (1.0 + (u_attenuation * distPos));

	vec3 ambiental = color.xyz * u_ambiental;
	vec3 Cdiff = color.xyz * u_diffuseColor * max(dot(v_norm, -vecLight), 0.0) * u_diffCoef;
	vec3 Cspec = u_specularColor * pow(max(dot(reflec,toeye),0.0), u_specPower) * u_specCoef;




	
	vec3 newColor = ambiental + (attenuation * (Cdiff + Cspec));


	vec3 reflectCam = normalize(reflect(toeye , v_norm));
	vec3 c_reflexie = textureCube(t_texture_1, reflectCam).rgb;
	vec3 c_finalRef= c_reflexie * 0.5 + newColor * 0.6;



	float dist = distance(v_pos, u_cam);
	float alpha = clamp((dist - u_r)/(u_R - u_r),0.0,1.0);
	vec4 c_Final = alpha * vec4(u_colorFog,1.0) + (1.0 - alpha) * vec4(c_finalRef, 1.0);

	
	gl_FragColor = c_Final;


}
