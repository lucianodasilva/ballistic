//
//  ballistic.resources.id.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/16/13.
//
//

#ifndef _ballistic_res_id_h_
#define _ballistic_res_id_h_

#include "ballistic.id.h"
#include <string>

using namespace std;

namespace ballistic {

	struct res_id_t {
	private:
		
		id_t	_id;
		string	_source;
		
	public:
		
		inline res_id_t ( const string & name )
		: _id (text_to_id (name.c_str ())) {}
		
		inline res_id_t ( const string & name, const string & source )
		: _id (text_to_id (name.c_str ())), _source (source) {}
		
		inline res_id_t ( res_id_t && origin )
		: _id (origin._id), _source (origin._source) {}

		inline res_id_t & operator = (res_id_t && origin) {
			_id = origin._id;
			_source = origin._source;

			return *this;
		}
		
		inline id_t id () const {
			return _id;
		}
		
		inline const string & source () const {
			return _source;
		}
		
	};
	
}

#endif
