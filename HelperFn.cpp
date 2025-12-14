#include <cctype> 
#include "HelperFn.h"


bool IsValue(string input)
{
	// checks if the input string is a double value
	// return true if it's double value, false otherwise
	// Double values can be: 12.5, -12.5, -23, -23. , -23.0  etc.


	if (input.length() == 0) //Check if the input string is empty
		return false;

	int decimalPointCounter = 0;
	bool digitIsFounded = false;
	int i = 0;


	if (input[i] == '+' || input[i] == '-')
		i++; //to skip the first character if it is a sign in the loop on the string and start from digits

	while (i < input.length()) {

		char c = input[i]; //easly access to avoid writing [] in every loop and condition 

		if (isdigit(c))
			digitIsFounded = true;

		else if (c == '.') {
			decimalPointCounter++;

			if (decimalPointCounter > 1) // of course there is one or no '.' in a decimal number
				return false;
		}

		else         //if another character which is not in {digit,+,-} like '&' for example then false input
			return false;

		i++; //go to the next index

	}

	return digitIsFounded;
	/*if all conditions comes true (one decimal point), (no another special characters) and there is one digit at least
	then this will be true else this input is false and cannot be used*/

}

bool IsVariable(string input)
{
	// checks if the input string is a variable name
	// return true if it can be a variable name, false otherwise
	// Variable names must start with an alphabetic letter (small or capital) or an underscore (_). 
	// After the first initial letter, variable names can contain letters, numbers and underscores.  
	// No spaces or special characters, however, are allowed.

	string* cppKeywords = new string[95] //c++ keywords which cannot be used as a variable name
	{
		"alignas", "alignof", "and", "and_eq", "asm", "auto",
		"bitand", "bitor", "bool", "break",
		"case", "catch", "char", "char8_t", "char16_t", "char32_t",
		"class", "compl", "concept", "const", "consteval", "constexpr",
		"const_cast", "continue", "co_await", "co_return", "co_yield",
		"decltype", "default", "delete", "do", "double", "dynamic_cast",
		"else", "enum", "explicit", "export", "extern",
		"false", "float", "for", "friend",
		"goto", "if", "inline", "int", "long",
		"mutable", "namespace", "new", "noexcept", "not", "not_eq", "nullptr",
		"operator", "or", "or_eq", "private", "protected", "public",
		"register", "reinterpret_cast", "requires", "return",
		"short", "signed", "sizeof", "static", "static_assert", "static_cast",
		"struct", "switch", "template", "this", "thread_local", "throw",
		"true", "try", "typedef", "typeid", "typename",
		"union", "unsigned", "using",
		"virtual", "void", "volatile",
		"wchar_t", "while", "xor", "xor_eq"
	};


	if (input.size() == 0)
		return false;

	for (int i = 0; i < 95; i++)
	{
		if (cppKeywords[i] == (input))
			return false;
	}
	int i = 0;

	if (input[0] == '_' || isalpha(input[0]))  //first index must be only underscore or an alphabetic letter.
		i++;

	else  return false;


	while (i < input.size()) {
		char c = input[i]; //easly access to avoid writing [] in every loop and condition .

		if (c == '_' || isalpha(c) || isdigit(c)); //only contains underscores numbers and alphabetic letters.
		else return false;
		i++;
	}
	delete[]  cppKeywords;
	return true;
}

OpType ValueOrVariable(string input)
{
	// checks if the input string is a double value or a variable name
	// chand returns enum "OpType" (the enum is declared in the .h)


	if (IsVariable(input))		return VARIABLE_OP;
	else if (IsValue(input))        return VALUE_OP;
	return INVALID_OP;
}

string OpToString(const string& op)
{
	if (op == "==")
		return "EQL";
	else if (op == "!=")
		return "NOTEQL";
	else if (op == ">")
		return "GRT";
	else if (op == "<")
		return "LSS";
	else if (op == ">=")
		return "GRTEQL";
	else if (op == "<=")
		return "LSSEQL";
	else
		return op; // Return as-is if not recognized
}

string StringToOp(const string& opStr)
{
	if (opStr == "EQL")
		return "==";
	else if (opStr == "NOTEQL")
		return "!=";
	else if (opStr == "GRT")
		return ">";
	else if (opStr == "LSS")
		return "<";
	else if (opStr == "GRTEQL")
		return ">=";
	else if (opStr == "LSSEQL")
		return "<=";
	else
		return opStr; // Return as-is if not recognized
}