#include "Board.h"
void Board::displayInfo(string message)
{
	if (infoCounter == 12) {
		for (string &i: info)
			i = "";
		infoCounter = 0;
	}
	info[infoCounter] = message;
	infoCounter++;
}
void Board::drawTwoBoards(Board& ai, string message)
{
	system("CLS");
	cout << "	 Ship Grid			  Attack Grid		" << info[0] << endl;
	cout << "    |A|B|C|D|E|F|G|H|I|J|	     |A|B|C|D|E|F|G|H|I|J|	" << info[1] << endl;
	for (int i = 0; i < columns; i++)
	{
		cout << "  " << i <<" ";
		for (int j = 0; j < rows; j++)
		{
			char temp;
			
			if (j + 1 != rows)
			{
				setDefaultColor();
				cout << "|"; 
				setShipGridColor(i, j);
				cout << shipgrid[0][i][j];
			}
			else
			{
				setDefaultColor();
				cout << "|";
				setShipGridColor(i, j);
				cout << shipgrid[0][i][j];
				setDefaultColor();
				cout << "|";
			}
		}
		cout << "	   " << i << " ";
		for (int j = 0; j < rows; j++)
		{
			if (j + 1 != rows)
			{
				setDefaultColor();
				cout << "|";
				setShotGridColor(ai, i, j);
				cout << shotgrid[i][j];
			}
			else
			{
				setDefaultColor();
				cout << "|";
				setShotGridColor(ai, i, j);
				cout << shotgrid[i][j];
				setDefaultColor();
				cout << "|";
			}
		}
		cout << "	" << info[i+2] << endl;
	}
	
	cout << endl;
	Board::legend();
	if (!message.empty()) {
		SetConsoleTextAttribute(Console, 10);
		cout << endl;
		cout << message;
		cout << endl;
		setDefaultColor();
	}
}

void Board::drawSigleBoard()
{
	system("CLS");
	cout << endl;
	cout << "	  Ship Grid" << endl;
	cout << "    |A|B|C|D|E|F|G|H|I|J|" << endl;
	for (int i = 0; i < columns; i++)
	{
		cout << "  " << i << " ";
		for (int j = 0; j < rows; j++)
		{
			if (j + 1 != rows)
			{
				cout << "|" << shipgrid[0][i][j];
			}
			else
			{
				cout << "|" << shipgrid[0][i][j] << "|";
			}
		}
		cout << endl;
	}
	cout << endl;
	Board::legend();
}

void Board::arrayClean()
{
	for (int i = 0; i < columns; i++)
	{
		for (int j = 0; j < rows; j++)
		{
			shipgrid[0][i][j] = ' ';
			shipgrid[1][i][j] = ' ';
			shipgrid[2][i][j] = ' ';
			shotgrid[i][j] = ' ';
			spawngrid[i][j] = ' ';
		}
	}

}

void Board::legend()
{
	cout << " ---Legend---" << endl;
	SetConsoleTextAttribute(Console, 10);
	cout << " O ";
	setDefaultColor();
	cout << "ship" << endl;
	SetConsoleTextAttribute(Console, 6);
	cout << " $ ";
	setDefaultColor();
	cout << "hited ship" << endl;
	SetConsoleTextAttribute(Console, 4);
	cout << " $ ";
	setDefaultColor();
	cout << "sinked ship" << endl;
	SetConsoleTextAttribute(Console, 14);
	cout << " X ";
	setDefaultColor();
	cout << "missed atack" << endl;
}

void Board::setShipGridColor(int i, int j)
{
	if (shipgrid[0][i][j] == '$' && count(numberOfShipTypes.begin(), numberOfShipTypes.end(), shipgrid[2][i][j]) == 0) {
		SetConsoleTextAttribute(Console, 4);
	}
	else if (shipgrid[0][i][j] == '$') {
		SetConsoleTextAttribute(Console, 6);
	}
	else if (shipgrid[0][i][j] == 'O') {
		SetConsoleTextAttribute(Console, 10);
	}
	else if (shipgrid[0][i][j] == 'X') {
		SetConsoleTextAttribute(Console, 14);
	}
	else {
		SetConsoleTextAttribute(Console, 7);
	}
}

void Board::setShotGridColor(Board& ai, int i, int j)
{
	if (shotgrid[i][j] == '$' && count(ai.numberOfShipTypes.begin(), ai.numberOfShipTypes.end(), ai.shipgrid[2][i][j]) == 0) {
		SetConsoleTextAttribute(Console, 4);
	}
	else if (shotgrid[i][j] == '$') {
		SetConsoleTextAttribute(Console, 6);
	}
	else if (shotgrid[i][j] == 'X') {
		SetConsoleTextAttribute(Console, 14);
	}
	else {
		SetConsoleTextAttribute(Console, 7);
	}
}

void Board::setDefaultColor()
{
	SetConsoleTextAttribute(Console, 7);
}

int Board::getrows()
{
	return rows;
}

int Board::getcolumns()
{
	return columns;
}




