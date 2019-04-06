#include "file.h"

File::File(std::string _filename) :filename(_filename)
{
	DEB(print_pointer(this));
}

File::~File()
{
	if (!in)
		in.close();
	if (!out)
		out.close();
	DEB(print_pointer(this));
}

const std::string File::read()
{
	LOG(filename);
	in.open(filename, std::ios::in);
	if (!in) {
		ERR("Can't open file: " + filename);
		return std::string();
	}
	std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();
	SUCC("");
	return str;
}

bool File::write(const std::string &_str)
{
	LOG(filename);
	out.open(filename, std::ios::out | std::ios::trunc);
	if (!out) {
		ERR("Can't open file: " + filename);
		return false;
	}
	out << _str;
	out.close();
	SUCC("");
	return false;
}