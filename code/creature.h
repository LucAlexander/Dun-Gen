#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "enemyattack.H"
#include "item.h"
#include "description.h"
using namespace std;
class creature {
	public:
		int hp;
		int max_hp;
		string name;
		int kills;
		bool block;
		bool canStrike;
};
class player : public creature {
public:
	int inventoryCount[4];
	wstring inventorySlot[4];
	item weapon;
	player();
	player(string choice);
	void playerHeal(int hp, wchar_t *surface);
	void playerStrike(item& weapon, creature *target, wchar_t *surface);
	void playerDie(wchar_t *surface);
	string chooseName();
	void printStats();
	void printStats(int line, wchar_t *surface);
};
class enemy : public creature {
public:
	//attributes
	description background;
	enemyAttack att;
	int potions;
	//functions
	enemy();
	enemy(string pn);
	void printStats(int line, wchar_t *surface);
	void enemyHeal(int hp, wchar_t *surface);
	void enemyStrike(creature *pl, enemyAttack& att);
	void enemyDie(creature& pl);
	bool willDrop(enemyAttack& att);
	void printDesc(string desc, int line, wchar_t *surface);
};
