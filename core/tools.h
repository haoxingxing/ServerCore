#ifndef TOOLS_H
#define TOOLS_H
#include <string>
#include <utility>
#include <vector>
/* std::string operations */
namespace stropr
{
	/*
	 *Split string into vector
	 *Usage:
	 * auto buf = SplitString("A,B,C,D,EFG,H",",");
	 */
	std::vector<std::string> split_string(const std::string& source, const std::string& c);

	std::string ReplaceAll(std::string str, const std::string& from, const std::string& to);
	/*
	 * Separate a substr
	 */
	std::string dig(std::string& data, const char& start = '(', const char& end = ')');
	/*
	 * Merge substr
	 */
	std::vector<std::string> merge(const std::vector<std::string>&, const std::string& de);
	/*
	 * Clean string
	 */
	std::string clean_str(std::string raw);
	/*
	 * Find the index of first char not alphabet
	 */
	size_t find_not_alphabet(const std::string& raw);
	/*
	 * Find the index of first char is alphabet
	 */
	size_t find_alphabet(const std::string& raw);

	/*
	 * Find char in string without ""
	 */
	size_t find(const std::string& raw, char find);
	/*
	 * Find last char in string without ""
	 */
	size_t find_last(const std::string& raw, char find);
	/*
	 * Separate string without ""
	 */
	std::vector<std::string> split_to_two_part(const std::string& source, char c);
}
#endif // TOOLS_H
