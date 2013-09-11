#ifndef	_ballistic_graphics_render_list_h_
#define _ballistic_graphics_render_list_h_

#include <ballistic.base.h>
#include "ballistic.graphics.render_item.h"

namespace ballistic {
	namespace graphics {

		class render_list {
		private:

			static const uint32 radix_count = sizeof (render_bucket);
			static const uint32 table_size = 256 * radix_count;

			uint32			_capacity;
			uint32			_size;

			render_item **	_data;
			render_item **	_swap_buffer;

			uint32			_histograms [table_size];
			uint32			_offsets [table_size];
			
			uint32 *		_hr [radix_count];
			uint32 *		_or [radix_count];

		public:

			uint32 size ();
			uint32 capacity ();

			render_list ();
			~render_list ();
			
			render_item & reserve_item ();

			void clear ();
			void reset ();

			void reserve (uint32 new_capacity);

			void sort ();

			inline render_item & operator [] (uint32 index);

		};

		render_item & render_list::operator [] (uint32 index) {
			return *_data [index];
		}


	}
}

#endif