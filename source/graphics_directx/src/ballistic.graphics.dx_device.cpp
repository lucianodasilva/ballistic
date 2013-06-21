#include "ballistic.graphics.dx_device.h"

#include <d3d9.h>
#include "ballistic.graphics.dx_mesh.h"

namespace ballistic {
	namespace graphics {
		
		dx_device::dx_device (HWND hWnd) {

			_d3d = Direct3DCreate9 (D3D_SDK_VERSION);
			if (FAILED (_d3d))
				throw "Unable to create d3d9 instance!";

			D3DPRESENT_PARAMETERS pp;
			ZeroMemory (&pp, sizeof (pp));

			D3DDISPLAYMODE mode;

			if (FAILED (_d3d->GetAdapterDisplayMode (D3DADAPTER_DEFAULT, &mode)))
				throw "Unable to get adapter display mode";

			pp.Windowed = TRUE;
			pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
			pp.BackBufferFormat = mode.Format;

			if (FAILED (_d3d->CheckDeviceType (
							D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							pp.BackBufferFormat,
							pp.BackBufferFormat,
							TRUE)))
			{
				throw "Unsuported device type";
			}

			if (FAILED (_d3d->CreateDevice ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_PUREDEVICE, &pp, &_d3d_device)))
				throw "Unable to create device";

		}
	
		imaterial * dx_device::create_material ()
		{
			return nullptr;
		}
		
		imesh *	dx_device::create_mesh ()
		{
			return new dx_mesh (_d3d_device);
		}
		
		itexture * dx_device::create_texture (const point & size)
		{
			return nullptr;
		}
		
		imaterial * dx_device::load_material ( const string & filename )
		{
			return nullptr;
		}
		
		imesh *	dx_device::load_mesh ( const string & filename )
		{
			return nullptr;
		}
		
		itexture * dx_device::load_texture ( const string & filename )
		{
			return nullptr;
		}
		
		void dx_device::set_transform(const mat4 & matrix)
		{
			_d3d_device->SetTransform 
				(D3DTS_WORLD, (D3DMATRIX *)matrix.data);
		}
		
		void dx_device::set_projection ( const mat4 & matrix ) {
			_d3d_device->SetTransform
				(D3DTS_PROJECTION, (D3DMATRIX *)matrix.data);
		}

		void dx_device::set_clear_color ( const color & cr ) {
			_clear_color = cr;
		}

		void dx_device::clear () {
			_d3d_device->Clear (
				0, 
				nullptr, 
				D3DCLEAR_TARGET, D3DCOLOR_XRGB (
					uint8 (_clear_color.r * 255.999), 
					uint8 (_clear_color.g * 255.999), 
					uint8 (_clear_color.b * 255.999)
				), 
				1.0F, 
				0);
		}
		
		void dx_device::begin_frame ()
		{
			_d3d_device->Clear (
				0, 
				nullptr, 
				D3DCLEAR_ZBUFFER, 
				D3DCOLOR_XRGB (
					uint8 (_clear_color.r * 255.999), 
					uint8 (_clear_color.g * 255.999), 
					uint8 (_clear_color.b * 255.999)
				), 
				1.0F, 
				0);
			_d3d_device->BeginScene ();
		}
		
		void dx_device::end_frame ()
		{
			_d3d_device->EndScene ();
		}
		
		void dx_device::set_current_mesh ( imesh * mesh )
		{
		
		}
		
		void dx_device::set_current_texture ( itexture * texture )
		{
		
		}
		
		void dx_device::present ()
		{
			_d3d_device->Present (nullptr, nullptr, nullptr, nullptr);
		}
		
		void dx_device::destroy ()
		{
			_d3d_device->Release ();
			_d3d->Release ();
		}
	
	}
}