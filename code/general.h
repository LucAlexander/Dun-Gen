#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class general {
	public:
		int findLength(const char* file);
		string randomSyllableName();
		string pullRandom(const char* file);
		void parse(vector<string> * arr, const char* file);
};
