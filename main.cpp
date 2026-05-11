#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <algorithm>
#include <cstdio>
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "Exam.h"

using namespace std;

/*
 * Grade Calculator (OOP Edition) — Final Project
 * Author: [Your Name]
 * Course: COSC 1437, [Semester Year]
 *
 * Concepts Demonstrated (Chapters 11-18 + Sprints 19-22)
 * ------------------------------------------------------
 * Ch 11 - Foundation from COSC 1436: std::vector, control flow, modular helper functions
 * Ch 12 - STL algorithms: std::max_element and std::min_element used to find highest and lowest grades
 * Ch 13 - File I/O: saveItems() and loadItems() use ofstream and ifstream
 * Ch 14 - User-defined classes: GradedItem base class with getters
 * Ch 15 - Object refinement: constructors, encapsulation, and getPercentage()
 * Ch 16 - Menu-driven UI: switch statement, setw formatting, helper functions
 * Ch 17 - Inheritance and polymorphism: Homework, Quiz, and Exam derive from GradedItem
 * Ch 18 - Smart pointers: vector<unique_ptr<GradedItem>>
 *
 * Sprint 19 - Input validation for invalid numeric input
 * Sprint 20 - File persistence with save/load functionality
 * Sprint 21 - ANSI color output and formatted tables
 * Sprint 22 - Extra credit functionality
 */

// Custom exception class for invalid user input
class InvalidInputException : public exception {
public:
    InvalidInputException(const string& message) : msg_(message) {}

    const char* what() const noexcept override {
        return msg_.c_str();
    }

private:
    string msg_;
};

// Changes console text color using ANSI escape codes
void setColor(const string& color) {
    if (color == "red") cout << "\033[31m";
    else if (color == "green") cout << "\033[32m";
    else if (color == "yellow") cout << "\033[33m";
    else if (color == "blue") cout << "\033[34m";
    else if (color == "pink") cout << "\033[38;2;255;105;180m";
    else if (color == "cyan") cout << "\033[36m";
    else if (color == "reset") cout << "\033[0m";
}

// Stores grading weights and letter grade cutoffs
struct GradingScheme {
    float homeworkWeight = 0.20f;
    float quizWeight = 0.30f;
    float examWeight = 0.50f;
    float cutoffA = 90.0f;
    float cutoffB = 80.0f;
    float cutoffC = 70.0f;
    float cutoffD = 60.0f;
};

// Saves graded items to a text file
void saveItems(const vector<unique_ptr<GradedItem>>& items, const string& filename) {
    ofstream file(filename);

    if (!file) {
        setColor("red");
        cout << "Error opening file.\n";
        setColor("reset");
        return;
    }

    for (const auto& item : items) {
        file << item->getCategory() << ","
             << item->getName() << ","
             << item->getPointsEarned() << ","
             << item->getPointsPossible() << "\n";
    }

    file.close();

    setColor("green");
    cout << "Items saved successfully!\n";
    setColor("reset");
}

// Loads graded items from a text file
void loadItems(vector<unique_ptr<GradedItem>>& items, const string& filename) {
    items.clear();

    ifstream file(filename);

    if (!file) {
        setColor("red");
        cout << "Could not open file.\n";
        setColor("reset");
        return;
    }

    string line;

    while (getline(file, line)) {
        stringstream ss(line);

        string category, name, earnedStr, possibleStr;

        getline(ss, category, ',');
        getline(ss, name, ',');
        getline(ss, earnedStr, ',');
        getline(ss, possibleStr, ',');

        float earned = stof(earnedStr);
        float possible = stof(possibleStr);

        if (category == "Homework") {
            items.push_back(make_unique<Homework>(name, earned, possible));
        }
        else if (category == "Quiz") {
            items.push_back(make_unique<Quiz>(name, earned, possible));
        }
        else if (category == "Exam") {
            items.push_back(make_unique<Exam>(name, earned, possible));
        }
    }

    file.close();

    setColor("green");
    cout << "Items loaded successfully!\n";
    setColor("reset");
}

// Deletes the saved grade file
void deleteSavedFile(const string& filename) {
    if (remove(filename.c_str()) == 0) {
        setColor("green");
        cout << "Saved file deleted.\n";
        setColor("reset");
    }
    else {
        setColor("red");
        cout << "No saved file found.\n";
        setColor("reset");
    }
}

// Validates numeric input so the program does not crash
float getValidNumber() {
    float value;

    while (true) {
        cin >> value;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            setColor("red");
            cout << "Invalid input. Please enter a number: ";
            setColor("reset");
        }
        else {
            return value;
        }
    }
}

