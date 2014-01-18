#ifndef	_ballistic_graphics_render_list_h_
#define _ballistic_graphics_render_list_h_

#include <ballistic.base.h>
#include "ballistic.graphics.render_item.h"

namespace ballistic {
	namespace graphics {

		class render_list {
		private:

			static const uint32_t radix_count = sizeof (render_bucket);
			static const uint32_t table_size = 256 * radix_count;

			uint32_t			_capacity;
			uint32_t			_size;

			render_item **	_data;
			render_item **	_swap_buffer;

			uint32_t			_histograms [table_size];
			uint32_t			_offsets [table_size];
			
			uint32_t *		_hr [radix_count];
			uint32_t *		_or [radix_count];

		public:

			uint32_t size ();
			uint32_t capacity ();

			render_list ();
			~render_list ();
			
			render_item & reserve_item ();

			void clear ();
			void reset ();

			void reserve (uint32_t new_capacity);

			void sort ();

			inline render_item & operator [] (uint32_t index);

		};

		render_item & render_list::operator [] (uint32_t index) {
			return *_data [index];
		}


	}
}

#endif