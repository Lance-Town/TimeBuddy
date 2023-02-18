// contains method definitions for linked list and node classes

#include <iostream>
#include <fstream>
#include "helper.h"

using namespace std;

/* ------------ Node class methods ------------*/
bool node::find(string target) {
    if (name == target) {
        return true;
    }

    if (next != NULL) {
        return next->find(target);
    } else {
        return false;
    }
}

// print the entire list
void node::print() {
    cout << "Course: " << name << '\t' << time.getTime() << endl;
    if (next != NULL) {
        next->print();
    }

    return;
}

void node::append(string name, string time) {
    if (next != NULL) {
        // not end of list
        next->append(name, time);
    } else {
        // end of list
        node *newNode = new node(name, time);
        this->setNext(newNode);
    }
    return;
}

void node::update(string courseName, double seconds) {
    if (name == courseName) {
        this->time.addTime(0 ,0 ,seconds);
        return;
    }

    if (next != NULL) {
        next->update(courseName, seconds);
    } else {
        cout << "Error node::update() -- Course not in list\n";
        return;
    }
}

void node::writeToFile(ofstream *outFile) {
    (*outFile) << name << ", " << time.getTime() << '\n';

    if (next != NULL) {
        next->writeToFile(outFile);
    } 

    return;
}

/* ---------- Linked list class methods ---------- */

// append new node to the end of the linked list
void linkedlist::append(string name, string time) {
    if (head != NULL) {
        head->append(name, time);
    } else {
        node *newNode = new node(name, time);
        newNode->setNext(head);
        head = newNode;
    }
    return;
}


// push a new node to the front of the linked list
void linkedlist::push(string name, string time) {
    node *newNode = new node(name, time);
    newNode->setNext(head);
    head = newNode;
    return;
}

void linkedlist::print() {
    if (head != NULL) {
        head->print();
    } else {
        cout << "Error linkedlist::print() -- List is empty\n";
    }
    return;
}

void linkedlist::update(string courseName, double duration) {
    if (head != NULL) {
        // list not empty
        head->update(courseName, duration);
    } else {
        // list empty
        cout << "Error linkedlist::update() -- List is empty\n";
        push(courseName, "00:00:00");
    }
}

// find the target in the linked list
bool linkedlist::find(string target) {
    if (head != NULL) {
        return head->find(target);
    } else {
        return false;
    }
}

void linkedlist::appendNewCourse(string courseName, double duration) {
    if (this->find(courseName) == false) {
        // course not in list
        this->append(courseName, "00:00:00");
    } else {
        // course in list
        this->update(courseName, duration);
    }
}

void linkedlist::writeToFile() {
    if (head != NULL) {
        ofstream outFile(FILE_NAME);
        outFile << "Course, Time\n";
        head->writeToFile(&outFile);
    } else {
        cout << "Error linkedlist::writeToFile() -- list is empty\n";
    }
    return;
}