#ifndef LIBRARY_H_
#define LIBRARY_H_

#include <cstdlib>

#ifdef _WIN32
#include <string>
#include <windows.h>
#else
#include <string.h>
#endif
#include "database.h"

class Library {
private:
	std::string _libPath;
	int _libVersion;

public:
	typedef bool(*handle)(_database*);
#ifdef _WIN32
	HMODULE _module;
#else
	void *_module;
#endif

public:
	Library();
	Library(const std::string filePath, std::string version = "0");
	virtual ~Library();
	/**
	*@brief load library
	*/
	bool load(std::string libFilePath);

	/**
	*@brief get symbol form library
	*/
	handle getSymbol(const std::string symbolName);

private:
	/**
	*@brief release library
	*/
	void releaseLibrary();
};

#endif /* LIBRARY_H_ */