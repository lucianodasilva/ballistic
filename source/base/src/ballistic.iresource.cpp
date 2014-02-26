#include "ballistic.iresource.h"

namespace ballistic {

	id_t iresource::id () const { return _id; }

	iresource::iresource (id_t id_v) : _id (id_v) {}

	iresource::~iresource () {}

}
