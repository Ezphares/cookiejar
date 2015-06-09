#version 400

in vec2 texture_coordinate;

uniform sampler2D u_texture;

out vec4 u_frag_color;

void main()
{
	vec4 color = texture2D(u_texture, texture_coordinate);
	
	u_frag_color = color;
}
