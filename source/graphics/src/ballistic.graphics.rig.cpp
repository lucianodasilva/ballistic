#include "ballistic.graphics.rig.h"
#include "ballistic.graphics.common_id.h"


namespace ballistic {
	namespace graphics {

		const rig_frame_tween rig_frame_tween::null_frame_tween = {
			std::vector < mat4 > (0),
			rig_animation::null_animation
		};

		const rig_animation rig_animation::null_animation = {
			0,
			0,
			0,
			std::vector < rig_frame > (0)
		};

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
			
			anim.frames.resize (frame_count);
			mat4 * bones = bone_data;
			
			for (auto f : anim.frames) {
				std::copy (bones, bones + _bone_count, f.bones.begin ());
				bones += _bone_count;
			}

			anim.duration = duration;
			anim.frame_duration = duration / _bone_count;
			anim.bone_count = _bone_count;
		}

		rig_frame_tween rig::create_frame_tween (const id_t & animation_id, real time) {
			auto it = _animations.find (animation_id);

			if (it == _animations.end ()) {
				debug_error ("rig " << id () << " animation " << animation_id << " was not found");
				return rig_frame_tween::null_frame_tween;
			}

			return it->second.create_frame_tween (time);
		}

	}
}