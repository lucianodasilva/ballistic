#include "ballistic.ifrontend.h"
#include "ballistic.ui.component.h"

namespace ballistic {

	ifrontend::~ifrontend () {}

	namespace frontend {
		void define_resources (game & game_inst) {
			component::declare < ui::component > (game_inst);
		}
	}

}