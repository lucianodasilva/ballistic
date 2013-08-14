#ifndef _ballistic_graphics_ieffect_h_
#define	_ballistic_graphics_ieffect_h_

#include <ballistic.base.h>
#include <string>

using namespace std;

namespace ballistic {
	namespace graphics {

		class ieffect : public ballistic::resources::iresource {
		public:

			virtual uint8 get_run_id () = 0;

			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			) = 0;

			virtual void apply () = 0;

		};

	}
}

#endif