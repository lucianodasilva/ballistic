#ifndef _ballistic_graphics_ieffect_h_
#define	_ballistic_graphics_ieffect_h_

#include <ballistic.base.h>
#include <string>

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice;

		class ieffect : public ballistic::resources::iresource {
		public:

			virtual uint8 get_run_id () = 0;

			virtual void load (
				const string & vs_shader_source,
				const string & fs_shader_source
			) = 0;

			virtual void apply (idevice * device) = 0;

		};

	}
}

#endif