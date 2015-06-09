#include "glshaderprogram.h"

#include <io\filereader.h>

namespace cookiejar
{
	GLShaderProgram::GLShaderProgram(const std::string &vertex_file, const std::string &fragment_file) : _program(0), _vertex(0), _fragment(0), _valid(false)
	{
		_valid = true;

		FileReader v(vertex_file), f(fragment_file);

		_vertex = compile_shader(v.read_string(), GL_VERTEX_SHADER);
		_fragment = compile_shader(f.read_string(), GL_FRAGMENT_SHADER);
		if (is_valid())
		{
			_program = link_program();
		}
	}

	GLShaderProgram::~GLShaderProgram()
	{

		glDeleteProgram(_program);
		glDeleteShader(_vertex);
		glDeleteShader(_fragment);
	}

	bool GLShaderProgram::is_valid()
	{
		return _valid;
	}

	void GLShaderProgram::activate()
	{
		if (is_valid())
		{
			glUseProgram(_program);
		}
		else
		{
			throw 1; // TODO GraphicsException
		}
	}

	GLuint GLShaderProgram::get_attribute_location(const std::string &name)
	{
		if (is_valid())
		{
			return glGetAttribLocation(_program, name.c_str());
		}
		else
		{
			throw 1; // TODO GraphicsException
		}
	}

	GLuint GLShaderProgram::get_uniform_location(const std::string &name)
	{
		if (is_valid())
		{
			auto val = glGetUniformLocation(_program, name.c_str());
			return val;
		}
		else
		{
			throw 1; // TODO GraphicsException
		}
	}

	GLuint GLShaderProgram::compile_shader(const std::string &source, GLenum type)
	{
		GLuint shader = glCreateShader(type);

		const char *csource = source.c_str();
		glShaderSource(shader, 1, &csource, NULL);
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		_valid = (status == GL_TRUE);

		return shader;
	}

	GLuint GLShaderProgram::link_program()
	{
		GLuint program = glCreateProgram();
		glAttachShader(program, _vertex);
		glAttachShader(program, _fragment);
		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		_valid = (status == GL_TRUE);

		return program;
	}
}
