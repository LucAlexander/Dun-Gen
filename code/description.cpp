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
	cout << " !!!! \n";
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
		int   c = 2; //PLACEHOLDER_AMT_OF_TEMPLATES; should be one less than the ammount of templates
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
		cout << " $M \n";
		desc.replace(desc.find("$M"), name.length(), name);
	}
	while (desc.find("%M") != string::npos) // filling random name(a new one)
	{
		cout << " %m \n";
		temp = obj.randomSyllableName();
		desc.replace(desc.find("%M"), temp.length(), temp);
	}
	while (desc.find("%V") != string::npos) // verbs
	{
		cout << "%v \n ";
		const char* dir = "./verb.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%V"), temp.length(), temp);
	}
	while (desc.find("%A") != string::npos) // all adjectives
	{
		cout << "%A \n ";
		int choice = rand() % 3 + 1;
		const char* dir = "./participleAdjectives.txt";
		const char* dir1 = "./descriptionAdjectives.txt";
		const char* dir2 = "./personalityAdjectives.txt";
		switch (choice) {
		case 1:
			temp = obj.pullRandom(dir2);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		case 2:
			temp = obj.pullRandom(dir1);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		case 3:
			temp = obj.pullRandom(dir2);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		default:
			temp = obj.pullRandom(dir2);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		}
	}
	while (desc.find("%P") != string::npos) // participle adj
	{
		cout << "%p \n ";
		const char* dir = "./participleAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%P"), temp.length(), temp);
	}
	while (desc.find("%D") != string::npos) // description adj
	{
		cout << "%D \n ";
		const char* dir = "./descriptionAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%D"), temp.length(), temp);
	}
	while (desc.find("%E") != string::npos) // personality adj
	{
		cout << "%E \n ";
		const char* dir = "./personalityAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%E"), temp.length(), temp);
	}
	while (desc.find("%O") != string::npos) // nouns
	{
		cout << "%O \n ";
		const char* dir = "./nouns.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%O"), temp.length(), temp);
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
		int   c = 0; //PLACEHOLDER_AMT_OF_TEMPLATES; should be one less than the ammount of templates
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
		desc.replace(desc.find("$M"), name.length(), name);
	}
	while (desc.find("%M") != string::npos) // filling random name(a new one)
	{
		temp = obj.randomSyllableName();
		desc.replace(desc.find("%M"), temp.length(), temp);
	}
	while (desc.find("%V") != string::npos) // verbs
	{
		const char* dir = "./verb.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%V"), temp.length(), temp);
	}
	while (desc.find("%A") != string::npos) // all adjectives
	{
		int choice = rand() % 3 + 1;
		const char* dir = "./participleAdjectives.txt";
		const char* dir1 = "./descriptionAdjectives.txt";
		const char* dir2 = "./personalityAdjectives.txt";
		switch (choice) {
		case 1:
			temp = obj.pullRandom(dir2);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		case 2:
			temp = obj.pullRandom(dir1);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		case 3:
			temp = obj.pullRandom(dir2);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		default:
			temp = obj.pullRandom(dir2);
			desc.replace(desc.find("%A"), temp.length(), temp);
			break;
		}
	}
	while (desc.find("%P") != string::npos) // participle adj
	{
		const char* dir = "./participleAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%P"), temp.length(), temp);
	}
	while (desc.find("%D") != string::npos) // description adj
	{
		const char* dir = "./descriptionAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%D"), temp.length(), temp);
	}
	while (desc.find("%E") != string::npos) // personality adj
	{
		const char* dir = "./personalityAdjectives.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%E"), temp.length(), temp);
	}
	while (desc.find("%O") != string::npos) // nouns
	{
		const char* dir = "./nouns.txt";
		temp = obj.pullRandom(dir);
		desc.replace(desc.find("%O"), temp.length(), temp);
	}
	return desc;
}
