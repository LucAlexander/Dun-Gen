#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "enemyattack.h"
using namespace std;
//constructor
enemyAttack::enemyAttack(){
	damage = ((rand() % 5) + 1);
	reliability = ((rand() % 8)+3);
	name = "hit";
}