#pragma once

#include <string>

namespace cookiejar
{

	class FileReader
	{
	public:
		FileReader(std::string filename, bool binary = false);
		~FileReader();

	public:
		bool can_read();
		std::string read_string();

	private:
		std::string _data, _filename;
		bool _read, _binary;
	};
}
