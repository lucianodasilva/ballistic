#include "ballistic.graphics.rig.h"
#include "ballistic.graphics.common_id.h"


namespace ballistic {
	namespace graphics {

		const id_t & rig_animation::id () const {
			return _id;
		}

		rig::rig (const id_t & id, uint32_t bone_count) : 
			iresource (id),
			_bone_count (bone_count)
		{}

		rig::~rig() {}

		
		void rig::create_animation (
			const id_t & id_v,
			mat4 * bone_data,
			uint32_t bone_data_size,
			uint32_t frame_count,
			real duration
		) {

			auto it = _animations.find (id_v);

			if (it != _animations.end ()) {
				debug_error ("animation id " << id_v << " already exists");
				return;
			}

			if (bone_data_size % frame_count != _bone_count) {
				debug_error ("animation " << id_v << " data does not match expected bone count for available frames");
				return;
			}

			rig_animation & anim = _animations [id_v];

			anim._frames.resize (frame_count);
			mat4 * bones = bone_data;

			for (auto f : anim._frames) {
				std::copy (bones, bones + _bone_count, f._bones);
				bones += _bone_count;
			}
		}

	}
}