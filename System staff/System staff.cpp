/*
Staff System

- This System is to manage Staff members data.
- The System has an abilty to Add, Remove, Search, Display, Sort and Update members.
- The System has many functions like cinInteger, cinDouble and cinString
that helps to keep the code clean and catch any user invalid inputs.
- The System saves the data on exit and loads it on run.
*/

#include <iostream>
#include <ctime> // time
#include <fstream> // Files

using namespace std; 

// Staff struct (id, name, job, age, salary)
struct Staff {
    int id;
    string name;
    string job;
    int age;
    double salary;
};

// Staf Members array
Staff members[100]; 
int counter = 0;

// function to ask user for number then return an (Integer)
// Also catch user invalid inputs
int cinInteger(string q) {
    string input;
    int number;
    
    while (true) { // a loop to keep asking the user until the input is valid
        cout << q; // print the question
        cin >> input; // get user input
        
        try {
            // convert the input string to integer and return it
            number = stoi(input); 
            return number;
        
        // otherwise if an error happend (user input a invalid integer)
        } catch (...) {
            cout << "Invalid Integer." << endl;
        }
        
    } // end of loop
}

// function to ask user for number then return a (Double)
// Also catch user invalid inputs
double cinDouble(string q) {
    string input;
    double number;
    
    while (true) { // a loop to keep asking the user until the input is valid
        cout << q; // print the question
        cin >> input; // get user input
    
        try {
            // convert the input string to double and return it
            number = stod(input); 
            return number;
        
        // otherwise if an error happend (user input a invalid double)
        } catch (...) {
            cout << "Invalid Double." << endl;
        }
        
    } // end of loop
}

// function to ask user for string then return it
string cinString(string q) {
    string input;
    
    cout << q; // print the question
    cin.ignore();
    getline(cin, input); // get user input
        
    return input;
}

// function to find member Index in the array by ID then return it
int findIndex() {
    int id = cinInteger("Enter the id: ");
    
    // search
    for (int i = 0; i < counter; i++) {
        if (members[i].id == id) return i; // return member index
    }
    
    cout << "Could not find a member with id: " << id << endl;
    return -1; // return -1 which mean not found
}

// Add Member
void addMember() {
    Staff member; // create a member
    
    // Get and save inputs 
    member.id = cinInteger("Enter the id: ");
    member.name = cinString("Enter the name: ");
    member.age = cinInteger("Enter the age: ");
    member.job = cinString("Enter the job name: ");
    member.salary = cinInteger("Enter the salary: ");
    
    // Save the member to the array
    members[counter] = member;
    counter++;
    cout << "You Successfully add a new member." << endl;
}

// Remove Member
void removeMember() {
    int index = findIndex();
    if (index == -1) return; // stop the function if not found 
    
    // Loop to shift members to the left to overwrite the member that we want to delete.
    for (int i = index; i < counter - 1; i++) {
        members[i] = members[i+1]; // Move each member left by one position.
    }
    
    counter--;
    cout << "You Successfully Delete the member." << endl;
}

// Sort Members
void sortMembers() {
    // Bubble Sort Algorithm
     for (int i = 0; i < counter - 1; i++) {
        for (int j = 0; j < counter - 1 - i; j++) { 
            
            // if out of order, swap!
            if (members[j].name > members[j + 1].name) {
                // swapping the members
                Staff member = members[j];
                members[j] = members[j + 1];
                members[j + 1] = member;
            }
            
        }
    }
    
    cout << "You Successfully sort members by names." << endl;
}

// Display Member Infomation
void displayMemberInfo(Staff& member) {
    cout << "Member Infomation:        "  << endl;
    cout << "  ID    : " << member.id     << endl;
    cout << "  Name  : " << member.name   << endl;
    cout << "  Job   : " << member.job    << endl;
    cout << "  Age   : " << member.age    << endl;
    cout << "  Salary: " << member.salary << " SAR" << endl;
}

// Display Member Infomation By asking user for ID
void displayMemberInfo() {
    int index = findIndex();
    if (index == -1) return; // stop the function if not found 
    
    displayMemberInfo(members[index]);
}

