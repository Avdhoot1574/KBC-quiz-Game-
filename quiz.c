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
volatile int timeout_happened = 0;

// Define color codes for text formatting (currently empty)
const char* COLOR_END = "";
const char* RED = "";
const char* GREEN = "";
const char* YELLOW = "";
const char* BLUE = "";
const char* PINK = "";
const char* AQUA = "";

// Structure to represent a question
typedef struct {
  char text[MAX_QUES_LEN]; // Question text
  char options[4][MAX_OPTION_LEN]; // Four options for the question
  char correct_option; // Correct option for the question
  int timeout; // Timeout for answering the question
  int prize_money; // Prize money for the question
} Question;

// Function prototypes
int read_questions(char* file_name, Question** questions);
void print_formatted_question(Question question);
void play_game(Question* questions, int no_of_questions);
int use_lifeline(Question* question, int* lifeline);

void timeout_handler() {
  timeout_happened = 1;
  printf("%s\n\nTime out!!!!!  Press Any Key...\n", RED);
  fflush(stdout);
}

void play_game(Question* questions, int no_of_questions) {
  int money_won = 0;
  int lifeline[] = {1, 1};

  for (int i = 0; i < no_of_questions; i++) {
    print_formatted_question(questions[i]);
    
    // Wait for input for the specified timeout duration
    DWORD start_time = GetTickCount();
    char ch = '\0';
    while (!timeout_happened && GetTickCount() - start_time < questions[i].timeout * 1000) {
      if (_kbhit()) { // Check if a key is pressed
        ch = _getch();
        break;
      }
    }

    if (ch == '\0') {
      timeout_happened = 1;
      break;
    }

    ch = toupper(ch);

    if (timeout_happened == 1) {
      break;
    }

    if (ch == 'L') {
      int value = use_lifeline(&questions[i], lifeline);
      if (value != 2) {
        i--;
      }
      continue;
    }

    if (ch == questions[i].correct_option) {
      printf("%s\nCorrect!\n", GREEN);
      money_won = questions[i].prize_money;
      printf("\n%sYou have won: Rs %d%s", BLUE, money_won, COLOR_END);
    } else {
      printf("%s\nWrong! Correct answer is %c.\n", RED, questions[i].correct_option);
      break;
    }
  }
  printf("\n\n%sGame Over! Your total winnings are: Rs %d\n", BLUE,  money_won);
}

// Function to use a lifeline during the game
int use_lifeline(Question* question, int* lifeline) {
  // Display available lifelines
  printf("\n\n%sAvailable Lifelines:%s", PINK, COLOR_END);
  if (lifeline[0]) printf("\n1. Fifty-Fifty (50/50)");
  if (lifeline[1]) printf("\n2. Skip the Question");
  printf("\nChoose a lifeline or 0 to return: ");

  // Get the user's choice
  char ch = _getch();
  printf("%c", ch);

  // Process the user's choice
  switch (ch)
  {
  case '1':
    // If Fifty-Fifty lifeline is chosen and available
    if (lifeline[0]) {
      lifeline[0] = 0; // Mark the lifeline as used
      int removed = 0;
      // Remove two incorrect options
      while (removed < 2) {
        int num = rand() % 4;
        if ((num + 'A') != question->correct_option &&
            question->options[num][0] != '\0') {
          question->options[num][0] = '\0';
          removed++;
        }
      }
      return 1; // Indicate that the lifeline was used
    }
    break;
  case '2':
    // If Skip the Question lifeline is chosen and available
    if (lifeline[1]) {
      lifeline[1] = 0; // Mark the lifeline as used
      return 2; // Indicate that the lifeline was used
    }
    break;
  }
  return 0; // Indicate that no lifeline was used
}

void print_formatted_question(Question question) {
  printf("\n\n%s%s%s", YELLOW, question.text, COLOR_END);
  for (int i = 0; i < 4; i++) {
    if (question.options[i][0] != '\0') {
      printf("%c. %s\n", ('A' + i), question.options[i]);
    }
  }
  printf("\nHurry!! You have only %d Seconds to answer..", question.timeout);
  printf("\nEnter your answer (A, B, C, or D) or L for lifeline: ");
}

int read_questions(char* file_name, Question** questions) {
  FILE *file = fopen("questions.txt", "r");  // Use the file name directly
  if (file == NULL) {
    printf("\nUnable to open the questions bank. Check the file path.\n");
    perror("Error details: ");
    exit(0);
  }
  char str[MAX_QUES_LEN];
  int no_of_lines = 0;
  while (fgets(str, MAX_QUES_LEN, file)) {
    no_of_lines++;
  }
  int no_of_questions = no_of_lines / 8;
  *questions = (Question *) malloc(no_of_questions * sizeof(Question));
  rewind(file);
  for (int i = 0; i < no_of_questions; i++) {
    fgets((*questions)[i].text, MAX_QUES_LEN, file);
    for (int j = 0; j < 4; j++) {
      fgets((*questions)[i].options[j], MAX_OPTION_LEN, file);
    }
    char option[10];
    fgets(option, 10, file);
    (*questions)[i].correct_option = option[0];

    char timeout[10];
    fgets(timeout, 10, file);
    (*questions)[i].timeout = atoi(timeout);

    char prize_money[10];
    fgets(prize_money, 10, file);
    (*questions)[i].prize_money = atoi(prize_money);
  }
  fclose(file);
  return no_of_questions;
}

// Main function
int main() {
  // Seed the random number generator
  srand(time(NULL));
  
  // Print the game title
  printf("\t\tChalo Kehlte hain KAUN BANEGA CROREPATI !!!");
  
  // Declare a pointer to hold the questions
  Question* questions;
  
  // Read questions from the file and get the number of questions
  int no_of_questions = read_questions("questions.txt", &questions);
  
  // Start the game with the read questions
  play_game(questions, no_of_questions);
  
  // Exit the program
  exit(0);
}
