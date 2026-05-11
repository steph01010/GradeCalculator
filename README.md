# Grade Calculator (OOP Edition)

A C++ console application that tracks graded items such as homework, quizzes, and exams. The program calculates grades using both points-based and weighted methods, allows users to customize the grading scheme, and saves grade data between sessions.

## Author
[Your Name] - COSC 1437, [Semester Year]

## Description

This program is designed for students who want to track their grades during a course. Users can add graded items, view assignments in a formatted table, remove items, calculate grades using different grading methods, and save grade data between sessions.

## Features

- Menu-driven interface
- Add homework, quiz, and exam grades
- View all graded items in a formatted table
- Remove graded items
- Set custom category weights and letter-grade cutoffs
- Calculate grades using points-based grading
- Calculate grades using weighted category averages
- Show highest and lowest grades using STL algorithms
- Save and load graded items from a text file
- Delete saved grade data
- Input validation for non-numeric and negative values
- ANSI color output for easier readability

## Files

| File          | Purpose                                      |
|---------------|----------------------------------------------|
| main.cpp      | Driver program: menu loop and main functions |
| GradedItem.h  | Base class for all graded items              |
| Homework.h    | Derived class for homework items             |
| Quiz.h        | Derived class for quiz items                 |
| Exam.h        | Derived class for exam items                 |
| USER_GUIDE.md | End-user instructions                        |
| README.md     | Project overview and build instructions      |

## How to Build

Using g++:

```bash
g++ -std=c++17 main.cpp -o GradeCalculator
```

## How to Run

macOS / Linux:

```bash
./GradeCalculator
```

Windows:

```bash
GradeCalculator.exe
```

## Requirements

- C++17 or newer compiler
- Terminal or command prompt that supports console input/output

## Course Concepts Demonstrated

This project demonstrates concepts from COSC 1437 Chapters 11-18, including vectors, STL algorithms, file I/O, classes, inheritance, polymorphism, smart pointers, formatted output, and menu-driven programming. It also includes UX enhancements from Labs 19-22, such as input validation, file saving/loading, color output, and extra credit support.
