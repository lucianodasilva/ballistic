#ifndef _math_h_
#define _math_h_

#include <cmath>
#include <limits>

struct vec3 {

	union {
		float data [3];

		struct {
			float x, y, z;
		};
	};

	inline vec3 & operator = (const vec3 & v) {
		x = v.x;
		y = v.y;
		z = v.z;

		return *this;
	}

	inline vec3 () : x (.0), y (.0), z (.0) {}

	inline vec3 (float vX, float vY, float vZ) : x (vX), y (vY), z (vZ) {}

	inline vec3 operator - (const vec3& v) const {
		return vec3 (
				x - v.x,
				y - v.y,
				z - v.z
			);
	}

	inline vec3 operator + (const vec3& v) const {
		return vec3 (
			x + v.x,
			y + v.y,
			z + v.z
			);
	}

	inline vec3 operator * (const float& v) const {
		return vec3 (
			x * v,
			y * v,
			z * v
			);
	}

};

inline float dot (const vec3 & v1, const vec3 & v2) {
	// avoid branching by avoiding zero ( floating point precision exploit )
	// returns minimum positive number for min
	float r = std::numeric_limits < float >::min ();

	for (unsigned int i = 0; i < 3; ++i)
		r += v1.data [i] * v2.data [i];

	return r;
}

inline vec3 cross (const vec3 & v1, const vec3 & v2) {
	return vec3 (
		v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x
	);
}

inline float sqr_length (const vec3 & v1) {
	return dot (v1, v1);
}

inline float length (const vec3 & v) {
	return sqrt (sqr_length (v));
}

inline float length (const vec3 & v1, const vec3 & v2) {
	return length (v2 - v1);
}

inline vec3 normalize (const vec3 & v) {
	float normal = 1.0F / length (v);
	return v * normal;
}

#endif