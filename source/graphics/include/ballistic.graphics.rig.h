#ifndef	_ballistic_graphics_rig_h_
#define _ballistic_graphics_rig_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class graphics_system;
		class rig;
		struct rig_animation;

		struct rig_frame_tween {

			static rig_frame_tween null_frame_tween;

			std::vector < mat4 >	bones;
			rig_animation &	animation;

			inline void update (real time);
		};

		struct rig_frame {
			std::vector < mat4 > bones;
		};

		struct rig_animation {
		public:

			static rig_animation null_animation;

			uint32_t	bone_count;
			real		duration;
			real		frame_duration;

			std::vector < rig_frame >
						frames;

			inline void update_frame_tween (rig_frame_tween & tween, real time) const {

				if (bone_count == 0)
					return;

				real a = time / frame_duration;

				int zero_frame = static_cast <int> (a);
				zero_frame = zero_frame - zero_frame / bone_count;

				a = a - (zero_frame * frame_duration);

				const rig_frame
					& frame_a = frames [zero_frame],
					& frame_b = frames [zero_frame + 1];

				for (uint32_t i = 0; i < bone_count; ++i) {
					math::lerp (frame_a.bones [i], frame_b.bones [i], a, tween.bones [i]);
				}
			}

		};

		// avoid issues with circular dependencies
		void rig_frame_tween::update (real time) {
			animation.update_frame_tween (*this, time);
		}

		class rig : public ballistic::iresource {
		private:

			uint32_t 
				_bone_count;

			std::map < id_t, rig_animation > 
				_animations;

		public:

			rig (const id_t & id, uint32_t bone_count);
			virtual ~rig();

			void			create_animation (const id_t & id_v, mat4 * bone_data, uint32_t bone_data_size, uint32_t frame_count, real duration);
			
			void			set_frame_tween (rig_frame_tween & tween) const;
			void			set_frame_tween (rig_frame_tween & tween, const id_t & animation_id, real time) const;

		};

		enum rig_state {
			rig_state_stopped,
			rig_state_running,
			rig_state_looping
		};

		class rigged : public ballistic::component {
		private:

			rig_state						_state;
			graphics_system					* _system;

			property < rig * >				* _p_rig;
			property < rig_frame_tween * >	* _p_rig_tween;

			real							_animation_start;
			rig_frame_tween					_rig_tween;

		public:

			static const id_t component_id;

			rigged ();

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters, ballistic::game & game_inst);

			virtual void terminate ();
			virtual void notify (ballistic::entity * sender, ballistic::message & message);

		};

	}
}

#endif