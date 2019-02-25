#include <iostream>
#include <string>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include "code/general.h"
#include "code/description.h"
#include "code/item.h"
#include "code/enemyattack.h"
#include "code/creature.h"
using namespace std;
int main() {
	int namechoice;
	cout << "Hello player, would you like to choose your own name, or have a random one \n 1) random \n 2) choose \n";
	cin >> namechoice;
	if (namechoice == 1){
		player my = player(); // instantiate player
	}
	else if namechoice == 2){
		string playerchoicename;
		cout << "name: \n";
		cin >> playerchoicename;
		player my = player(playerchoicename); // instantiate player
	}
	enemy opponent = enemy(); // instantiate first enemy
	int turn = 1; // turn var [1 if player's, 2 if enemy's]
	cout << my.printStats() << "\n";
	cout << opponent.printStats() << "\n";
	while(my.hp > 0){ // main loop: terminates upon player's death
		if (turn){ // ---------------------------------------------------------------------player's turn
			int choice;
			cout << "choose action \n"; // list options
			cout << "1) attack \n";
			cout << "2) block next turn \n";
			cin >> choice; // read in choice
			switch(choice){
				case 1: // attack enemy
					my.playerStrike(my.weapon, opponent);
				break;
				case 2: // parry next turn
					my.block = true;
				break;
				case 3:
					//other options
				break;
			}
			turn *= -1; // change turn
		}
		if (!turn){ // ---------------------------------------------------------------------enemy's turn
			int choice = (rand() % 1) + 1; // randomize choice
			switch(choice){
				case 1: // attack player
					opponent.enemyStrike(my, opponent.att);
				break;
				case 2: // parry next turn
					opponent.block = true;
				break;
				case 3:
					// other options
				break;
			}
			turn *= -1; // change turn
		} // ---------------------------------------------------------------------end round checks and specifications
		if (opponent.hp <= 0){ // if opponent is dead;
			cout << my.name << " defeated " << opponent.name << " using " << my.weapon.name << "\n"; // print tagline for defeating enemy
			if (opponenet.willDrop(opponent.att)){
				cout << opponent.name << "dropped " << opponent.att.name << "\n";
				cout << "Pickup? \n 1)yes \n 2)no \n";
				int option;
				cin >> option;
				if (option == 1){
					my.weapon = item(opponent.att.name, opponent.att.damage, opponenet.att.reliability);
					cout << "You have pickd up " << my.weapon.name << "\n";
					cout << my.printStats();
				}
				else{
					cout "You have decided to leave behind " << opponent.att.name << "\n";
				}
			}
			opponent.enemyDie(my); // kill off current enemy
			opponent = enemy(); // spawn new enemy
			cout << opponent.name << " has appeared \n"; // introduce new enemy
			cout << opponent.background.earlyLife << "\n"; // early life of the enemy
			cout << opponent.background.characteristics << "\n"; // description
			cout << opponent.background.qualities << "\n"; // stats
			cout << opponent.printStats() << "\n \n";
			cout << "Would you like to go to the door to your left, or to your right? \n 1)left \n 2)right";
			int dir;
			cin >> dir;
			cout << \n;
		}
	}
	cout << my.name << " has been defeated by " << opponent.name << " using " << opponent.att.name << "\n"; // print endgame
	my.playerDie(); // print final outputs (legacy and stats etc)
}
