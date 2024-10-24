#pragma once
#include<iostream>
using namespace std;

struct NewNode
{
    int data;
    NewNode* next;
    NewNode* prev;
};

class LinkingList {
public:
    NewNode* Dabba;
    NewNode* head;
    NewNode* tail;
public:
    LinkingList() {
        this->Dabba = nullptr;
        this->head = nullptr;
        this->tail = nullptr;
    }
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

};

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




