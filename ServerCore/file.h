#ifndef FILE_H
#define FILE_H
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include "log.h"
class File {
public:
	File(std::string filename);
	~File();
	const std::string read();
	bool write(const std::string& _str);
private:
	std::ifstream in;
	std::ofstream out;	
	std::string filename;	
};
#endif
