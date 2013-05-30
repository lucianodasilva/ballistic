
#include <ballistic.base.h>

struct t_vec2 {
	real x, y;
};

struct t_vec3 {
	union {
		struct { real x, y, z; };
		struct { t_vec2 xy; };

		struct { real r, g, b; };
	};
};

struct t_vec4 {
	union {
		struct { real x, y, z, w; };
		struct { t_vec2 xy; };
		struct { t_vec3 xyz; };

		struct { real a, r, g, b; };
		struct { real __f; t_vec3 rgb; };
	};
};

void main () {

	t_vec4 v;



	//auto v3 = v1 + v2;

}