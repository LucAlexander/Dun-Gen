#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class enemyAttack{
	public: 
		string name;
		int damage; // 1-5
		int reliability;//chance out of 10 that it will hit 30% to 100%
		enemyAttack();
		string randomName();
};
