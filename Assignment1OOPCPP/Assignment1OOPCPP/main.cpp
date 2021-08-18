#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"

//Mark Joyce 2019 SID: 10421019

using namespace std;

int main()
{
	//constructor
	Dictionary myDict("dictionary.txt"); 
	
	myDict.run(); // Run the Dictionary application.

	return 0;
}