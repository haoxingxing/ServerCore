#include "libraryloader.h"
#include <iostream>
#include <sys/stat.h>

using namespace std;

bool  fileIsExist(std::string &libFilePath)
{
	struct stat statbuf;
	return stat(libFilePath.c_str(), &statbuf) == 0;
}

Library::Library()
	:_libPath(""),
	_libVersion(0),
	_module(NULL)
{
}

Library::Library(const std::string filePath, std::string version)
	:_libPath(""),
	_libVersion(0),
	_module(NULL)
{
	if (!load(filePath))
	{
		std::cout << "Load library failed !" << std::endl;
	}
}
Library::~Library()
{
	releaseLibrary();
}

bool Library::load(std::string libFilePath)
{
	if (_module != NULL)
	{
		std::cout << "The library has loaded !" << std::endl;
		return false;
	}

	if (!fileIsExist(libFilePath))
	{
		std::cout << "The library is not exist!" << std::endl;
	}
#ifdef _WIN32
	_module = LoadLibrary(libFilePath.data());
	if (_module == nullptr)
	{
		std::cout << GetLastError() << std::endl;
	}
#else
	_module = dlopen(libFilePath.c_str(), RTLD_NOW | RTLD_GLOBAL);
	if (_module == nullptr)
	{
		std::cout << strerror(errno) << std::endl;
	}
#endif
	return _module != nullptr;
}

Library::handle Library::getSymbol(const string symbolName)
{
	if (_module == nullptr)
	{
		std::cout << "The library has not loaded !" << std::endl;
	}
#ifdef _WIN32
	return (handle)GetProcAddress(_module, symbolName.c_str());
#else
	return (handle)dlsym(_module, symbolName.c_str());
#endif
}

void Library::releaseLibrary()
{
	if (_module)
	{
#ifdef _WIN32
		FreeLibrary(_module);
#else
		_module = nullptr;
		_libPath = "";
#endif
	}
}