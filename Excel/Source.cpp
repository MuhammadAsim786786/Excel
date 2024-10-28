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


/*
void insertAtFront(int value) {
    if (Dabba == nullptr) {
        Dabba = new NewNode();
        Dabba->data = value;
        Dabba->next = nullptr;
        Dabba->prev = nullptr;
        this->head = Dabba;
        this->tail = Dabba;
    }
    else {
        NewNode* TempDabba = new NewNode();
        TempDabba->data = value;
        TempDabba->next = head;
        TempDabba->prev = nullptr;
        this->head = TempDabba;


    }
}
void inserAtBack(int value) {
    if (Dabba == nullptr) {
        Dabba = new NewNode();
        Dabba->data = value;
        Dabba->next = nullptr;
        Dabba->prev = nullptr;
        this->head = Dabba;
        this->tail = Dabba;
    }
    else {
        NewNode* TempDabba = new NewNode;
        TempDabba->data = value;
        TempDabba->next = nullptr;
        TempDabba->prev = tail;
        tail->next = TempDabba;
        tail = TempDabba;
    }
}
void deleteAtFirst() {
    if (Dabba == nullptr) {
        cout << "List already empty." << endl;
    }
    delete[] head->prev;

    head = head->next;
    head->prev = nullptr;
}
bool isEmpty() {
    return Dabba == nullptr;
}
int size() {
    NewNode* TempDabba = head;
    int size = 0;
    while (TempDabba->next != nullptr) {
        size++;
        TempDabba = TempDabba->next;
    }
    size++;
    return size;
}
void displayList() {
    NewNode* TempDabba = head;

    while (TempDabba->next != nullptr) {
        cout << TempDabba->data << " ";
        TempDabba = TempDabba->next;
    }
    cout << TempDabba->data << " " << endl;
}

};*/
/*
class iterating {
private:
    NewNode* Active;

public:
    iterating(NewNode* Temp) {
        this->Active = Temp;
    }

    int& operator*() {
        return Active->data;
    }

    iterating& operator++() {
        if (Active != nullptr) {
            Active = Active->next;
        }
        return *this;
    }

    iterating& operator--() {
        if (Active != nullptr) {
            Active = Active->prev;
        }
        return *this;
    }

    bool isValid() {
        return Active != nullptr;
    }
};
*/



