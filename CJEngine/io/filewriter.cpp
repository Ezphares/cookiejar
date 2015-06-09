#include "filewriter.h"

namespace cookiejar
{

	FileWriter::FileWriter(std::string filename, Existing existing, bool binary) :
		_filename(filename), _existing(existing), _open(false), _binary(binary), _fstream()
	{ }

	FileWriter::~FileWriter() { }

	bool FileWriter::can_write()
	{
		if (!_open)
		{
			//TODO Handle existing files if BLOCK is set
			std::ios_base::openmode mode = std::ios::out;
			if (_binary)
			{
				mode |= std::ios::binary;
			}

			if (_existing == OVERWRITE)
			{
				mode |= std::ios::trunc;
			}
			else if (_existing == APPEND)
			{
				mode |= std::ios::app | std::ios::ate;
			}

			_fstream.open(_filename, mode);
			_open = _fstream.is_open();
		}

		return _open;
	}

	void FileWriter::write(std::string str)
	{
		if (can_write())
		{
			_fstream << str;
		}
		else
		{
			throw 1; //TODO: IOException
		}
	}
}
