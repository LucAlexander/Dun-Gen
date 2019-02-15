#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "description.h"
using namespace std;
//constructor
description::description(){
	earlyLife = fillLife(earlyLife);
	characteristics = fillCharacteristics(characteristics);
}
//functions
string description::fillLife(string str){
	// read in template
	string desc;
	// write function to fill in template.
	// use directory: TextFiles/Formats/earlyLife, and TextFiles/WordsToPlugIn/... for adjectives, participles, and nouns to plug in.
	return desc;
}
string description::fillCharacteristics(string str){
	// read in template
	string desc;
	 // write function to fill in template. 
	 // use directory TextFiles/Formats/characteristics for template directory, and TextFiles/WordsToPlugIn/... for adjectives, participles, and nouns to plug in.
	return desc;
}