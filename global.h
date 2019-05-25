#pragma once
/*
 * Output very very verbose log information
 */
#define DEBUG
 /*
  * Use Memory Leak Check
  * Causes Performance loss
  */
#define UsingMemoryLeakCheck

  /*
   * The Marco is used to switch string
   * Example:
   *	SWITCH_BEGIN(str)
   *	SWITCH_CASE("void")
   *	{
   *		<---- The Process Stream will goto here if str=="void"
   *	}
   *	SWITCH_CASE("int")
   *	{
   *		<---- The Process Stream will goto here if str=="int"
   *	}
   *	SWITCH_DEFAULT
   *	{
   *		<---- The Process Stream will goto here if str doesn't equal "void" or "int"
   *	}
   *	SWITCH_END
   * By If Else Statement
   */
#define SWITCH_BEGIN(str) {\
const std::string &SWITCH_KEY=str;\
if(false);
   /*
	* See Detail in SWITCH_BEGIN
	*/
#define SWITCH_CASE(str) else if (SWITCH_KEY==str)
	/*
	 * See Detail in SWITCH_BEGIN
	 */
#define SWITCH_END \
}
	 /*
	  * See Detail in SWITCH_BEGIN
	  */
#define SWITCH_DEFAULT else