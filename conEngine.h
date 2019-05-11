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
class conEngine {
public:
	void conPrint(int line, wstring word, wchar_t *screen);
	void conPrintAdd(int line, wstring word, wchar_t *screen);
	void conClear(wchar_t *screen);
	wstring StringToWString(string s);
};
