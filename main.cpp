#include <iostream>
#include <fstream>
#include "helper.h"

    /*
    Course, Time
    COMM101, 00:00:00
    MATH176, 00:00:00
    ECON202, 00:00:00
    ENGL102, 00:00:00
    CS120, 00:00:00
    */

int main() {
    linkedlist ls;
    importFileContents(ls);
    ls.print();

    // ofstream outFile(FILE_NAME);

    // if (outFile.is_open()) {
    //     outFile << "Opened\n";
    // }

    // outFile.close();

    // ifstream inFile(FILE_NAME);

    // if (inFile.is_open()) {
    //     string x;
    //     inFile >> x;
    //     cout << x;
    // }

    // inFile.close();
}