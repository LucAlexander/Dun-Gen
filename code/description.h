#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class description {
public:
	string earlyLife;
	string characteristics;
	string qualities;
	string name;
	string playerName;
	//constructor
	description();
	description(string pn);
	description(string n, string pn);
	//template filler function
	string replaceCharCode(string desc, const string code, const char* dir);
	string fillTemplate(const char*  directory);
	string addLineBreaks(string desc, int delim);
};
