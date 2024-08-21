#include <iostream>
#include <string>
#include "clsString.h"  
#pragma region usings
using std::endl;
using std::cout;
using std::cin;
using std::string;

using clsString::opContainsBy;
#pragma endregion

int main(int argc, char *argv[]) {
	string varStr = "merequetengue";
	string varParttern = "que";

	cout
		<< varStr << " contains "
		<< varParttern << "? :"
		<< (opContainsBy(varStr, varParttern,0 ,0) ? " yes" : " no")
		<< endl;
	return 0;
}