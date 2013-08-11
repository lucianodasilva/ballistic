
#ifndef _ballistic_graphics_opengl_effectfield_h_
#define _ballistic_graphics_opengl_effectfield_h_

namespace ballistic {
	namespace graphics {
		
		template < class T >
		class opengl_effectfield_base {
		private:
			
			T _value;
			
		public:
			
			virtual ieffectfield * clone ();
			
		};
		
	}
}

#endif
