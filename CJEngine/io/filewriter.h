#pragma once

#include <string>
#include <fstream>

namespace cookiejar
{

	class FileWriter
	{
	public:
		enum Existing { BLOCK, APPEND, OVERWRITE };

	public:
		FileWriter(std::string filename, Existing existing = OVERWRITE, bool binary = false);
		~FileWriter();

	public:
		bool can_write();
		void write(std::string str);

	private:
		std::string _filename;
		Existing _existing;
		bool _open, _binary;
		std::ofstream _fstream;
	};

}
