#ifndef	_ballistic_graphics_renderable_h_
#define _ballistic_graphics_renderable_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class imesh;
		class imaterial;

		struct render_bucket {

			union {
				uint32 data;

				struct {
					uint8	_b0;
					uint8	_b1;
					uint8	_b2;
					uint8	_b3;
				};
			};

			inline void set_value (int8 layer, bool translucent, uint16 depth, uint8 material) {
				// set layer
				_b0 = (layer << 1);
				// set translucent
				if (translucent) {
					_b0 ^= 0x01;
					_b1 = material;
					*((uint16 *)&_b2) = depth;
				} else {
					_b0 |= 0x01;
					*((uint16 *)&_b1) = depth;
					_b3 = material;
				}

			}

			inline bool get_translucent () { return _b0 & 0x01; }

			inline int8 get_layer () { return (_b0 >> 1) & 0x7F; }


			inline uint16 get_depth () {
				return get_depth (get_translucent ());
			}

			inline uint16 get_depth (bool translucent) {
				if (translucent)
					return *(uint16 *)&_b2;
				else
					return *(uint16 *)&_b1;
			}

			inline uint8 get_material () {
				return get_material (get_translucent ());
			}

			inline uint8 get_material (bool translucent) {
				if (translucent)
					return _b3;
				else
					return _b1;
			}
		};


		struct renderable {

			inline renderable (const renderable & o);
			inline renderable (imesh * mesh, imaterial * material, mat4 & transform );

			render_bucket	key;

			imesh *			mesh;
			imaterial *		material;
			mat4 &			transform;

		};

		renderable::renderable (const renderable & o) 
			: key (o.key), mesh (o.mesh), material (o.material), transform (o.transform) {}

		renderable::renderable (imesh * mesh, imaterial * material, mat4 & transform) 
			: mesh (mesh), material (material), transform (transform) 
		{
			key.set_value (0, false, 0, 0);
		}

	}
}

#endif