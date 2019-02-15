#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class item{
	public:
		string name;
		int damage;
		int reliability;
		int special;
		item();
		string itemName();
};