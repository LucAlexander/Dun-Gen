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
	while(desc.find("$M")!=desc.npos()) // existing name
	{
		desc.replace(desc.find("$M"), name.length(), name);
	}
	while(desc.find("%M")!=desc.npos()) // filling random name(a new one)
	{
		temp = obj.randomName();
		desc.replace(desc.find("%M"), temp.length(), temp);
	}
	while(desc.find("%V")!=desc.npos()) // verbs
	{
		infile.open("TextFiles/WordsToPlugIn/verb.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%V"), temp.length(), temp);
	}
	while(desc.find("%A")!=desc.npos()) // all adjectives
	{
		int choice = rand() %3 + 1;
		switch (choice){
			case 1:
				infile.open("TextFiles/WordsToPlugIn/participleAdjectives.txt");
			break;
			case 2:
				infile.open("TextFiles/WordsToPlugIn/descriptionAdjectives.txt");
			break;
			case 3:
			defaullt:
				infile.open("TextFiles/WordsToPlugIn/personalityAdjectives.txt");
			break;
		}
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%A"), temp.length(), temp);
	}
	while(desc.find("%P")!=desc.npos()) // participle adj
	{
		infile.open("TextFiles/WordsToPlugIn/participleAdjectives.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%P"), temp.length(), temp);
	}
	while(desc.find("%D")!=desc.npos()) // description adj
	{
		infile.open("TextFiles/WordsToPlugIn/descriptionAdjectives.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%D"), temp.length(), temp);
	}
	while(desc.find("%E")!=desc.npos()) // personality adj
	{
		infile.open("TextFiles/WordsToPlugIn/personalityAdjectives.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%E"), temp.length(), temp);
	}
	while(desc.find("%O")!=desc.npos()) // nouns
	{
		infile.open("TextFiles/WordsToPlugIn/nouns.txt");
		temp = obj.pullRandom(infile);
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
	while(desc.find("$M")!=desc.npos()) // existing name
	{
		desc.replace(desc.find("$M"), name.length(), name);
	}
	while(desc.find("%M")!=desc.npos()) // filling random name(a new one)
	{
		temp = obj.randomName();
		desc.replace(desc.find("%M"), temp.length(), temp);
	}
	while(desc.find("%V")!=desc.npos()) // verbs
	{
		infile.open("TextFiles/WordsToPlugIn/verb.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%V"), temp.length(), temp);
	}
	while(desc.find("%A")!=desc.npos()) // all adjectives
	{
		int choice = rand() %3 + 1;
		switch (choice){
			case 1:
				infile.open("TextFiles/WordsToPlugIn/participleAdjectives.txt");
			break;
			case 2:
				infile.open("TextFiles/WordsToPlugIn/descriptionAdjectives.txt");
			break;
			case 3:
			defaullt:
				infile.open("TextFiles/WordsToPlugIn/personalityAdjectives.txt");
			break;
		}
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%A"), temp.length(), temp);
	}
	while(desc.find("%P")!=desc.npos()) // participle adj
	{
		infile.open("TextFiles/WordsToPlugIn/participleAdjectives.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%P"), temp.length(), temp);
	}
	while(desc.find("%D")!=desc.npos()) // description adj
	{
		infile.open("TextFiles/WordsToPlugIn/descriptionAdjectives.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%D"), temp.length(), temp);
	}
	while(desc.find("%E")!=desc.npos()) // personality adj
	{
		infile.open("TextFiles/WordsToPlugIn/personalityAdjectives.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%E"), temp.length(), temp);
	}
	while(desc.find("%O")!=desc.npos()) // nouns
	{
		infile.open("TextFiles/WordsToPlugIn/nouns.txt");
		temp = obj.pullRandom(infile);
		desc.replace(desc.find("%O"), temp.length(), temp);
	}
	return desc;
}
