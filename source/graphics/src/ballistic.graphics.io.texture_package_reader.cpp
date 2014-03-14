#include "ballistic.graphics.io.texture_package_reader.h"

#include "ballistic.graphics.itexture.h"
#include <png.h>

namespace ballistic {
	namespace graphics {
		namespace io {

			texture_wrap texture_package_reader::text_to_wrap (const char * value) {
				
				if (strcmp (value, "clamp_to_border") == 0)
					return texture_wrap_clamp_to_border;
				else if (strcmp (value, "clamp_to_edge") == 0)
					return texture_wrap_clamp_to_edge;
				else if (strcmp (value, "mirrored_repeat") == 0)
					return texture_wrap_mirrored_repeat;
				else if (strcmp (value, "repeat") == 0)
					return texture_wrap_repeat;
				else {
					debug_print ("unknown texture wrap value \"" << value << "\". defaulted to clamp_to_border");
					return texture_wrap_clamp_to_border;
				}
			}

			texture_filter texture_package_reader::text_to_filter (const char * value) {
				if (strcmp (value, "nearest") == 0)
					return texture_filter_nearest;
				else if (strcmp (value, "linear") == 0)
					return texture_filter_linear;
				else {
					debug_print ("unknown texture filter value \"" << value << "\". defaulted to nearest");
					return texture_filter_nearest;
				}
			}

			bool texture_package_reader::load_file (const char * filename, char *& data, texture_format & format, uint32_t & width, uint32_t & height) {
				png_byte header [8];

				FILE *fp = fopen (filename, "rb");
				if (fp == 0) {
					debug_print ("failed to open texture file \"" << filename << "\"")
					return false;
				}

				// read the header
				fread (header, 1, 8, fp);

				if (png_sig_cmp (header, 0, 8)) {
					debug_print ("file \"" << filename << "\" is not a valid png file");
					fclose (fp);
					return false;
				}

				png_structp png_ptr = png_create_read_struct (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
				if (!png_ptr) {
					debug_print ("file \"" << filename << "\" is not a valid png file");
					fclose (fp);
					return false;
				}

				// create png info struct
				png_infop info_ptr = png_create_info_struct (png_ptr);
				if (!info_ptr) {
					debug_print ("file \"" << filename << "\" is not a valid png file");
					png_destroy_read_struct (&png_ptr, (png_infopp)NULL, (png_infopp)NULL);
					fclose (fp);
					return false;
				}

				// create png info struct
				png_infop end_info = png_create_info_struct (png_ptr);
				if (!end_info) {
					debug_print ("file \"" << filename << "\" is not a valid png file");
					png_destroy_read_struct (&png_ptr, &info_ptr, (png_infopp)NULL);
					fclose (fp);
					return false;
				}

				// the code in this if statement gets called if libpng encounters an error
				if (setjmp (png_jmpbuf (png_ptr))) {
					debug_print ("file \"" << filename << "\" failed to load");
					png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
					fclose (fp);
					return false;
				}

				// init png reading
				png_init_io (png_ptr, fp);

				// let libpng know you already read the first 8 bytes
				png_set_sig_bytes (png_ptr, 8);

				// read all the info up to the image data
				png_read_info (png_ptr, info_ptr);

				// variables to pass to get info
				int bit_depth, color_type;

				// get info about png
				png_get_IHDR (png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
								NULL, NULL, NULL);

				if (bit_depth != 8) {
					debug_print ("file \"" << filename << "\" is of an unsupported bit depth");
					png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
					fclose (fp);
					return false;
				}

				switch (color_type) {
				case PNG_COLOR_TYPE_RGB:
					format = texture_format_rgb;
					break;
				case PNG_COLOR_TYPE_RGB_ALPHA:
					format = texture_format_rgba;
					break;
				default:
					debug_print ("file \"" << filename << "\" is of an usupported color type");
					png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
					fclose (fp);
					return false;
				}

				// Update the png info struct.
				png_read_update_info (png_ptr, info_ptr);

				// Row size in bytes.
				int rowbytes = png_get_rowbytes (png_ptr, info_ptr);

				// glTexImage2d requires rows to be 4-byte aligned
				rowbytes += 3 - ((rowbytes - 1) % 4);

				// Allocate the image_data as a big block, to be given to opengl
				data = (char *)malloc (rowbytes * height * sizeof(png_byte)+15);
				if (data == NULL) {
					debug_print ("failed to allocate memory for png image");
					png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
					fclose (fp);
					return false;
				}


				// row_pointers is for pointing to image_data for reading the png with libpng
				png_byte ** row_pointers = (png_byte **)malloc (height * sizeof(png_byte *));
				if (row_pointers == NULL) {
					debug_print ("failed to allocate memory for png row pointers");
					png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
					free (data);
					fclose (fp);
					return false;
				}

				// set the individual row_pointers to point at the correct offsets of image_data
				for (unsigned int i = 0; i < height; i++) {
					row_pointers [height - 1 - i] = (png_byte*)data + i * rowbytes;
				}

				// read the png into image_data through row_pointers
				png_read_image (png_ptr, row_pointers);

				// clean up
				png_destroy_read_struct (&png_ptr, &info_ptr, &end_info);
				free (row_pointers);
				fclose (fp);

				return true;
			}


			texture_package_reader::texture_package_reader (idevice * device) : _device (device) {}

			const char * texture_package_reader::type () const {
				return "texture";
			}

			void texture_package_reader::load_element (const tinyxml2::XMLElement * element, resource_container & container) {

				const char * name = element->Attribute ("name");
				
				itexture * texture = _device->create_texture (text_to_id (name));
			
				texture_filter
					mag_filter = texture_filter_nearest,
					min_filter = texture_filter_nearest;

				texture_wrap
					wrap_s = texture_wrap_clamp_to_border,
					wrap_t = texture_wrap_clamp_to_border;

				const char * file = nullptr;

				auto * cursor = element->FirstAttribute ();
				
				while (cursor) {
				
					if (strcmp (cursor->Name (), "wrap_s") == 0)
						wrap_s = text_to_wrap (cursor->Value ());
					else if (strcmp (cursor->Name (), "wrap_t") == 0)
						wrap_t = text_to_wrap (cursor->Value ());
					else if (strcmp (cursor->Name (), "mag_filter") == 0)
						mag_filter = text_to_filter (cursor->Value ());
					else if (strcmp (cursor->Name (), "min_filter") == 0)
						min_filter = text_to_filter (cursor->Value ());
					else if (strcmp (cursor->Name (), "file") == 0)
						file = cursor->Value ();
					else if (strcmp (cursor->Name (), "name")) {
						debug_print ("unexpected texture property \"" << cursor->Name () << "\". value ignored.");
					}
				
					cursor = cursor->Next ();
				}

				char * data = nullptr;
				uint32_t width, height;
				texture_format format;

				if (load_file (file, data, format, width, height)) {
					texture->set_data (
						data,
						width,
						height,
						format,
						wrap_s,
						wrap_t,
						mag_filter,
						min_filter
						);

					free (data);
					container.add_to_level (texture);
				} else {
					debug_print ("texture \"" << file << "\" failed to load");
				}
			}

		}
	}
}