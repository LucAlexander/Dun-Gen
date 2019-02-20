#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "general.h"
using namespace std;
//functions---------------------------------- add functions here for general use across classes
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
