#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "general.h"
using namespace std;
//functions---------------------------------- add functions here for general use across classes, dont forget to declare in header file aswell
int general::findLength(ifstream& file){
	int i = 0;
	if (file.is_open()){
		while (file.good()){
			infile.ignore(256,'\n');
			i++;
		}
	}
	return i;
}
void general::parse(string arr[], ifstream& infile){
	if (infile.is_open()){
		int i = 0;
		while (infile.good()){
			getline(infile, arr[i], '\n');
			i++;
		}
	}
}
string general::randomName(){
	ifstream infile;
	infile.open("TextFiles/WordsToPlugIn/syllables.txt");
	string syllables[findLength(infile)];
	if (infile.is_open()){
		int i = 0;
		while (infile.good()){
			getline(infile, syllables[i], '\n');
			i++;
		}
	}
	infile.close();

	//syllable ammount shoudl be random as well, so there shoudl be a chance for there to be a single syllable name
	//code for randomize method goes here. append syllables to string called name:
	//use the array called syllables[], it should have all the strings stored in it so long as you place all the syllables yo want to use in the syllibles.txt file at TextFiles/Syllables.txt in the file directory in repl.it
	
	string name;
	int length = sizeof(syllables);
	int chunks = rand() % 5;
	int chunkselect;
	for(int i = 1; i <= chunks; i++)
	{
		chunkselect = rand() % length;
		name.append(syllables[chunkselect]);
	}
	return name;
}
string general::pullRandom(ifstream& infile){
	string name;
	string list[findlength(infile)];
	parse(list, infile);
	infile.close();
	//code here
	//this should pull a random string index the  list array and place that into 'name'
	return name;
}
