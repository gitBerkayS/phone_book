#include <iostream>
#include <string>
#include <map>
#include <iomanip>
#include <cctype>
#include <iterator>
#include <fstream>
using namespace std;

//global variables so we can access these everywhere.
string user_option;
bool repeat = true;
map<string, string> phone_book;

void print_phone_book() {
    //making the layout of the phone book. 
    cout << right << setw(20) << "Phone";
    cout << setw(1) << "";
    cout << left << setw(20) << "Book" << endl;;
    cout << "*****************************************" << endl;
    //for every pair of the phone book. we print out the first part of the pair, then the second part of the pair.
    for (auto pair: phone_book) {
        cout << right << setw(18) <<pair.first;
        cout << setw(4) << "";
        cout << left << setw(18) << pair.second << endl;
    }
}
void save_file() {
    ofstream file("phone_book.txt"); //calling the text file
    //if file cant open. error message
    if (!file) {
        cout << "Error: Can't open file." << endl;
        return;
    }
    //if file does open, we go through the phone book and write into it starting from first part of the pair in our map. then out second part of the pair.
    for (auto pair : phone_book) {
        file << pair.first << "," << pair.second << endl;
    }

    //important to close the file after we are done.
    file.close();
    cout << "\nSaving data to \"phone_book.txt\"..." << endl;
}
void load_phone_book_from_file() {
    ifstream file("phone_book.txt"); //calling the text file
    //if we cant open the file. error
    if (!file) {
        cerr << "Error: Can't open file." << endl;
        return;
    }
    //if we can open the file, check if file meets the way we formated the save.
    string name, number;
    while (getline(file, name, ',') && getline(file, number)) {
        // if the file meets our formatting save it back in our map.
        phone_book[name] = number;
    }
    //close it back
    file.close();
    cout << "\nLoading \"phone_book.txt\"..." << endl;
    print_phone_book();
}
void choices() {
    string name = "", number = "";
    bool back_to_start = false;

    cin >> user_option;

    if ((user_option[0] == 'A' || user_option[0] == 'a') && user_option[1] == '\0') {
        //asking for input
        cout << "Enter the name of the person you would like to add: ";
        cin.ignore();
        getline(cin, name);
        //checking if its made up of letters.
        for (int x = 0; x < name.length(); x++) {
            if ((name[x] == ' ')) {
                continue;
            
            
                while (!isalpha(name[x])) {
                    cout << "ERROR.You've not entered a name. Please re-enter the name you would like to add: ";
                    getline(cin, name);
                    x = 0;
                }
            }
        }

        cout << "Enter the phone number of the person you would like to add: ";
        cin >> number;
        for (int x = 0; x < number.length(); x++) {
            // want to check every digit of number to see if its a number.
            while (!isdigit(number[x])) {
                cout << "ERROR. You've not entered a positive integer. Please re-enter the phone number you would like to add:  ";
                cin >> number;
                x = 0;
            }
        }

        for (auto pair : phone_book) {
            //if we get duplicate names. error.
            while (pair.first == name || pair.second == number) {
                cin.clear();
                cin.ignore();

                cout << "\n!!Detected Duplicates.. Cannot add the same name or number!!\n" << endl;
                cout << "Enter the name of the person you would like to add: ";
                getline(cin, name);
                for (int x = 0; x < name.length(); x++) {
                    if ((name[x] == ' ')) {
                        continue;
                    
                    //checking if its made up of letters.
                        while (!isalpha(name[x])) {
                            cout << "ERROR.You've not entered a name. Please re-enter the name you would like to add: ";
                            getline(cin, name);
                            x = 0;
                        }
                    }
                }
                cout << "Enter the phone number of the person you would like to add: ";
                cin >> number;
                for (int x = 0; x < number.length(); x++) {
                    // want to check every digit of number to see if its a number.
                    while (!isdigit(number[x])) {
                        cout << "ERROR. You've not entered a positive integer. Please re-enter the phone number you would like to add:  ";
                        cin >> number;
                        x = 0;
                    }
                }
                    
            }
        }

        
        //inserting into the map
        phone_book.insert(pair<string, string>(name, number));
        cout << "..." << endl;
        cout << "..." << endl;
        cout << "..." << endl;
        cout << "Records Updated...\n";
        print_phone_book();

        cin.ignore();
        cin.clear();
    }
    else if ((user_option[0] == 'E' || user_option[0] == 'e') && user_option[1] == '\0') {
        bool repeatt = true;

        do {
            cout << "Enter the name of the person you would like to edit: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter the new phone number of the person: ";
            cin >> number;
            //another way to find the name we want to edit,
            bool name_found = false;
            for (auto& pair : phone_book) {
                //if the name is found we change the number attached to it.
                if (pair.first == name) {
                    name_found = true;
                    pair.second = number;
                    repeatt = false;
                }
            }

            if (!name_found) {
                cout << "\nThat name cannot be found." << endl;
                    repeatt = false;
            }
        } while (repeatt);
    }
    else if ((user_option[0] == 'D' || user_option[0] == 'd') && user_option[1] == '\0') {
        cout << "Enter the name of the person you would like to delete: ";
        cin.ignore();
        getline(cin, name);

        //searching to find the name we want,
        auto it = phone_book.find(name);
        if (it != phone_book.end()) {
            //then simply deleting it.
            phone_book.erase(it);
            cout << "Entry deleted successfully." << endl << endl;
        }
        //if we cant find it then error.
        else {
            cout << "Entry not found in the phone book." << endl;
        }
    }
    else if ((user_option[0] == 'E' || user_option[0] == 'e') && user_option[1] == 'x' || user_option[1] == 'X') {
        //ending our dowhile loop in main
        cout << "\nEnding program... Goodbye";
        repeat = false;
    }
    else if ((user_option[0] == 'P' || user_option[0] == 'p') && user_option[1] == '\0'){
    //simple command to show the size then print.
    cout << "\nThere are currently " << phone_book.size() << " student/s in your phone book\n\n";
    print_phone_book();
}
}
void program_start() {

    cout << "\"A\" to add, \"E\" to edit, \"D\" to delete, \"P\" to print, \"Ex\" to exit.  ";
}


int main() {
    //running everything.
    cout << " Program starting... \n... \n... \n... \nWelcome to the Phone-book! ";
    load_phone_book_from_file();

    do {
        program_start();
        choices();
    } while (repeat);

    save_file();
}

