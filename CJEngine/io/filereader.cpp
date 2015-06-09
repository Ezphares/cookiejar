#include "filereader.h"

#include <fstream>

namespace cookiejar
{
	FileReader::FileReader(std::string filename, bool binary) : _data(""), _filename(filename), _read(false), _binary(binary) {}
	FileReader::~FileReader() {}

	bool FileReader::can_read()
	{
		if (!_read)
		{
			std::ios_base::openmode mode = std::ios::in;
			mode |= std::ios::binary;


			std::ifstream fstream(_filename, mode);

			if (fstream.is_open())
			{

				fstream.seekg(0, std::ios::end);
				size_t size = fstream.tellg();
				char *buffer = new char[size + 1];
				fstream.seekg(0, std::ios::beg);

				fstream.read(buffer, size);
				buffer[size] = '\0';
				_data = std::string(buffer, size);
				_data.shrink_to_fit();

				fstream.close();
				delete[] buffer;
				_read = true;
			}
		}

		return _read;
	}

	std::string FileReader::read_string()
	{
		if (can_read())
		{
			return _data;
		}
		else
		{
			throw 1; //TODO: IOException
		}
	}
}
