#ifndef _ballistic_graphics_iraster_font_h_
#define	_ballistic_graphics_iraster_font_h_

#include <ballistic.base.h>
#include <string>

#include "ballistic.graphics.imaterial.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice;
		

		class iraster_font : public imaterial {
		private:
		public:

			iraster_font (const id_t & id);

			virtual string text () = 0;
			virtual void text (const string & value) = 0;

		};

	}
}

#endif