#include "ballistic.io.storage_filesystem.h"
#include "ballistic.io.iloader.h"

#include <fstream>

namespace ballistic {
	namespace io {

		storage_filesystem::~storage_filesystem () {}

		bool storage_filesystem::contains (const string & path) {
			//TODO: probably replace this for a more efficient alternative
			return !ifstream (path).fail ();
		}

		bool storage_filesystem::load (iloader * loader, const string & path, ballistic::resource_container & container) {
			ifstream file_stream (path, ios::in | ios::binary | ios::ate);

			uint32_t length = file_stream.tellg ();
			file_stream.seekg (ios::beg);

			return loader->load (file_stream, length, container);
		}
	}
}