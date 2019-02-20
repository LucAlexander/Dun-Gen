#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class general{
	public:
		int findLength(ifstream& file);
		string randomName();
		string randomVerb();
		string randomParticipleAdj();
		string randomDescriptionAdj();
		string randomPersonalityAdj();
		string randomAdjective();
		string randomNoun();
};
