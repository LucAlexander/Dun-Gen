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
item::item(string n, int d, int r){
	name = n;
	damage = d;
	reliability = r;
	//deal with special
}
//functions
string item::itemName(){
	//reading through the file goes here
	string name = "The" + randomAdjective() + randomNoun();
	//function to generate name goes here
	return name;
}
