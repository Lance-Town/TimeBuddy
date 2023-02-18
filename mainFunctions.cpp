// contains the definitions for the functions that main uses

#include <iostream>
#include <fstream>

#include "helper.h"

using namespace std;

extern const string FILE_NAME;

// get string input from user and return
string getInput() {
    string ans;
    cout << "Enter: ";
    cin >> ans;
    return ans;
}

// import the file contents
void importFileContents(linkedlist &ls) {
    ifstream inFile(FILE_NAME);

    string course, tmpTime;

    // throwaway the header of CSV file
    getline(inFile, course, ',');
    getline(inFile, tmpTime, '\n');

    if (inFile.is_open()) {
        while (!inFile.eof()) {
            getline(inFile, course, ',');
            getline(inFile, tmpTime, '\n');
            if ((course.length() > 1) && tmpTime != "") {
                ls.append(course, tmpTime);
            }
        }
    }
}

// capitalize a word that is passed in
string toCapitalize(string word) {
    for (int i = 0; i < word.length(); i++) {
        word[i] = toupper(word[i]);
    }

    return word;
}

// get the course's name and make sure the user inputted it correctly
string getCourseName(linkedlist *ls) {
    string checkInput;
    string courseName;
    bool inCSV;

    cout << "What course are your working on: ";
    cin >> courseName;

    courseName = toCapitalize(courseName);

    if (ls->find(courseName) == false) {
        cout << "Are you ready to study " << courseName 
            << "?\nIt was not registered in the \"studyTimes.csv\" file, are you sure you typed the right course?" 
            << "\nEnter \"no\" to re-enter name, else enter \"yes\": ";
        
        cin >> checkInput;

        if (checkInput == "no") {
            return getCourseName(ls);
        }
    }
    return courseName;
}