// Displays a formatted section header
void displayHeader(const string& title) {
    cout << "\n";

    setColor("cyan");

    cout << string(50, '=') << '\n';
    cout << " " << title << '\n';
    cout << string(50, '=') << '\n';

    setColor("reset");
}

// Displays the main menu options
void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");

    setColor("pink");

    cout << "1. Set Grading Scheme\n";
    cout << "2. Add Graded Item\n";
    cout << "3. View All Items\n";
    cout << "4. Remove Item\n";
    cout << "5. Calculate Grade (Points-Based)\n";
    cout << "6. Calculate Grade (Weighted)\n";
    cout << "7. Show Highest and Lowest Grades\n";
    cout << "8. Save Graded Items\n";
    cout << "9. Load Graded Items\n";
    cout << "10. Delete Saved File\n";
    cout << "0. Exit\n";

    setColor("reset");
}

// Returns a letter grade based on the grading scheme
char getLetterGrade(float percentage, const GradingScheme& scheme) {
    if (percentage >= scheme.cutoffA) return 'A';
    if (percentage >= scheme.cutoffB) return 'B';
    if (percentage >= scheme.cutoffC) return 'C';
    if (percentage >= scheme.cutoffD) return 'D';

    return 'F';
}

// Allows the user to customize weights and grade cutoffs
void setGradingScheme(GradingScheme& scheme) {
    displayHeader("SET GRADING SCHEME");

    float hw, qz, ex;

    cout << "Enter weight for Homework (%): ";
    cin >> hw;

    cout << "Enter weight for Quizzes (%): ";
    cin >> qz;

    cout << "Enter weight for Exams (%): ";
    cin >> ex;

    float total = hw + qz + ex;

    if (total != 100.0f) {
        setColor("red");
        cout << "Weights must add up to 100%.\n";
        setColor("reset");
        return;
    }

    scheme.homeworkWeight = hw / 100.0f;
    scheme.quizWeight = qz / 100.0f;
    scheme.examWeight = ex / 100.0f;

    cout << "Enter minimum % for A: ";
    cin >> scheme.cutoffA;

    cout << "Enter minimum % for B: ";
    cin >> scheme.cutoffB;

    cout << "Enter minimum % for C: ";
    cin >> scheme.cutoffC;

    cout << "Enter minimum % for D: ";
    cin >> scheme.cutoffD;

    setColor("green");
    cout << "Grading scheme updated!\n";
    setColor("reset");
}

// Adds a homework, quiz, or exam item to the vector
void addGradedItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ADD GRADED ITEM");

    cout << "1. Homework\n";
    cout << "2. Quiz\n";
    cout << "3. Exam\n";
    cout << "Choice: ";

    int category;
    cin >> category;
    cin.ignore();

    string name;

    cout << "Name: ";
    getline(cin, name);

    cout << "Points possible: ";
    float possible = getValidNumber();

    cout << "Points earned: ";
    float earned = getValidNumber();

    try {
        if (earned < 0) {
            throw InvalidInputException("Points earned cannot be negative.");
        }
    }
    catch (const InvalidInputException& e) {
        setColor("red");
        cout << "Error: " << e.what() << '\n';
        setColor("reset");
        return;
    }

    switch (category) {
        case 1:
            items.push_back(make_unique<Homework>(name, earned, possible));
            break;

        case 2:
            items.push_back(make_unique<Quiz>(name, earned, possible));
            break;

        case 3:
            items.push_back(make_unique<Exam>(name, earned, possible));
            break;

        default:
            setColor("red");
            cout << "Invalid category.\n";
            setColor("reset");
            return;
    }

    setColor("green");
    cout << "Item added!\n";
    setColor("reset");
}

// Displays all graded items in a formatted table
void viewItems(const vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ALL GRADED ITEMS");

    if (items.empty()) {
        cout << "No items entered.\n";
        return;
    }

    cout << left << setw(5) << "#"
         << setw(20) << "Name"
         << setw(12) << "Category"
         << right << setw(10) << "Earned"
         << setw(10) << "Possible"
         << setw(10) << "Percent" << '\n';

    cout << fixed << setprecision(1);

    for (size_t i = 0; i < items.size(); ++i) {
        cout << left << setw(5) << (i + 1)
             << setw(20) << items[i]->getName()
             << setw(12) << items[i]->getCategory()
             << right << setw(10) << items[i]->getPointsEarned()
             << setw(10) << items[i]->getPointsPossible()
             << setw(9) << items[i]->getPercentage() << "%\n";
    }
}

