#ifndef GLOBAL_H
#define GLOBAL_H   
/*
	* The Marco is used to switch string
	* Example:
	*	SWITCH_BEGIN(str)
	*	SWITCH_CASE("void")
	*	{
	*		do_something();
	*	}
	*	SWITCH_CASE("int")
	*	{
	*		do_something();
	*	}
	*	SWITCH_DEFAULT
	*	{
	*		do_something();
	*	}
	*	SWITCH_END
	* Using If Else Statement
*/
#define SWITCH_BEGIN(str) {\
const std::string &SWITCH_KEY=str;\
if(false);
	/*
	 * See Detail in SWITCH_BEGIN
	 */
#define SWITCH_CASE(str) else if (SWITCH_KEY==(str))
	 /*
	  * See Detail in SWITCH_BEGIN
	  */
#define SWITCH_END \
}
	  /*
	   * See Detail in SWITCH_BEGIN
	   */
#define SWITCH_DEFAULT else
#endif // GLOBAL_H
