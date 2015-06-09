#include "gltexture.h"

#include <cstdio>

namespace cookiejar
{
	GLTexture::GLTexture(std::string filename, FileType type) :
		_index(0), _width(0), _height(0)
	{
		switch (type)
		{
		case cookiejar::GLTexture::FT_RAW:
			throw 10; //TODO: Implement RAW textures
			break;
		case cookiejar::GLTexture::FT_PNG:
			load_png(filename);
			break;
		default:
			break;
		}

		//process_texture();
	}

	GLTexture::~GLTexture()
	{
		if (_index)
		{
			glDeleteTextures(1, &_index);
		}
	}

	void GLTexture::bind()
	{
		if (_index)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _index);
		}
		else
		{
			throw 1; //TODO: GraphicsException
		}
	}

	void GLTexture::load_png(std::string filename)
	{
		FILE *fp;
		fp = fopen(filename.c_str(), "rb");
		if (!fp)
		{
			throw 1; //TODO: GraphicsException
		}

		png_byte header[8];
		fread(header, 1, 8, fp);

		if (png_sig_cmp(header, 0, 8))
		{
			//set_error(CJ_TEXTURE_ERROR, "Texture type mismatch"); // TODO: str format filename
			throw 1; //TODO: GraphicsException
		}

		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png)
		{
			//set_error(CJ_TEXTURE_ERROR, "Texture load error"); // TODO: str format filename
			throw 1; //TODO: GraphicsException
		}

		png_infop png_info = png_create_info_struct(png);
		if (!png_info)
		{
			png_destroy_read_struct(&png, NULL, NULL);
			//set_error(CJ_TEXTURE_ERROR, "Texture load error"); // TODO: str format filename
			throw 1; //TODO: GraphicsException
		}

		png_infop png_end = png_create_info_struct(png);
		if (!png_end)
		{
			png_destroy_read_struct(&png, &png_info, NULL);
			//set_error(CJ_TEXTURE_ERROR, "Texture load error"); // TODO: str format filename
			throw 1; //TODO: GraphicsException
		}

		if (setjmp(png_jmpbuf(png)))
		{
			png_destroy_read_struct(&png, &png_info, &png_end);
			//set_error(CJ_TEXTURE_ERROR, "Texture load error"); // TODO: str format filename
			throw 1; //TODO: GraphicsException
		}

		png_init_io(png, fp);
		png_set_sig_bytes(png, 8);
		png_read_info(png, png_info);

		int bit_depth, color_type;
		png_uint_32 w, h;

		png_get_IHDR(png, png_info, &w, &h, &bit_depth, &color_type, NULL, NULL, NULL);
		_width = (int)w;
		_height = (int)h;
		png_read_update_info(png, png_info);

		std::cout << std::endl;

		int rowbytes = (int)png_get_rowbytes(png, png_info);

		png_byte *idata = new png_byte[rowbytes * h];
		png_bytep *rowpointers = new png_bytep[h];

		for (unsigned int i = 0; i < h; ++i)
			rowpointers[h - 1 - i] = idata + i * rowbytes;


		png_read_image(png, rowpointers);

		glGenTextures(1, &_index);
		try
		{
			bind();
		}
		catch (int) //TODO: GraphicsException
		{
			png_destroy_read_struct(&png, &png_info, &png_end);
			//set_error(CJ_TEXTURE_ERROR, "Texture load error"); // TODO: str format filename
			delete[] idata;
			delete[] rowpointers;
			throw 1; //TODO: GraphicsException
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)idata);
		process_texture();

		png_destroy_read_struct(&png, &png_info, &png_end);
		delete[] idata;
		delete[] rowpointers;
		std::fclose(fp);
	}

	Point<int32_t> GLTexture::get_size() const
	{
		Point<int32_t> p = { _width, _height };
		return p;
	}

	void GLTexture::process_texture()
	{
		if (!_index)
		{
			throw 1; //TODO: GraphicsException
		}

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
}
