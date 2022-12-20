#ifndef HELPER_H_12_17_2022
#define HELPER_H_12_17_2022

using namespace std;

// global file name
const string FILE_NAME = "courses.csv";

/*--------------- Necessary Function Prototypes ---------------*/
string getInput();
string toCapitalize(string);

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
        void append(string, string);
        void print();
        bool find(string);
        void update(string, double);
        void writeToFile(ofstream *);
};

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

class linkedlist {
    private:
        node *head;
    public:
        linkedlist() {head = NULL;}
        void append(string, string);
        void push(string, string);
        void print();
        bool find(string);
        void appendNewCourse(string, double);
        void update(string, double);
        void writeToFile();
};

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

class Clock {
    private:
        double duration;
        chrono::steady_clock::time_point startTime;
        chrono::steady_clock::time_point endTime;
    public:
        Clock() {duration = 0;}
        void start() {startTime = chrono::steady_clock::now();}
        void end();
        double getDuration() {return duration;}
};

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

/*------------------------- Functions -------------------------*/
string getInput() {
    string ans;
    cout << "Enter: ";
    cin >> ans;
    return ans;
}

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

// capitalize word
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

#endif /* HELPER_H_12_17_2022 */