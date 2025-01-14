#include "quiz.h"

// Global variable definition
volatile int timeout_happened = 0;

// Define color codes for text formatting (can be updated)
const char* COLOR_END = "";
const char* RED = "";
const char* GREEN = "";
const char* YELLOW = "";
const char* BLUE = "";
const char* PINK = "";
const char* AQUA = "";

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

    DWORD start_time = GetTickCount();
    char ch = '\0';
    while (!timeout_happened && GetTickCount() - start_time < questions[i].timeout * 1000) {
      if (_kbhit()) {
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

int use_lifeline(Question* question, int* lifeline) {
  printf("\n\n%sAvailable Lifelines:%s", PINK, COLOR_END);
  if (lifeline[0]) printf("\n1. Fifty-Fifty (50/50)");
  if (lifeline[1]) printf("\n2. Skip the Question");
  printf("\nChoose a lifeline or 0 to return: ");

  char ch = _getch();
  printf("%c", ch);

  switch (ch)
  {
  case '1':
    if (lifeline[0]) {
      lifeline[0] = 0;
      int removed = 0;
      while (removed < 2) {
        int num = rand() % 4;
        if ((num + 'A') != question->correct_option &&
            question->options[num][0] != '\0') {
          question->options[num][0] = '\0';
          removed++;
        }
      }
      return 1;
    }
    break;
  case '2':
    if (lifeline[1]) {
      lifeline[1] = 0;
      return 2;
    }
    break;
  }
  return 0;
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
  FILE *file = fopen("questions.txt", "r");
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

int main() {
  srand(time(NULL));
  printf("\t\tChalo Kehlte hain KAUN BANEGA CROREPATI !!!");

  Question* questions;
  int no_of_questions = read_questions("questions.txt", &questions);
  play_game(questions, no_of_questions);
  exit(0);
}
