#ifndef _ballistic_vector_inl_
#define _ballistic_vector_inl_

#include <utility>

vec2::vec2 (real vx, real vy) : x (vx), y (vy) {}

vec2::vec2 () : x (real ()), y (real ()) {}

vec2::vec2 ( const vec2 & v ) : x (v.x), y (v.y) {}

vec2 & vec2::operator = ( vec2 v ) {
	std::swap (x, v.x);
	std::swap (y, v.y);

	return *this;
}

vec2 vec2::operator + ( const vec2 & v ) const {
	return vec2 ( x + v.x, y + v.y );
}

vec2 vec2::operator - ( const vec2 & v ) const {
	return vec2 ( x - v.x, y - v.y);
}

vec2 vec2::operator * ( real v ) const {
	return vec2 ( x * v, y * v);
}

vec2 vec2::operator / ( real v ) const {
	return vec2 ( x / v, y / v);
}

vec2 & vec2::operator += ( const vec2 & v ) {
	x += v.x;
	y += v.y;

	return *this;
}

vec2 & vec2::operator -= ( const vec2 & v ) {
	x -= v.x;
	y -= v.y;

	return *this;
}

vec2 & vec2::operator *= ( real v ) {
	x *= v;
	y *= v;

	return *this;
}

vec2 & vec2::operator /= ( real v ) {
	x /= v;
	y /= v;

	return *this;
}

vec2::operator real * () {
	return &data [0];
}

// ----------------------------------------------------------------------------

vec3::vec3 (real vx, real vy, real vz) : x (vx), y (vy), z(vz) {}

vec3::vec3 () : x (real ()), y (real ()), z (real ()) {}

vec3::vec3 ( const vec3 & v ) : x (v.x), y (v.y), z (v.z) {}

vec3 & vec3::operator = ( vec3 v ) {
	std::swap (x, v.x);
	std::swap (y, v.y);
	std::swap (z, v.z);

	return *this;
}

vec3 vec3::operator + ( const vec3 & v ) const {
	return vec3 ( x + v.x, y + v.y, z + v.z );
}

vec3 vec3::operator - ( const vec3 & v ) const {
	return vec3 ( x - v.x, y - v.y, z - v.z );
}

vec3 vec3::operator * ( real v ) const {
	return vec3 ( x * v, y * v, z * v);
}

vec3 vec3::operator / ( real v ) const {
	return vec3 ( x / v, y / v, z / v);
}

vec3 & vec3::operator += ( const vec3 & v ) {
	x += v.x;
	y += v.y;
	z += v.z;

	return *this;
}

vec3 & vec3::operator -= ( const vec3 & v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;

	return *this;
}

vec3 & vec3::operator *= ( real v ) {
	x *= v;
	y *= v;
	z *= v;

	return *this;
}

vec3 & vec3::operator /= ( real v ) {
	x /= v;
	y /= v;
	z /= v;

	return *this;
}


vec3::operator real * () {
	return &data [0];
}

// ----------------------------------------------------------------------------

vec4::vec4 (real vx, real vy, real vz, real vw) : x (vx), y (vy), z(vz), w (vw) {}

vec4::vec4 () : x (real ()), y (real ()), z (real ()), w (real ()) {}

vec4::vec4 ( const vec4 & v ) : x (v.x), y (v.y), z (v.z), w (v.w) {}

vec4 & vec4::operator = ( vec4 v ) {
	std::swap (x, v.x);
	std::swap (y, v.y);
	std::swap (z, v.z);
	std::swap (w, v.w);

	return *this;
}

vec4 vec4::operator + ( const vec4 & v ) const {
	return vec4 ( x + v.x, y + v.y, z + v.z, w + v.w );
}

vec4 vec4::operator - ( const vec4 & v ) const {
	return vec4 ( x - v.x, y - v.y, z - v.z, w - v.w );
}

vec4 vec4::operator * ( real v ) const {
	return vec4 ( x * v, y * v, z * v, w * v);
}

vec4 vec4::operator / ( real v ) const {
	return vec4 ( x / v, y / v, z / v, w / v);
}

vec4::operator real * () {
	return &data [0];
}

vec4 & vec4::operator += ( const vec4 & v ) {
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;

	return *this;
}

vec4 & vec4::operator -= ( const vec4 & v ) {
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;

	return *this;
}

vec4 & vec4::operator *= ( real v ) {
	x *= v;
	y *= v;
	z *= v;
	w *= v;

	return *this;
}

vec4 & vec4::operator /= ( real v ) {
	x /= v;
	y /= v;
	z /= v;
	w /= v;

	return *this;
}


#endif