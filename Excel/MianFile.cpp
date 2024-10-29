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
	
	
		/*LinkingList list;

	
		cout << "Inserting elements at the front:" << endl;
		list.insertAtFront(10);
		list.insertAtFront(20);
		list.insertAtFront(30);

		cout << "Inserting elements at the back:" << endl;
		list.inserAtBack(40);
		list.inserAtBack(50);


		cout << "Displaying list after insertions:" << endl;
		list.displayList(); 


		cout << "Size of the list: " << list.size() << endl;


		cout << "Testing forward iteration using the iterator in a for loop:" << endl;
		for (iterating it(list.head); it.isValid(); ++it) {
			cout << *it << " ";
		}
		cout << endl;

		
		cout << "Testing backward iteration using the iterator in a for loop:" << endl;
		for (iterating it(list.tail); it.isValid(); --it) {
			cout << *it << " ";
		}
		cout << endl;

		
		cout << "Deleting the first element:" << endl;
		list.deleteAtFirst();
		list.displayList(); 

		
		cout << "Is the list empty? " << (list.isEmpty() ? "Yes" : "No") << endl;
		*/
	Excel miniExcel;
	miniExcel.displayGrid();
	miniExcel.RemoveColumn();
	miniExcel.insertDownRow();
	miniExcel.RemoveColumn();
	miniExcel.RemoveRow();
	miniExcel.clearRow();
	miniExcel.clearColumn();




	system("cls");
	miniExcel.displayGrid();
	return 0;
}
