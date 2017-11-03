precision mediump float;

varying vec3 v_color;
uniform sampler2D t_texture_0, t_texture_1, t_texture_2, t_texture_3;

varying vec2 v_uv;
varying vec2 v_uvt;

varying vec3 v_pos;
uniform vec3 u_cam;
uniform float u_r, u_R;
uniform vec3 u_colorFog;


//light-----------------------------
uniform vec3 u_posLight;
varying vec3 v_norm;
uniform vec3 u_ambiental;
uniform vec3 u_diffuseColor;
uniform vec3 u_specularColor;
uniform float u_specCoef;
uniform float u_diffCoef;
uniform float u_specPower;
uniform float u_shininess;
uniform float u_attenuation;
uniform float u_type;





//atenuarea este corecta?
// proiectie cerc de lumina directionala pe teren
//if(1/2/3){directional/point/spotLight}
void main()
{	
vec4 c_Grass = texture2D(t_texture_0,v_uv);
vec4 c_Rock = texture2D(t_texture_1,v_uv);
vec4 c_Dirt = texture2D(t_texture_2,v_uv);
vec3 vBlendMap = (texture2D(t_texture_3, v_uvt)).rgb;

vec4 vBaseColor = c_Rock*(vBlendMap.r) + c_Grass*(vBlendMap.g) + c_Dirt*(vBlendMap.b);


	vec3 vecLightDirectional	= normalize(-u_posLight);
	vec3 vecLightPoint			= normalize(v_pos - u_posLight);
	vec3 vecLight				= u_type * (vecLightPoint) + (1.0 - u_type) * vecLightDirectional;
	
	
	vec3 toeye		= normalize(u_cam - v_pos);
	vec3 reflec		= normalize(reflect(vecLight, v_norm));

	float distPos	= distance(v_pos, u_posLight);


	float attenuation = 1.0 / (1.0 + (u_attenuation * distPos));

	vec3 ambiental = vBaseColor.xyz * u_ambiental;
	vec3 Cdiff = vBaseColor.xyz * u_diffuseColor * max(dot(v_norm, -vecLight), 0.0) * u_diffCoef;
	vec3 Cspec = u_specularColor * pow(max(dot(reflec,toeye),0.0), u_specPower);


	vec3 newColor = ambiental + attenuation * (Cdiff + Cspec);



	//cetata----------------------------------
	float dist = distance(v_pos, u_cam);
	float alpha = clamp((dist - u_r)/(u_R - u_r),0.0,1.0);
	vec4 c_Final = alpha * vec4(u_colorFog,1.0) + (1.0 - alpha) * vec4(newColor, 1.0);

	

	//coefmediu  = (lightsource - fragment)*parametru
	// coef_mediu /distPatrat



	gl_FragColor = c_Final;

	//gl_FragColor = vec4(vBaseColor.rgb,0.3);
	//gl_FragColor = vec4(v_uv.x, v_uv.y, 0.0, 1.0);
	//gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);
}
