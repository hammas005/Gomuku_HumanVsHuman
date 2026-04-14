#include<iostream>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<conio.h>
#include<math.h>

using namespace std;
#define MAX 20

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void color(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, k);
}

void Init(char B[][19], char Ss[], int& NOP, int& WinC, char Ns[][20], int& Turn)
{
	for (int r = 0; r < 19; r++)
		for (int c = 0; c < 19; c++)
			B[r][c] = '-';
	NOP = 2;
	cout << "Names: ";
	cin >> Ns[0];
	cin >> Ns[1];

	cout << "Symbols: ";
	cin >> Ss[0] >> Ss[1];
	WinC = 5;

	Turn = rand() % 2; 
}

void BoardPrint(char B[][19], char Ss[])
{
	system("cls");

	color(14);
	for (int i = 0; i < 19; i++)
	{
		cout << "____";
	}
	cout << "_" << endl;

	for (int r = 0; r < 19; r++)
	{
		for (int c = 0; c < 19; c++)
		{
			color(14);
			cout << "| ";

			if (B[r][c] == '-')
			{
				color(8);
				cout << B[r][c] << " ";
			}
			else if (B[r][c] == Ss[0])
			{
				color(12);
				cout << B[r][c] << " ";
			}
			else if (B[r][c] == Ss[1])
			{
				color(10);
				cout << B[r][c] << " ";
			}
		}
		color(14);
		cout << "|" << endl;
	}

	for (int i = 0; i < 19; i++)
	{
		cout << "|___";
	}
	cout << "|" << endl;

	color(7);
}

void TurnMsg(char Naam[], char sym)
{
	cout << endl<< Naam << "'s turn. Symbol " << sym << endl;
}

void SelectPos(int& r, int& c)
{
	int x, y;
	getRowColbyLeftClick(y, x);

	r = y - 1;
	c = x / 4;

	if (r < 0)
	{
		r = 0;
	}
}

bool isValid(char B[][19], int &r, int &c)
{
	return r < 19 and c < 19 and B[r][c] == '-';
}

void UpdateBoard(char B[][19], int r, int c, char sym)
{
	B[r][c] = sym;
}

void TurnChange(int &Turn, int NOP)
{
	Turn = (Turn + 1) % NOP;
}

bool isDraw(char B[][19])
{
	for (int r = 0; r < 19; r++)
	{
		for (int c = 0; c < 19; c++)
		{
			if (B[r][c] == '-')
			{
				return false;
			}
		}
	}
	return true;
}

bool checkHorizontal(char B[][19], int cr, int cc, int WinC, char sym)
{
	int symCount = 1;
	for (int c = cc + 1; c < 19; c++)
	{
		if (B[cr][c] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	for (int c = cc - 1; c >= 0; c--)
	{
		if (B[cr][c] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	return symCount >= WinC;
}

bool checkVertical(char B[][19], int cr, int cc, int WinC, char sym)
{
	int symCount = 1;
	for (int r = cr + 1; r < 19; r++)
	{
		if (B[r][cc] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	for (int r = cr - 1; r >= 0; r--)
	{
		if (B[r][cc] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	return symCount >= WinC;
}

bool checkDiagonalForward(char B[][19], int cr, int cc, int WinC, char sym)
{
	int symCount = 1;
	for (int i = 1; cr - i >= 0 && cc + i < 19; i++)
	{
		if (B[cr - i][cc + i] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	for (int i = 1; cr + i < 19 && cc - i >= 0; i++)
	{
		if (B[cr + i][cc - i] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	return symCount >= WinC;
}

bool checkDiagonalBackward(char B[][19], int cr, int cc, int WinC, char sym)
{
	int symCount = 1;
	for (int i = 1; cr + i < 19 && cc + i < 19; i++)
	{
		if (B[cr + i][cc + i] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	for (int i = 1; cr - i >= 0 && cc - i >= 0; i++)
	{
		if (B[cr - i][cc - i] == sym)
		{
			symCount++;
		}
		else
		{
			break;
		}
	}
	return symCount >= WinC;
}

bool isWin(char B[][19], int WinC, char sym)
{
	for (int r = 0; r < 19; r++)
	{
		for (int c = 0; c < 19; c++)
		{
			if (B[r][c] == sym)
			{
				if (checkHorizontal(B, r, c, WinC, sym))
				{
					return true;
				}
				if (checkVertical(B, r, c, WinC, sym))
				{
					return true;
				}
				if (checkDiagonalForward(B, r, c, WinC, sym))
				{
					return true;
				}
				if (checkDiagonalBackward(B, r, c, WinC, sym))
				{
					return true;
				}
			}
		}
	}
	return false;
}

int main()
{
	char B[19][19];
	char Ss[2];
	int NOP, WinC, r, c, Turn;
	char Ns[MAX][20];

	Init(B, Ss, NOP, WinC, Ns, Turn);
	BoardPrint(B, Ss);
	do {

		TurnMsg(Ns[Turn], Ss[Turn]);

		do
		{
			SelectPos(r, c);
		} while (!isValid(B, r, c));
		UpdateBoard(B, r, c, Ss[Turn]);
		BoardPrint(B, Ss);
		if (isDraw(B))
		{
			cout << "The game is a draw!" << endl;
			cout << "Press any key to exit..." << endl;
			_getch();
			break;
		}
		if (isWin(B, WinC, Ss[Turn]))
		{
			cout << Ns[Turn] << " Wins!" << endl;
			cout << "Press any key to exit..." << endl;
			_getch();
			break;
		}
		TurnChange(Turn, NOP);
	} while (true);
	return 0;
}

