#ifndef _ballistic_vec3_inl_
#define _ballistic_vec3_inl_

vec3::vec3 (real vx, real vy, real vz) : x (vx), y (vy), z(vz) {}

vec3::vec3 () : x (real ()), y (real ()), z (real ()) {}

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

vec3::operator real * () {
	return (real *)this;
}

#endif