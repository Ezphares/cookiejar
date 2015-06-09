#pragma once

#include "glbuffer.h"

namespace cookiejar
{

	class GLVertexArray
	{
	public:
		GLVertexArray();
		~GLVertexArray();

	public:
		void add_buffer(GLBuffer *buffer, GLuint layout);
		void bind();

	private:
		GLuint _index;
	};
}
