#include "ballistic.isystem.h"
#include "ballistic.game.h"

namespace ballistic {

	isystem::isystem (ballistic::game & game_ref) : _game (game_ref) {}
	isystem::~isystem () {}

}