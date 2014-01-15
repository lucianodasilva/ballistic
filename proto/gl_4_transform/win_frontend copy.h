#ifndef	_matrix_h_
#define _matrix_h_

struct matrix {
	
	float data [16] =
	{
		1.F, .0F, .0F, .0F,
		.0F, 1.F, .0F, .0F,
		.0F, .0F, 1.F, .0F,
		.0F, .0F, .0F, 1.F
	};
	
	inline matrix operator * (matrix & v) {
		return  
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
		};
	}
	
};

#endif