#pragma once
#include <string>

using std::string;

namespace clsString {

	bool opContainsBy(string prmStr, string prmPattern, size_t prmStrPost, size_t prmPatternPost)
	{
		if (prmStrPost >= prmStr.length() && prmPatternPost < prmPattern.length()) return false;
		if (prmPatternPost >= prmPattern.length()) return true;

		if (prmStr[prmStrPost] == prmPattern[prmPatternPost]) 
		{
			return opContainsBy(prmStr, prmPattern, prmStrPost + 1, prmPatternPost + 1);
		}
		else {
			return opContainsBy(prmStr, prmPattern, prmStrPost + 1, 0);
		}

		return false;
	}
}