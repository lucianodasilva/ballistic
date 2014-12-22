uniform vec4        effect_diffuse;
uniform mat4        effect_t_model;
uniform mat4        effect_t_view;
uniform mat4        effect_t_proj;
uniform mat4        effect_t_normal;
uniform mat4        effect_t_mvp;

#ifdef VERTEX_SHADER

layout (location = 1) in vec3 in_position;
layout (location = 2) in vec2 in_uv;
layout (location = 3) in vec3 in_normal;

out vec3            var_normal;
out vec2            var_uv;

void main () {

	vec4 pos = effect_t_mvp * vec4 (in_position, 1.0);

	var_normal = (effect_t_normal * vec4 (in_normal, 1.0)).xyz;

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