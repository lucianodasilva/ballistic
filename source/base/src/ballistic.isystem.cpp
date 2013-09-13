#include "ballistic.isystem.h"

namespace ballistic {

	isystem::~isystem () {}

	game * isystem::get_game () { return _game; }
	void isystem::set_game (ballistic::game * value) { _game = value; }

}