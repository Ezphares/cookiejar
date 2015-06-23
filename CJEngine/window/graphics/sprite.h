#pragma once

#include <foundation\vector.h>
#include "gltexture.h"

namespace cookiejar
{
#ifdef USE_GL_RENDERER
	typedef GLTexture Texture;
#endif
	class Sprite
	{
	public:
		Sprite(Texture *texture, int32_t frames, int32_t frames_per_row, Point<int32_t> frame_size, Point<int32_t> frame_offset, Point<int32_t> draw_offset);
		virtual ~Sprite();

	public:
		Vector2 get_size() const;
		Vector2 get_offset(int frame) const;
		Vector2 get_framesize() const;
		Point<int32_t> get_draw_offset() const;
		Texture *get_texture() const;
		int get_frames() const;

	private:
		Texture *_texture;
		int _frames;
		Vector2 _texsize;
		Vector2 _framesize;
		Vector2 *_frame_texoffsets;
		Point<int32_t> _draw_offset;
	};
}
