#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include "general.h"
using namespace std;
//functions---------------------------------- add functions here for general use across classes, dont forget to declare in header file aswell
int general::findLength(const char* file) {
	int i = 0;
	ifstream infile;
	infile.open(file);
	if (infile.is_open()) {
		while (infile.good()) {
			infile.ignore(256, '\n');
			i++;
		}
	}
	else {
		cout << "\n error opening file \n";
	}
	infile.close();
	return i;
}
int general::countSubstring(const string& str, const string& sub) {
	if (sub.length() == 0) return 0;
	int count = 0;
	for (int offset = str.find(sub); offset != string::npos; offset = str.find(sub, offset + sub.length())) {
		++count;
	}
	return count;
}
void general::parse(vector<string> *arr, const char* file) {
	ifstream infile;
	infile.open(file);
	if (infile.is_open()) {
		string str;
		while (getline(infile, str))
		{
			// Line contains string of length > 0 then save it in vector
			if (str.size() > 0) {
				arr->push_back(str);
			}
		}
	}
	infile.close();
}
string general::randomSyllableName() {
	const char* dir = "./syllables.txt";
	const int length = findLength(dir);
	vector<string> syllables;
	parse(&syllables, dir);
	string name;
	int chunks = rand() % 4 + 1;
	int chunkselect;
	for (int i = 1; i <= chunks; i++)
	{
		chunkselect = rand() % length;
		name.append(syllables[chunkselect]);
	}
	return name;
}
string general::pullRandom(const char* file) {
	srand(time(NULL));
	string name;
	int len = findLength(file);
	vector<string> list;
	parse(&list, file);
	len = list.size();
	int stopper = rand() % len;
	name = list[stopper];
	return name;
}
