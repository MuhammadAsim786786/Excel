/*#include <iostream>
using namespace std;

struct NewNode {
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
    }
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

    void insertAboveRow() {
        
        NewNode* rowAdded[5];
        for (int i = 0; i < 5; i++) {
            rowAdded[i] = new NewNode('*'); 
        }

    
        NewNode* currentActiveRow = currentActive;
        while (currentActiveRow->left) {
            currentActiveRow = currentActiveRow->left;
        }

        for (int i = 0; i < 5; i++) {

            rowAdded[i]->down = currentActiveRow; 
            if (currentActiveRow) {
                currentActiveRow->up = rowAdded[i];
            }
    
            currentActiveRow = currentActiveRow->right;
        }

        for (int i = 0; i < 5; i++) {
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

};

int main() {
    Excel miniExcel;
    miniExcel.displayGrid(); // Show initial grid
    miniExcel.insertAboveRow();

    system("cls");
    miniExcel.displayGrid(); // Show updated grid
    return 0;
}*/
