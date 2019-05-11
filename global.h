#pragma once
//#define DEBUG
#define UsingMemoryLeakCheck

/*
 * The Marco is used to switch string
 * Example:
 *	std::string str = "void";
 *	SWITCH_BEGIN(str)
 *	SWITCH_CASE("void")
 *	{
 *		<---- The Process Stream will goto here
 *	}
 *	SWITCH_END
 * By If Else Statement
 */
#define SWITCH_BEGIN(str) {\
const std::string &SWITCH_KEY=str;\
if(false);
#define SWITCH_CASE(str) else if (SWITCH_KEY==str)
#define SWITCH_END \
}
#define SWITCH_DEFAULT else