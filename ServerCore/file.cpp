#include "file.h"

File::File(std::string _filename):filename(_filename)
{
	log::print(log::Debug, "New File: " + filename);
}

File::~File()
{
	if (!in)
		in.close();
	if (!out)
		out.close();
}

const std::string File::read()
{
	log::print(log::Debug, "Read File: " + filename);
	in.open(filename,std::ios::in);
	if (!in) { 
		log::print(log::Error, "Can't open file: " + filename);
		return std::string();
	}
	std::string str((std::istreambuf_iterator<char>(in)),std::istreambuf_iterator<char>());
	in.close();	
	return str;
}

bool File::write(const std::string &_str)
{
	log::print(log::Debug, "Write File: " + filename);
	out.open(filename,std::ios::out|std::ios::trunc);
	if (!out) {
		log::print(log::Error, "Can't open file: " + filename);
		return false;
	}
	out << _str;
	out.close();
	return false;
}
