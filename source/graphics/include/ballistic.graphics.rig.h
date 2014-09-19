#ifndef	_ballistic_graphics_rig_h_
#define _ballistic_graphics_rig_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class rig;
		struct rig_animation;

		struct rig_frame_tween {

			static const rig_frame_tween null_frame_tween;

			std::vector < mat4 >	bones;
			const rig_animation &	animation;

			inline void update (real time);
		};

		struct rig_frame {
			std::vector < mat4 > bones;
		};

		struct rig_animation {
		public:

			const static rig_animation null_animation;

			uint32_t	bone_count;
			real		duration;
			real		frame_duration;

			std::vector < rig_frame >
						frames;

			inline void update_frame_tween (real time, rig_frame_tween & tween) const {

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
				
			inline rig_frame_tween create_frame_tween (real time) const {

				rig_frame_tween new_tween = {
					std::vector < mat4 > (bone_count),
					*this
				};

				update_frame_tween (time, new_tween);
				return new_tween;
			}

		};

		// avoid issues with circular dependencies
		void rig_frame_tween::update (real time) {
			animation.update_frame_tween (time, *this);
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
			
			rig_frame_tween create_frame_tween () const;
			rig_frame_tween create_frame_tween (const id_t & animation_id, real time) const;

		};

		class rigged : public ballistic::component {
		private:

			property < rig * > *			_rig;
			property < rig_frame_tween * >	_rig_tween_p;

			real
				_animation_start;

			rig_frame_tween _

		public:

			rigged ();

			static void require_properties (entity_type * new_type, component_info & info);

			virtual void setup (ballistic::entity * parent, ballistic::containers::property_container & parameters);

			virtual void terminate ();
			virtual void notify (ballistic::entity * sender, ballistic::message & message);

		};

	}
}

#endif