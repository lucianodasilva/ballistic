#include "ballistic.frontend.ui_control.h"

namespace ballistic {
	namespace frontend {

		control * control::find_containing (const vec2 & p) {
			for (control * c : _controls) {

				if (c->bounds ().contains (p)) {
					return c;
				}
			}

			return nullptr;
		}

		void control::on_mouse_move (const vec2 & position) {
			control * c = find_containing (position);

			if (c) {
				vec2 client_pos = position - c->location ();
				c->on_mouse_move (client_pos);
			} else {
				on_mouse_move_event (this, position);
			}
		}

		void control::on_mouse_down (const mouse_event_args & args) {
			control * c = find_containing (args.position);

			if (c) {
				vec2 client_pos = args.position - c->location ();
				c->on_mouse_move ({
					client_pos,
					args.buttons
				});
			} else {
				on_mouse_down_event (this, args);
			}
		}

		void control::on_mouse_up (const mouse_event_args & args) {
			control * c = find_containing (args.position);

			if (c) {
				vec2 client_pos = args.position - c->location ();
				c->on_mouse_move ({
					client_pos,
					args.buttons
				});
			} else {
				on_mouse_up_event (this, args);
			}
		}

		void control::on_draw (const draw & d) {
			d.fill_rect (
				_background_color,
				to_absolute (_location),
				to_absolute (_location + _size)
			);
			
			on_draw_event (this, d);

			for (control * c : _controls) {
				c->on_draw (d);
			}
		}

		control::control () :
			_parent (nullptr),
			_location (),
			_size ()
		{}

		control::~control () {}

		control * control::parent () const { return _parent; }
		control * control::parent (control * v) {
			_parent = v;
			return v;
		}

		std::vector < control * > & control::controls () {
			return _controls;
		}

		vec2 control::location () const { return _location; }
		vec2 control::location (const vec2 & v) {
			_location = v;
			return _location;
		}

		vec2 control::size () const { return _size; }
		vec2 control::size (const vec2 & v) {
			_size = v;
			return v;
		}

		color control::background_color () const { return _background_color; }
		color control::background_color (const color & v) {
			_background_color = v;
			return v;
		}

		rect control::bounds () const {
			rect r;
			r.position = _location;
			r.size = _size;

			return r;
		}

		rect control::to_absolute (const rect & client_rect) const{
			if (!_parent)
				return client_rect;

			rect temp;

			temp.position = client_rect.position + _location;
			temp.size = client_rect.size;

			return _parent->to_absolute (temp);
		}

		vec2 control::to_absolute (const vec2 & client_location) const {
			if (!_parent)
				return client_location;

			vec2 temp = client_location + _location;

			return _parent->to_absolute (temp);
		}

		rect control::to_client (const rect & absolute_rect) const {
			if (!_parent)
				return absolute_rect;

			rect temp = to_absolute (bounds ());

			temp.position = _location - temp.position;

			return temp;
		}

		vec2 control::to_client (const vec2 & absolute_location) const {
			if (!_parent)
				return absolute_location;

			return absolute_location - to_absolute (_location);
		}

	}
}