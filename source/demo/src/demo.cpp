
#include <ballistic.base.h>

void main () {

	vec3 v1 (1.0F, 1.0F, 0.0F);

	mat4 t = mat4::make_translation (vec3 (2.0F, 0.0F, 0.0F));

	vec3 v2 = t * v1;

	ballistic::aabox 
		b1 (vec3 (1.0F, 2.0F, 0.0F), vec3 (1.0F, 1.0F, 1.0F)),
		b2 (vec3 (10.0F, 2.0F, 0.0F), vec3 (0.5F, 0.5F, 0.5F));

	ballistic::intersection_type intersect = b1.intersect (b2);

}