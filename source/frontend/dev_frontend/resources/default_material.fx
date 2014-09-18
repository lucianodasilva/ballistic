uniform vec4        effect_diffuse;
uniform mat4        effect_t_model;
uniform mat4        effect_t_view;
uniform mat4        effect_t_proj;
uniform mat4        effect_t_normal;
uniform mat4        effect_t_mvp;

uniform	bool		effect_has_bones;
uniform mat4		effect_t_bones [32];

#ifdef VERTEX_SHADER

layout (location = 1) in vec3 in_position;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in uvec2 in_bone_index;
layout (location = 4) in float in_bone_weight;
//layout (location = 3) in vec3 in_normal;

//out vec3            var_normal;
out vec2            var_uv;

void main () {

	vec4 pos = vec4 (in_position, 1.0);

	if (effect_has_bones) {
		mat4 A = effect_t_bones [in_bone_index.x];
		mat4 B = effect_t_bones [in_bone_index.y];

		pos = mix (
			effect_t_bones [in_bone_index.x], 
			effect_t_bones [in_bone_index.y], 
			in_bone_weight
		) * pos;
	}

	pos = effect_t_mvp * pos;

	//var_normal = (effect_t_normal * vec4 (in_normal, 1.0)).xyz;

	var_uv = in_uv;
	// opengl invert texture
	var_uv.y = 1.0 - var_uv.y;

	gl_Position = pos;
}

#endif

#ifdef FRAGMENT_SHADER

uniform sampler2D   effect_texture;

in vec3 var_normal;
in vec2 var_uv;
out vec4 out_color;

void main () {

	vec4 texture_color = texture (effect_texture, var_uv);
	out_color = texture_color;

}

#endif