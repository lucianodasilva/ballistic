//
//  ballistic.iresource.h
//  ballistic_graphics
//
//  Created by Luciano da Silva on 7/14/13.
//
//

#ifndef _ballistic_iresource_h
#define _ballistic_iresource_h

#include "ballistic.id.h"

namespace ballistic {

	class iresource {
	private:

		id_t _id;

	public:

		id_t id () const;
			
		iresource (const id_t & id_v);
		virtual ~iresource ();
	};
}

#endif
