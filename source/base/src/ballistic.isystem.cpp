#include "ballistic.isystem.h"

namespace ballistic {

	isystem::~isystem () {}

	igame * isystem::get_game () { return _game; }
	void isystem::set_game (ballistic::igame * value) { _game = value; }

}