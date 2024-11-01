#pragma once
#include "LinkedListall.h"
class Excel;

class Iterator {
private:
    NewNode* currentActive;
    Excel* sheet;

public:
    
    Iterator(NewNode* startNode, Excel* sheet) {
        this->currentActive = startNode;
		this->sheet = sheet;
    } 

    
    Iterator& operator++() {
        if (currentActive && currentActive->down) {
            currentActive = currentActive->down;
        }
        return *this;
    }

    
    Iterator& operator--() {
        if (currentActive && currentActive->up) {
            currentActive = currentActive->up;
        }
        return *this;
    }

  
    Iterator operator++(int) {
        Iterator temp = *this;
        if (currentActive && currentActive->right) {
            currentActive = currentActive->right;
        }
        return temp;
    }


    Iterator operator--(int) {
        Iterator temp = *this;
        if (currentActive && currentActive->left) {
            currentActive = currentActive->left;
        }
        return temp;
    }



    bool operator==(Iterator& other)  {
        if (currentActive == other.currentActive) {
            return true;
        }
        else {
            return false;
        }
    }

    bool operator!=( Iterator& other)  {
        return !(currentActive == other.currentActive);
    }


    bool isValid()  {
        return currentActive != nullptr;
    }
};
