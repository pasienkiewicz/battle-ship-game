#include "Board.h"
void Board::drawTwoBoards()
{
	system("CLS");
	cout << endl;
	cout << "	 Ship Grid			  Attack Grid			" << info1 << endl;
	cout << "    |A|B|C|D|E|F|G|H|I|J|	     |A|B|C|D|E|F|G|H|I|J|			" << info2 << endl;
	for (int i = 0; i < columns; i++)
	{
		cout << "  " << i <<" ";
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
		cout << "	   " << i << " ";
		for (int j = 0; j < rows; j++)
		{
			if (j + 1 != rows)
			{
				cout << "|" << shotgrid[i][j];
			}
			else
			{
				cout << "|" << shotgrid[i][j] << "|";
			}
		}
		cout << endl;
	}
	cout << endl;
	Board::legend();
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
			shotgrid[i][j] = ' ';
		}
	}

}

void Board::legend()
{
	cout << " ---Legend---" << endl;
	cout << " O ship" << endl;
	cout << " $ hited ship" << endl;
	cout << " X missed atack" << endl;
}

int Board::getrows()
{
	return rows;
}

int Board::getcolumns()
{
	return columns;
}




