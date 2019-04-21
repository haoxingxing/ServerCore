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

#define _SWITCH_BEGIN(str) {\
std::string SWITCH_KEY=str;\
if(false);
#define _SWITCH_CASE(str) else if (SWITCH_KEY==str)
#define _SWITCH_END \
}
#define _SWITCH_DEFAULT else


