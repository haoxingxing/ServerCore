#pragma once
/*
 *	This file contains some public defines
 */
#include "log.h"
#include "translates_CN.h"
#define data_file "data"
/*
 * convert pointer to std::string
 *  ptr -> long long -> std::string
 */
#define print_pointer(ptr) std::string("["+std::to_string((long long)ptr)+"]")

/*
 * Print Debug Information
 * Level: Debug 
 * With __FUNCTION__
 */
#define DEB(info) log::print(log::Debug,"["+std::string(__FUNCTION__)+"]"+info)

/*
 * Print Notice Information
 * Level: Info
 * With __FUNCTION__
 */
#define LOG(info) log::print(log::Info,"["+std::string(__FUNCTION__)+"]"+info)

// success
#define SUCC(info) log::print(log::Debug,"["+std::string(__FUNCTION__)+"] " TS_ID_18 + info)

// error
#define ERR(info) log::print(log::Error,"["+std::string(__FUNCTION__)+"]"+info)

// warning
#define WARN(info) log::print(log::Warning,"["+std::string(__FUNCTION__)+"]"+info)

/*
 * Exit The Program With Error Info
 * 1. print Error Info
 * 2. exit
 */
#define EXIT_ERR(info) ERR(info);exit(EXIT_FAILURE)

typedef std::uint64_t hash_t;
constexpr hash_t prime = 0x100000001B3ull;
constexpr hash_t basis = 0xCBF29CE484222325ull;

hash_t hash_(char const* str);
constexpr hash_t hash_compile_time(char const* str, hash_t last_value = basis)
{
	return *str ? hash_compile_time(str + 1, (*str ^ last_value) * prime) : last_value;
}
constexpr hash_t operator "" _hash(char const* p, size_t)
{
	return hash_compile_time(p);
}