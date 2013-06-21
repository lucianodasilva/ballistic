#include "ballistic.graphics.dx_mesh.h"

#include <GL/glew.h>

namespace ballistic {
	namespace graphics {
		
		dx_mesh::dx_mesh (LPDIRECT3DDEVICE9 device) : _device (device) {}
		
		dx_mesh::~dx_mesh() {

		}
		
		void dx_mesh::set_data (
			vertex vert_buffer [],
			uint32 vert_buffer_size,
			uint16 index_buffer [],
			uint32 index_buffer_size
		){

			_device->CreateVertexBuffer (
				sizeof (vertex) * vert_buffer_size,
				0,
				D3DFVF_XYZ | D3DFVF_TEXCOORDSIZE2 (0),
				D3DPOOL_MANAGED,
				&_buffer,
				NULL);

			// Copy buffer
			VOID* buffer_void;
			_buffer->Lock (0, 0,(void **)&buffer_void, 0);
			memcpy (buffer_void, vert_buffer, sizeof (vert_buffer));
			_buffer->Unlock ();

			_device->CreateIndexBuffer (
				sizeof (uint16) * index_buffer_size,
				D3DUSAGE_WRITEONLY,
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&_index,
				NULL);

			VOID* index_void;
			_index->Lock (0, 0, (void**)&index_void, 0);
			memcpy (index_void, index_buffer, sizeof (index_buffer));
			_index->Unlock ();
		}
		
		void dx_mesh::attach () {
			_device->SetStreamSource (
				0,
				_buffer,
				0,
				sizeof (vertex)
			);

			_device->SetIndices (_index);
		}
		
		void dx_mesh::render () {
			_device->DrawPrimitive (
				D3DPT_TRIANGLELIST,
				0,
				1 // store or calculate primitive count
			);
		}
		
		void dx_mesh::detach() {
		}
	}
}