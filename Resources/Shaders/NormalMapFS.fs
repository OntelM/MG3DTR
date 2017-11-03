precision mediump float;

varying vec3 v_color;
uniform sampler2D t_texture_0, t_texture_1;
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
	vec3 c_normalMap = texture2D(t_texture_1, v_uv).rgb;

	vec3 normal2	= normalize(2.0 * v_norm -1.0);

	mat3 TBN = mat3(vec3(v_tgt.x, v_binorm.x, normal2.x),
					vec3(v_tgt.y, v_binorm.y, normal2.y),
					vec3(v_tgt.z, v_binorm.z, normal2.z));
	
	vec3 normal3 = normalize(c_normalMap * TBN + v_norm);

	

	if(color.a == 0.0){
		discard;
	}

	vec3 vecLightDirectional	= normalize(-u_posLight);
	vec3 vecLightPoint			= normalize(v_pos - u_posLight);
	vec3 vecLight				= u_type * (vecLightPoint) + (1.0 - u_type) * vecLightDirectional;
	
	
	vec3 toeye		= normalize(u_cam - v_pos);
	vec3 reflec		= normalize(reflect(vecLight, normal3));
	//vec3 reflectCam = reflect(toeye , normalize(normal3));

	float distPos	= normalize(distance(v_pos, u_posLight));


	float attenuation = 1.0 / (1.0 + (u_attenuation * distPos));

	vec3 ambiental = color.xyz * u_ambiental;
	vec3 Cdiff = color.xyz * u_diffuseColor * max(dot(normal3, -vecLight), 0.0) * u_diffCoef;
	vec3 Cspec = u_specularColor * pow(max(dot(reflec,toeye),0.0), u_specPower);


	vec3 newColor = ambiental + attenuation * (Cdiff + Cspec);

	float dist = distance(v_pos, u_cam);
	float alpha = clamp((dist - u_r)/(u_R - u_r),0.0,1.0);
	vec4 c_Final = alpha * vec4(u_colorFog,1.0) + (1.0 - alpha) * vec4(newColor, 1.0);

	
	gl_FragColor = c_Final;


}
