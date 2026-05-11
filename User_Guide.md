# User Guide: Grade Calculator

## Introduction

The Grade Calculator is a console program that helps users track grades for homework, quizzes, and exams. It can calculate the final grade using either total points or weighted category averages. The program also allows users to save and load their grade data.

## Getting Started

Build and run the program using the instructions in the README file. Once the program starts, a main menu will appear with numbered options.

## Menu Walkthrough

### 1. Set Grading Scheme

This option lets you change the grading weights and letter-grade cutoffs.

The program asks for:
- Homework weight as a percentage
- Quiz weight as a percentage
- Exam weight as a percentage

The three weights must add up to 100%.

The program also asks for:
- Minimum percentage for an A
- Minimum percentage for a B
- Minimum percentage for a C
- Minimum percentage for a D

Example:

```text
Homework: 20
Quizzes: 30
Exams: 50
```

### 2. Add Graded Item

This option lets you add a homework, quiz, or exam grade.

The program asks for:
- Category number: 1 for Homework, 2 for Quiz, 3 for Exam
- Name of the item
- Points possible
- Points earned

Points earned cannot be negative. The program also checks for invalid non-numeric input.

Example:

```text
Select category:
1. Homework
2. Quiz
3. Exam
Choice: 1
Name: Homework 1
Points possible: 100
Points earned: 95
```

### 3. Add Extra Credit

This option lets you add extra credit points to the points-based grade calculation.

The program asks for:
- Extra credit points to add

The number cannot be negative.

Example:

```text
Enter extra credit points to add: 5
```

### 4. View All Items

This option displays all entered graded items in a formatted table.

The table shows:
- Item number
- Name
- Category
- Points earned
- Points possible
- Percentage

It also displays the current extra credit total.

### 5. Remove Item

This option lets you remove a graded item by number. It also lets you remove extra credit.

The program asks for:
- The item number to remove
- Or the extra credit option

Enter `0` to cancel.

### 6. Calculate Grade (Points-Based)

This option calculates the final grade by adding all points earned and dividing by all points possible.

Extra credit is included in this calculation.

Use this option when your class grade is based mainly on total points.

### 7. Calculate Grade (Weighted)

This option calculates the final grade by averaging each category and applying the grading weights.

Example:

```text
Homework Average: 90.0%
Quiz Average: 85.0%
Exam Average: 88.0%

Final Weighted Grade: 87.7%
Letter Grade: B
```
### 8. Show Highest and Lowest Grades

This option displays the graded item with the highest percentage and the graded item with the lowest percentage. The feature uses STL algorithms to compare assignment percentages.

Example:

```text
Highest Grade:
Homework - Homework 1: 95.0%

Lowest Grade:
Quiz - Quiz 2: 72.0%
```

Use this option when your class has separate category weights, such as homework being 20%, quizzes being 30%, and exams being 50%.

### 9. Save Graded Items

This option saves the current graded items to a file called:

```text
graded_items.txt
```

This allows the grades to be loaded again later.

### 10. Load Graded Items

This option loads saved grades from `graded_items.txt`.

If the file does not exist, the program displays an error message.

### 11. Delete Saved File

This option deletes the saved grade file and clears the current graded items and extra credit.

The program asks for confirmation before deleting:

```text
Are you sure you want to delete saved data? (y/n):
```

### 0. Exit

This option exits the program. The program saves the current graded items before closing.

## Sample Session

```text
GRADE CALCULATOR - MAIN MENU
1. Set Grading Scheme
2. Add Graded Item
3. Add Extra Credit
4. View All Items
5. Remove Item
6. Calculate Grade (Points-Based)
7. Calculate Grade (Weighted)
8. Save Graded Items
9. Load Graded Items
10. Delete Saved File
0. Exit

Enter choice: 1

SET GRADING SCHEME
Enter weight for Homework (%): 20
Enter weight for Quizzes (%): 30
Enter weight for Exams (%): 50
Weights saved!

Enter minimum % for A: 90
Enter minimum % for B: 80
Enter minimum % for C: 70
Enter minimum % for D: 60
Cutoffs saved!

Enter choice: 2

ADD GRADED ITEM
Select category:
1. Homework
2. Quiz
3. Exam
Choice: 1
Name: Homework 1
Points possible: 100
Points earned: 95
Item added!

Enter choice: 2

ADD GRADED ITEM
Select category:
1. Homework
2. Quiz
3. Exam
Choice: 2
Name: Quiz 1
Points possible: 50
Points earned: 45
Item added!

Enter choice: 4

ALL GRADED ITEMS
#    Name                Category        Earned  Possible   Percent
1    Homework 1          Homework          95.0     100.0     95.0%
2    Quiz 1              Quiz              45.0      50.0     90.0%

Extra Credit: 0.0

Enter choice: 6

POINTS-BASED GRADE
Earned: 140.0 / 150.0
Extra Credit: 0.0
Total: 140.0 / 150.0
Overall: 93.3%
Letter Grade: A
```

## Sprint Features

### Sprint 19: Input Validation

The program uses input validation to prevent non-numeric input from crashing the program. If the user enters invalid text instead of a number, the program asks again.

### Sprint 20: File Persistence

The program can save and load graded items using a text file. This allows users to keep their grade data between program runs.

### Sprint 21: Color Output

The program uses ANSI color codes to display success messages, error messages, and menu text in different colors. This makes the program easier to read.

### Sprint 22: Extra Credit

The program allows users to add extra credit points. Extra credit is included in the points-based grade calculation.

## Understanding Your Results

The points-based grade uses total points earned divided by total points possible. This method is useful when every assignment is part of one large point total.

The weighted grade calculates an average for each category, such as homework, quizzes, and exams. Then it multiplies each average by the category weight. This method is useful when the class syllabus gives each category a specific percentage.

## Known Limitations

- The program currently saves graded items but does not save the custom grading scheme.
- The weighted grade calculation does not include extra credit.
- ANSI colors may not display correctly in every terminal.

## Troubleshooting

### Problem: The program says the saved file cannot be opened.

Make sure `graded_items.txt` exists in the same folder as the program. If no grades have been saved yet, choose option 8 to save grades first.

### Problem: The program says the weights do not add up to 100%.

Re-enter the homework, quiz, and exam weights so they total exactly 100.

### Problem: The program rejects my input.

Make sure number prompts receive numbers only. Do not type letters or symbols when the program asks for points, percentages, or menu choices.
