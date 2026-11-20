#include <iostream>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <vector>
#include <numeric>
#include <sstream>
// Function declarations, these are required for some function operators, like std::accumulate, 

void login();
void registerUser();
void password(int counter);
void Datas(int counter);
void addData(int counter);
void analyzeData(int counter);
void updateData(int counter);
// It is best to always split the parts of the overall program into smaller functions,
int main() {
 
  std::cout << "Welcome to the water tracking program!!" << std::endl;
  std::cout << "Please enter 'L' to login in or 'R' to register" << std::endl;
  std::string choice;

   std::getline(std::cin, choice);
  choice[0] = toupper(choice[0]);
  
  choice = toupper(choice[0]); //extract the firt letter
// using toupper to ensure the input works with the if statements. the [0] makes the first characeter uppercase, 
 
  if (choice == "L") {
    login();
  } else if (choice == "R") {
    registerUser();
  }


return 0;
}

void login() {
    std::cout << "Please enter your username" << std::endl;
    std::string username;
    
    std::getline(std::cin, username);
    
    std::cout << "User:" << username << std::endl;
    std::ifstream file("login.txt");
    std::string storedUsername;
    std::vector<std::string> storedUsernames;
    //std::vector is a dynamic array, can grow or shrink, used to make a temporary storage for strings storedusernames
    int counter = 0;
    if (file.is_open()){
        while (file >> storedUsername) {
            storedUsernames.push_back(storedUsername);
        }
        file.close();
    //this is a loop that keeps on reading the txt file and  stores it into the vector    
    }
    if (std::find(storedUsernames.begin(), storedUsernames.end(), username) != storedUsernames.end()) {
        std::cout << "User found" << std::endl;
        counter = std::distance(storedUsernames.begin(), std::find(storedUsernames.begin(), storedUsernames.end(), username));
        //workaround to knowing what index the user is at, distance returns the integer between the value found and beginning.
        std::cout << "User is at index: " << counter << std::endl;

        password(counter);
    } else {
        std::cout << "User not found" << std::endl;
        std::cout << "Please register" << std::endl;
        registerUser();
    }
}

void registerUser() {
    std::cout << "**Registration**" << std::endl;
    std::cout << "Please pick your username" << std::endl;
    std::string username;
    std::getline(std::cin, username);
    std::ofstream file("login.txt", std::ios::app);
    file << std::endl;
    file << username;
    file.close();
    std::string password;
    std::cout << "Please pick your password" << std::endl;  
    std::getline(std::cin, password);
    std::ofstream file2("password.txt", std::ios::app);
    //offstream is used to modify text
    file2 << std::endl;
    file2 << password;
    file2.close();
    std::cout << "Registration complete" << std::endl;
    login();
}

void password(int counter) {
  std::cout << "Please enter your password" << std::endl;
  std::string password;
  std::getline(std::cin, password);
  std::ifstream file("password.txt");
  //ifstream used to read text file
    std::string storedPassword;
    std::vector<std::string> storedPasswords;
    if (file.is_open()){
        while (file >> storedPassword) {
            storedPasswords.push_back(storedPassword);
            //here again we store the passwords into a vector
        }
        file.close();
    }
    if (std::find(storedPasswords.begin(), storedPasswords.end(), password) != storedPasswords.end()) {
        std::cout << "Password correct" << std::endl;
        std::cout << "Welcome to the water tracking program!!" << std::endl;
        Datas(counter);
    } else {
        std::cout << "Incorrect password" << std::endl;
    }
}
    
