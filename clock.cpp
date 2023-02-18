// Contains method definitions for the clock and custom time classes

#include <iostream>
#include "helper.h"

using namespace std;

/* ----------- Custom Time Methods ----------- */

string cusTime::getTime() {
    string strSec, strMin;
    if (sec < 10) {
        strSec = '0' + to_string(sec);
    } else {
        strSec = to_string(sec);
    }

    if (min < 10) {
        strMin = '0' + to_string(min);
    } else {
        strMin = to_string(min);
    }

    return (to_string(hour) + ':' + strMin + ':' + strSec);
}

void cusTime::formatStringToTime(string tmp) {
    string delimiter = ":";
    size_t pos = 0;
    string token;

    token = tmp.substr(0, tmp.find(delimiter));
    tmp.erase(0, tmp.find(delimiter) + delimiter.length());
    this->hour = stoi(token);


    token = tmp.substr(0, tmp.find(delimiter));
    tmp.erase(0, tmp.find(delimiter) + delimiter.length());
    this->min = stoi(token);

    token = tmp.substr(0, tmp.find(delimiter));
    tmp.erase(0, tmp.find(delimiter) + delimiter.length());
    this->sec = stoi(token);
}

void cusTime::printTime() {
    cout << this->getTime() << endl;
}

// format time method
void cusTime::formatTime() {
    if (sec > 59) {
        min += 1;
        sec -= 60;
    }
    
    if (min > 59) {
        hour += 1;
        min -= 60;
    }

    return;
}

/* ----------- Clock class Methods -----------*/

void Clock::end() {
    cout << "Enter \"done\" when you are done studying\n";
    string input = getInput();
    
    if (toCapitalize(input) == "DONE") {
        endTime = chrono::steady_clock::now();
        duration = chrono::duration_cast<chrono::seconds>(endTime - startTime).count();
        return;
    }

    return end();
}