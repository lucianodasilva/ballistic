#ifndef _ballistic_graphics__ballistic_graphics_dx_mesh_h_
#define _ballistic_graphics__ballistic_graphics_dx_mesh_h_

#include <ballistic.base.h>
#include <ballistic.graphics.h>

#include <d3d9.h>

namespace ballistic {
	namespace graphics {
		
		class dx_mesh : public ballistic::graphics::imesh
		{
		private:
			
			LPDIRECT3DDEVICE9 _device;

			LPDIRECT3DVERTEXBUFFER9 _buffer;
			LPDIRECT3DINDEXBUFFER9 _index;
			
		public:
			
			dx_mesh (LPDIRECT3DDEVICE9 device);
			~dx_mesh ();
			
			virtual void set_data (
				vertex vert_buffer [],
				uint32 vert_buffer_size,
				uint16 index_buffer [],
				uint32 index_buffer_size
			);
			
			virtual void attach ();
			virtual void render ();
			virtual void detach ();
			
		};
		
	}
}


#endif