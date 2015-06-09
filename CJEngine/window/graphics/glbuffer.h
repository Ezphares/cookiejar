#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include <stdint.h>

namespace cookiejar
{
	class GLBuffer
	{
	public:
		GLBuffer(GLfloat *data, uint32_t size, GLuint dimensions = 2, GLuint gltype = GL_FLOAT);
		~GLBuffer();

	public:
		void set_data(GLfloat *data, uint32_t size);
		void bind();
		GLuint get_dimensions() const;
		GLuint get_gltype() const;

	private:
		GLuint _index, _dimensions, _gltype;
	};
}
