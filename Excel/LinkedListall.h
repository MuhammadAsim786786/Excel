#pragma once
#include<iostream>
using namespace std;
static  int noOfNodes = 0;

struct NewNode {
    int data; // Change from char to int
    NewNode* right;
    NewNode* left;
    NewNode* up;
    NewNode* down;

    NewNode(char initial) {
        if (initial == ' ' || initial == '\0') {
            data = 0; // Assign a default value for empty
        }
        else {
            data = initial - '0'; // Convert char to int
        }
        right = nullptr;
        left = nullptr;
        up = nullptr;
        down = nullptr;
    }
};
struct indices {
    int row;
    int col;
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
                grid[i][j] = new NewNode('1');
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
                if (c != nullptr) {
                    cout << "[ " << (c->data != ' ' ? c->data : ' ') << " ] ";
                }
                else {
                    cout << "[ NULL ] ";
                }
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
        if (!currentActive) return;
        int size = getcolLength();
        NewNode** rowAdded = new NewNode * [size];

        // Step 1: Initialize each cell in the new row
        for (int i = 0; i < size; i++) {
            rowAdded[i] = new NewNode(' ');
        }

        // Step 2: Traverse to the leftmost cell of the current active row
        NewNode* currentActiveRow = currentActive;
        while (currentActiveRow && currentActiveRow->left) {
            currentActiveRow = currentActiveRow->left;
        }

        // Step 3: Link each cell in the new row with the current row
        for (int i = 0; i < size; i++) {
            // Link downwards to the current active row
            rowAdded[i]->down = currentActiveRow;
            if (currentActiveRow) {
                currentActiveRow->up = rowAdded[i];
                currentActiveRow = currentActiveRow->right;
            }

            // Link horizontally within the new row
            if (i > 0) {
                rowAdded[i]->left = rowAdded[i - 1];
                rowAdded[i - 1]->right = rowAdded[i];
            }
        }

        // Step 4: Update the 'first' pointer if we are adding at the top
        if (currentActive == first) {
            first = rowAdded[0];
        }

        delete[] rowAdded; // Clean up temporary array to avoid memory leak
    }
    void insertDownRow() {
        if (!currentActive) return;
        int size = getcolLength();
        NewNode** rowAdded = new NewNode * [size];
        for (int i = 0; i < 5; i++) {
            rowAdded[i] = new NewNode(' ');
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
        if (!currentActive) return;
        int size = getRowLength();
        NewNode** columnAdded = new NewNode * [size];

        for (int i = 0; i < size; i++) {
            columnAdded[i] = new NewNode(' ');
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
        if (!currentActive) return;
		int size = getRowLength();
        NewNode** columnAdded = new NewNode * [size];
        for (int i = 0; i < size; i++) {
            columnAdded[i] = new NewNode(' ');
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
    void RemoveRow() {
        if (!currentActive) return;  

        NewNode* currentRow = currentActive;
        NewNode* prevRow = nullptr;
        NewNode* nextFirst = nullptr;

        while (currentRow->left) {
            currentRow = currentRow->left;
        }

        if (!currentRow->down) { 
            while (currentRow->right) {
                prevRow = currentRow->up;
                currentRow = currentRow->right;

                if (prevRow) {
                    prevRow = prevRow->right;
                }
            }

            if (prevRow) {
                prevRow->down = nullptr;
            }
        }
        else {
            nextFirst = currentRow->down; 
            while (currentRow) {
                NewNode* nextCell = currentRow->right;

                if (currentRow->up) {
                    currentRow->up->down = currentRow->down;
                }
                if (currentRow->down) {
                    currentRow->down->up = currentRow->up;
                }

                delete currentRow;
                currentRow = nextCell;
            }
        }

        
        first = nextFirst;

        currentActive = first;
    }
    
    void RemoveColumn() {
        if (!currentActive) return; 

        NewNode* columnNode = currentActive;

        while (columnNode->up) {
            columnNode = columnNode->up;
        }

        if (columnNode == first) {
            if (first->right) {
                first = first->right;
            }
            else {
                first = nullptr;
            }
        }

        while (columnNode) {
            NewNode* nextNode = columnNode->down;

            if (columnNode->left) {
                columnNode->left->right = columnNode->right;
            }

            if (columnNode->right) {
                columnNode->right->left = columnNode->left;
            }

            if (columnNode == currentActive) {
                if (currentActive->left) {
                    currentActive = currentActive->left;
                }
                else if (currentActive->right) {
                    currentActive = currentActive->right;
                }
                else {
                    currentActive = nullptr;
                }
            }

            delete columnNode;
            columnNode = nextNode;
        }
    }

    void clearRow() {
        if (currentActive == nullptr) return;  
        NewNode* currentRow = currentActive;

        while (currentRow && currentRow->left) {
            currentRow = currentRow->left;
        }

        // CLEARING     
        while (currentRow) {
            currentRow->data = ' ';
            currentRow = currentRow->right;
        }
    }
    void clearColumn() {
        if (currentActive == nullptr) return;
        NewNode* columnNode = currentActive;
        while (columnNode->up && columnNode) {
			columnNode = columnNode->up;
        }
		// CLEARING
		while (columnNode) {
			columnNode->data = ' ';
			columnNode = columnNode->down;
        }
    }
    int getRangeSum(indices start, indices end) {
        noOfNodes = 0;
        int rowLength = getRowLength();
        int colLength = getcolLength();

        if (start.row >= rowLength || start.col >= colLength ||
            end.row >= rowLength || end.col >= colLength) {
            cout << "You entered invalid indices. Exiting......." << endl;
            return 0;
        }

        NewNode* firstNode = first;
        for (int i = 0; i < start.row; i++) {
            if (firstNode) {
                firstNode = firstNode->down;
            }
        }

        NewNode* currentNode = firstNode;
        for (int j = 0; j < start.col; j++) {
            if (currentNode) {
                currentNode = currentNode->right;
            }
        }

        int sum = 0;
       

        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                noOfNodes++;
                sum += rowNode->data;
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }

        
        
        return sum;
    }

    float getAverage(indices A,indices B) {
        int sum = getRangeSum(A, B);
        int average = sum / noOfNodes;
        noOfNodes = 0;
		return average;
    }
};


