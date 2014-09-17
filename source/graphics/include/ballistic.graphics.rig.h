#ifndef	_ballistic_graphics_rig_h_
#define _ballistic_graphics_rig_h_

#include <ballistic.base.h>

namespace ballistic {
	namespace graphics {

		class rig;
		class rig_animation;

		class rig_frame {
		private:
			std::vector < mat4 > _bones;
		public:

			friend class rig;

			inline const std::vector < mat4 > & bones () const { return _bones; }

		};

		class rig_animation {
		private:

			id_t		
				_id;

			std::vector < rig_frame >
				_frames;

		public:

			friend class rig;

			const id_t & id () const;

		};

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
			
			rig_frame &		create_frame (const id_t & animation_id, real time);
			void			update_frame (rig_frame & frame, real time);

		};

	}
}

#endif