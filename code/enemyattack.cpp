#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "enemyattack.h"
#include "general.h"
using namespace std;
//constructor
enemyAttack::enemyAttack() {
	damage = ((rand() % 5) + 1);
	reliability = ((rand() % 8) + 3);
	name = randomName();
}
string enemyAttack::randomName() {
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
