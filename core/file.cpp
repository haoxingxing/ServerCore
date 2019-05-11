#include "file.h"
#include <iostream>
#include "log.h"
#include "core.h"
#include <cstdio>
#include <utility>

file::file(std::string _filename) : filename(std::move(_filename))
{
	DEB(print_pointer(this));
}

file::~file()
{
	try {
		if (!in)
			in.close();
		if (!out)
			out.close();
	}
	catch (...)
	{
	}
	DEB(print_pointer(this));
}

std::string file::read()
{
	DEB(filename);
	in.open(filename, std::ios::in);
	if (!in)
	{
		ERR(TS_ID_12 ": " + filename);
		return std::string();
	}
	std::string str((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
	in.close();
	return str;
}

bool file::write(const std::string & _str)
{
	DEB(filename);
	out.open(filename, std::ios::out | std::ios::trunc);
	if (!out)
	{
		ERR(TS_ID_12 ": " + filename);
		return false;
	}
	out << _str;
	out.close();
	return false;
}