
namespace ballistic {
namespace math {

	template < class T >
	const uint32 quat_t < T >::count = 4;
	
	template < class T >
	quat_t < T >::quat_t () : x (T()), y (T()), z (T()), w (T()) {}
	
	template < class T >
	quat_t < T >::quat_t ( T vx, T vy, T vz, T vw ) : x (vx), y (vy), z (vz), w (vw) {}
	
	template < class T >
	quat_t < T >::quat_t ( const quat_t < T > & v ) 
	: x (v.x), y (v.y), z (v.z), w (v.w) {}
	
	template < class T >
	quat_t < T > & quat_t < T >::operator = ( const quat_t < T > & v ) {
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
		
		return *this;
	}
	
	template < class T >
	quat_t < T >::operator T * () {
		return &_data [0];
	}
	
		template < class T >
	quat_t < T > quat_t < T >::operator + ( const quat_t < T > & v ) const {
		return quat_t ( x + v.x, y + v.y, z + v.z, w + v.w );
	}

	template < class T >
	quat_t < T > quat_t < T >::operator * ( T v ) const {
		return quat_t ( x * v, y * v, z * v, w * v);
	}
	
	template < class t >
	quat_t < T > quat_t < T >::operator * ( const quat_t < T > & v ) const {
		return quat_t < T >
		(
			v.w * x + v.x * w + v.y * z - v.z * y,
			v.w * y + v.y * w + v.z * x - v.x * z,
			v.w * z + v.z * w + v.x * y - v.y * x,
			v.w * w - v.x * x - v.y * y - v.z * z
		);
	}
	
	template < class T >
	vec3_t < T > quat_t < T >::operator * ( const vec3_t < T > & v ) const {
		vec3_t < T > qvec(x, y, z);
		vec3_t < T > uv = math::cross (qvec, v);
		vec3_t < T > uuv = math::cross (qvec, uv);
		
		uv *= (2.0f * w);
		uuv *= 2.0f;

		return v + uv + uuv;
	}

	template < class T >
	quat_t < T > & quat_t < T >::operator += ( const quat_t < T > & v ) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

	template < class T >
	quat_t < T > & quat_t < T >::operator *= ( T v ) {
		x *= v;
		y *= v;
		z *= v;
		w *= v;

		return *this;
	}

	template < class T >
	quat_t < T > & quat_t < T >::operator *= ( const quat_t < T > & v ) {
		x = v.w * x + v.x * w + v.y * z - v.z * y;
		y = v.w * y + v.y * w + v.z * x - v.x * z;
		z = v.w * z + v.z * w + v.x * y - v.y * x;
		w = v.w * w - v.x * x - v.y * y - v.z * z;
		
		return *this;
	}
	
	template < class T >
	mat4_t < T > quat_t < T >::to_matrix () const {
		return mat4_t < T > (
			(1.0F - (2.0F * ((y * y) + (z * z)))),
			(2.0F * ((x * y) - (z * w))),
			(2.0F * ((x * z) + (y * w))),
			0.0F,
			(2.0F * ((x * y) + (z * w))),
			(1.0F - (2.0F * ((x * x) + (z * z)))),
			(2.0F * ((y * z) - (x * w))),
			0.0F,
			(2.0F * ((x * z) - (y * w))),
			(2.0F * ((y * z) + (x * w))),
			(1.0F - (2.0F * ((x * x) + (y * y))))
			0.0F,
			0.0F,
			0.0F,
			0.0F,
			1.0F
		);
	}

}
}