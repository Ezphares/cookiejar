#include "glgraphicscontroller.h"

namespace cookiejar
{
	GLGraphicsController::GLGraphicsController() :
		_window (NULL),
		_program_sprite(NULL),
		_uniform_sprite(),
		_vbo_unit(NULL),
		_vao_sprite(NULL) { }

	GLGraphicsController::~GLGraphicsController()
	{
		destroy_buffers();
		destroy_shaders();
	}

	void GLGraphicsController::initialize()
	{
		//TODO Stub
	}

	void GLGraphicsController::post_window_setup(GLFWwindow *window, Point<uint32_t> resolution)
	{
		_window = window;

		// Set up glew for the new window
		//glewExperimental = TRUE;
		if (glewInit() != GLEW_OK)
		{
			throw 3; //TODO GraphicsException
		}

		// Enable blending
		glEnablei(GL_BLEND, 0);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		// Create shader programs and buffers
		create_shaders();
		create_buffers();

		// Set constant uniforms according to new settings
		_program_sprite->activate();
		_uniform_sprite = UniformGeneric::create_from_program(_program_sprite);
		glUniform2f(_program_sprite->get_uniform_location("u_resolution"), (GLfloat)resolution.x, (GLfloat)resolution.y);
		glUniform1i(_program_sprite->get_uniform_location("u_texture"), 0);
	}

	void GLGraphicsController::draw_start()
	{
		if (_window)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			_program_sprite->activate();
			_vao_sprite->bind();
		}
	}

	void GLGraphicsController::draw_end()
	{
		if (_window)
		{
			glfwSwapBuffers(_window);
			glfwPollEvents();
		}
	}

	void GLGraphicsController::draw_textured_rectangle(Point<float> offset, Point<float> size, Point<float> texoffset, Point<float> texsize)
	{
		// TODO: Call glUseProgram here? May need that for primitives later.
		glUniform2f(_uniform_sprite.offset, offset.x, offset.y);
		glUniform2f(_uniform_sprite.size, size.x, size.y);
		glUniform2f(_uniform_sprite.texoffset, texoffset.x, texoffset.y);
		glUniform2f(_uniform_sprite.texsize, texsize.x, texsize.y);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	void GLGraphicsController::create_shaders()
	{
		destroy_shaders();

		_program_sprite = new GLShaderProgram("vsprite.glsl", "fsprite.glsl");
		if (!_program_sprite->is_valid())
		{
			throw 4; //TODO: GraphicsException
		}
	}

	void GLGraphicsController::destroy_shaders()
	{
		delete _program_sprite;
	}

	void GLGraphicsController::create_buffers()
	{
		destroy_buffers();

		GLfloat unit[] =
		{
			// Tirangle A
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			// Triangle B
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		_vbo_unit = new GLBuffer(unit, 12);
		_vao_sprite = new GLVertexArray();
		_vao_sprite->add_buffer(_vbo_unit, _program_sprite->get_attribute_location("i_vertex_position"));
	}

	void GLGraphicsController::destroy_buffers()
	{
		delete _vao_sprite;
		delete _vbo_unit;
	}
}
