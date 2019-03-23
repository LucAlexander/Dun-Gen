#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "general.h" 
#include "item.h"
using namespace std;
//constructor
item::item() {
	name = itemName();
	damage = ((rand() % 5) + 1);
	reliability = ((rand() % 8) + 3);
	special = 0;
}
item::item(string n, int d, int r) {
	name = n;
	damage = d;
	reliability = r;
	special = 0;
}
//functions
string item::itemName() {
	const char* dir1 = "./nouns.txt";
	const char* dir2 = "./participleAdjectives.txt";
	const char* dir4 = "./personalityAdjectives.txt";
	const char* dir3 = "./descriptionAdjectives.txt";
	general obj;
	string name;
	int choice = rand() % 3 + 1;
	switch (choice) {
		case 1:
			name = "The " + obj.pullRandom(dir2) + " " + obj.pullRandom(dir1);
		break;
		case 2:
			name = "The " + obj.pullRandom(dir3) + " " + obj.pullRandom(dir1);
		break;
		case 3:
			name = "The " + obj.pullRandom(dir4) + " " + obj.pullRandom(dir1);
		break;
		default:
			name = "The " + obj.pullRandom(dir4) + " " + obj.pullRandom(dir1);
		break;
	}
	return name;
}