// Uses STL algorithms to find the highest and lowest grades
void showHighestLowest(const vector<unique_ptr<GradedItem>>& items) {
    displayHeader("HIGHEST AND LOWEST GRADES");

    if (items.empty()) {
        cout << "No items to compare.\n";
        return;
    }

    auto highest = max_element(items.begin(), items.end(),
        [](const unique_ptr<GradedItem>& a, const unique_ptr<GradedItem>& b) {
            return a->getPercentage() < b->getPercentage();
        });

    auto lowest = min_element(items.begin(), items.end(),
        [](const unique_ptr<GradedItem>& a, const unique_ptr<GradedItem>& b) {
            return a->getPercentage() < b->getPercentage();
        });

    cout << fixed << setprecision(1);

    cout << "Highest Grade:\n";
    cout << (*highest)->getCategory() << " - "
         << (*highest)->getName() << ": "
         << (*highest)->getPercentage() << "%\n";

    cout << "\nLowest Grade:\n";
    cout << (*lowest)->getCategory() << " - "
         << (*lowest)->getName() << ": "
         << (*lowest)->getPercentage() << "%\n";
}

// Removes an item selected by the user
void removeItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("REMOVE ITEM");

    if (items.empty()) {
        cout << "No items to remove.\n";
        return;
    }

    for (size_t i = 0; i < items.size(); ++i) {
        cout << (i + 1) << ". "
             << items[i]->getCategory()
             << " - "
             << items[i]->getName() << '\n';
    }

    cout << "Enter item number to remove: ";

    int index;
    cin >> index;

    if (index < 1 || index > static_cast<int>(items.size())) {
        cout << "Invalid selection.\n";
        return;
    }

    items.erase(items.begin() + (index - 1));

    setColor("green");
    cout << "Item removed.\n";
    setColor("reset");
}

// Calculates grade using total points earned and possible
void calculatePointsBased(const vector<unique_ptr<GradedItem>>& items,
                          const GradingScheme& scheme) {
    displayHeader("POINTS-BASED GRADE");

    if (items.empty()) {
        cout << "No items entered.\n";
        return;
    }

    float totalEarned = 0;
    float totalPossible = 0;

    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    float percentage = (totalEarned / totalPossible) * 100;

    cout << fixed << setprecision(1);

    cout << "Overall Grade: " << percentage << "%\n";
    cout << "Letter Grade: "
         << getLetterGrade(percentage, scheme) << '\n';
}

// Calculates grade using weighted category averages
void calculateWeighted(const vector<unique_ptr<GradedItem>>& items,
                       const GradingScheme& scheme) {
    displayHeader("WEIGHTED GRADE");

    if (items.empty()) {
        cout << "No items entered.\n";
        return;
    }

    map<string, float> totals;
    map<string, int> counts;

    for (const auto& item : items) {
        string category = item->getCategory();

        totals[category] += item->getPercentage();
        counts[category]++;
    }

    float hwAvg = counts["Homework"] > 0
        ? totals["Homework"] / counts["Homework"]
        : 0;

    float quizAvg = counts["Quiz"] > 0
        ? totals["Quiz"] / counts["Quiz"]
        : 0;

    float examAvg = counts["Exam"] > 0
        ? totals["Exam"] / counts["Exam"]
        : 0;

    float finalGrade =
        (hwAvg * scheme.homeworkWeight) +
        (quizAvg * scheme.quizWeight) +
        (examAvg * scheme.examWeight);

    cout << fixed << setprecision(1);

    cout << "Homework Average: " << hwAvg << "%\n";
    cout << "Quiz Average: " << quizAvg << "%\n";
    cout << "Exam Average: " << examAvg << "%\n";

    cout << "\nFinal Weighted Grade: "
         << finalGrade << "%\n";

    cout << "Letter Grade: "
         << getLetterGrade(finalGrade, scheme) << '\n';
}

// Main program loop
int main() {
    GradingScheme scheme;

    vector<unique_ptr<GradedItem>> items;

    const string filename = "graded_items.txt";

    int choice;

    do {
        displayMenu();

        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                setGradingScheme(scheme);
                break;

            case 2:
                addGradedItem(items);
                break;

            case 3:
                viewItems(items);
                break;

            case 4:
                removeItem(items);
                break;

            case 5:
                calculatePointsBased(items, scheme);
                break;

            case 6:
                calculateWeighted(items, scheme);
                break;

            case 7:
                showHighestLowest(items);
                break;

            case 8:
                saveItems(items, filename);
                break;

            case 9:
                loadItems(items, filename);
                break;

            case 10:
                deleteSavedFile(filename);
                break;

            case 0:
                displayHeader("GOODBYE");

                setColor("green");
                cout << "Thank you for using Grade Calculator!\n";
                setColor("reset");
                break;

            default:
                setColor("red");
                cout << "Invalid choice. Please try again.\n";
                setColor("reset");
        }

    } while (choice != 0);

    return 0;
}
