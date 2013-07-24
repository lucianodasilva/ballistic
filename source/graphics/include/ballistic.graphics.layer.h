#ifndef _ballistic_graphics_ilayer_h_
#define _ballistic_graphics_ilayer_h_

#include <vector>

#include "ballistic.graphics.renderable.h"

using namespace std;

namespace ballistic {
	namespace graphics {

		class idevice;
		class imesh;
		class imaterial;

		class ilayer {
		public:

			virtual void clear () = 0;

			virtual void push_renderable (imesh * mesh, imaterial * material) = 0;

			virtual void render (idevice * device) = 0;

			virtual ~ilayer ();

		};

		class layer : public ilayer {
		private:

			vector < renderable > _items;

		public:

			virtual void clear ();

			virtual void push_renderable (imesh * mesh, imaterial * material);

			virtual void render (idevice * device);

		};

	}
}

#endif