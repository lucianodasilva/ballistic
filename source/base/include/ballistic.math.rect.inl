namespace ballistic {
	namespace math {

		template < class T >
		rect_t < T >::rect_t () 
			: x ( T() ), y ( T() ), width ( T() ), height ( T() ) 
		{}

		template < class T >
		rect_t < T >::rect_t ( T x, T y, T width, T height )
			: x (x), y (y), width (width), height (height)
		{}

		template < class T >
		rect_t < T >::rect_t ( vec2_t < T > position, vec2_t < T > size )
			: position ( position ), size (size)
		{}

		template < class T >
		rect_t < T >::rect_t ( const rect_t < T > & v ) 
			: position (v.position), size (v.size)
		{}

		template < class T >
		rect_t < T > & rect_t < T >::operator = ( const rect_t < T > & v ) {
			position = v.position;
			size = v.size;

			return *this;
		}
	}
}