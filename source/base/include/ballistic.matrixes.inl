
#include <cmath>

mat4::mat4 () :
	m00 (real (1)), m01 (real ()), m02 (real ()), m03 (real ()),
	m04 (real ()), m05 (real (1)), m06 (real ()), m07 (real ()),
	m08 (real ()), m09 (real ()), m10 (real (1)), m11 (real ()),
	m12 (real ()), m13 (real ()), m14 (real ()), m15 (real (1))
{}

mat4::mat4 ( real _m00, real _m01, real _m02, real _m03, real _m04, real _m05, real _m06, real _m07, real _m08, real _m09, real _m10, real _m11, real _m12, real _m13, real _m14, real _m15 )
	:
	m00 (_m00), m01 (_m01), m02 (_m02), m03 (_m03),
	m04 (_m04), m05 (_m05), m06 (_m06), m07 (_m07),
	m08 (_m08), m09 (_m09), m10 (_m11), m11 (_m11),
	m12 (_m12), m13 (_m13), m14 (_m14), m15 (_m15)
{}

mat4 & mat4::operator = ( const mat4 & v ) {
	for ( int i = 0; i < data_length; ++i )
		data [i] = v.data [i];

	return *this;
}

mat4 mat4::operator * ( const mat4 & v ) const {
	return mat4 (
		data[ 0]*v.data[ 0] +
        data[ 1]*v.data[ 4] +
        data[ 2]*v.data[ 8] +
        data[ 3]*v.data[12],

        data[ 0]*v.data[ 1] +
        data[ 1]*v.data[ 5] +
        data[ 2]*v.data[ 9] +
        data[ 3]*v.data[13],

        data[ 0]*v.data[ 2] +
        data[ 1]*v.data[ 6] +
        data[ 2]*v.data[10] +
        data[ 3]*v.data[14],

        data[ 0]*v.data[ 3] +
        data[ 1]*v.data[ 7] +
        data[ 2]*v.data[11] +
        data[ 3]*v.data[15],

        data[ 4]*v.data[ 0] +
        data[ 5]*v.data[ 4] +
        data[ 6]*v.data[ 8] +
        data[ 7]*v.data[12],

        data[ 4]*v.data[ 1] +
        data[ 5]*v.data[ 5] +
        data[ 6]*v.data[ 9] +
        data[ 7]*v.data[13],

        data[ 4]*v.data[ 2] +
        data[ 5]*v.data[ 6] +
        data[ 6]*v.data[10] +
        data[ 7]*v.data[14],

        data[ 4]*v.data[ 3] +
        data[ 5]*v.data[ 7] +
        data[ 6]*v.data[11] +
        data[ 7]*v.data[15],

        data[ 8]*v.data[ 0] +
        data[ 9]*v.data[ 4] +
        data[10]*v.data[ 8] +
        data[11]*v.data[12],

        data[ 8]*v.data[ 1] +
        data[ 9]*v.data[ 5] +
        data[10]*v.data[ 9] +
        data[11]*v.data[13],

        data[ 8]*v.data[ 2] +
        data[ 9]*v.data[ 6] +
        data[10]*v.data[10] +
        data[11]*v.data[14],

        data[ 8]*v.data[ 3] +
        data[ 9]*v.data[ 7] +
        data[10]*v.data[11] +
        data[11]*v.data[15],

        data[12]*v.data[ 0] +
        data[13]*v.data[ 4] +
        data[14]*v.data[ 8] +
        data[15]*v.data[12],

        data[12]*v.data[ 1] +
        data[13]*v.data[ 5] +
        data[14]*v.data[ 9] +
        data[15]*v.data[13],

        data[12]*v.data[ 2] +
        data[13]*v.data[ 6] +
        data[14]*v.data[10] +
        data[15]*v.data[14],

        data[12]*v.data[ 3] +
        data[13]*v.data[ 7] +
        data[14]*v.data[11] +
        data[15]*v.data[15]
	);
}

vec4 mat4::operator * ( const vec4 & v ) const {
    return vec4 (
        v.x * data [0] + v.y * data [4] + v.z * data[8] + v.w * data [12],
        v.x * data [1] + v.y * data [5] + v.z * data[9] + v.w * data [13],
        v.x * data [2] + v.y * data [6] + v.z * data[10] + v.w * data [14],
        v.x * data [3] + v.y * data [7] + v.z * data[11] + v.w * data [15]
	);
}

vec3 mat4::operator * ( const vec3 & v ) const {
    return vec3 (
        v.x * data [0] + v.y * data [4] + v.z * data[8] + real (1) * data [12],
        v.x * data [1] + v.y * data [5] + v.z * data[9] + real (1) * data [13],
        v.x * data [2] + v.y * data [6] + v.z * data[10] + real (1)  * data [14]
	);
}

mat4 mat4::transpose () const {
	return mat4 (
		data[ 0],
		data[ 4],
		data[ 8],
		data[12],
		data[ 1],
		data[ 5],
		data[ 9],
		data[13],
		data[ 2],
		data[ 6],
		data[10],
		data[14],
		data[ 3],
		data[ 7],
		data[11],
		data[15]
	);
}

// Create matrix
mat4 mat4::make_translation ( const vec3 & p ) {
	return mat4 (
		real (1), real (0), real (0), real (0),
		real (0), real (1), real (0), real (0),
		real (0), real (0), real (1), real (0),
		p.x,	  p.y,		p.z,	  real (1)
	);
}

mat4 mat4::make_translation ( const vec4 & p ) {
	return mat4 (
		real (1), real (0), real (0), real (0),
		real (0), real (1), real (0), real (0),
		real (0), real (0), real (1), real (0),
		p.x,	  p.y,		p.z,	  p.w
	);
}

mat4 mat4::make_rotation_x ( real r ) {
	real 
		r_sin = sin (r),
		r_cos = cos (r);

	return mat4 (
		real (1), real (0), real (0), real (0),
		real (0), r_cos, r_sin, real (0),
		real (0), -r_sin, r_cos, real (0),
		real (0), real (0),	real (0), real (1)
	);
}

mat4 mat4::make_rotation_y ( real r ) {
	real 
		r_sin = sin (r),
		r_cos = cos (r);

	return mat4 (
		r_cos, real (0), -r_sin, real (0),
		real (0), real (1), real (0), real (0),
		r_sin, real (0), r_cos, real (0),
		real (0), real (0),	real (0), real (1)
	);
}

mat4 mat4::make_rotation_z ( real r ) {
	real 
		r_sin = sin (r),
		r_cos = cos (r);

	return mat4 (
		r_cos, r_sin, real (0), real (0),
		-r_sin, r_cos, real (0), real (0),
		real (0), real (0), real (1), real (0),
		real (0), real (0),	real (0), real (1)
	);
}

mat4 mat4::make_scale ( const vec3 & p ) {
	return mat4 (
		p.x, real (0), real (0), real (0),
		real (0), p.y, real (0), real (0),
		real (0), real (0), p.z, real (0),
		real (0), real (0), real (0), real (1)
	);
}

mat4 mat4::make_scale ( const vec4 & p ) {
	return mat4 (
		p.x, real (0), real (0), real (0),
		real (0), p.y, real (0), real (0),
		real (0), real (0), p.z, real (0),
		real (0), real (0), real (0), p.w
	);
}