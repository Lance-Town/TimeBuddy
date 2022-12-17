#ifndef HELPER_H_12_17_2022
#define HELPER_H_12_17_2022

using namespace std;

// global file name
const string FILE_NAME = "courses.csv";

/*-------------------------- Classes --------------------------*/

// custom time class
class cusTime {
    public:
        int hour;
        int min;
        int sec;
        cusTime() {hour = 0; min = 0; sec = 0;}
        void addTime(int hour, int min, int sec) {this->hour += hour; this->min += min; this->sec += sec; formatTime();}
        void formatTime();
        void formatStringToTime(string);
        string getTime();
        void printTime();
};

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

// node class
class node {
    private:
        node *next;
        string name;
        cusTime time;
    public:
        node() {next = NULL;name = "";}
        node(string s) {next = NULL; name = s;}
        node(string s, string t) {next = NULL; name = s; time.formatStringToTime(t);}
        string getName() {return name;}
        void setNext(node *n) {next = n;}
        void append(string line, string t);
        void print();
};

// print the entire list
void node::print() {
    cout << "Course: " << name << '\t' << time.getTime() << endl;
    if (next != NULL) {
        next->print();
    }

    return;
}

void node::append(string name, string t) {
    if (next != NULL) {
        // not end of list
        next->append(name, t);
    } else {
        // end of list
        node *newNode = new node(name, t);
        this->setNext(newNode);
    }
    return;
}

class linkedlist {
    private:
        node *head;
    public:
        linkedlist() {head = NULL;}
        void append(string, string);
        void push(string, string);
        void print();
};

// append new node to the end of the linked list
void linkedlist::append(string name, string t) {
    if (head != NULL) {
        head->append(name, t);
    } else {
        node *newNode = new node(name, t);
        newNode->setNext(head);
        head = newNode;
    }
    return;
}


// push a new node to the front of the linked list
void linkedlist::push(string name, string t) {
    node *newNode = new node(name, t);
    newNode->setNext(head);
    head = newNode;
    return;
}

void linkedlist::print() {
    if (head != NULL) {
        head->print();
    } else {
        cout << "Error: List is empty\n";
    }
    return;
}

/*------------------------- Functions -------------------------*/
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

#endif /* HELPER_H_12_17_2022 */