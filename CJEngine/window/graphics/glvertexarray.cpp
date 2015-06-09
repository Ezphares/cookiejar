#include "glvertexarray.h"

namespace cookiejar
{
	GLVertexArray::GLVertexArray() : _index(0)
	{
		glGenVertexArrays(1, &_index);
	}

	GLVertexArray::~GLVertexArray()
	{
		glDeleteVertexArrays(1, &_index);
	}

	void GLVertexArray::bind()
	{
		glBindVertexArray(_index);
	}

	void GLVertexArray::add_buffer(GLBuffer *buffer, GLuint layout)
	{
		buffer->bind();
		this->bind();

		glEnableVertexAttribArray(layout);
		glVertexAttribPointer(layout, buffer->get_dimensions(), buffer->get_gltype(), GL_FALSE, 0, NULL);
	}
}
