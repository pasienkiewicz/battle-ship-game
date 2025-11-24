#include "Board.h"
#include "IO.h"

void Board::displayInfo(string message)
{
	if (infoCounter == 12)
	{
		for (string &i : info)
			i = "";
		infoCounter = 0;
	}
	info[infoCounter] = message;
	infoCounter++;
}

void Board::drawTwoBoards(Board &ai, string message)
{
	IO::clearScreen();
	cout << "	 Ship Grid			  Attack Grid		" << info[0] << endl;
	cout << "    |A|B|C|D|E|F|G|H|I|J|	     |A|B|C|D|E|F|G|H|I|J|	" << info[1] << endl;
	for (int i = 0; i < columns; i++)
	{
		cout << "  " << i << " ";
		for (int j = 0; j < rows; j++)
		{
			if (j + 1 != rows)
			{
				IO::resetColor();
				cout << "|";
				setShipGridColor(i, j);
				cout << shipgrid[0][i][j];
			}
			else
			{
				IO::resetColor();
				cout << "|";
				setShipGridColor(i, j);
				cout << shipgrid[0][i][j];
				IO::resetColor();
				cout << "|";
			}
		}
		cout << "	   " << i << " ";
		for (int j = 0; j < rows; j++)
		{
			if (j + 1 != rows)
			{
				IO::resetColor();
				cout << "|";
				setShotGridColor(ai, i, j);
				cout << shotgrid[i][j];
			}
			else
			{
				IO::resetColor();
				cout << "|";
				setShotGridColor(ai, i, j);
				cout << shotgrid[i][j];
				IO::resetColor();
				cout << "|";
			}
		}
		cout << "	" << info[i + 2] << endl;
	}

	cout << endl;
	Board::legend();
	if (!message.empty())
	{
		IO::setGreen();
		cout << endl;
		cout << message;
		cout << endl;
		IO::resetColor();
	}
}

void Board::drawSigleBoard()
{
	IO::clearScreen();
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
	std::cout << " ---Legend---" << std::endl;
	IO::setGreen();
	std::cout << " O ";
	IO::resetColor();
	std::cout << "ship" << std::endl;
	IO::setYellow();
	std::cout << " $ ";
	IO::resetColor();
	std::cout << "hit ship" << std::endl;
	IO::setRed();
	std::cout << " $ ";
	IO::resetColor();
	std::cout << "sunk ship" << std::endl;
	IO::setYellow();
	std::cout << " X ";
	IO::resetColor();
	std::cout << "missed attack" << std::endl;
}

void Board::setShipGridColor(int i, int j)
{
	if (shipgrid[0][i][j] == '$' && count(numberOfShipTypes.begin(), numberOfShipTypes.end(), shipgrid[2][i][j]) == 0)
	{
		IO::setRed();
	}
	else if (shipgrid[0][i][j] == '$')
	{
		IO::setYellow();
	}
	else if (shipgrid[0][i][j] == 'O')
	{
		IO::setGreen();
	}
	else if (shipgrid[0][i][j] == 'X')
	{
		IO::setYellow();
	}
	else
	{
		IO::resetColor();
	}
}

void Board::setShotGridColor(Board &ai, int i, int j)
{
	if (shotgrid[i][j] == '$' && count(ai.numberOfShipTypes.begin(), ai.numberOfShipTypes.end(), ai.shipgrid[2][i][j]) == 0)
	{
		IO::setRed();
	}
	else if (shotgrid[i][j] == '$')
	{
		IO::setYellow();
	}
	else if (shotgrid[i][j] == 'X')
	{
		IO::setYellow();
	}
	else
	{
		IO::resetColor();
	}
}

int Board::getrows()
{
	return rows;
}

int Board::getcolumns()
{
	return columns;
}
