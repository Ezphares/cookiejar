#pragma once

#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <string>

namespace cookiejar
{
	class GLShaderProgram
	{
	public:
		GLShaderProgram(const std::string &vertex_file, const std::string &fragment_file);
		~GLShaderProgram();

	public:
		bool is_valid();
		void activate();
		GLuint get_attribute_location(const std::string &name);
		GLuint get_uniform_location(const std::string &name);

	private:
		GLuint compile_shader(const std::string &source, GLenum type);
		GLuint link_program();

	private:
		GLuint _program, _vertex, _fragment;
		bool _valid;
	};
}