void Datas(int counter) {
    bool dataFound = false;
    std::ifstream file("data.txt");
    int targetline = counter;
    int currentline = 0;
    std::string line;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            if (currentline == targetline) {
                std::cout << "Data for user at index " << counter << ": " << line << std::endl;
                dataFound = true;
                analyzeData(counter);
                if (line.empty()) {
                    std::cout << "No data found for this user." << std::endl;
                    std::cout << "Would you like to add data? (Y/N)" << std::endl;
                    std::string choice;
                    std::getline(std::cin, choice);
                    choice[0] = toupper(choice[0]);
                    if (choice == "Y") {
                        addData(counter);
                    } else {
                        std::cout << "No data added." << std::endl;
                    }
                } 
                
            }
            currentline++;
            
        }
        if (!dataFound) {
            std::cout << "No data found for this user." << std::endl;
            
                    std::cout << "Would you like to add data? (Y/N)" << std::endl;
                    std::string choice;
                    std::getline(std::cin, choice);
                    choice[0] = toupper(choice[0]);
                    if (choice == "Y") {
                        addData(counter);
                    } else {
                        std::cout << "No data added." << std::endl;
                    }
        }
    }
}

void addData(int counter) {
    std::string line;
    std::cout << "Please enter your data" << std::endl << "Seperated by spaces" << std::endl;
    std::getline(std::cin, line);
    std::ofstream file("data.txt", std::ios::app);
    if (file.is_open()) {
        file << std::endl;
        file << line;
        file.close();
    }
    std::cout << "Data added successfully" << std::endl;
    std::cout << "Would you like to analyze your data? (Y/N)" << std::endl;
    std::string choice;
    std::getline(std::cin, choice);
    choice[0] = toupper(choice[0]);
    if (choice == "Y") {
        analyzeData(counter);
    }
    if (choice == "N") {
        std::cout << "No data analyzed." << std::endl;
        std::cout << "Have a great day!" << std::endl;
        
    }
}

void analyzeData(int counter) {
    
    std::ifstream file("data.txt");
    std::string line;
    if (file.is_open()) {
        int currentline = 0;
        while (std::getline(file, line)) {
            if (currentline == counter) {
                std::cout << "Analyzing data for user at index " << counter << ": " << line << std::endl;
                std::istringstream iss(line);
                std::vector<int> data;
                int value;
                while (iss >> value) {
                    data.push_back(value);
                }
                double average = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
                //accumulates sums the data and data size gives total number and then we divide to get average.
                std::cout << "Average days until reorder: " << average << std::endl;
                std::cout << "What do you want to do next?" << std::endl;
                std::cout << "1. Add more data" << std::endl;
                std::cout << "2. Analyze data again" << std::endl;
                std::cout << "3. Exit" << std::endl;
                int choice;
                std::cin >> choice;
                std::cin.ignore();
                switch (choice) {
                    case 1:
                        updateData(counter);
                        break;
                    case 2:
                    analyzeData(counter);   
                break;
                case 3:
                    std::cout << "Exiting..." << std::endl;
                    break;
            }}
            currentline++;
        }
        file.close();
    }
}
void updateData(int counter) {
    std::ifstream file("data.txt");
    std::string line;
    std::vector<std::string> lines;
    if (file.is_open()) {
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    std::cout << "Current data for user at index " << counter << ": " << lines[counter] << std::endl;
    std::cout << "Please enter your new data" << std::endl << "Seperated by spaces" << std::endl;
    
    std::getline(std::cin, line);
    lines[counter] += " " +line;

    std::ofstream outfile("data.txt", std::ios::trunc);
    for (const std::string& data : lines) {
        outfile << data << std::endl;
    }
    outfile.close();
    std::cout << "Data updated successfully" << std::endl;
std::cout << "What do you want to do next?" << std::endl;
                std::cout << "1. Add more data" << std::endl;
                std::cout << "2. Analyze data again" << std::endl;
                std::cout << "3. Exit" << std::endl;
                int choice;
                std::cin >> choice;
                std::cin.ignore();
                switch (choice) {
                    case 1:
                        updateData(counter);
                        break;
                    case 2:
                    analyzeData(counter);   
                break;
                case 3:
                    std::cout << "Exiting..." << std::endl;
                    break;
                }
}