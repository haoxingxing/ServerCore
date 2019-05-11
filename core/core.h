#pragma once

/*
 *	This file contains some public defines
 */
#include "../global.h"
#include "log.h"
#include "translates_CN.h"
 /*
  * convert pointer to std::string
  *  ptr -> long long -> std::string
  */
#define PRINT_POINTER(ptr) std::string("["+std::to_string((long long)(ptr))+"]")

  /*
   * Print Debug Information
   * Level: Debug
   * With __FUNCTION__
   */
#ifdef DEBUG
#define DEB(info) log::print(log::Debug,"["+std::string(__FUNCTION__)+"]"+info)
#else
#define DEB(info)
#endif
   /*
	* Print Notice Information
	* Level: Info
	* With __FUNCTION__
	*/
#define LOG(info) log::print(log::Info,"["+std::string(__FUNCTION__)+"]"+(info))

	// error
#define ERR(info) log::print(log::Error,"["+std::string(__FUNCTION__)+"]"+(info))

// warning
#define WARN(info) log::print(log::Warning,"["+std::string(__FUNCTION__)+"]"+(info))

/*
 * Exit The Program With Error Info
 * 1. print Error Info
 * 2. exit
 */
#define EXIT_ERR(info) ERR(info);exit(EXIT_FAILURE)
