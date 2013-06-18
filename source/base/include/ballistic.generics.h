#ifndef	_ballistic_generics_h_
#define _ballistic_generics_h_

#include "ballistic.id.h"

#include <map>
#include <string>

using namespace std;

namespace ballistic {

	template < class T >
	class generic_singleton : public T {
	private:
		static generic_singleton < T > * _instance;

		inline generic_singleton () {};
		inline generic_singleton ( const generic_singleton & o ) {}

	public:

		inline static generic_singleton < T > & instance ();
																																										  
	};

	template < class T, class ctor_T >
	class generic_factory {
	private:

		map < id_t, ctor_T > _const_inst;

	public:
		
		inline void define ( const string & name_id , ctor_T ctor_inst );
		inline void define ( id_t id, ctor_T ctor_inst );

		inline bool contains ( const string & name_id ) const;
		inline bool contains ( id_t id ) const;

		inline T create ( const string & name_id ) const;
		inline T create ( id_t id ) const;

	};

	template < class T >
	struct indirection {
		static inline T & demote ( T & inst );
	};

	template < class T >
	struct indirection < T * > {
		static inline T & demote ( T * inst );
	};

}

#include "ballistic.generics.inl"

#endif