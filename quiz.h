#ifndef QUIZ_H
#define QUIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>  // For _kbhit() and _getch()
#include <windows.h> // For Sleep()
#include <time.h>

// Define maximum lengths for question text and options
#define MAX_QUES_LEN 300
#define MAX_OPTION_LEN 100

// Global variable to track if a timeout has occurred
extern volatile int timeout_happened;

// Define color codes for text formatting (can be updated)
extern const char* COLOR_END;
extern const char* RED;
extern const char* GREEN;
extern const char* YELLOW;
extern const char* BLUE;
extern const char* PINK;
extern const char* AQUA;

// Structure to represent a question
typedef struct {
  char text[MAX_QUES_LEN]; // Question text
  char options[4][MAX_OPTION_LEN]; // Four options for the question
  char correct_option; // Correct option for the question
  int timeout; // Timeout for answering the question
  int prize_money; // Prize money for the question
} Question;

// Function prototypes
void timeout_handler();
int read_questions(char* file_name, Question** questions);
void print_formatted_question(Question question);
void play_game(Question* questions, int no_of_questions);
int use_lifeline(Question* question, int* lifeline);

#endif // QUIZ_H
