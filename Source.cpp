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
/*
	When you use an include such as #include "header.h" the same directory as the file is searched.
	When you use an include such as #include <header.h> a specific directory is searched, chosen by your compiler, which is where you will find most standard library header files.
	1 = blue ob \n
	2 = green ob \n
	3 = dark purple ob \n
	4 = maroon ob \n
	5 = dark brown ob \n
	6 = caramel ob \n
	7 = white ob \n
	8 = periwinkle ob \n
	9 = diff blue on black \n
	10 = lime ob \n
	11 = light blue ob \n
	12 = red on black
	13 = yellow ob \n
	14 = orange ob \n
	16 = black on blue \n
	18 = green on blue \n
	19 = purple on blue \n
	20 = red on blue \n
	29 = yellow on blue \n
	30 = orange on blue \n
	31 = white on blue \n
	32 = black on green \n
	33 = blue on green \n
	35 = purple on green \n
	36 = maroon on green \n
	37 = brown on green \n
	38 = caramel on green \n
	39 = gray on green \n
	40 = periwinkle on green \n
	42 = lime on green \n
	43 = light blue on green \n
	44 = red on green \n
	45 = yellow on green \n
	46 = orange on green \n
	47 = white on green \n
	48 = black on purple \n
	56 = periwinkle on purple \n
	64 = black on red \n
	76 = red on maroon \n
	80 = black on brown \n
	96 = black on caramel \n
	97 = blue on caramel \n
	98 = green on caramel \n
	99 = purple on caramel \n
	100 = red on caramel \n
	127 = white on gray \n
	128 = black on periwinkle \n
	129 = blue on periwinkle \n
	180 = maroon on light blue \n
	196 = maroon on red \n
	200 = periwinkle on red \n
	etc, hopefully you see the pattern \n
*/
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
void printReadMe() {
	char cont;
	cout << "<WARNING> \n -------\n";
	cout << "This game will only run correctly if your CMD default proportions are set to [120 x 40] \n \n";
	cout << "If you have not done so, do that now. \nOnce you have dont that, restart this program and continue. \n \n";
	cout << "Press any key to continue. \n";
	cin >> cont;
	system("CLS");
}
void printPreliminary() {
	char settings;
	cout << "_____________________________________________________\n";
	cout << "| ___________________________________________________\n";
	cout << "| | ______	                 _____              \n";
	cout << "| | |  _  |                       |  __ |             \n";
	cout << "| | | | | | _   _  _ ___   _____  | |  |/  ___  _ ___ \n";
	cout << "| | | | | || | | || '_  | |_____| | | __  / _ || '_  | \n";
	cout << "| | | |/ / | |_| || | | |         | |_) )|  __/| | | |\n";
	cout << "| | |___/  |___,_||_| |_|         |____/ |___| |_| |_|\n";
	cout << "| |__________________________________________________ \n";
	cout << "|____________________________________________________ \n|";
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
		fPlayerX -= sinf(fPlayerA + 3.14159/2) * fSpeed * fElapsedTime;
		fPlayerY -= cosf(fPlayerA + 3.14159/2) * fSpeed * fElapsedTime;
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
}
void lapseLevel(wstring map) {
	if (fPlayerX <= 1.5) {
		inCombat = true;
		lapsed = true;
		fPlayerX = 30.0f;
		fPlayerY = 2.0f;
	}
}
void enemyRandomMove(wstring map, float fElapsedTime, int pos){
	srand(time(NULL));
	int plane = rand() % 1;
	int dir = rand() % 1;
	if (plane){
		
	}
	else if (!plane){
		
	}
}
void enemyUpdate(wstring map, float fElapsedTime) {
	// supposedly move enemies in a random direction unless the player is within a certain distance from them
	// in which case they opt to instead chase the player
	for (int i = 0;i<nMapWidth*nMapHeight;i++){
		if (map.c_str()[i] == 'X'){ // if i have located an enemy
			if (((fPlayerX - (i % nMApWidth)) < fDepth) && ((fPlayerY - (i / nMapWidth) < fDepth)){ // distance to player is less than render distance
				bool hitWall = false;
				bool hitPlayer = false;
				int nEnemyX = i % nMapWidth; // enemy x pos in room
				int nEnemyY = i / nMapHeight; // enemy y pos in room
				while(!hitWall && !hitPlayer){
					int lengthdir_x = int(fPlayerX) - (i%nMapWidth);
					int lengthdir_y = int(fPlayerY) - (i / nMapHeight);
					nEnemyX += lengthdir_x/lengthdir_y;
					nEnemyY += (lengthdir_y/lengthdir_x) * nMapWidth;
					if (map.c_str()[nEnemyX * nEnemyY] == '#'){ // ray hits wall
						hitWall = true;
					}
					else if (map.c_str()[nEnemyX * nEnemyY] == 'P'){ // ray hits player
						hitPlayer = true;
					}
				}
				int lengthdir_x = int(fPlayerX) - (i%nMapWidth);
				int lengthdir_y = int(fPlayerY) - (i / nMapHeight);
				if (hitPlayer){ // i can see the player
					map.c_str()[i] = '.'; // replace tile im about to leave
					if (map.c_str()[i+(lengthdir_x/lengthdir_y)+((lengthdir_y/lengthdir_x)*nMapWidth)] == '.'){ // if tileom moving to is free
						map.c_str()[i+(lengthdir_x/lengthdir_y)+((lengthdir_y/lengthdir_x)*nMapWidth)] == 'X'; // move to place
					}
				}
				else{ // if not within line of sight of player
					enemyRandomMove(map, fElapsedTime, i);
				}
			}
			else{ // if not in range of player
				enemyRandomMove(map, fElapsedTime, i);
			}
		}
	}
	/*
	Line of sight:
		lengthdir_x
			fPlayerX - (i%nMapWidth)
		lengthdir_y
			fPlayerY - (i / nMapHeight)
	range:
		enemy x:
			i % nMapWidth
		enemy y:
			i / nMapHeight
	*/
}
void conEngine::conPrint(int line, wstring word, wchar_t *screen) {
	for (int i = 0; i < nScreenWidth; i++) {
		screen[(nScreenWidth * (line-1)) + i] = ' ';
	}
	for (int i = 0; i < word.length(); i++) {
		screen[(nScreenWidth * (line-1)) + i] = word[i];
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
void updateAlarms(float arr[],int arrlength) {
	for (int i = 0; i < arrlength; i++) {
		if (arr[i] > -1) {
			arr[i] --;
		}
		if (arr[i] < -1) {
			arr[i] = -1;
		}
	}
}
int main(){
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
	// Create Map of world space # = wall block, . = space
	wstring map;
	map = randLevel();
	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();
	while (1) {
		if (!inCombat) {
			srand(time(NULL));
			map = randLevel();
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
						engine.conPrint(1, L"You drink a potion to heal your wounds.", screen);
						engine.conPrint(2, L"Continue(k)", screen);
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
									WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
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
						engine.conPrint(1, engine.StringToWString(opponent.name) + L" drinks a healing potion", screen);
						engine.conPrint(2, L"Continue(k)", screen);
						if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
							progress++;
							engine.conClear(screen);
						}
					}
				break;
				}
				if (progress == 3) {
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
							Sleep(100);
							engine.conPrint(1, L"Your opponents weapon was too damaged for you to be able to use it in further battles." , screen);
							progress ++ ;
						}
					}
					else {
						Sleep(200);
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
					engine.conPrint(2, L"you picked up 1 new key, and 1 new head, continue(k)", screen);
					if (GetAsyncKeyState((unsigned short)'K') & 0x8000) {
						my.inventoryCount[1]++;
						opponent.enemyDie(my);
						my.inventoryCount[3]++;
						inCombat = false;
					}
				}
				//engine.conClear(screen);
				updateAlarms(alarm, alarmLength);
				WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
			}
			if (my.hp <= 0) {
				return 0;
			}
		}
		while (!lapsed) {
			if (GetAsyncKeyState((unsigned short)'Q') & 0x8000) {
				return 0;
			}
			lapseLevel(map);
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
			enemyUpdate(map, fElapsedTime);
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
					if (fDistanceToWall <= fDepth / 4.0f){
						nShade = 0x2588;	// Very close	
					}
					else if (fDistanceToWall < fDepth / 3.0f){
						nShade = 0x2593;
					}
					else if (fDistanceToWall < fDepth / 2.0f){
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
				for (int y = 0; y < nScreenHeight; y++) {
					// Each Row
					if (y <= nCeiling)
						screen[y*nScreenWidth + x] = ' ';
					else if (y > nCeiling && y <= nFloor)
						screen[y*nScreenWidth + x] = nShade;
					else {// Floor
						// Shade floor based on distance
						float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
						if (b < 0.25)		nShade = 0x2588;
						else if (b < 0.5)	nShade = 0x2593;
						else if (b < 0.75)	nShade = 0x2592;
						else if (b < 0.9)	nShade = 0x2591;
						else				nShade = ' ';
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
					engine.conPrintAdd(i+5,L"             |: " + itemCount, screen);
					engine.conPrintAdd(i+5,L"   | " + my.inventorySlot[i], screen);
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
			WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, { 0,0 }, &dwBytesWritten);
		}
	}
	return 0;
}
