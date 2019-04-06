#pragma once
/*
	This file contains some public defines
 */
#include "log.h"
#define data_file "data"
 // convert pointer to printable
#define print_pointer(ptr) std::string("["+std::to_string((long long)ptr)+"]")

// debug
#define DEB(info) log::print(log::Debug,"["+std::string(__FUNCTION__)+"]"+info)

 //log macro
#define LOG(info) log::print(log::Info,"["+std::string(__FUNCTION__)+"]"+info)

// success
#define SUCC(info) log::print(log::Success,"["+std::string(__FUNCTION__)+"]" + info)

// error
#define ERR(info) log::print(log::Error,"["+std::string(__FUNCTION__)+"]"+info)

// warning
#define WARN(info) log::print(log::Warning,"["+std::string(__FUNCTION__)+"]"+info)