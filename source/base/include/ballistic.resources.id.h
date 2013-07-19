//
//  ballistic.resources.id.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/16/13.
//
//

#ifndef _ballistic_resources_id_h_
#define _ballistic_resources_id_h_

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
		: _id (string_to_id (name)) {}
		
		inline res_id_t ( const string & name, const string & source )
		: _id (string_to_id (name)), _source (source) {}
		
		inline res_id_t ( const res_id_t & origin )
		: _id (origin._id), _source (origin._source) {}
		
		
		inline operator id_t () const {
			return _id;
		}
		
		inline const string & get_source () const {
			return _source;
		}
		
	};
	
}

#endif
