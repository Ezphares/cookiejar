#version 400

in vec2 i_vertex_position;

uniform vec2 u_resolution;

uniform vec2 u_size;
uniform vec2 u_offset;

uniform vec2 u_texsize;
uniform vec2 u_texoffset;

out vec2 texture_coordinate;

vec2 pixel_to_gl(vec2 point)
{
	return ((point / u_resolution * 2.0) - 1.0) * vec2(1.0, -1.0);
}

void main()
{
	vec2 point = u_offset + (u_size * i_vertex_position);

	texture_coordinate = u_texoffset + (u_texsize * i_vertex_position * vec2(1.0, -1.0));

	gl_Position = vec4(pixel_to_gl(point), 0.0, 1.0);
}
