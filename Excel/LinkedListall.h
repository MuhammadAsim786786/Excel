#pragma once
#include<iostream>
using namespace std;

struct NewNode
{
    char data;
    NewNode* right;
    NewNode* left;
    NewNode* up;
    NewNode* down;
    NewNode(char initial) {
        data = initial;
        right = nullptr;
        left = nullptr;
        up = nullptr;
        down = nullptr;
    };
};

class Excel {
public:
    NewNode* first;
    NewNode* currentActive;
    NewNode* grid[5][5];
public:
    Excel() {
       
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                grid[i][j] = new NewNode('*');
            }
        }
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (i > 0) {
                    grid[i][j]->up = grid[i - 1][j];
                }
                if (i < 4) {
                    grid[i][j]->down = grid[i + 1][j];
                }
                if (j > 0) {
                    grid[i][j]->left = grid[i][j - 1];
                }
                if (j < 4) {
                    grid[i][j]->right = grid[i][j + 1];
                }
            }
        }
        first = grid[0][0];
        currentActive = first;
    }

    void displayGrid() {
        NewNode* row = first;
        while (row) {
            NewNode* c = row;
            while (c) {
                cout << c->data << " ";
                c = c->right;
            }
            cout << endl;
            row = row->down;
        }
    }
    int getcolLength() {
        int size = 0;
        NewNode* node = first;
		while (node) {
			size++;
			node = node->right;
		}
		return size;
	}

    void insertAboveRow() {
        int size = getcolLength();
		NewNode** rowAdded = new NewNode * [size];
        for (int i = 0; i < size; i++) {
            rowAdded[i] = new NewNode('*');
        }


        NewNode* currentActiveRow = currentActive;
        while (currentActiveRow->left) {
            currentActiveRow = currentActiveRow->left;
        }

        for (int i = 0; i < size; i++) {

            rowAdded[i]->down = currentActiveRow;
            if (currentActiveRow) {
                currentActiveRow->up = rowAdded[i];
            }

            currentActiveRow = currentActiveRow->right;
        }

        for (int i = 0; i < size; i++) {
            if (i > 0) {
                rowAdded[i]->left = rowAdded[i - 1];
                rowAdded[i - 1]->right = rowAdded[i];
            }
        }

        if (first == currentActive) {
            first = rowAdded[0];
        }
        else {

            NewNode* prevRow = first;
            while (prevRow->down) {
                prevRow = prevRow->down;
            }
            prevRow->down = rowAdded[0];
            rowAdded[0]->up = prevRow;
        }
    }
    void insertDownRow() {
        int size = getcolLength();
        NewNode** rowAdded = new NewNode * [size];
        for (int i = 0; i < 5; i++) {
            rowAdded[i] = new NewNode('*');
        }

        NewNode* currentActiveRow = currentActive;
        while (currentActiveRow->left) {
            currentActiveRow = currentActiveRow->left;
        }

        for (int i = 0; i < size; i++) {
            rowAdded[i]->up = currentActiveRow;
            if (currentActiveRow) {
                rowAdded[i]->down = currentActiveRow->down;  
                if (currentActiveRow->down) {
                    currentActiveRow->down->up = rowAdded[i];  
                }
                currentActiveRow->down = rowAdded[i];
            }
            currentActiveRow = currentActiveRow->right;
        }

        for (int i = 0; i < size; i++) {
            if (i > 0) {
                rowAdded[i]->left = rowAdded[i - 1];
                rowAdded[i - 1]->right = rowAdded[i];
            }
        }
    }
    int getRowLength() {
        int size = 0;
		NewNode* node = first;
		while (node) {
			size++;
            node = node->down;
		}
        return size;
	}
    void insertColumnLeft() {
        int size = getRowLength();
        NewNode** columnAdded = new NewNode * [size];

        for (int i = 0; i < size; i++) {
            columnAdded[i] = new NewNode('*');
        }

        NewNode* currentActiveColumnTop = currentActive;
        NewNode* currentActiveColumn = currentActive;

        while (currentActiveColumnTop->up) {
            currentActiveColumnTop = currentActiveColumnTop->up;
            currentActiveColumn = currentActiveColumn->up;
        }

        for (int i = 0; i < size; i++) {
            currentActiveColumnTop->left = columnAdded[i];
            columnAdded[i]->right = currentActiveColumnTop;

            if (i > 0) {
                columnAdded[i]->up = columnAdded[i - 1];
                columnAdded[i - 1]->down = columnAdded[i];
            }

            if (currentActiveColumnTop->down) {
                currentActiveColumnTop = currentActiveColumnTop->down;
            }
        }

        if (first == currentActiveColumn) {
            first = columnAdded[0];
        }
    }

    
    void insertColuuumnRight() {
		int size = getRowLength();
        NewNode** columnAdded = new NewNode * [size];
        for (int i = 0; i < size; i++) {
            columnAdded[i] = new NewNode('*');
        }

        NewNode* currentActiveColumn = currentActive;
        NewNode* currentActiveColumnTop = currentActive;

        while (currentActiveColumnTop->up) {
            currentActiveColumnTop = currentActiveColumnTop->up;
        }

        if (currentActiveColumnTop->right == nullptr) {
            for (int i = 0; i < size; i++) {
                currentActiveColumnTop->right = columnAdded[i];
                columnAdded[i]->left = currentActiveColumnTop;

                currentActiveColumnTop = currentActiveColumnTop->down;
                if (i < size-1) {
                    columnAdded[i]->down = columnAdded[i + 1];
                    columnAdded[i + 1]->up = columnAdded[i];
                }
            }
        }
        else {
            NewNode* existingRightColumn = currentActiveColumnTop->right;

            for (int i = 0; i < size; i++) {
                currentActiveColumnTop->right = columnAdded[i];
                columnAdded[i]->left = currentActiveColumnTop;

                columnAdded[i]->right = existingRightColumn;
                existingRightColumn->left = columnAdded[i];

                currentActiveColumnTop = currentActiveColumnTop->down;
                existingRightColumn = existingRightColumn->down;
                if (i < size-1) {
                    columnAdded[i]->down = columnAdded[i + 1];
                    columnAdded[i + 1]->up = columnAdded[i];
                }
            }
        }
    }

   
};


