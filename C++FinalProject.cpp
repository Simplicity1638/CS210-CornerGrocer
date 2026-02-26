/*
Dylan Demarco
CS 210 Project Three - Corner Grocer
Program Purpose:
- Read purchased items from an input file 
- Count item frequencies using map
- Write counts to a backup file
- Provide a menu to:
- Search for an item frequency
- Print all item frequencies
- Print a histogram of frequencies

*/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>

using namespace std;

/* Class stores item name as key and frequency as value, reads input and fills map, 
and returns map for use in functions */

class CornerGrocer {
private:
	// store item name and number of times purchased
    map<string, int> grocList;

    // removes '\r' if the file has line endings
    static void fixLineEnding(string& s) {
    if (!s.empty() && s[s.size() - 1] == '\r') {
        s.erase(s.size() - 1, 1);
        }
    }

public:
    //Build frequency map from input file
    void buildMap(ifstream& inputFile) {
        string item;

        while (getline(inputFile, item)) { //reads one line at time and cleans formatting
            fixLineEnding(item);

            if (!item.empty()) { // Ignore blank lines and incrments count if item exists/creates if it doesn't
                grocList[item]++;
            }
        }
    }

    // return copy of map
    map<string, int> getMap() const {
        return grocList;
    }
};

//Function prototypes

void displayMenu();
int getInteger(int lowest, int highest, const string& prompt);

bool openInputFile(ifstream& inputFile, const string& filename);
bool openOutputFile(ofstream& outputFile, const string& filename);

map<string, int> readInputFile(ifstream& inputFile, CornerGrocer& grocer);
void writeOutputFile(ofstream& outputFile, const map<string, int>& grocList);

string printStars(int count);

void findItem(const map<string, int>& grocList);
void listItems(const map<string, int>& grocList);
void printHistogram(const map<string, int>& grocList);

void runMenu(const map<string, int>& grocList);

void pause(const string& message = "Press enter to continue ");
void cls();

// main function 

int main() {

    ifstream inputFile; // read/write files
    ofstream outputFile;

    map<string, int> grocList; // Store frequencies

    CornerGrocer grocer;

    // Open input file
    if (!openInputFile(inputFile, "FoodList.txt")) {
        cout << "Error opening input file.\n";
        cout << "Make sure input file is in the same folder as program.\n";
        return EXIT_FAILURE;
    }
    cout << "Input File Opened\n";

    // open output file 
    if (!openOutputFile(outputFile, "frequency.dat")) {
        cout << "Error opening output file.\n";
        return EXIT_FAILURE;
    }
    cout << "Output File Opened\n";

    pause("Press enter to read the file "); // Pause so user can see confirmation
    cls();

    // build frequency map
    grocList = readInputFile(inputFile, grocer);

    // write backup file automatically
    writeOutputFile(outputFile, grocList);

    // close files after reading/writing
    inputFile.close();
    outputFile.close();

    // Run menu
    runMenu(grocList);

    cout << "Goodbye.\n";
    return 0;
}

// Function definitions 

void displayMenu() {
    cout << "=====================================\n";
    cout << "           Corner Grocer Menu        \n";
    cout << "=====================================\n";
    cout << "1. Find an item frequency\n";
    cout << "2. List all item frequencies\n";
    cout << "3. Print histogram\n";
    cout << "4. Exit\n";
    cout << "-------------------------------------\n";
}
// gets validated integer within range
int getInteger(int lowest, int highest, const string& prompt) {
    int value;

    cout << prompt << "(" << lowest << "-" << highest << "): ";
//loop until valid input is recieved
    while (!(cin >> value) || value < lowest || value > highest) {
        cin.clear(); // Clear error and remove invalid characters
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt << "(" << lowest << "-" << highest << "): ";
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear leftover newline
    return value;
}
// opens input file for reading
bool openInputFile(ifstream& inputFile, const string& filename) {
    inputFile.open(filename.c_str());   
    return !inputFile.fail();
}
 // Opend output file for writing
bool openOutputFile(ofstream& outputFile, const string& filename) {
    outputFile.open(filename.c_str());  
    return !outputFile.fail();
}
// Uses class to build map and returns
map<string, int> readInputFile(ifstream& inputFile, CornerGrocer& grocer) {
    grocer.buildMap(inputFile);
    return grocer.getMap();
}
// write frequency map to backup file
void writeOutputFile(ofstream& outputFile, const map<string, int>& grocList) {
    map<string, int>::const_iterator it;

    for (it = grocList.begin(); it != grocList.end(); ++it) {
        outputFile << it->first << " " << it->second << endl;
    }
}

string printStars(int count) {
    return string(count, '*');
}

void findItem(const map<string, int>& grocList) {

    string item;

    // Input validation
    do {
        cout << "Enter item name: ";
        getline(cin, item);

        if (item.empty()) {
            cout << "Item name cannot be blank.\n";
        }
    } while (item.empty());

    // user input echo
    cout << "You searched for: " << item << endl;

    if (grocList.count(item)) {
        cout << "Frequency: " << grocList.at(item) << endl;
    }
    else {
        cout << "Frequency: 0" << endl;
    }
}
// Print items and frequency
void listItems(const map<string, int>& grocList) {
    map<string, int>::const_iterator it;

    for (it = grocList.begin(); it != grocList.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
}
// Print histogram
void printHistogram(const map<string, int>& grocList) {
    map<string, int>::const_iterator it;

    for (it = grocList.begin(); it != grocList.end(); ++it) {
        cout << it->first << " " << printStars(it->second) << endl;
    }
}
 // controls menu loop
void runMenu(const map<string, int>& grocList) {
    int selection = 0;
    bool notDone = true;

    do {
        displayMenu();
        selection = getInteger(1, 4, "Select menu option ");

        switch (selection) {
        case 1:
            findItem(grocList);
            pause();
            cls();
            break;

        case 2:
            listItems(grocList);
            pause();
            cls();
            break;

        case 3:
            printHistogram(grocList);
            pause();
            cls();
            break;

        case 4:
            notDone = false;
            break;
        }
    } while (notDone);
}
// pauses until user hits enter
void pause(const string& message) {
    cout << message;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
 // Spacing for clearing screen
void cls() {
    cout << string(40, '\n');
}
