#include "ballistic.graphics.render_list.h"

namespace ballistic {
	namespace graphics {

		uint32 render_list::size () {
			return _size;
		}

		uint32 render_list::capacity () {
			return _capacity;
		}

		render_list::render_list () : _capacity (0), _size (0), _data (nullptr), _swap_buffer (nullptr) {
		}

		render_list::~render_list () {
			reset ();
		}

		render_item & render_list::reserve_item () {

			if (_size == _capacity) {
				if (_capacity == 0) {
					reserve (100);
				} else {
					reserve (_size * 2);
				}
			}

			return *_data [_size++];
		}

		void render_list::clear () {
			_size = 0;
		}

		void render_list::reset () {
			for (uint32 i = 0; i < _capacity; ++i)
				delete _data [i];

			delete [] _data;
			_data = nullptr;
		}

		void render_list::reserve (uint32 new_capacity) {

			render_item ** new_data = new render_item * [new_capacity];

			if (_data) {
				// copy and clean up
				for (uint32 i = 0; i < _capacity; ++i) {
					if (i < _size)
						new_data [i] = _data [i];
					else
						delete _data [i];
				}

				delete [] _data;
				delete [] _swap_buffer;
			}

			_data = new_data;
			_swap_buffer = new render_item * [new_capacity];

			_capacity = new_capacity;

			for (uint32 i = _size; i < _capacity; ++i) {
				_data [i] = new render_item ();
			}
		}

		void render_list::sort () {

			uint8 value;
			uint8 * p_value;

			render_item * item;
			render_item ** swap_tmp;

			for (int i = 0; i < radix_count; ++i) {
				_hr [i] = &_histograms [256 * i];
				_or [i] = &_offsets [256 * i];
			}
			
			// calculate histograms
			memset ((void *)&_histograms [0], 0, table_size * sizeof (uint32));

			for (uint32 i = 0; i < _size; ++i) {
				p_value = (uint8 *)&(_data [i]->bucket);
			
				for (uint32 j = 0; j < radix_count; ++j)
					++_hr [j][p_value [j]];
			}

			for (uint32 i = 0; i < table_size; ++i) {
				if (i % 256 == 0)
					_offsets [i] = 0;
				else
					_offsets [i] = _offsets [i - 1] + _histograms [i - 1];
			}

			// swap stuff around
			for (uint32 radix = 0; radix < radix_count; ++radix) {

				// check if empty byte pass
				if (_hr [radix][0] == _size) {
					continue;
				}

				// copy to offseted positions
				for (uint32 i = 0; i < _size; ++i) {
					item = _data [i];

					value = ((uint8 *)&(item->bucket)) [radix];
					_swap_buffer [_or [radix][value]++] = item;
				}

				// swap
				swap_tmp = _data;
				_data = _swap_buffer;
				_swap_buffer = swap_tmp;
			}

		}

	}
}