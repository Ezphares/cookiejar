#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "glshaderprogram.h"
#include "glvertexarray.h"
#include <foundation\vector.h>

namespace cookiejar
{
	typedef GLFWwindow WindowType;

	class GLGraphicsController
	{
	public:
		GLGraphicsController();
		~GLGraphicsController();

	public:
		void initialize();
		void post_window_setup(GLFWwindow *window, Point<uint32_t> resolution);

		void draw_start();
		void draw_end();

		void draw_textured_rectangle(Point<float> offset, Point<float> size, Point<float> texoffset, Point<float> texsize);

	private:
		void create_buffers();
		void destroy_buffers();
		void create_shaders();
		void destroy_shaders();

	private:
		struct UniformGeneric
		{
			GLuint offset, size, texoffset, texsize;

			static inline UniformGeneric create_from_program(GLShaderProgram *program)
			{
				UniformGeneric n = { program->get_uniform_location("u_offset"),
									 program->get_uniform_location("u_size"), 
									 program->get_uniform_location("u_texoffset"), 
									 program->get_uniform_location("u_texsize") };
				return n;
			}
		};

	private:
		GLFWwindow *_window;

		GLShaderProgram *_program_sprite;
		UniformGeneric _uniform_sprite;

		GLBuffer *_vbo_unit;
		GLVertexArray *_vao_sprite;
	};

}
