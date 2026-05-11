# GradeCalculator
COSC 1437 Final Project- Grade Calculator Object-Oriented Application Edition 

A C++ console application that tracks course graded items such as homework, quizzes, and exams. The program calculates grades using both points-based and weighted methods, allows users to customize the grading scheme, and saves grade data between sessions.
 
## Author
Stephani Hernandez Estrada - COSC 1437, Spring 2026

## Description
This program is designed for students who want to track their grades during a course. Users can add graded items, view all assignments in a formatted table, remove items, add extra credit, and calculate their final grade using different grading methods.

## Features
- Menu-driven interface
- Add homework, quiz, and exam grades
- View all graded items in a formatted table
- Remove graded items
- Add or remove extra credit
- Set custom category weights and letter-grade cutoffs
- Calculate grades using points-based grading
- Calculate grades using weighted category averages
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
