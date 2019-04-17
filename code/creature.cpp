#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "general.h"
#include "creature.h"
#include "conEngine.h"
using namespace std;
//--------------------------------------------------------------------------player----------------------------------
//constructor
player::player() {
	kills = 0;
	max_hp = 30;
	hp = max_hp;
	weapon = item();
	inventoryCount[0] = 1; // weapon
	inventoryCount[1] = 0; // keys
	inventoryCount[2] = 2; // potions
	inventoryCount[3] = kills; // heads
	inventorySlot[0] = L"Weapon";
	inventorySlot[1] = L"Keys";
	inventorySlot[2] = L"Potions";
	inventorySlot[3] = L"Heads";
	name = chooseName();
	block = false;
	canStrike = true;
}
player::player(string choice) {
	kills = 0;
	hp = 30;
	weapon = item();
	inventoryCount[0] = 1;
	inventoryCount[1] = 0;
	inventoryCount[2] = 2;
	inventoryCount[3] = kills;
	inventorySlot[0] = L"Weapon";
	inventorySlot[1] = L"Keys";
	inventorySlot[2] = L"Potions";
	inventorySlot[3] = L"Heads";
	name = choice;
	block = false;
	canStrike = true;
}
//functions
string player::chooseName() {
	general obj;
	string str;
	const char* dir = "./playerNames.txt";
	str = obj.pullRandom(dir);
	return str;
}
void player::playerHeal(int hp, wchar_t *screen) {
	// heal player a variable ammount, make sure that is does not exceed the max health val
	// remove a pot from third inventoryCount slot
	// engine.conPrint to screen how much you healed on line 2
	// add continue(k) prompt at end of engine.conPrint call
}
void player::playerStrike(item& weapon, creature *target, wchar_t *screen) {
	conEngine engine;
	if (target->block == false) {
		wstringstream ss;
		ss << weapon.damage;
		wstring damageDealt = ss.str();
		if (canStrike == true) {
			target->hp -= weapon.damage;
			canStrike = false;
		}
		engine.conPrint(4,engine.StringToWString(target->name) + L" Was not able to block it, and you dealt " + damageDealt + L" damage.", screen);
	}
	else if (target->block == true) {
		target->block = false;
		engine.conPrint(4, engine.StringToWString(target->name) + L" was successful in blocking your attack, you dealt 0 damage", screen);
	}
}
void player::playerDie(wchar_t *screen) {
	conEngine engine;
	engine.conClear(screen);
	wstring legacy;
	if (kills / 5 < 1) {
		legacy = L"rather poor";
	}
	else if (kills / 5 > 1 && kills / 5 < 2) {
		legacy = L"pretty good";
	}
	else {
		legacy = L"epic";
	}
	wstringstream ss;
	ss << this->kills;
	wstring ks = ss.str();
	engine.conPrint(1, engine.StringToWString(this->name) + L" had achieved " + ks + L" kills", screen);
	engine.conPrint(2, L"His lgacy was " + legacy, screen);
}
void player::printStats() {
	cout << "| Your name is " << this->name << ". \n";
	cout << "| Your health is at " << this->hp << ". \n";
	cout << "| You wield " << this->weapon.name << ", which does " << this->weapon.damage << " damage. \n| ";
	cout << this->weapon.name << " is at " << this->weapon.reliability << "/10 reliability.";
}
void player::printStats(int line, wchar_t *screen) {
	conEngine engine;
	wstring n = engine.StringToWString(this->name);
	wstringstream ss1;
	ss1 << this->hp;
	wstring h = ss1.str();
	wstringstream ss2;
	ss2 << this->weapon.damage;
	wstring wd = ss2.str();
	wstring wn = engine.StringToWString(this->weapon.name);
	wstringstream ss4;
	ss4 << this->weapon.reliability;
	wstring wr = ss4.str();
	engine.conPrint(line, L"Your name is " + n, screen);
	engine.conPrint(line + 1, L"Your health is at " + h, screen);
	engine.conPrint(line + 2, L"You wield " + wn + L" which does " + wd + L" damage.", screen);
	engine.conPrint(line + 3, wn + L" has a " + wr + L"/10 reliability", screen);
}
//--------------------------------------------------------------------------enemy----------------------------------
//constructor
enemy::enemy() {
	general obj;
	potions = rand() % 4;
	att = enemyAttack();
	max_hp = ((rand() % 16) + 5);
	hp = max_hp;
	name = obj.randomSyllableName();
	background = description();
	block = false;
	canStrike = true;
}
enemy::enemy(string pn) {
	general obj;
	potions = rand() % 4;
	att = enemyAttack();
	max_hp = ((rand() % 16) + 5);
	hp = max_hp;
	name = obj.randomSyllableName();
	background = description(name, pn);
	block = false;
	canStrike = true;
}
//functions
void enemy::printStats(int line, wchar_t *screen) {
	conEngine engine;
	wstring n = engine.StringToWString(this->name);
	wstringstream ss1;
	ss1 << this->hp;
	wstring h = ss1.str();
	wstringstream ss2;
	ss2 << this->att.damage;
	wstring wd = ss2.str();
	wstring wn = engine.StringToWString(this->att.name);
	wstringstream ss4;
	ss4 << this->att.reliability;
	wstring wr = ss4.str();
	engine.conPrint(line, n + L" wields " + wn + L", which does " + wd + L" damage.", screen);
	engine.conPrint(line + 1, L"This weapon has a reliability of " + wr + L"/10 reliability.", screen);
	engine.conPrint(line + 2, n + L" Has a health of " + h, screen);
}
void enemy::printDesc(string description, int line, wchar_t *surface) {
	conEngine source;
	string desc = description;
	int adder = 0;
	int lastpos = 0;
	char temp[120];
	string tot;
	while(desc.find("~N") != string::npos){
		tot = desc.copy(temp, desc.find("~N"), lastpos);
		source.conPrint(line+adder, source.StringToWString(tot), surface);
		lastpos = desc.find("~N");
		desc.erase(desc.find("~N"), 2);
		tot = "";
		for (int i = 0;i<120;i++){
			temp[i] = ' ';
		}
	}
}
void enemy::enemyDie(creature& pl) {
	pl.kills++;
}
void enemy::enemyHeal(int hp, wchar_t *screen) {
	// heal creature a variable ammount, make sure that is does not exceed the max health val
	// remove a pot from third pots val
	// engine.conPrint to screen how much it healed on line 2
}
void enemy::enemyStrike(creature *pl, enemyAttack& att) {
	if (canStrike == true) {
		pl->hp -= att.damage + pl->kills / 5;
		canStrike = false;
	}
}
bool enemy::willDrop(enemyAttack& att) {
	int startIndex = att.name.find(' ');
	int size = att.name.length();
	int endIndex = size - startIndex;
	string str = att.name.substr(startIndex, endIndex);
	int chance = (unsigned char)(str.at(0));
	chance -= 96;
	if (rand() % chance == chance) {
		return true;
	}
	return false;
}
