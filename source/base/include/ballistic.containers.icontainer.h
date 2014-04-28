#ifndef	_ballistic_containers_icontainer_h_
#define _ballistic_containers_icontainer_h_

namespace ballistic {
	namespace containers {

		template < class data_container_t >
		class icontainer {
		protected:
			data_container_t data;
		public:

			inline icontainer () {}

			// erase copy constructors and operators
			icontainer (const icontainer &) = delete;
			icontainer & operator = (const icontainer &) = delete;

			// default iterator types
			typedef typename data_container_t::iterator iterator;
			typedef typename data_container_t::const_iterator const_iterator;

			// default iteration fixtures
			inline iterator begin () { return data.begin (); }
			inline iterator end () { return data.end (); }

			inline const_iterator cbegin () const { return data.cbegin (); }
			inline const_iterator cend () const { return data.cend (); }

			// ---
			virtual ~icontainer () {}

		};

	}
}

#endif