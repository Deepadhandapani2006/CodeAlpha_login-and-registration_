#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <functional>  // for std::hash

using namespace std;

// File to store user data
const string FILENAME = "users.txt";

// Function to load all users from file
unordered_map<string, size_t> loadUsers() {
    unordered_map<string, size_t> users;
    ifstream infile(FILENAME);
    string username;
    size_t passwordHash;

    while (infile >> username >> passwordHash) {
        users[username] = passwordHash;
    }
    return users;
}

// Function to save a new user into file
void saveUser(const string &username, size_t passwordHash) {
    ofstream outfile(FILENAME, ios::app);
    outfile << username << " " << passwordHash << "\n";
}
void registerUser() {
    auto users = loadUsers();
    string username, password;

    cout << "\n--- User Registration ---\n";
    cout << "Enter username: ";
    cin >> username;

    // Check for duplicate username
    if (users.find(username) != users.end()) {
        cout << "Username already exists! Please choose another.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Hash password (beginner-friendly way)
    hash<string> hasher;
    size_t passwordHash = hasher(password);

    saveUser(username, passwordHash);
    cout << "Registration successful!\n";
}

// Function to login user
void loginUser() {
    auto users = loadUsers();
    string username, password;

    cout << "\n--- User Login ---\n";
    cout << "Enter username: ";
    cin >> username;

    // Check if username exists
    if (users.find(username) == users.end()) {
        cout << "Invalid username or password.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Hash entered password
    hash<string> hasher;
    size_t enteredHash = hasher(password);

    if (enteredHash == users[username]) {
        cout << "Login successful! Welcome, " << username << "!\n";
    } else {
        cout << "Invalid username or password.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n============================\n";
        cout << "   Simple Login System\n";
        cout << "============================\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1: registerUser(); break;
            case 2: loginUser(); break;
            case 3: cout << "Exiting... Goodbye!\n"; return 0;
            default: cout << "Invalid choice! Try again.\n"; break;
        }
    }
}