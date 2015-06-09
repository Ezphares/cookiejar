#include "glbuffer.h"

namespace cookiejar
{
	GLBuffer::GLBuffer(GLfloat *data, uint32_t size, GLuint dimensions, GLuint gltype) :
		_index(0), _dimensions(dimensions), _gltype(gltype)
	{
		glGenBuffers(1, &_index);
		set_data(data, size);
	}

	GLBuffer::~GLBuffer()
	{
		glDeleteBuffers(1, &_index);
	}

	void GLBuffer::set_data(GLfloat *data, uint32_t size)
	{
		this->bind();
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), data, GL_STATIC_DRAW);
	}

	void GLBuffer::bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _index);
	}

	GLuint GLBuffer::get_dimensions() const
	{
		return _dimensions;
	}

	GLuint GLBuffer::get_gltype() const
	{
		return _gltype;
	}
}
