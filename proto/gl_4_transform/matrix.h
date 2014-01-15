#ifndef _matrix_h_
#define _matrix_h_

#include <cmath>

struct matrix {
	
	union {
		float data [16];
		struct {
			float
				m00, m01, m02, m03,
				m04, m05, m06, m07,
				m08, m09, m10, m11,
				m12, m13, m14, m15;
		};
	};

	inline matrix () :
		m00 (float (1)), m01 (float (0)), m02 (float (0)), m03 (float (0)),
		m04 (float (0)), m05 (float (1)), m06 (float (0)), m07 (float (0)),
		m08 (float (0)), m09 (float (0)), m10 (float (1)), m11 (float (0)),
		m12 (float (0)), m13 (float (0)), m14 (float (0)), m15 (float (1))
	{}

	inline matrix (const matrix & v)
		:
		m00 (v.m00), m01 (v.m01), m02 (v.m02), m03 (v.m03),
		m04 (v.m04), m05 (v.m05), m06 (v.m06), m07 (v.m07),
		m08 (v.m08), m09 (v.m09), m10 (v.m10), m11 (v.m11),
		m12 (v.m12), m13 (v.m13), m14 (v.m14), m15 (v.m15) 
	{}

	inline matrix ( float _m00, float _m01, float _m02, float _m03, float _m04, float _m05, float _m06, float _m07, float _m08, float _m09, float _m10, float _m11, float _m12, float _m13, float _m14, float _m15 )
		:
		m00 (_m00), m01 (_m01), m02 (_m02), m03 (_m03),
		m04 (_m04), m05 (_m05), m06 (_m06), m07 (_m07),
		m08 (_m08), m09 (_m09), m10 (_m10), m11 (_m11),
		m12 (_m12), m13 (_m13), m14 (_m14), m15 (_m15)
	{}

	inline matrix & operator = ( const matrix & v ) {
		for ( int i = 0; i < 16; ++i )
			data [i] = v.data [i];

		return *this;
	}

	inline matrix operator * ( const matrix & v ) const {
		return matrix (
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

	inline matrix transpose () const {
		return matrix (
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
	inline static matrix make_translation ( float x, float y, float z ) {
		return matrix (
			float (1), float (0), float (0), float (0),
			float (0), float (1), float (0), float (0),
			float (0), float (0), float (1), float (0),
			x,	  y,	z,	  float (1)
		);
	}

	inline static matrix make_rotation_x ( float r ) {
		float
			r_sin = sin (r),
			r_cos = cos (r);

		return matrix (
			float (1), float (0), float (0), float (0),
			float (0), r_cos, r_sin, float (0),
			float (0), -r_sin, r_cos, float (0),
			float (0), float (0),	float (0), float (1)
		);
	}

	inline static matrix make_rotation_y ( float r ) {
		float
			r_sin = sin (r),
			r_cos = cos (r);

		return matrix (
			r_cos, float (0), -r_sin, float (0),
			float (0), float (1), float (0), float (0),
			r_sin, float (0), r_cos, float (0),
			float (0), float (0),	float (0), float (1)
		);
	}

	inline static matrix make_rotation_z ( float r ) {
		float
			r_sin = sin (r),
			r_cos = cos (r);

		return matrix (
			r_cos, r_sin, float (0), float (0),
			-r_sin, r_cos, float (0), float (0),
			float (0), float (0), float (1), float (0),
			float (0), float (0),	float (0), float (1)
		);
	}
	
};

#endif
