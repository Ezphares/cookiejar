#pragma once

#include <GL\glew.h>
#include <png/png.h>
#include <iostream>
#include <stdint.h>

#include <foundation\vector.h>

namespace cookiejar
{
	class GLTexture
	{
	public:
		enum FileType { FT_RAW, FT_PNG };

	public:
		GLTexture(std::string filename, FileType type = FT_PNG);
		~GLTexture();

	public:
		void bind();
		Point<int32_t> get_gl_coordinates(Point<int32_t> &pixel_point) const; /* DEPRECATE*/
		Point<int32_t> get_size() const;

	private:
		void load_png(std::string filename);
		void process_texture();

	private:
		GLuint _index;
		int32_t _width, _height;
	};
}
