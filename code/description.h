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
		//constructor
		description();
		//template filler functions
		string fillLife(string str); // early life
		string fillCharacteristics(string str); // description
};