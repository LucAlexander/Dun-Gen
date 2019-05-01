#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <stdlib.h>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <Windows.h>
#include "general.h"
#include "conEngine.h"
#include "creature.h"
using namespace std;
int nScreenWidth = 120;			// Console Screen Size X (columns)
int nScreenHeight = 40;			// Console Screen Size Y (rows)
int nMapWidth = 32;				// World Dimensions
int nMapHeight = 32;
int colorMode = 7;
float fPlayerX = 30.0f;			// Player Start Position
float fPlayerY = 2.0f;
float fPlayerA = -3.14159 / 2.0;			// Player Start Rotation
float fFOV = 3.14159f / 3.0f;	// Field of View
float fDepth = 11.0f;			// Maximum rendering distance;
float fTurn = 5.0f;
float fMaxSpeed = 5.5f;
float fMinSpeed = 0.1f;
float fSpeed = fMinSpeed;		// Walking Speed
float fAccelerate = 0.1f;
bool showMap = false;
bool showInventory = false;
bool lapsed = false;
bool inCombat = false;
bool canCombat = true;
stirng seed;
void printReadMe() {
	char cont;
	cout << "<WARNING> \n -------\n";
	cout << "This game will only run correctly if your CMD default proportions are set to [120 x 40] \n\n";
	cout << "It is also necessary tyhast under these conditions, the font and font size you choose must allow the cmd window \n";
	cout << "to be completely on screen and un-fullscreened\n\n";
	cout << "If you have not done so, do that now. \nOnce you have dont that, restart this program and continue. \n \n";
	cout << "Press any key to continue. \n";
	cin >> cont;
	system("CLS");
}
void printPreliminary() {
	char settings;
	cout << "__________________________________________________________\n";
	cout << "| ______________________________________________________ |\n";
	cout << "| | ______	                    _____               | |\n";
	cout << "| | |  _  |                       |  __ |              | |\n";
	cout << "| | | | | | _   _  _ ___   _____  | |  |/  ___  _ ___  | |\n";
	cout << "| | | | | || | | || '_  | |_____| | | __  / _ || '_  | | |\n";
	cout << "| | | |/ / | |_| || | | |         | |_) )|  __/| | | | | |\n";
	cout << "| | |___/  |___,_||_| |_|         |____/ |___| |_| |_| | |\n";
	cout << "| |____________________________________________________| |\n";
	cout << "|________________________________________________________|\n|";
	cout << "\n| \n| ";
	cout << "$ Would you like to change these settings? \n| \n|   - Look Sensetivity: 5 \n|   - Render Distance: 11.0 \n|   - FOV: 3.0 \n|   - Color Mode: 7 \n| \n| $ (y/n) \n| \n| ";
	cout << "<<< ";
	cin >> settings;
	cout << "|\n";
	if (settings == 'y') {
		cout << "|___________________________________________________ \n| \n";
		cout << "| >>> Input Turning Sensetivity, \n|  >>> Minimum of 1, \n|  >>> Maximum of 8: \n| <<< ";
		cin >> fTurn;
		if (fTurn > 8) {
			fTurn = 8;
		}
		else if (fTurn < 1) {
			fTurn = 1;
		}
		cout << "|\n| >>> Input Render Distance, \n|  >>> Minimun of 8, \n|  >>> Maximum of 32: \n| <<< ";
		cin >> fDepth;
		if (fDepth > 32) {
			fDepth = 32;
		}
		else if (fDepth < 8) {
			fDepth = 8;
		}
		float fovDivisor;
		cout << "|\n| >>> Input Field of view, \n|  >>> Minimun of 2.0, \n|  >>> Maximum of 5.0: \n| <<< ";
		cin >> fovDivisor;
		if (fovDivisor > 5) {
			fovDivisor = 5;
		}
		else if (fovDivisor < 2) {
			fovDivisor = 2;
		}
		fFOV = 3.14159 / fovDivisor;
		cout << "|\n| >>> Input Color Scheme: \n| <<< ";
		cin >> colorMode;
		cout << "Seed? \n";
		cin >> seed;
		cout << "\n";
	}
	cout << "|___________________________________________________ \n";
}
wstring randLevel() {
	wstring map;
	map += L"################################";
	int n;
	for (int i = 0; i < 5; i++) {
		n = rand() % 5;
		switch (n) {
		case 0:
			map += L"#############...################";
			map += L"#.........#....................#";
			map += L"#.........#....................#";
			map += L"#..................#...........#";
			map += L"#..................#...........#";
			map += L"#.........#........#...........#";
			break;
		case 1:
			map += L"###...##########################";
			map += L"#..............#...............#";
			map += L"#.....####...........#.........#";
			map += L"#.....####...........#.........#";
			map += L"#.....####.....#.....#.........#";
			map += L"#..............#...............#";
			break;
		case 2:
			map += L"#########################...####";
			map += L"#............#.....#...........#";
			map += L"#.......#....#.................#";
			map += L"#.......#.................#....#";
			map += L"#.......#..........#...........#";
			map += L"#..................#...........#";
			break;
		case 3:
			map += L"#########..###########..########";
			map += L"#...............#..............#";
			map += L"#...###.........#..............#";
			map += L"#...###.........#........#.....#";
			map += L"#...............#..............#";
			map += L"#..............................#";
			break;
		case 4:
			map += L"#############.....##############";
			map += L"#..............................#";
			map += L"#..............#...............#";
			map += L"#.....####.#########.####......#";
			map += L"#..............#...............#";
			map += L"#..............................#";
			break;
		}
	}
	map += L"################################";
	for (int i = 0; i < map.length(); i++) {
		n = rand() % 64;
		if (n == 0) {
			if (map[i] != '#') {
				map[i] = 'X';
			}
		}
	}
	return map;
}
int instanceNearest(wstring map, wchar_t entity) {
	int xDist = nMapWidth;
	int yDist = nMapHeight;
	int total = xDist * yDist;
	int xPos = 0;
	int yPos = 0;
	for (int x = 0; x < nMapWidth; x++) {
		for (int y = 0; y < nMapHeight; y++) {
			if (map.c_str()[x + (nMapWidth*y)] == entity) {
				if ((abs(x - (int)fPlayerX) + 1)*(abs(y - (int)fPlayerY) + 1) < total) {
					xDist = abs(x - (int)fPlayerX);
					yDist = abs(y - (int)fPlayerY);
					total = xDist * yDist;
					xPos = x;
					yPos = y;
				}
			}
		}
	}
	return yPos + (nMapWidth * xPos);
}
void touchEnemy(wstring map) {
	if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == 'X') {
		if (canCombat) {
			map[(int)fPlayerX * nMapWidth + (int)fPlayerY] = '.';
			inCombat = true;
			lapsed = true;
			canCombat = false;
			map[instanceNearest(map, 'X')] = '.';
		}
	}
}
void touchPlayer(wstring map, int pos) {
	if (map.c_str()[pos] == (round(fPlayerX)*nMapWidth)+round(fPlayerY)) {
		if (canCombat) {
			map[pos] = '.';
			inCombat = true;
			lapsed = true;
			canCombat = false;
			map[instanceNearest(map, 'X')] = '.';
		}
	}
}
void setKeyMapping(wstring map, float fElapsedTime) {
	//Show map
	if (GetAsyncKeyState((unsigned short)'M') & 0x8000) {
		showMap = true;
	}
	// Show Inventory
	if (GetAsyncKeyState((unsigned short)'I') & 0x8000) {
		showInventory = true;
	}
	// Handle CCW Rotation
	if (GetAsyncKeyState((unsigned short)'J') & 0x8000)
		fPlayerA -= (fTurn * 0.75f) * fElapsedTime;
	// Handle CW Rotation
	if (GetAsyncKeyState((unsigned short)'L') & 0x8000)
		fPlayerA += (fTurn * 0.75f) * fElapsedTime;
	// Handle Forwards movement & collision
	if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
		if (fSpeed < fMaxSpeed) {
			fSpeed += fAccelerate;
		}
		fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
		fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
		if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
			fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;
		}
	}
	// Handle backwards movement & collision
	if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
		if (fSpeed < fMaxSpeed) {
			fSpeed += fAccelerate;
		}
		fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;
		fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;
		if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
			fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
		}
	}
	// Handle right movement & collision
	if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
		if (fSpeed < fMaxSpeed) {
			fSpeed += fAccelerate;
		}
		fPlayerX += sinf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
		fPlayerY += cosf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
		if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
			fPlayerX -= sinf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
			fPlayerY -= cosf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
		}
	}
	// Handle left movement & collision
	if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
		if (fSpeed < fMaxSpeed) {
			fSpeed += fAccelerate;
		}
		fPlayerX -= sinf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
		fPlayerY -= cosf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
		if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
			fPlayerX += sinf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
			fPlayerY += cosf(fPlayerA + 3.14159 / 2) * fSpeed * fElapsedTime;
		}
	}
	if (!(GetAsyncKeyState((unsigned short)'A') & 0x8000) &&
		!(GetAsyncKeyState((unsigned short)'D') & 0x8000) &&
		!(GetAsyncKeyState((unsigned short)'S') & 0x8000) &&
		!(GetAsyncKeyState((unsigned short)'W') & 0x8000)) {
		if (fSpeed > fMinSpeed)
			fSpeed -= 0.1;
		else if (fSpeed < fMinSpeed)
			fSpeed = fMinSpeed;
	}
	touchEnemy(map); // combat if im touching an enemy weith my next position upadte
}
int signOf(int num) {
	if (num < 0) {
		return -1;
	}
	return 1;
}
wstring enemyUpdate(wstring map) {
	for (int i = 0; i < map.length(); i++) {
		if (map[i] == 'X') {
			int n = rand() % 1000;
			int h = rand() % 1000;
			if (n == h) {
				int dir = rand() % 1;
				int yOffSet = 1;
				if (n < 500) {
					if (n < 250) {
						dir = 1;
						yOffSet = 1;
					}
					else{
						dir = 1;
						yOffSet = nMapHeight;
					}
				}
				else {
					if (n > 750) {
						dir = -1;
						yOffSet = 1;
					}
					else{
						dir = -1;
						yOffSet = nMapWidth;
					}
				}
				if (map[i + dir* yOffSet] != '#' && map[i + dir*yOffSet] != 'X') {
					map[i] = '.';
					map[i + dir*yOffSet] = 'X';
					touchPlayer(map, i + (dir*yOffSet));
					break;
				}
			}
		}
	}
	return map;
}
void conEngine::conPrint(int line, wstring word, wchar_t *screen) {
	for (int i = 0; i < nScreenWidth; i++) {
		screen[(nScreenWidth * (line - 1)) + i] = ' ';
	}
	for (int i = 0; i < word.length(); i++) {
		screen[(nScreenWidth * (line - 1)) + i] = word[i];
	}
}
void conEngine::conPrintAdd(int line, wstring word, wchar_t *screen) {
	for (int i = 0; i < word.length(); i++) {
		screen[(nScreenWidth * (line - 1)) + i] = word[i];
	}
}
void conEngine::conClear(wchar_t *screen) {
	for (int i = 0; i < nScreenWidth*nScreenHeight; i++) {
		screen[i] = ' ';
	}
}
wstring conEngine::StringToWString(string s)
{
	wstring temp(s.length(), L' ');
	copy(s.begin(), s.end(), temp.begin());
	return temp;
}
void fillTree(node* head){
	int outer = 4;
	int inner = 0;
	node* temp = head;
	for (int p = 0;p<15;p++){
		for (int i = 0;i<outer;i++){
			//go left
			node* q = temp.left;
			temp = temp.left;
		}
		for (int k = 0;k<inner;k++){
			//go right
			node* q = temp.right;
			temp = temp.right;
		}
		temp = head;
	}
	for (int p = 0;p<15;p++){
		for (int i = 0;i<outer;i++){
			//go right
			node* q = temp.right;
			temp = temp.right;
		}
		for (int k = 0;k<inner;k++){
			//go left
			node* q = temp.left;
			temp = temp.left;
		}
	}
	temp.head;
}
wstring conEngine::generateLevel(node* tree){
	string temp = seed;
	node* store = tree;
	wstring floor;
	stringstream ss;
	string room = str.copy(temp, 2, 0);
	int seg1 = int(room.at(0));
	int seg2 = int(room.at(1));
	ss << seg1 << seg2;
	string totalRoom = ss.str();
	for (int i = 0;i<4;i++){
		int car = totalRoom.at(i) - '0';
		if (car % 2 == 0){
			store = store.left;
		}
		else{
			store = store.right;
		}
		if (store.chunk != "Q"){
			floor += store.chunk;
		}
	}
	seed = str.erase(0, 2);
	return floor;
}
void conEngine::nodeAdd(node* head, wstring section){
	node* parser = head;
	if (parse.chunk == NULL){
		if (parser.left == NULL && parser.right == NULL){
			if (parser.chunk == NULL){
				parser.chunk = section; // this node is the target
			}
			else{
				nodeAdd(parser.parent, section);//go up to parent node of parser
			}
		}
		else{
			node* pLeft = parser.left;
			node* pRight = parser.right;
			if (pLeft.chunk == NULL){
				nodeAdd(pLeft, section);//go to left
			}
			else if (pRight.chunk == NULL){
				nodeAdd(pRight, section);//go to right
			}
			else if (pRight.chunk != NULL && pLeft.chunk != NULL){
				nodeAdd(parser.parent, section);//go up to parent of parser
				parser.chunk = L"Q"; // cut off branch
			}
		}
	}
}
void updateAlarms(float arr[], int arrlength) {
	for (int i = 0; i < arrlength; i++) {
		if (arr[i] > -1) {
			arr[i] --;
		}
		if (arr[i] < -1) {
			arr[i] = -1;
		}
	}
}
int removeNearestEnemy(wstring map) {
	bool found = false;
	int itterator = 2;
	int dir = 0;
	int pos = (int(floor(fPlayerX))*nMapWidth + int(floor(fPlayerY))) - 1;
	if (map[pos] == 'X') {
		found = true;
	}
	else if (map[pos - nMapWidth] == 'X ') {
		found = true;
	}
	else {
		pos -= nMapWidth;
	}
	while (!found) {
		for (int i = 0; i < 2; i++) {
			for (int k = 0; k < itterator; k++) {
				switch (dir) {
				case 0:
					pos++;
					break;
				case 1:
					pos += nMapWidth;
					break;
				case 2:
					pos--;
					break;
				case 3:
					pos -= nMapWidth;
					break;
				}
			}
			if (map[pos] == 'X') {
				found = true;
				return pos;
			}
		}
		dir++;
		if (dir == 4) {
			dir = 0;
		}
		itterator++;
	}
	return -1;
}
int main() {
	srand(time(NULL));
	printReadMe();
	printPreliminary();
	conEngine engine;
	general gen;
	player my = player();
	cout << "|\n";
	my.printStats();
	cout << "\n| \n| ";
	char changeName;
	cout << "$ would you like to change your players name? (y/n) \n| <<< ";
	cin >> changeName;
	if (changeName == 'y') {
		cout << "| \n| >>> What would you like your new name to be? \n| <<< ";
		cin >> my.name;
		cout << "|__________________________________________________ \n| \n";
		my.printStats();
	}
	cout << "|\n| press any key to continue.\n| ";
	char cont;
	cin >> cont;
	// Set Colors
	HANDLE CConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(CConsole);
	DWORD CdwBytesWritten = 0;
	SetConsoleTextAttribute(CConsole, colorMode);
	// Create Screen Buffer
	wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;
	HANDLE buffer = hConsole;
	// Create Map of world space # = wall block, . = space
	wstring map;
	//make seed based binary tree
	node* tree;
	fillTree(tree);
	map = generateLevel(tree);
	//define time variables
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();
	while (1) {
		if (!inCombat) {
			srand(time(NULL));
			//map = randLevel();
			lapsed = false;
		}
		else if (inCombat) {
			engine.conClear(screen);
			int progress = 0; // which stage in the combat returns he is in
			int chance = rand() % 10 + 1; // if hit or miss
			int blockchance = rand() % 3 + 1;
			int n = rand() % 10 + 1;
			int enemyChoice = rand() % 2 + 1;
			int enemyMissChance = rand() % 10 + 1;
			const int alarmLength = 5;
			int sliderPos = 0;
			int sliderMax = my.kills + 5;
			if (my.kills % 2 == 0 || my.kills == 0) {
				sliderMax++;
			}
			int sliderTarget = (sliderMax) / 2;
			bool canSlide = true;
			float alarm[alarmLength];
			for (int i = 0; i < alarmLength; i++) {
				alarm[i] = -1;
			}
			int turn = 1;
			enemy opponent = enemy(my.name);
			while (inCombat && my.hp > 0) {
				switch (turn) {
				case 1:
					if (progress == 0) {
						my.printStats(1, screen);
						engine.conPrint(6, engine.StringToWString(opponent.background.earlyLife), screen);
						engine.conPrint(7, engine.StringToWString(opponent.background.characteristics), screen);
						opponent.printStats(9, screen);
						engine.conPrint(14, L"What Action would you like to take", screen);
						engine.conPrint(15, L"1) attack with " + engine.StringToWString(my.weapon.name), screen);
						if (my.inventoryCount[2] != 0) {
							engine.conPrint(16, L"2) Drink Potion", screen);
						}
						if (GetAsyncKeyState((unsigned short)'1') & 0x8000) {
							engine.conClear(screen);
							progress++;
						}
						else if (GetAsyncKeyState((unsigned short)'2') & 0x8000) {
							engine.conClear(screen);
							progress += 2;
						}
					}
					if (progress == 1) {
						engine.conClear(screen);
						engine.conPrint(1, L"You attempt to strike " + engine.StringToWString(opponent.name) + L" with " + engine.StringToWString(my.weapon.name), screen);
						if (chance <= my.weapon.reliability) {
							engine.conPrint(2, L"Your swing lands", screen);
							if (blockchance < 3) {
								opponent.block = true;
							}
							else {
								opponent.block = false;
							}
							my.playerStrike(my.weapon, &opponent, screen);
						}
						else {
							engine.conPrint(2, L"You missed", screen);
							opponent.printStats(3, screen);
						}
						engine.conPrint(3, L"Continue(K)", screen);
						if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
							progress += 2;
						}
					}
					if (progress == 2) {
						engine.conClear(screen);
						my.playerHeal(my.hp, screen);
						if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
							progress++;
						}
					}
					break;
				case -1:
					if (progress == 0) {
						if (opponent.potions <= 0) {
							enemyChoice = 1;
						}
						progress = enemyChoice;
					}
					if (progress == 1) {
						if (canSlide == true) {
							engine.conPrint(1, engine.StringToWString(opponent.name) + L" attacks you with " + engine.StringToWString(opponent.att.name), screen);
						}
						if (enemyMissChance <= opponent.att.reliability + my.kills / 5) {
							if (canSlide) {
								engine.conPrint(2, L"Its hit is going to land if you do not block it!", screen);
								bool sliding = true;
								int dir = 1;
								wstring slider;
								for (int p = 0; p <= sliderMax; p++) {
									if (p == sliderTarget) {
										slider += L"*";
									}
									else {
										slider += L"=";
									}
								}
								engine.conPrint(5, slider, screen);
								Sleep(100);
								while (sliding) {
									wstring pointer;
									if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
										sliding = false;
										break;
									}
									Sleep(50);
									if (dir == 1) {
										if (sliderPos >= sliderMax - 1) {
											dir *= -1;
										}
										sliderPos++;
									}
									else if (dir == -1) {
										if (sliderPos <= 1) {
											dir *= -1;
										}
										sliderPos--;
									}
									for (int p = 0; p < sliderPos; p++) {
										pointer += L" ";
									}
									pointer += L"^";
									engine.conPrint(6, pointer, screen);
									WriteConsoleOutputCharacter(buffer, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
								}
								canSlide = false;
							}
							engine.conClear(screen);
							if (sliderPos == sliderTarget) {
								engine.conClear(screen);
								engine.conPrint(1, L"You blocked the attack", screen);
								Sleep(100);
								engine.conPrint(2, L"Continue(k)", screen);
								if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
									progress += 2;
									engine.conClear(screen);
								}
							}
							else {
								engine.conClear(screen);
								engine.conPrint(1, L"You were unsuccessful in blocking the attack", screen);
								opponent.enemyStrike(&my, opponent.att);
								Sleep(100);
								engine.conPrint(2, L"Continue(k)", screen);
								if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
									progress += 2;
									engine.conClear(screen);
								}
							}
						}
						else {
							Sleep(100);
							engine.conPrint(2, L"Its hit missed you", screen);
							engine.conPrint(3, L"Continue(k)", screen);
							if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
								progress += 2;
								engine.conClear(screen);
							}
						}
						Sleep(100);
					}
					else if (progress == 2) {
						Sleep(100);
						opponent.enemyHeal(opponent.hp, screen);
						if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
							progress++;
							engine.conClear(screen);
						}
					}
					break;
				}
				if (progress == 3) {
					Sleep(100);
					if (opponent.hp <= 0) {
						if (opponent.willDrop(opponent.att)) {
							engine.conClear(screen);
							engine.conPrint(1, engine.StringToWString(opponent.name) + L" dropped his weapon, " + engine.StringToWString(opponent.att.name), screen);
							engine.conPrint(2, L" Would you like to pick this weapon up, in exchange for your own?", screen);
							engine.conPrint(3, L"Y", screen);
							engine.conPrint(4, L"N", screen);
							if (GetAsyncKeyState((unsigned short)'Y') & 0x8000) {
								my.weapon = item(opponent.att.name, opponent.att.damage, opponent.att.reliability);
								engine.conClear(screen);
								engine.conPrint(1, L"New weapon aquired!", screen);
							}
							if (GetAsyncKeyState((unsigned short)'N') & 0x8000) {
								engine.conClear(screen);
								engine.conPrint(1, L"You opted to keep your own weapon.", screen);
								progress++;
							}
						}
						else {
							engine.conClear(screen);
							engine.conPrint(1, L"Your opponents weapon was too damaged for you to be able to use it in further battles.", screen);
							engine.conPrint(2, L"Continue(k)", screen);
							if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
								progress++;
							}
						}
					}
					else {
						Sleep(100);
						engine.conClear(screen);
						engine.conPrint(1, L"turn lapsed, continue(k)", screen);
						if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
							turn *= -1;
							progress = 0;
							chance = rand() % 10 + 1;
							blockchance = rand() % 3 + 1;
							my.canStrike = true;
							opponent.canStrike = true;
							n = rand() % 10 + 1;
							enemyChoice = rand() % 2 + 1;
							canSlide = true;
							sliderPos = 0;
							enemyMissChance = rand() % 10 + 1;
						}
					}
				}
				if (progress == 4) {
					Sleep(100);
					engine.conPrint(2, L"you picked up 1 new key, and 1 new head, continue(k)", screen);
					if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
						my.inventoryCount[1]++;
						opponent.enemyDie(my);
						my.inventoryCount[3]++;
						inCombat = false;
						lapsed = false;
					}
				}
				//engine.conClear(screen);
				updateAlarms(alarm, alarmLength);
				WriteConsoleOutputCharacter(buffer, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			}
			if (my.hp <= 0) {
				return 0;
			}
		}
		while (!lapsed) {
			if (!canCombat) { // if coming out of combat
				map[instanceNearest(map, 'X')] = '.'; // find nearest enemy and remove
				canCombat = true; // make it so tht i can fight again
			}
			if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) { // this is a quit condition
				return 0;
			}
			// We'll need time differential per frame to calculate modification
			// to movement speeds, to ensure consistant movement, as ray-tracing
			// is non-deterministic
			tp2 = chrono::system_clock::now();
			chrono::duration<float> elapsedTime = tp2 - tp1;
			tp1 = tp2;
			float fElapsedTime = elapsedTime.count();
			// Detect keys
			setKeyMapping(map, fElapsedTime);
			// Move Enemies
			map = enemyUpdate(map);
			for (int x = 0; x < nScreenWidth; x++) {
				// For each column, calculate the projected ray angle into world space
				float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
				// Find distance to wall
				float fStepSize = 0.1f;		  // Increment size for ray casting, decrease to increase										
				float fDistanceToWall = 0.0f; //                                      resolution
				bool bHitWall = false;		// Set when ray hits wall block
				bool bHitEnemy = false;
				bool bBoundary = false;		// Set when ray hits boundary between two wall blocks
				float fEyeX = sinf(fRayAngle); // Unit vector for ray in player space
				float fEyeY = cosf(fRayAngle);
				// Incrementally cast ray from player, along ray angle, testing for 
				// intersection with a block
				while (!bHitEnemy && !bHitWall && fDistanceToWall < fDepth) {
					fDistanceToWall += fStepSize;
					int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
					int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
					// Test if ray is out of bounds
					if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
						bHitWall = true;			// Just set distance to maximum depth
						fDistanceToWall = fDepth;
					}
					else {
						// Ray is inbounds so test to see if the ray cell is a wall block
						if (map.c_str()[nTestX * nMapWidth + nTestY] == '#') {
							// Ray has hit wall
							bHitWall = true;
							// To highlight tile boundaries, cast a ray from each corner
							// of the tile, to the player. The more coincident this ray
							// is to the rendering ray, the closer we are to a tile 
							// boundary, which we'll shade to add detail to the walls
							vector<pair<float, float>> p;
							// Test each corner of hit tile, storing the distance from
							// the player, and the calculated dot product of the two rays
							for (int tx = 0; tx < 2; tx++)
								for (int ty = 0; ty < 2; ty++) {
									// Angle of corner to eye
									float vy = (float)nTestY + ty - fPlayerY;
									float vx = (float)nTestX + tx - fPlayerX;
									float d = sqrt(vx*vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							// Sort Pairs from closest to farthest
							sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first; });
							// First two/three are closest (we will never see all four)
							float fBound = 0.01;
							if (acos(p.at(0).second) < fBound) bBoundary = true;
							if (acos(p.at(1).second) < fBound) bBoundary = true;
							if (acos(p.at(2).second) < fBound) bBoundary = true;
						}
						else if (map.c_str()[nTestX * nMapWidth + nTestY] == 'X') {
							// Ray has hit wall
							bHitEnemy = true;
							// To highlight tile boundaries, cast a ray from each corner
							// of the tile, to the player. The more coincident this ray
							// is to the rendering ray, the closer we are to a tile 
							// boundary, which we'll shade to add detail to the walls
							vector<pair<float, float>> p;
							// Test each corner of hit tile, storing the distance from
							// the player, and the calculated dot product of the two rays
							for (int tx = 0; tx < 2; tx++)
								for (int ty = 0; ty < 2; ty++) {
									// Angle of corner to eye
									float vy = (float)nTestY + ty - fPlayerY;
									float vx = (float)nTestX + tx - fPlayerX;
									float d = sqrt(vx*vx + vy * vy);
									float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
									p.push_back(make_pair(d, dot));
								}
							// Sort Pairs from closest to farthest
							sort(p.begin(), p.end(), [](const pair<float, float> &left, const pair<float, float> &right) {return left.first < right.first; });
							// First two/three are closest (we will never see all four)
							float fBound = 0.01;
							if (acos(p.at(0).second) < fBound) bBoundary = true;
							if (acos(p.at(1).second) < fBound) bBoundary = true;
							if (acos(p.at(2).second) < fBound) bBoundary = true;
						}
					}
				}
				// Calculate distance to ceiling and floor
				int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
				int nFloor = nScreenHeight - nCeiling;
				// Shader walls based on distance
				short nShade = ' ';
				if (bHitWall) {
					if (fDistanceToWall <= fDepth / 4.0f) {
						nShade = 0x2588;	// Very close	
					}
					else if (fDistanceToWall < fDepth / 3.0f) {
						nShade = 0x2593;
					}
					else if (fDistanceToWall < fDepth / 2.0f) {
						nShade = 0x2592;
					}
					else if (fDistanceToWall < fDepth) {
						nShade = 0x2591;
					}
					else {
						nShade = ' ';		// Too far away
					}
					if (bBoundary) {
						nShade = '|'; // Black it out
					}
				}
				else if (bHitEnemy) {
					if (fDistanceToWall <= fDepth / 4.0f) {
						nShade = '@';	// Very close	
					}
					else if (fDistanceToWall < fDepth / 3.0f) {
						nShade = '0';
					}
					else if (fDistanceToWall < fDepth / 2.0f) {
						nShade = 'O';
					}
					else if (fDistanceToWall < fDepth) {
						nShade = 'o';
					}
					else {
						nShade = ' ';		// Too far away
					}
					if (bBoundary) {
						nShade = 'X'; // Black it out
					}
				}
				for (int y = 0; y < nScreenHeight; y++) { // Draw individual pixel chars
					// Each Row
					if (y <= nCeiling) {
						screen[y*nScreenWidth + x] = ' ';
					}
					else if (y > nCeiling && y <= nFloor) {
						screen[y*nScreenWidth + x] = nShade;
					}
					else {// Floor
						// Shade floor based on distance
						float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
						if (b < 0.25) {
							nShade = 0x2588;
						}
						else if (b < 0.5) {
							nShade = 0x2593;
						}
						else if (b < 0.75) {
							nShade = 0x2592;
						}
						else if (b < 0.9) {
							nShade = 0x2591;
						}
						else {
							nShade = ' ';
						}
						screen[y*nScreenWidth + x] = nShade;
					}
				}
			}
			// Display Stats
			swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f, FPS=%3.2f", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);
			//Disply Inventory
			if (showInventory) {
				showMap = false;
				for (int i = 2; i <= 10; i++) {
					engine.conPrintAdd(i, L"                                        ", screen);
				}
				engine.conPrintAdd(2, L"   ___________", screen);
				engine.conPrintAdd(3, L"   INVENTORY", screen);
				engine.conPrintAdd(4, L"   ___________", screen);
				wstring itemCount;
				int invLen = 4;
				engine.conPrintAdd(5, L"   | " + my.inventorySlot[0] + L"  |: " + engine.StringToWString(my.weapon.name), screen);
				for (int i = 1; i < invLen; i++) {
					wstringstream wss;
					wss << my.inventoryCount[i];
					itemCount = wss.str();
					engine.conPrintAdd(i + 5, L"             |: " + itemCount, screen);
					engine.conPrintAdd(i + 5, L"   | " + my.inventorySlot[i], screen);
				}
				wstringstream hss;
				hss << my.hp;
				wstring health = hss.str();
				wstringstream mhss;
				mhss << my.max_hp;
				wstring maxHealth = mhss.str();
				engine.conPrintAdd(9, L"   ___________", screen);
				engine.conPrintAdd(10, L"   HEALTH: " + health + L"/" + maxHealth, screen);
				showInventory = false;
			}
			// Display Map
			if (showMap) {
				for (int nx = 0; nx < nMapWidth; nx++) {
					for (int ny = 0; ny < nMapWidth; ny++) {
						screen[(ny + 1)*nScreenWidth + nx] = map[ny * nMapWidth + nx];
					}
				}
				screen[((int)fPlayerX + 1) * nScreenWidth + (int)fPlayerY] = 'P';
				showMap = false;
			}
			// Display Frame
			screen[nScreenWidth * nScreenHeight - 1] = '\0';
			WriteConsoleOutputCharacter(buffer, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			if (fPlayerY <= 31){
				map = generateLEvel(tree);
				fPlayerX = 30.0;
				fPlayerY = 2.0;
				colorMode = rand()%256;
				HANDLE newColor = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
				SetConsoleActiveScreenBuffer(newColor);
				DWORD CdwBytesWritten = 0;
				SetConsoleTextAttribute(newColor, colorMode);
				// Create Screen Buffer
				wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
				HANDLE newBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
				SetConsoleActiveScreenBuffer(newBuffer);
				DWORD dwBytesWritten = 0;
				buffer = newBuffer;
				Sleep(100);
			}
		}
	}
	return 0;
}
