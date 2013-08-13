#ifndef _ballistic_graphics_constant_h_
#define _ballistic_graphics_constant_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class ieffect;

		class ihardware_constant {
		public:
			
			virtual ~ihardware_constant ();
			
			virtual id_t get_id () = 0;

			virtual void set (const var & v) = 0;
			virtual var get () const = 0;
			
			virtual void apply () = 0;

		};

		template < class T  >
		class ihardware_constant_base : public ihardware_constant {
		protected:

			id_t	_id;
			T		_value;

		public:

			virtual id_t get_id ();

			virtual void set (const var & v);
			virtual var get () const;

		};

		class constant {
		private:

			ihardware_constant *	_hardware;
			var						_value;

		public:

			inline constant ();
			inline constant (const constant & v);
			inline constant (ihardware_constant * v);

			inline id_t get_id () const ;
			
			inline operator var () const;

			template < class T >
			inline operator T () const;

			template < class T >
			inline T as () const;

			inline void bind (ihardware_constant * v);

			template < class T >
			inline constant & operator = (const T & v);

			inline constant & operator = (const constant & v);

			inline void apply ();
		};
	}
}

#include "ballistic.graphics.constant.inl"

#endif //!_ballistic_graphics_ieffectfield_h_
