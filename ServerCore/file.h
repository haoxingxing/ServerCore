#ifndef FILE_H
#define FILE_H
#include <string>
#include <fstream>

class file
{
public:
	// Open File to read and write
	file(std::string filename);
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
