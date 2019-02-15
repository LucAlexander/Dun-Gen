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
	player my = player(); // instantiate player
	enemy opponent = enemy(); // instantiate first enemy
	int turn = 1; // turn var [1 if player's, 2 if enemy's]
	while(my.hp > 0){ // main loop: terminates upon player's death
		if (turn){ // ---------------------------------------------------------------------player's turn
			int choice;
			cout << "choose action \n"; // list options
			cout << "1) attack \n";
			cout << "2) attack double turn \n";
			cin >> choice; // read in choice
			switch(choice){
				case 1: // attack enemy
					my.playerStrike(my.weapon, opponent);
				break;
				case 2: // doulbe turn attack
					turn *= -1;
					my.playerStrike(my.weapon, opponent);
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
				case 2: // double turn strike
					turn *= -1;
					opponent.enemyStrike(my, opponent.att);
				break;
				case 3:
					// other options
				break;
			}
			turn *= -1; // change turn
		} // ---------------------------------------------------------------------end round checks and specifications
		if (opponent.hp <= 0){ // if opponent is dead;
			cout << my.name << " defeated " << opponent.name << " using " << opponent.att.name << "\n"; // print tagline for defeating enemy
			opponent.enemyDie(my); // kill off current enemy
			opponent = enemy(); // spawn new enemy
			cout << opponent.name << " has appeared \n"; // introduce new enemy
			cout << opponent.background.earlyLife << "\n"; // early life of the enemy
			cout << opponent.background.characteristics << "\n"; // description
			cout << opponent.background.qualities << "\n"; // stats
		}
	}
	my.playerDie();
	cout << my.name << " has been defeated by " << opponent.name << " using " << opponent.att.name << "\n"; // print endgame
}