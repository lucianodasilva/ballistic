#include "ballistic.graphics.rig.h"
#include "ballistic.graphics.common_id.h"
#include "ballistic.graphics.graphics_system.h"


namespace ballistic {
	namespace graphics {

		rig_frame_tween rig_frame_tween::null_frame_tween = {
			std::vector < mat4 > (0),
			rig_animation::null_animation
		};

		rig_animation rig_animation::null_animation = {
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

		void rig::set_frame_tween (rig_frame_tween & tween) const {
			tween.animation = rig_animation::null_animation;
			tween.bones.resize (_bone_count);
		}

		void rig::set_frame_tween (rig_frame_tween & tween, const id_t & animation_id, real time) const {

			auto it = _animations.find (animation_id);

			if (it == _animations.end ()) {
				debug_error ("rig " << id () << " animation " << animation_id << " was not found");
				tween.animation = rig_animation::null_animation;
				tween.bones.resize (0);
			}

			tween.animation = it->second;
			tween.bones.resize (_bone_count);
			
			it->second.update_frame_tween (tween, time);
		}

		const id_t rigged::component_id = id::graphics::rigged;

		rigged::rigged () :
			_state (rig_state_stopped),
			_p_rig (nullptr),
			_p_rig_tween (nullptr),
			_rig_tween (rig_frame_tween::null_frame_tween)
		{}

		void rigged::require_properties (entity_type * new_type, component_info & info) {
			new_type->properties.require < id_t > (id::graphics::rig_id, id::null);
			new_type->properties.require < rig * > (id::graphics::rig, nullptr);
			new_type->properties.require < rig_frame_tween * > (id::graphics::rig_tween, &rig_frame_tween::null_frame_tween);
		}

		void rigged::setup (ballistic::containers::property_container & parameters) {
			component::setup (parameters);

			entity & p = parent ();

			_system = dynamic_cast <graphics_system *> (game ().systems [ballistic::id::graphics::system]);

			if (!*_p_rig)
				*_p_rig = game ().resources [
					p.properties [id::graphics::rig_id].as < id_t > ()
				].as < rig > ();

			if (*_p_rig) {
				rig * rig_inst = *_p_rig;
				rig_inst->set_frame_tween (_rig_tween);
				*_p_rig_tween = &_rig_tween;
			}

			game ().global_notifier.attach (id::message::update, this);
			p.local_notifier.attach (id::message::start_rig_animation, this);
			p.local_notifier.attach (id::message::stop_rig_animation, this);
		}

		void rigged::terminate () {
			game ().global_notifier.detach (id::message::update, this);
			parent ().local_notifier.detach (id::message::start_rig_animation, this);
			parent ().local_notifier.detach (id::message::stop_rig_animation, this);
		}

		void rigged::notify (ballistic::entity * sender, ballistic::message & message) {
			
			id_t message_id = message.id ();

			if (message_id == id::message::update) {

				if (_state == rig_state_stopped)
					return;

				//TODO: check if object "in" camera... if not, don't update

				real game_time = message [id::game_time];
				real elapsed = game_time - _animation_start;

				real lapse = elapsed;

				if (_state != rig_state_looping && elapsed > _rig_tween.animation.duration) {
					lapse = _rig_tween.animation.duration;
					_state = rig_state_stopped;
				}

				_rig_tween.update (lapse);

			} else {

				if (message_id == id::message::start_rig_animation) {

					rig * rig_inst = *_p_rig;

					_animation_start = game ().game_time ();
					rig_inst->set_frame_tween (
						_rig_tween,
						message [id::graphics::rig_animation_id].as < id_t > (),
						0
					);
				} else if (message_id == id::message::stop_rig_animation) {
					_state = rig_state_stopped;
				}

			}

		}

	}
}