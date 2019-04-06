#ifndef FILE_H
#define FILE_H
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "log.h"
#include "ServerCore.h"
class File {
public:
	// Open File to read and write
	File(std::string filename);
	~File();
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
