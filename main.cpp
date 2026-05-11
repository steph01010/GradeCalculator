#include <iostream>
#include <vector>
#include <iomanip>
#include <memory>
#include <string>
#include "GradedItem.h"
#include "Homework.h"
#include "Quiz.h"
#include "Exam.h"

using namespace std;

struct GradingScheme {
    float homeworkWeight = 0.20f;
    float quizWeight = 0.30f;
    float examWeight = 0.50f;
    float cutoffA = 90.0f;
    float cutoffB = 80.0f;
    float cutoffC = 70.0f;
    float cutoffD = 60.0f;
};

void displayHeader(const string& title) {
    cout << "\n";
    cout << string(50, '=') << '\n';
    cout << "  " << title << '\n';
    cout << string(50, '=') << '\n';
}

void displaySeparator() {
    cout << string(50, '-') << '\n';
}

void displayMenu() {
    displayHeader("GRADE CALCULATOR - MAIN MENU");
    cout << "1. Set Grading Scheme\n";
    cout << "2. Add Graded Item\n";
    cout << "3. View All Items\n";
    cout << "4. Remove Item\n";
    cout << "5. Calculate Grade (Points-Based)\n";
    cout << "6. Calculate Grade (Weighted)\n";
    cout << "0. Exit\n";
    displaySeparator();
}

char getLetterGrade(float percentage, const GradingScheme& scheme) {
    if (percentage >= scheme.cutoffA) return 'A';
    if (percentage >= scheme.cutoffB) return 'B';
    if (percentage >= scheme.cutoffC) return 'C';
    if (percentage >= scheme.cutoffD) return 'D';
    return 'F';
}

void setGradingScheme(GradingScheme& scheme) {
    displayHeader("SET GRADING SCHEME");

    cout << "-- Category Weights --\n";
    float hw, qz, ex;
    cout << "Enter weight for Homework (%): ";
    cin >> hw;
    cout << "Enter weight for Quizzes (%): ";
    cin >> qz;
    cout << "Enter weight for Exams (%): ";
    cin >> ex;

    float total = hw + qz + ex;
    if (total != 100.0f) {
        cout << "Weights must sum to 100%. Got " << total << "%. Try again.\n";
        return;
    }

    scheme.homeworkWeight = hw / 100.0f;
    scheme.quizWeight = qz / 100.0f;
    scheme.examWeight = ex / 100.0f;
    cout << "Weights saved!\n";

    cout << "\n-- Letter Grade Cutoffs --\n";
    cout << "Enter minimum % for A: ";
    cin >> scheme.cutoffA;
    cout << "Enter minimum % for B: ";
    cin >> scheme.cutoffB;
    cout << "Enter minimum % for C: ";
    cin >> scheme.cutoffC;
    cout << "Enter minimum % for D: ";
    cin >> scheme.cutoffD;
    cout << "Cutoffs saved!\n";
}

void addGradedItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ADD GRADED ITEM");

    cout << "Select category:\n";
    cout << "1. Homework\n";
    cout << "2. Quiz\n";
    cout << "3. Exam\n";
    cout << "Choice: ";

    int category;
    cin >> category;
    cin.ignore();

    cout << "Name: ";
    string name;
    getline(cin, name);

    cout << "Points possible: ";
    float possible;
    cin >> possible;

    cout << "Points earned: ";
    float earned;
    cin >> earned;

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
            cout << "Invalid category.\n";
            return;
    }
    cout << "Item added!\n";
}

void viewItems(const vector<unique_ptr<GradedItem>>& items) {
    displayHeader("ALL GRADED ITEMS");
    if (items.empty()) {
        cout << "No items entered yet.\n";
        return;
    }
    cout << left << setw(5) << "#"
         << setw(20) << "Name"
         << setw(12) << "Category"
         << right << setw(10) << "Earned"
         << setw(10) << "Possible"
         << setw(10) << "Percent" << '\n';
    displaySeparator();
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

void removeItem(vector<unique_ptr<GradedItem>>& items) {
    displayHeader("REMOVE ITEM");
    if (items.empty()) {
        cout << "No items to remove.\n";
        return;
    }
    for (size_t i = 0; i < items.size(); ++i) {
        cout << (i + 1) << ". " << items[i]->getCategory()
             << " - " << items[i]->getName() << '\n';
    }
    cout << "Enter item number to remove (0 to cancel): ";
    int index;
    cin >> index;

    if (index < 1 || index > static_cast<int>(items.size())) {
        cout << "Cancelled.\n";
        return;
    }
    cout << "Removed: " << items[index - 1]->getName() << '\n';
    items.erase(items.begin() + (index - 1));
}

void calculatePointsBased(const vector<unique_ptr<GradedItem>>& items,
                           const GradingScheme& scheme) {
    displayHeader("POINTS-BASED GRADE");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float totalEarned = 0, totalPossible = 0;
    for (const auto& item : items) {
        totalEarned += item->getPointsEarned();
        totalPossible += item->getPointsPossible();
    }

    float percentage = (totalPossible > 0) ? (totalEarned / totalPossible) * 100 : 0;

    cout << fixed << setprecision(1);
    cout << "Total Earned: " << totalEarned << " / " << totalPossible << '\n';
    cout << "Overall: " << percentage << "%\n";
    cout << "Letter Grade: " << getLetterGrade(percentage, scheme) << '\n';
}

void calculateWeighted(const vector<unique_ptr<GradedItem>>& items,
                        const GradingScheme& scheme) {
    displayHeader("WEIGHTED GRADE CALCULATION");
    if (items.empty()) {
        cout << "No items to calculate.\n";
        return;
    }

    float hwTotal = 0, hwCount = 0;
    float quizTotal = 0, quizCount = 0;
    float examTotal = 0, examCount = 0;

    for (const auto& item : items) {
        if (item->getCategory() == "Homework") {
            hwTotal += item->getPercentage();
            hwCount++;
        } else if (item->getCategory() == "Quiz") {
            quizTotal += item->getPercentage();
            quizCount++;
        } else if (item->getCategory() == "Exam") {
            examTotal += item->getPercentage();
            examCount++;
        }
    }

    float hwAvg = hwCount > 0 ? hwTotal / hwCount : 0;
    float quizAvg = quizCount > 0 ? quizTotal / quizCount : 0;
    float examAvg = examCount > 0 ? examTotal / examCount : 0;

    float finalGrade = (hwAvg * scheme.homeworkWeight)
                     + (quizAvg * scheme.quizWeight)
                     + (examAvg * scheme.examWeight);

    cout << fixed << setprecision(1);
    cout << "Homework Average:  " << hwAvg << "% ("
         << (scheme.homeworkWeight * 100) << "% weight)\n";
    cout << "Quiz Average:      " << quizAvg << "% ("
         << (scheme.quizWeight * 100) << "% weight)\n";
    cout << "Exam Average:      " << examAvg << "% ("
         << (scheme.examWeight * 100) << "% weight)\n";
    cout << "\nFinal Weighted Grade: " << finalGrade << "%\n";
    cout << "Letter Grade: " << getLetterGrade(finalGrade, scheme) << '\n';
}

int main() {
    GradingScheme scheme;
    vector<unique_ptr<GradedItem>> items;

    int choice = 0;
    do {
        displayMenu();
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: setGradingScheme(scheme); break;
            case 2: addGradedItem(items); break;
            case 3: viewItems(items); break;
            case 4: removeItem(items); break;
            case 5: calculatePointsBased(items, scheme); break;
            case 6: calculateWeighted(items, scheme); break;
            case 0:
                displayHeader("GOODBYE");
                cout << "Thank you for using Grade Calculator!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
