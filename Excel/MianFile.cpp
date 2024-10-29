#include <iostream>
#include"LinkedListAll.h"
#include <Windows.h>

using namespace std;

#define BLACK 0
#define BROWN 6
#define WHITE 15
#define GREEN 2
#define RED 4
#define LBLUE 9
char sym = -37;

void SetClr(int tcl, int bcl)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (tcl + (bcl * 16)));
}

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
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

void boxDisplay(int cr, int cc, int br, int bc)
{
	for (int r = 0; r < br; r++)
	{
		for (int c = 0; c < bc; c++)
		{
			if (r == 0 || r == br - 1 || c == 0 || c == bc - 1)
			{
				gotoRowCol(cr + r, cc + c);
				cout << sym;
			}
		}
	}
}

void gridDisplay(int width, int height, int rows, int cols)
{
	int bRows = height / rows;
	int bCols = width / cols;
	for (int ri = 0; ri < rows; ri++)
	{
		for (int ci = 0; ci < cols; ci++)
		{
			boxDisplay(ri * bRows, ci * bCols, bRows, bCols);
		}
	}
}


int main()
{/*
	SetClr(WHITE, BLACK);

	int width = 50, height = 12;
	int rows = 3, cols = 10;
	int bRows = height / rows;
	int bCols = width / cols;

	gridDisplay(width, height, rows, cols);

	cout << endl << "Click anywhere to get the cursor position!" << endl;

	while (true)
	{
		int row = 0, col = 0;
		getRowColbyLeftClick(row, col);

		
		int gridRow = row / bRows;
		int gridCol = col / bCols;

	
		system("cls");


		gridDisplay(width, height, rows, cols);

		gotoRowCol(row, col);

	
		if (gridRow < rows && gridCol < cols)
		{
			SetClr(GREEN, BLACK);

			cout << "You clicked on grid row: " << gridRow << " and grid column: " << gridCol << endl;
		}
		else
		{
			SetClr(RED, BLACK);
			cout << "Click was outside the grid!" << endl;
		}
	}*/
	
	
	Excel miniExcel;
	miniExcel.printSheet();
	miniExcel.insertDownRow();
	indices A;
	indices B;
	A.row = 0;
	A.col = 0;
	B.row = 1;
	B.col = 4;
	int sum=miniExcel.getRangeSum(A,B);
	int average = miniExcel.getAverage(A, B);
	cout << average;
	system("cls");
	
	miniExcel.printSheet();
		/*
	system("cls");
	miniExcel.cut(A,B);
	A.row = 2;
	A.col = 0;
	B.row = 3;
	B.col = 4;	
	miniExcel.paste(A, B);
	miniExcel.printSheet();

	miniExcel.RemoveColumn();
	miniExcel.insertDownRow();
	miniExcel.RemoveColumn();
	miniExcel.RemoveRow();
	miniExcel.clearRow();
	miniExcel.clearColumn();
	*/



	
	return 0;
}
