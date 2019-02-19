#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
using namespace std;
class creature{
	public:
		int hp;
		string name;
		int kills;
};
class player : public creature{
	friend enemy;
	public:
		item weapon;
		player();
		void playerStrike(item& weapon, creature& target);
		void playerDie();
		string chooseName();
		string printStats();
};
class enemy : public creature{
	friend player;
	public: 
		//attributes
		description background;
		enemyAttack att;
		//functions
		enemy(); // constructs hp, name
		string randomName(); // generates random name
		string printStats();
		void enemyStrike(creature& pl, enemyAttack& att);
		void enemyDie(creature& pl);
};
