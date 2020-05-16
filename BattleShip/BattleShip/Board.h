#pragma once
#include <iostream>
#include <vector>
using namespace std;
class Board
{
public:
	string info1, info2;
	void drawTwoBoards();
	void drawSigleBoard();
	Board()
	{
		arrayClean();
	}
protected:
	
	void arrayClean();
protected:
	char shipgrid[2][10][10];
	char shotgrid[10][10];
	int getrows();
	int getcolumns();
private:
	void legend();
private:
	const int rows = 10;
	const int columns = 10;
};

