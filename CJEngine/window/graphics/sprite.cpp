#include "sprite.h"

namespace cookiejar
{
	Sprite::Sprite(Texture *texture, int32_t frames, int32_t frames_per_row, Point<int32_t> frame_size, Point<int32_t> frame_offset, Point<int32_t> draw_offset) :
		_texture(texture),
		_frames(frames),
		_draw_offset(draw_offset)
	{
		auto texi = texture->get_size();
		Vector2 texf = point_cast<BasePrecision>(texi);

		_framesize = point_cast<BasePrecision>(frame_size);
		// Size of a frame in texture coordinates
		_texsize = _framesize / texf;

		Vector2 frameoffset = point_cast<BasePrecision>(frame_offset);
		_frame_texoffsets = new Point<BasePrecision>[frames];
		for (int32_t i = 0; i < frames; i++)
		{
			float x = (float)(i % frames_per_row);
			float y = (float)(i / frames_per_row);

			_frame_texoffsets[i] = Vector2{ frameoffset.x + _texsize.x * x, frameoffset.y + _texsize.y * y };
		}
	}

	Vector2 Sprite::get_size() const
	{
		return _texsize;
	}

	Vector2 Sprite::get_framesize() const
	{
		return _framesize;
	}

	Vector2 Sprite::get_offset(int frame) const
	{
		return _frame_texoffsets[frame % _frames];
	}

	Point<int32_t> Sprite::get_draw_offset() const
	{
		return _draw_offset;
	}

	Texture *Sprite::get_texture() const
	{
		return _texture;
	}

	int Sprite::get_frames() const
	{
		return _frames;
	}

	Sprite::~Sprite()
	{
		delete[] _frame_texoffsets;
	}
}
