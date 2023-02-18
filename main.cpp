/* 
* Lance Townsend
* 
* Program to track how much time I have spent studying in 
* my various classes in college.
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include "helper.h"

int main() {
    Clock clock;
    linkedlist ls;
    importFileContents(ls);
    ls.print();

    string courseName = getCourseName(&ls);
    clock.start();

    clock.end();

    ls.appendNewCourse(courseName, clock.getDuration());

    ls.writeToFile();
    ls.print();

    return 0;
}