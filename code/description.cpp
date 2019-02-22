#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "description.h"
#include "general.h"
using namespace std;
//constructor
description::description(string n){
	earlyLife = fillLife(earlyLife);
	characteristics = fillCharacteristics(characteristics);
	name = n;
}
//functions
string description::fillLife(string str){
	// read in template
	string desc;
	string temp;
	general obj;
	infile.open ("TextFiles/Formats/earlyLife.txt");
	if (infile.is_open())
	{
		int   c=PLACEHOLDER_AMT_OF_TEMPLATES;
		int val = rand() % c;
		for(int i = 0;i<val;i++)
		{
			infile.ignore(256, "/n");
		}
		infile.getline(desc, 256, '/n');
		infile.close();
	}
	else
	{
		cout << "Error opening file";
	}
	// write function to fill in template.
	// use directory: TextFiles/Formats/earlyLife, and TextFiles/WordsToPlugIn/... for adjectives, participles, and nouns to plug in.
	while(desc.find("$M")!=desc.npos())
	{
		desc.replace(desc.find("$M"), name.length(), name);
	}
	while(desc.find("%M")!=desc.npos())
	{
		temp = obj.randomName();
		desc.replace(desc.find("%M"), temp.length(), temp);
	}
	while(desc.find("%V")!=desc.npos())
	{
		ifstream infile;
		infile.open("TextFiles/WordsToPlugIn/verb.txt");
		temp = obj.pullWord(infile);
		desc.replace(desc.find("%V"), temp.length(), temp);
	}
	while(desc.find("%A")!=desc.npos())
	{
		temp = obj.randomAdjective();
		desc.replace(desc.find("%A"), temp.length(), temp);
	}
	while(desc.find("%P")!=desc.npos())
	{
		temp = obj.randomParticipleAdj();
		desc.replace(desc.find("%P"), temp.length(), temp);
	}
	while(desc.find("%D")!=desc.npos())
	{
		temp = obj.randomDescriptionAdj();
		desc.replace(desc.find("%D"), temp.length(), temp);
	}
	while(desc.find("%E")!=desc.npos())
	{
		temp = obj.randomPersonalityAdj();
		desc.replace(desc.find("%E"), temp.length(), temp);
	}
	while(desc.find("%O")!=desc.npos())
	{
		temp = obj.randomNoun();
		desc.replace(desc.find("%O"), temp.length(), temp);
	}
	return desc;
}
string description::fillCharacteristics(string str){
	// read in template
	string desc;
	string temp;
	general obj;
	infile.open ("TextFiles/Formats/characteristics.txt");
	if (infile.is_open())
	{
		int   c=PLACEHOLDER_AMT_OF_TEMPLATES;
		int val = rand() % c;
		for(int i = 0;i<val;i++)
		{
			infile.ignore(256, "/n");
		}
		infile.getline(desc, 256, '/n');
		infile.close();
	}
	else
	{
		cout << "Error opening file";
	}
	while(desc.find("$M")!=desc.npos())
	{
		desc.replace(desc.find("$M"), name.length(), name);
	}
	while(desc.find("%M")!=desc.npos())
	{
		temp = obj.randomName();
		desc.replace(desc.find("%M"), temp.length(), temp);
	}
	while(desc.find("%V")!=desc.npos())
	{
		temp = obj.randomVerb();
		desc.replace(desc.find("%V"), temp.length(), temp);
	}
	while(desc.find("%A")!=desc.npos())
	{
		temp = obj.randomAdjective();
		desc.replace(desc.find("%A"), temp.length(), temp);
	}
	while(desc.find("%P")!=desc.npos())
	{
		temp = obj.randomParticipleAdj();
		desc.replace(desc.find("%P"), temp.length(), temp);
	}
	while(desc.find("%D")!=desc.npos())
	{
		temp = obj.randomDescriptionAdj();
		desc.replace(desc.find("%D"), temp.length(), temp);
	}
	while(desc.find("%E")!=desc.npos())
	{
		temp = obj.randomPersonalityAdj();
		desc.replace(desc.find("%E"), temp.length(), temp);
	}
	while(desc.find("%O")!=desc.npos())
	{
		temp = obj.randomNoun();
		desc.replace(desc.find("%O"), temp.length(), temp);
	}
	return desc;
	 // write function to fill in template. 
	 // use directory TextFiles/Formats/characteristics for template directory, and TextFiles/WordsToPlugIn/... for adjectives, participles, and nouns to plug in.
}
