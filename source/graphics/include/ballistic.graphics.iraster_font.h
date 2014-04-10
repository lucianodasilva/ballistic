#ifndef _ballistic_graphics_iraster_font_h_
#define	_ballistic_graphics_iraster_font_h_

#include <ballistic.base.h>
#include <string>

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice;

		class iraster_font : public ballistic::iresource {
		public:

			iraster_font (const id_t & id);

			virtual uint8_t run_id () = 0;


		};

	}
}

#endif