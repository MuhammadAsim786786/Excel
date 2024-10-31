#include <iostream>
#include "LinkedListAll.h"
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

void createSheet(Excel& miniExcel)
{
    miniExcel.printSheet();
}

indices getIndex()
{
    int rpos, cpos;
    getRowColbyLeftClick(rpos, cpos);

    int cellWidth = 6;
    int cellHeight = 1;

    indices A;
    A.row = rpos / cellHeight;
    A.col = cpos / cellWidth;
    return A;
}

void enterValueInCell(Excel& miniExcel)
{
    indices A = getIndex();
    int value;
    cout << "Enter value for cell (" << A.row << ", " << A.col << "): ";
    cin >> value;
    miniExcel.setValueAt(A.row, A.col, value);
}

int main()
{
    Excel miniExcel;
    int choice;
    do
    {
        cout << "\n=== Excel Application Menu ===\n";
        cout << "1. Create a new sheet\n";
        cout << "2. Load an existing sheet (not implemented yet)\n";
        cout << "3. Enter value in a cell\n";
        cout << "4. Print sheet\n";
        cout << "5. Insert row above\n";
        cout << "6. Insert row below\n";
        cout << "7. Insert column to the left\n";
        cout << "8. Insert column to the right\n";
        cout << "9. Remove row\n";
        cout << "10. Remove column\n";
        cout << "11. Clear row\n";
        cout << "12. Clear column\n";
        cout << "13. Get range sum\n";
        cout << "14. Get range average\n";
        cout << "15. Get range min\n";
        cout << "16. Get range max\n";
        cout << "17. Copy range\n";
        cout << "18. Paste range\n";
        cout << "19. Cut range\n";
        cout << "20. Save sheet\n";
        cout << "21. Exit\n";
        cout << "Enter your choice: ";

        cin.clear();
        cin >> choice;

        indices start, end;
        int value;
        switch (choice)
        {
        case 1:
            createSheet(miniExcel);
            break;
        case 3:
            system("cls");
            miniExcel.printSheet();
            enterValueInCell(miniExcel);
            system("cls");
            miniExcel.printSheet();
            break;
        case 4:
            system("cls");
            miniExcel.printSheet();
            break;
        case 5:
            miniExcel.insertAboveRow();
            break;
        case 6:
            miniExcel.insertDownRow();
            break;
        case 7:
            miniExcel.insertColumnLeft();
            break;
        case 8:
            miniExcel.insertColuuumnRight();
            break;
        case 9:
            start = getIndex();
            miniExcel.calculateCurrent(start);
            miniExcel.RemoveRow();
            break;
        case 10:
            start = getIndex();
            miniExcel.calculateCurrent(start);
            miniExcel.RemoveColumn();
            break;
        case 11:
            start = getIndex();
            miniExcel.calculateCurrent(start);
            miniExcel.clearRow();
            miniExcel.printSheet();
            break;
        case 12:
            start = getIndex();
            miniExcel.calculateCurrent(start);
            miniExcel.clearColumn();
            miniExcel.printSheet();
            break;
        case 13:
            system("cls");
            miniExcel.printSheet();
            start = getIndex();
            end = getIndex();
            cout << "Range Sum: " << miniExcel.getRangeSum(start, end) << endl;
            break;
        case 14:
            system("cls");
            miniExcel.printSheet();
            start = getIndex();
            end = getIndex();
            cout << "Range Average: " << miniExcel.getAverage(start, end) << endl;
            break;
        case 15:
            start = getIndex();
            end = getIndex();
            cout << "Range Min: " << miniExcel.getRangeMin(start, end) << endl;
            break;
        case 16:
            start = getIndex();
            end = getIndex();
            cout << "Range Max: " << miniExcel.getRangeMax(start, end) << endl;
            break;
        case 17:
            start = getIndex();
            end = getIndex();
            miniExcel.copy(start, end);
            break;
        case 18:
            start = getIndex();
            end = getIndex();
            miniExcel.paste(start, end);
            break;
        case 19:
            start = getIndex();
            end = getIndex();
            miniExcel.cut(start, end);
            break;
        case 20:
            miniExcel.saveSheet("TextFile1.txt");
            cout << "Sheet saved as TextFile1.txt\n";
            break;
        case 21:
            cout << "Exiting the program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 21);
    return 0;
}
