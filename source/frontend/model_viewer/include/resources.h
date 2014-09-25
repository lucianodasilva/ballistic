#ifndef	_ballistic_model_viewer_resources_h_
#define _ballistic_model_viewer_resources_h_

#include <ballistic.base.h>

#define default_res_folder "model_viewer_res/"
#define default_res_file default_res_folder "default.xml"

ballistic::res_id_t
	res_default_material ("default_material.effect", default_res_folder "default_material.fx"),
	res_overlay_material ("overlay_material.effect", default_res_folder "overlay_material.fx");

#endif