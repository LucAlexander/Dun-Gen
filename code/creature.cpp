#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "item.h"
#include "general.h"
#include "enemyattack.h"
#include "description.h"
#include "creature.h"
using namespace std;
//--------------------------------------------------------------------------player---------------------------------- 
//constructor
player::player(){
	kills = 0;
	hp = 30;
	weapon = item();
	name = chooseName();
	block = false;
}
//functions
string player::chooseName(){
	string str;
	
	return str;
}
void player::playerStrike(item& weapon, creature& target){
	int n = rand() % 10 + 1;
	int blockchance = rand() % 3 + 1;
	if (n <= weapon.reliability){
		if (target.block == false || blockchance == 3){
			target.hp -= weapon.damage;
		}
		else if (blockchace <= 3){
			target.block = false;
		}
	}
}
void player::playerDie(){
	string legacy;
	if (kills / 5 < 1){
		legacy = "rather poor";
	}
	else if (kills/5 > 1 && kills/5 < 2){
		legacy = "pretty good";
	}
	else{
		legacy = "epic";
	}
	cout << this.name << " had achieved " << this.kills << " kills \n";
	cout << "His legacy was " << legacy << "\n";
}
string player::printStats(){
	string str;
	//return a string with name, health, weapon, and kills
	//weapon name, weapon damage, weapon reliability, and special
	return str;
}
//--------------------------------------------------------------------------enemy----------------------------------
//constructor
enemy::enemy(){
	general obj;
	att = enemyAttack();
	hp = ((rand() % 16) + 5);
	name = general.randomName();
	background = description(name);
	block = false;
}
//functions
string enemy::printStats(){
	string str;
	//return string with name, health, damage of attack
	return str;
}
void enemy::enemyDie(creature& pl){
	pl.kills++;
}
void enemy::enemyStrike(creature& pl, enemyAttack& att){
	int n = rand() % 10 + 1;
	int blockchance = rand() % 3 + 1;
	if (n <= att.reliability + pl.kills / 5){
		if (pl.block == false || blockchance == 3){
			pl.hp -= att.damage + pl.kills / 5;
		}
		else if (blockchance <= 2){
			my.block = false;
		}
	}
}
bool enemy::willDrop(enemyAttack& att){
	int startIndex = att.name.find(' ');
	int size = att.name.length();
	int endIndex = size-startIndex;
	string str = att.name.substr(startIndex, endIndex);
	int chance = (unsigned char)(str.at(0));
	chance -= 96;
	if (rand() % chance = chance){
		return true;}
	return false;
}
