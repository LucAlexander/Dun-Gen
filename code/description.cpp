#include <iostream>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <istream>
#include "description.h"
#include "general.h"
using namespace std;
//constructor
description::description() {
	earlyLife = "";
	characteristics = "";
	name = "";
}
description::description(string n) {
	earlyLife = fillLife();
	characteristics = fillCharacteristics();
	name = n;
}
//functions
string description::fillLife() {
	// read in template
	ifstream infile;
	string desc;
	string temp;
	general obj;
	infile.open("./earlyLife.txt");
	if (infile.is_open())
	{
		int c = 2; //PLACEHOLDER_AMT_OF_TEMPLATES; should be one less than the ammount of templates
		int val = rand() % c + 1;
		for (int i = 0; i < val; i++)
		{
			infile.ignore(256, '\n');
		}
		getline(infile, desc);
	}
	else
	{
		cout << "Error opening file";
	}
	infile.close();
	while (desc.find("$M") != string::npos) // existing name
	{
		desc.insert(desc.find("$M") + 2, name);
		desc.erase(desc.find("$M"), 2);
	}
	while (desc.find("%M") != string::npos) // filling random name(a new one)
	{
		temp = obj.randomSyllableName();
		desc.insert(desc.find("%M") + 2, temp);
		desc.erase(desc.find("%M"), 2);
		
	}
	while (desc.find("%V") != string::npos) // verbs
	{
		const char* dir = "./verb.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%V") + 2, temp);
		desc.erase(desc.find("%V"), 2);
	}
	while (desc.find("%A") != string::npos) // all adjectives
	{
		int choice = rand() % 3 + 1;
		const char* dir = "./participleAdjectives.txt";
		const char* dir1 = "./descriptionAdjectives.txt";
		const char* dir2 = "./personalityAdjectives.txt";
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
	while (desc.find("%P") != string::npos) // participle adj
	{
		const char* dir = "./participleAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%P") + 2,  temp);
		desc.erase(desc.find("%P"), 2);
	}
	while (desc.find("%D") != string::npos) // description adj
	{
		const char* dir = "./descriptionAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%D") + 2, temp);
		desc.erase(desc.find("%D"), 2);
	}
	while (desc.find("%E") != string::npos) // personality adj
	{
		const char* dir = "./personalityAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%E") + 2, temp);
		desc.erase(desc.find("%E"), 2);
	}
	while (desc.find("%O") != string::npos) // nouns
	{
		const char* dir = "./nouns.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%O") + 2, temp);
		desc.erase(desc.find("%O"), 2);
	}
	return desc;
}
string description::fillCharacteristics() {
	// read in template
	ifstream infile;
	string desc;
	string temp;
	general obj;
	infile.open("./characteristics.txt");
	if (infile.is_open())
	{
		int c = 0; //PLACEHOLDER_AMT_OF_TEMPLATES; should be one less than the ammount of templates
		int val = rand() % c;
		for (int i = 0; i < val; i++)
		{
			infile.ignore(256, '\n');
		}
		getline(infile, desc);
	}
	else
	{
		cout << "Error opening file";
	}
	infile.close();
	while (desc.find("$M") != string::npos) // existing name
	{
		desc.insert(desc.find("$M") + 2, name);
		desc.erase(desc.find("$M"), 2);
	}
	while (desc.find("%M") != string::npos) // filling random name(a new one)
	{
		temp = obj.randomSyllableName();
		desc.insert(desc.find("%M") + 2, temp);
		desc.erase(desc.find("%M"), 2);
		
	}
	while (desc.find("%V") != string::npos) // verbs
	{
		const char* dir = "./verb.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%V") + 2, temp);
		desc.erase(desc.find("%V"), 2);
	}
	while (desc.find("%A") != string::npos) // all adjectives
	{
		int choice = rand() % 3 + 1;
		const char* dir = "./participleAdjectives.txt";
		const char* dir1 = "./descriptionAdjectives.txt";
		const char* dir2 = "./personalityAdjectives.txt";
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
	while (desc.find("%P") != string::npos) // participle adj
	{
		const char* dir = "./participleAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%P") + 2,  temp);
		desc.erase(desc.find("%P"), 2);
	}
	while (desc.find("%D") != string::npos) // description adj
	{
		const char* dir = "./descriptionAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%D") + 2, temp);
		desc.erase(desc.find("%D"), 2);
	}
	while (desc.find("%E") != string::npos) // personality adj
	{
		const char* dir = "./personalityAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%E") + 2, temp);
		desc.erase(desc.find("%E"), 2);
	}
	while (desc.find("%O") != string::npos) // nouns
	{
		const char* dir = "./nouns.txt";
		temp = obj.pullRandom(dir);
		desc.insert(desc.find("%O") + 2, temp);
		desc.erase(desc.find("%O"), 2);
	}
	return desc;
}
