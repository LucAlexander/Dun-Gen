#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class description{
	public: 
		string earlyLife;
		string characteristics;
		string qualities;
		string name;
		//constructor
		description(string name);
		//template filler functions
		string fillLife(string str); // early life
		string fillCharacteristics(string str); // description
};
