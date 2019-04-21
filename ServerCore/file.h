#ifndef FILE_H
#define FILE_H
#include <string>
#include <fstream>
#include "log.h"
class file
#ifdef UsingMemoryLeakCheck
	: MemoryLeak_Probe
#endif
{
public:
	// Open File to read and write
	explicit file(std::string filename);
	~file();
	// Read the whole file
	const std::string read();
	// Overwrite the file
	bool write(const std::string& _str);
private:
	std::ifstream in;
	std::ofstream out;
	std::string filename;
};
#endif
