#include "ballistic.graphics.material.h"
#include "ballistic.graphics.defines.h"


namespace ballistic {
	namespace graphics {

		void material::activate () {
			
			glPushAttrib(GL_CURRENT_BIT);
			glColor4fv (&color[0]);

		}

		void material::deactivate () {
			glPopAttrib ();
		}

	}
}