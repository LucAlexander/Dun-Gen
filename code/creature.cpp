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
}
//functions
string player::chooseName(){
	string str;
	//chopose random name from either list/array or read in from file
	return str;
}
void player::playerStrike(item& weapon, creature& target){
	int n = rand() % 10 + 1;
	if (n <= weapon.reliability){
		target.hp -= weapon.damage;
	}
}
void player::playerDie(){
	// what happens when the game ends/player dies
}
string player::printStats(){
	//print name, health, weapon, and kills
	//weapon name, weapon damage, weapon reliability, and special
}
//--------------------------------------------------------------------------enemy----------------------------------
//constructor
enemy::enemy(){
	att = enemyAttack();
	hp = ((rand() % 16) + 5);
	name = randomName();
	background = description();
}
//functions
string enemy::printStats(){
	//print name, health, damage of attack
}
void enemy::enemyDie(creature& pl){
	pl.kills++;
}
void enemy::enemyStrike(creature& pl, enemyAttack& att){
	int n = rand() % 10 + 1;
	if (n <= att.reliability + pl.kills / 5){
		pl.hp -= att.damage + pl.kills / 5;
	}
}
string enemy::randomName(){	
	general obj = general();
	ifstream infile;
	infile.open("TextFiles/WordsToPlugIn/syllables.txt");
	string syllables[obj.findLength(infile)];
	if (infile.is_open()){
		int i = 0;
		while (infile.good()){
			getline(infile, syllables[i], '\n');
			i++;
		}
	}
	infile.close();
	string name;
	//code for randomize method goes here. append syllables to string called name:
	//use the array called syllables[], it should have all the strings stored in it so long as you place all the syllables you want to use in the syllibles.txt file at TextFiles/Syllables.txt in the file directory in repl.it
	return name;
}