// Display Memebers List
void displayMembersList() {
    // a loop to print memebers list
    cout << "Members List:" << endl;
    for (int i = 0; i < counter; i++) {
        cout << "[ID: " << members[i].id << "] " <<  members[i].name << endl;
    }
}

// Search for Staff Member by Name or Job
void search() {
    // Get user search words
    string search_words = cinString("Enter the search words: ");
    
    bool found = false;
    
    // Loop to search in each member
    for (int i = 0; i < counter; i++) {
        // Search in member Name or Job.
        if (members[i].name == search_words || members[i].job == search_words) {
            displayMemberInfo(members[i]); // print member info
            found = true;
        }
    } // end of loop
    
    // if 'found' still false, print error.
    if (!found) cout << "There is no name or job match your search words." << endl;
}

// Update Member Salary
void updateMemberSalary() {
    int index = findIndex();
    if (index == -1) return; // stop the function if not found
    
    // Ptint to the user the current Salary then get the new Salary.
    cout << "Current Salary: " << members[index].salary << " SAR" << endl;
    members[index].salary = cinDouble("Enter the new salary: ");
    
    cout << "Salary has been updated." << endl;
}

// Save Members to a File ||| And a report file
void saveMembers() {
    ofstream outFile("members.txt"); // Open output file.
    if (!outFile.is_open()) return; // if not open, stop the function
    
    // Loop through all Members
    for (int i = 0; i < counter; i++) {
        // write the member data to the output file 
        outFile 
               << members[i].id << endl
               << members[i].name << endl
               << members[i].age << endl
               << members[i].job << endl
               << members[i].salary << endl;
    }

    // Close the output file.
    outFile.close();
    
    // ============ Create Statical Report File =========
    ofstream outFileReport("report.txt"); // Open output file.
    if (!outFileReport.is_open()) return; // if not open, stop the function
    
    time_t currentTime = time(0);
    
    // write the counter and current time
    outFileReport
            << "Counter: " << counter << endl
            << "Last Update: " << ctime(&currentTime);
    
    // Close the output file.
    outFileReport.close();
    
}

// Load Members from a File
void loadMembers() {
    ifstream inFile("members.txt"); // Open input file.
    if (!inFile.is_open()) return; // if not open, stop the function
    
    string line;
    while(true) {
        // Create a member
        Staff member;
        
        // read ID
        getline(inFile, line);
        // if nothing, this mean the end of file so break the loop
        if (line == "") break;
        member.id = stoi(line);
        
        // read Name
        getline(inFile, line); 
        member.name = line;
        
        // read Age
        getline(inFile, line); 
        member.age = stoi(line);
        
        // read Job
        getline(inFile, line); 
        member.job = line;
        
        // read Salary
        getline(inFile, line); 
        member.salary = stod(line);
    
        // Add the member to the array
        members[counter] = member;
        counter++;
    }
    
    // Close the input file.
    inFile.close();
}

int main() {
    loadMembers(); 
    
    while (true) {
        
        // System Menu
        cout << endl;
        cout << "---------- System Menu ----------" << endl;
        cout << "1- Add Staff Member" << endl;
        cout << "2- Search" << endl;
        cout << "3- Sort" << endl;
        cout << "4- Display Member Info" << endl;
        cout << "5- Display Members List" << endl;
        cout << "6- Remove Staff Member" << endl;
        cout << "7- Update Staff Member Salary" << endl;
        cout << "8- Exit" << endl;
        
        // Get user selected option
        int selectedOption = cinInteger("Select your option: ");
        cout << endl;
        
        // Swicth (Control Statment) base on 'selectedOption'
        switch (selectedOption) {
            case 1:
                addMember();
                break;
            
            case 2:
                search();
                break;
            
            case 3:
                sortMembers();
                break;
                
            case 4:
                displayMemberInfo();
                break;
                
            case 5:
                displayMembersList();
                break;
                
            case 6:
                removeMember();
                break;
    
            case 7:
                updateMemberSalary();
                break;
    
            case 8: // Exit
                saveMembers();
                cout << "Closing the system..." << endl;
                return 0; // Close the program
    
            default:
                cout << "Invalid option." << endl;
                
        } // end of switch
        
    } // end of while loop
}