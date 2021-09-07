#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;
class Board
{
public:
	string info[12] = {};
	void displayInfo(string message);
	void drawTwoBoards(Board& oponentBoard, string message="");
	void drawSigleBoard();
	Board()
	{
		arrayClean();
	}
protected:	
	void arrayClean();
protected:
	char shipgrid[3][10][10];		// Used to 0 store ships position, 1 to to calculate types, 2 to store types
	char spawngrid[10][10];			// used if used option advancedShipSpawn is used
	vector<char> numberOfShipTypes = { '0','1','2','3','4' };
	char shotgrid[10][10];
	int getrows();
	int getcolumns();
private:
	void legend();
	void setShipGridColor(int i, int j);
	void setShotGridColor(Board& ai, int i, int j);
	void setDefaultColor();
private:
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	const int rows = 10;
	const int columns = 10;
	int infoCounter = 0;
};

