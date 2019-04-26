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
	max_hp = 30;
	hp = max_hp;
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
	conEngine engine;
	general gen;
	if(inventoryCount[2] == 0){
		engine.conPrint(2,engine.StringToWString("You ruffle through your bag only to realize you don't have any potions."), screen);	
	}
	else{
		// heal player a variable ammount, make sure that is does not exceed the max health val
		if(hp == max_hp){
			engine.conPrint(2,engine.StringToWString("You're at the maximum hp possible."), screen);
		}
		else{
			int heal = ((rand() %3) + 2);
			while(hp + heal>max_hp){
				heal--;
			}
			hp = hp + heal;
			inventoryCount[2]--;
			engine.conPrint(2,engine.StringToWString("You " + gen.pullRandom(verb.txt) + " the potion and it heals you " + heal + " hp."), screen);
		}
	}
	engine.conPrint(3,engine.StringToWString("Press (k) to continue."), screen);
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
	general database;
	string desc = description;
	int adder = 0;
	int lastpos = 0;
	while(desc.find("~N") != string::npos){
		char temp[500];
		desc.copy(temp, desc.find("~N")-lastpos, lastpos);
		source.conPrint(line+adder, source.StringToWString(temp), surface);
		lastpos = desc.find("~N");
		if (database.countSubstring(desc, "~N") > 1){
			desc.erase(desc.find("~N"), 3);
		}
		else{
			adder++;
			break;
		}
		adder++;
		for (int i = 0;i<500;i++){
			temp[i] = NULL;
		}
	}
	char tomp[500];
	desc.copy(tomp, desc.length(), desc.find("~N")+3);
	source.conPrint(line+adder, source.StringToWString(tomp), surface);
}
void enemy::enemyDie(creature& pl) {
	pl.kills++;
}
void enemy::enemyHeal(int hp, wchar_t *screen) {
	conEngine engine;
	general gen;
	if (potions > 0){
		engine.conPrint(1, gen.StringToWString(name) + L" drinks a potion", screen);
		int heal = ((rand() %3) + 2);
		while (hp+heal > max_hp){
			heal--;
		}
		potions--;
		hp += heal;
		stringstream ss;
		ss << heal;
		string healedAmmount = ss.str();
		engine.conPrint(2, engine.StringToWString(name) + L" has been healed " + StringToWString(healedAmmount), screen);
	}
	engine.conPrint(3, L"Continue(k)", screen);
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
