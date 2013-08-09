#ifndef _ballistic_graphics_ieffectfield_h_
#define _ballistic_graphics_ieffectfield_h_

namespace ballistic {
	namespace graphics {

		class ieffectfield {
		private:



		public:

			virtual void apply () = 0;

		};

		template < class T >
		class effectfield {
		private:

		public:

			virtual void apply () = 0;

		};

		template <>
		class effectfield : public ieffectfield {

		};

	}
}

#endif //!_ballistic_graphics_ieffectfield_h_
