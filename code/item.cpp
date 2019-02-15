#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "item.h"
using namespace std;
//constructor
item::item(){
	name = itemName();
	damage = ((rand() % 5) + 1);
	reliability = ((rand() % 8)+3);
	//deal with special
}
//functions
string item::itemName(){
	//reading through the file goes here
	string name;
	//function to generate name goes here
	return name;
}