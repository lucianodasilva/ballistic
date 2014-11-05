// transforms
uniform vec3		effect_t_eye;
uniform mat4        effect_t_model;
uniform mat4        effect_t_view;
uniform mat4        effect_t_proj;
uniform mat4        effect_t_normal;
uniform mat4        effect_t_mvp;

// Lights
/*
	mat [0].xyz		= position
	mat [0].w		= fallout
	mat [1].xyz		= color
	mat [1].w		= intensity
*/
uniform mat2x4		effect_lights [8];
uniform int			effect_light_count;

// material
uniform vec3        effect_diffuse;
uniform vec3		effect_specular;
uniform float		effect_specular_intensity;
uniform float		effect_specular_hardness;

uniform vec3 		effect_ambient_sky;
uniform vec3		effect_ambient_ground;
uniform float		effect_ambient_intensity;

uniform float		effect_opacity;

#ifdef VERTEX_SHADER

layout (location = 1) in vec3 in_position;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec3 in_normal;

out vec3			var_position;
out vec3            var_normal;
out vec2            var_uv;

void main () {

	vec4 pos = effect_t_mvp * vec4 (in_position, 1.0);

	var_position = (effect_t_model * vec4 (in_position, 1.0)).xyz;
	
	var_normal = ((effect_t_normal * vec4 (in_normal, 1.0)).xyz);

	var_uv = in_uv;
	// opengl invert texture
	var_uv.y = 1.0 - var_uv.y;

	gl_Position = pos;
}

#endif

#ifdef FRAGMENT_SHADER

uniform sampler2D   effect_texture;

in vec3	var_position;
in vec3 var_normal;
in vec2 var_uv;
out vec4 out_color;

void main () {

	vec3
		light_pos,
		light_vec,
		light_col,
		temp_col = vec3 (.0, .0, .0);

	float
		light_fal,
		light_dst,
		light_int,
		att = 0.0,
		bgt = 0.0,
		sky_bgt = 0.0;

	temp_col = effect_diffuse;

	vec3 normal = normalize (var_normal);

	// --- sky color ---
	vec3 up = vec3 (.0, 1.0, .0);
	sky_bgt = 0.5 * (1.0 + dot (up, normal));
	
	temp_col *= ((sky_bgt * effect_ambient_sky + (1.0 - sky_bgt) * effect_ambient_ground) * effect_ambient_intensity);
	
	// --- lights ---
	for (int i = 0; i < effect_light_count; ++i) {
		light_pos = effect_lights [i] [0].xyz;
		light_fal = effect_lights [i] [0].w;
		light_col = effect_lights [i] [1].xyz;
		light_int = effect_lights [i] [1].w;
	
		// --- attenuation ---
		// distance and normalize in one sqrt
		light_vec = light_pos - var_position;
		light_dst = max (length (light_vec), 0.0);
		light_vec = light_vec / light_dst;
	
		vec3 normal = normalize (var_normal);
		bgt = max (dot (normal, light_vec), 0.0);
	
		att = 0;
	
		if (light_dst < light_fal) {
			att = light_dst / light_fal + 1;
			att = 1.0 / (att * att);
		}
	
		light_col =  bgt * att * light_col * effect_diffuse;
	
		// --- specular ---
		if (effect_specular_intensity > 0.0) {
		
			vec3 eye_v = normalize (effect_t_eye - var_position);
		
			float spec_bgt = dot (normal, light_vec);
		
			if (spec_bgt > 0.0) {
				spec_bgt = pow (max (0.0, dot (eye_v, reflect (-light_vec, normal))), effect_specular_hardness), 1.0;
				light_col += spec_bgt * att * effect_lights [i] [1].xyz * effect_specular_intensity;
			}
		}
	
		temp_col += light_col;
	}

	out_color = vec4 (temp_col, effect_opacity);
}

#endif