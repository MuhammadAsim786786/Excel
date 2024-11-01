#pragma once
#include<iostream>
#include<queue>
#include<sstream>
#include<climits>
#include<fstream>
#include<string>
using namespace std;
static  int noOfNodes = 0;

static queue<int> copyQueue;
static queue<int> pasteQueue;



string customColor(int r, int g, int b) {
    stringstream ss;
    ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return ss.str();
}


#define RESET "\033[0m"


struct NewNode {
    int data;
    NewNode* right;
    NewNode* left;
    NewNode* up;
    NewNode* down;

    NewNode(int initial) {
   
        data = initial;
        right = nullptr;
        left = nullptr;
        up = nullptr;
        down = nullptr;
    }
};


int currentR = 255, currentG = 255, currentB = 255;


void setColor(int r, int g, int b) {
    currentR = r;
    currentG = g;
    currentB = b;
}
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
                grid[i][j] = new NewNode(INT_MAX);
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

    void printSheet() {
        NewNode* row = first;
        while (row) {
            NewNode* c = row;
            while (c) {
                if (c != nullptr) {
                    cout << customColor(currentR, currentG, currentB);
                    if (c->data == INT_MAX) {
                        cout << "[ "<<"  "<<" ]";
                    }
                    else{
                    cout << "[ " << (c->data != ' ' ? c->data : ' ') << " ] ";

                    }
                    cout << RESET;
                }
                else {
                    cout << "[ Em ] ";
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

    
        for (int i = 0; i < size; i++) {
            rowAdded[i] = new NewNode(INT_MAX);
        }


        NewNode* currentActiveRow = currentActive;
        while (currentActiveRow && currentActiveRow->left) {
            currentActiveRow = currentActiveRow->left;
        }


        for (int i = 0; i < size; i++) {

            rowAdded[i]->down = currentActiveRow;
            if (currentActiveRow) {
                currentActiveRow->up = rowAdded[i];
                currentActiveRow = currentActiveRow->right;
            }


            if (i > 0) {
                rowAdded[i]->left = rowAdded[i - 1];
                rowAdded[i - 1]->right = rowAdded[i];
            }
        }

        if (currentActive == first) {
            first = rowAdded[0];
        }

        delete[] rowAdded; 
    }
    void insertDownRow() {
        if (!currentActive) return;
        int size = getcolLength();
        NewNode** rowAdded = new NewNode * [size];
        for (int i = 0; i < 5; i++) {
            rowAdded[i] = new NewNode(INT_MAX);
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
            columnAdded[i] = new NewNode(INT_MAX);
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

      
        while (currentRow) {
            currentRow->data = INT_MAX;
            currentRow = currentRow->right;
        }
    }
    void calculateCurrent(indices Cell) {
        if (currentActive == nullptr) return;
        int rowLength = getRowLength();
        int colLength = getcolLength();

        if (Cell.row >= rowLength || Cell.col >= colLength) {
            cout << "You entered invalid indices. Exiting......." << endl;
            return;
        }

        NewNode* firstNode = first;
        for (int i = 0; i < Cell.row; i++) {
            if (firstNode) {
                firstNode = firstNode->down;
            }
        }

        NewNode* currentNode = firstNode;
        for (int j = 0; j < Cell.col; j++) {
            if (currentNode) {
                currentNode = currentNode->right;
            }
        }

    
        if (currentNode) {
            currentActive = currentNode;
            cout << "Current active cell set to (" << Cell.row << ", " << Cell.col << ") with value: ";
            if (currentNode->data == INT_MAX) {
                cout << "Empty" << endl;
            }
            else {
                cout << currentNode->data << endl;
            }
        }
        else {
            cout << "Cell at (" << Cell.row << ", " << Cell.col << ") is out of bounds." << endl;
        }
    }

    void clearColumn() {
        if (currentActive == nullptr) return;
        NewNode* columnNode = currentActive;
        while (columnNode->up && columnNode) {
			columnNode = columnNode->up;
        }

		while (columnNode) {
			columnNode->data = INT_MAX;
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
                
                if(rowNode->data==INT_MAX){
                    sum += 0;
                }
                else {
                    noOfNodes++;
                    sum += rowNode->data;
                }
                
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
    int getRangeCount(indices start, indices end) {
        int count = 0;
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

        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                if (rowNode->data != ' ') { 
                    count++;
                }
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }

        return count;
    }
    
    
    int getRangeMin(indices start, indices end) {
        int minVal = INT_MAX;
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

        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                if (rowNode->data !=INT_MAX) { 
                    minVal = min(minVal, rowNode->data); 
                }
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }

        if (minVal != INT_MAX) {
            return minVal;
        }
        else {
            return 0; 
        }
    }
    int getRangeMax(indices start, indices end) {
        int maxVal = INT_MIN;
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

        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                if (rowNode->data != ' ') { 
                    maxVal = max(maxVal, rowNode->data); 
                }
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }
        if (maxVal != INT_MIN) {
			return maxVal;
        }
        else {
            return 0; 
        }
    }
    
    void copy(indices start, indices end) {
        while (!copyQueue.empty()) {
            copyQueue.pop();
        }
        noOfNodes = 0;
        int rowLength = getRowLength();
        int colLength = getcolLength();

        if (start.row >= rowLength || start.col >= colLength ||
            end.row >= rowLength || end.col >= colLength) {
            cout << "You entered invalid indices. Exiting......." << endl;
            return;
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

        


        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                noOfNodes++;
                copyQueue.push(rowNode->data);
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }
    }
    void paste(indices start, indices end) {
        while (!pasteQueue.empty()) {
            pasteQueue.pop();
        }
        if (copyQueue.empty()) {
            cout << "No data to paste. Copy data first." << endl;
            return;
        }
        noOfNodes = 0;
        int rowLength = getRowLength();
        int colLength = getcolLength();

        if (start.row >= rowLength || start.col >= colLength ||
            end.row >= rowLength || end.col >= colLength) {
            cout << "You entered invalid indices. Exiting......." << endl;
            return;
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

        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                noOfNodes++;
                rowNode->data=copyQueue.front();
                copyQueue.pop();
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }
    }
   
    
    void cut(indices start, indices end) {
        while (!copyQueue.empty()) {
            copyQueue.pop();
        }
        noOfNodes = 0;
        int rowLength = getRowLength();
        int colLength = getcolLength();

        if (start.row >= rowLength || start.col >= colLength ||
            end.row >= rowLength || end.col >= colLength) {
            cout << "You entered invalid indices. Exiting......." << endl;
            return;
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

        for (int i = start.row; i <= end.row && currentNode; i++) {
            NewNode* rowNode = currentNode;
            for (int j = start.col; j <= end.col && rowNode; j++) {
                noOfNodes++;
                copyQueue.push(rowNode->data);
                rowNode->data = INT_MAX; 
                rowNode = rowNode->right;
            }
            currentNode = currentNode->down;
        }
    }
    void saveSheet(const string& TextFile1) {
        ofstream out(TextFile1);
        if (!out) {
            cout << "Error opening file for saving." << endl;
            return;
        }

        if (first == nullptr) {
            cout << "Sheet is empty" << endl;
            return;
        }

        NewNode* row = first;
        while (row) {
            NewNode* col = row;
            while (col) {
                if (col->data == INT_MAX) {
                    out << "[   ] "; 
                }
                else {
                    out << "[ " << col->data << " ] ";
                }
                col = col->right;
            }
            out << "\n";
            row = row->down;
        }

        cout << "Sheet saved to " << TextFile1 << endl;
    }

    void setValueAt(int row, int col, int value) {
        int validRowSize = getRowLength();
		int validColSize = getcolLength();
        if (row >= validRowSize || col >= validColSize || row < 0 || col < 0) {
            cout << "Invalid cell position." << endl;
            return;
        }

        NewNode* target = first;
        for (int i = 0; i < row; i++) {
            if (target) target = target->down;
        }
        for (int j = 0; j < col; j++) {
            if (target) target = target->right;
        }

        if (target) {
            target->data = value;
        }
        else {
            cout << "Cell not found." << endl;
        }
    }
    


    void saveSheetAsHtml(const string& filename) {
        ofstream out(filename);
        if (!out) {
            cout << "Error opening file for saving HTML." << endl;
            return;
        }

        if (first == nullptr) {
            cout << "Sheet is empty" << endl;
            return;
        }

       
        out << "<!DOCTYPE html>\n<html>\n<head>\n";
        out << "<style>\n";
        out << "body { font-family: Arial, sans-serif; background-image: url('https://www.bing.com/images/search?view=detailV2&ccid=iS8VJpKG&id=F1263421507C376D7E8C6B74BB6F4B81D1EB0342&thid=OIP.iS8VJpKGtOa6_yrpJCplEwHaEt&mediaurl=https%3A%2F%2Fstatic.vecteezy.com%2Fsystem%2Fresources%2Fpreviews%2F005%2F182%2F612%2Foriginal%2Fgreen-abstract-geometric-shape-background-free-vector.jpg&cdnurl=https%3A%2F%2Fth.bing.com%2Fth%2Fid%2FR.892f15269286b4e6baff2ae9242a6513%3Frik%3DQgPr0YFLb7t0aw%26pid%3DImgRaw%26r%3D0&exph=1220&expw=1920&q=background+images&simid=608008396086520768&FORM=IRPRST&ck=AC46CDFC8DE41D62951C44A00B88C578&selectedIndex=18&itb=0&cw=914&ch=941&ajaxhist=0&ajaxserp=0'); background-size: cover; margin: 0; padding: 20px; }\n";
        out << "h2 { color: #444; text-align: center; margin-top: 20px; }\n";
        out << "table { border-collapse: collapse; width: 80%; margin: 0 auto; box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1); }\n";
        out << "table, th, td { border: 2px solid #555; }\n";
        out << "th, td { padding: 15px; text-align: center; font-size: 18px; }\n";
        out << "th { background-color: #4CAF50; color: white; font-weight: bold; }\n";
        out << "td { background-color: rgba(255, 255, 255, 0.9); color: #333; }\n";
        out << "td.empty-cell { background-color: rgba(240, 240, 240, 0.9); color: #aaa; }\n";
        out << "tr:nth-child(even) td { background-color: rgba(255, 255, 255, 0.8); }\n";
        out << "</style>\n";
        out << "<title>Sheet</title>\n";
        out << "</head>\n<body>\n";

    
        out << "<h2>Excel Sheet</h2>\n";
        out << "<table>\n";

   
        NewNode* row = first;
        while (row) {
            out << "<tr>\n";
            NewNode* col = row;
            while (col) {
                if (col->data == INT_MAX) {
                    out << "<td class='empty-cell'>&nbsp;</td>";
                }
                else {
                    out << "<td>" << col->data << "</td>";
                }
                col = col->right;
            }
            out << "</tr>\n";
            row = row->down;
        }
        out << "</table>\n";

 
        out << "</body>\n</html>";

        cout << "Sheet saved to HTML file: " << filename << endl;
    }
    void InsertCellByRightShift() {
        if (!currentActive) {
            cout << "No active cell to insert by right shift." << endl;
            return;
        }

        NewNode* tempo = new NewNode(INT_MAX); 
        tempo->data = INT_MAX; 

     
        tempo->right = currentActive->right;
        currentActive->right = tempo;

     
        NewNode* temp = currentActive;
        while (temp->right) {
            swap(temp->data, temp->right->data);
            temp = temp->right;
        }

        cout << "Cell inserted by right shift." << endl;
    }

    void InsertCellByDownShift() {
        if (!currentActive) {
            cout << "No active cell to insert by down shift." << endl;
            return;
        }

        NewNode* tempo = new NewNode(INT_MAX);
    


        tempo->down = currentActive->down;
        currentActive->down = tempo;

    
        NewNode* temp = currentActive;
        while (temp->down) {
            swap(temp->data, temp->down->data);
            temp = temp->down;
        }

        cout << "Cell inserted by down shift." << endl;
    }

    void DeleteCellByLeftShift() {
        if (!currentActive || !currentActive->right) {
            cout << "No cell to delete by left shift." << endl;
            return;
        }

  
        NewNode* temp = currentActive;
        while (temp->right) {
            temp->data = temp->right->data;
            if (!temp->right->right) { 
                delete temp->right;
                temp->right = nullptr;
                break;
            }
            temp = temp->right;
        }

        cout << "Cell deleted by left shift." << endl;
    }

    void DeleteCellByUpShift() {
        if (!currentActive || !currentActive->down) {
            cout << "No cell to delete by up shift." << endl;
            return;
        }

  
        NewNode* temp = currentActive;
        while (temp->down) {
            temp->data = temp->down->data;
            if (!temp->down->down) { 
                delete temp->down;
                temp->down = nullptr;
                break;
            }
            temp = temp->down;
        }

        cout << "Cell deleted by up shift." << endl;
    }


};


