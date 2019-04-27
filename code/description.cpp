#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "description.h"
#include "general.h"
using namespace std;
//constructor
description::description() {
	name = "Gigabit";
	playerName = "James";
	earlyLife = fillTemplate("./earlyLife.txt");
	characteristics = fillTemplate("./characteristics.txt");
}
description::description(string pn) {
	name = "GigaBit";
	playerName = pn;
	earlyLife = fillTemplate("./earlyLife.txt");
	characteristics = fillTemplate("./characteristics.txt");
}
description::description(string n, string pn) {
	name = n;
	playerName = pn;
	earlyLife = fillTemplate("./earlyLife.txt");
	characteristics = fillTemplate("./characteristics.txt");
}
//functions
string description::replaceCharCode(string desc, const string code, const char* dir) {
	string temp;
	general obj;
	for (int i = 0; i < 5; i++) {
		while (desc.find(code) != string::npos)
		{
			const char* curdir = dir;
			temp = obj.pullRandom(curdir);
			desc.insert(desc.find(code) + 2, temp);
			desc.erase(desc.find(code), 2);
		}
	}
	return desc;
}
string description::fillTemplate(const char* direct) {
	string desc;
	string temp;
	general obj;
	// read in template
	desc = obj.pullRandom(direct);
	//special replacement cases
	while (desc.find("$M") != string::npos) // existing name
	{
		desc.insert(desc.find("$M") + 2, name);
		desc.erase(desc.find("$M"), 2);
	}
	while (desc.find("$N") != string::npos) // existing player name
	{
		desc.insert(desc.find("$N") + 2, playerName);
		desc.erase(desc.find("$N"), 2);
	}
	while (desc.find("%M") != string::npos) // filling random name(a new one)
	{
		temp = obj.randomSyllableName();
		desc.insert(desc.find("%M") + 2, temp);
		desc.erase(desc.find("%M"), 2);
	}
	while (desc.find("%A") != string::npos) // all adjectives
	{
		const char* dirs[] = { "./verb.txt", "./nouns", "./participleAdjectives.txt", "./descriptionAdjectives.txt", "./personalityAdjectives.txt" };
		int choice = rand() % 3 + 1;
		const char* dir = dirs[2];
		const char* dir1 = dirs[3];
		const char* dir2 = dirs[4];
		switch (choice) {
			case 1:
				temp = obj.pullRandom(dir);
				desc.insert(desc.find("%A") + 2, temp);
				desc.erase(desc.find("%A"), 2);
			break;
			case 2:
				temp = obj.pullRandom(dir1);
				desc.insert(desc.find("%A") + 2, temp);
				desc.erase(desc.find("%A"), 2);
			break;
			case 3:
				temp = obj.pullRandom(dir2);
				desc.insert(desc.find("%A") + 2, temp);
				desc.erase(desc.find("%A"), 2);
			break;
			default:
				temp = obj.pullRandom(dir2);
				desc.insert(desc.find("%A") + 2, temp);
				desc.erase(desc.find("%A"), 2);
			break;
		}
	}
	// standard character replacement cases
	desc = replaceCharCode(desc, "%O", "./nouns.txt");
	desc = replaceCharCode(desc, "%V", "./verb.txt");
	desc = replaceCharCode(desc, "%P", "./participleAdjectives.txt");
	desc = replaceCharCode(desc, "%D", "./descriptionAdjectives.txt");
	desc = replaceCharCode(desc, "%E", "./personalityAdjectives.txt");
	desc = replaceCharCode(desc, "%N", "./playerNames.txt");
	//remove # char in begining of template
	desc.erase(desc.find("#"), 1);
	return desc;
}
