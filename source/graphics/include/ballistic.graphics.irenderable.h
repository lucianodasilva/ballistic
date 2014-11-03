#ifndef _ballistic_graphics_irenderable_h_
#define	_ballistic_graphics_irenderable_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class idevice;

		class irenderable : public ballistic::iresource {
		public:

			irenderable (const id_t & id);

			virtual uint8_t run_id () const = 0;

			virtual void apply (idevice * device) = 0;
			virtual void render () = 0;

			virtual aabox bounding_box () const = 0;

		};

	}
}

#endif