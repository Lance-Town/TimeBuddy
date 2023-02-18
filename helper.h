#ifndef HELPER_H_12_17_2022
#define HELPER_H_12_17_2022

using namespace std;

/*---------------------- Global Variables ---------------------*/

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

/*------------------------- Functions -------------------------*/
string getInput();

void importFileContents(linkedlist &ls);

// capitalize word
string toCapitalize(string word);

// get the course's name and make sure the user inputted it correctly
string getCourseName(linkedlist *ls);

#endif /* HELPER_H_12_17_2022 */