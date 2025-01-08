# Kaun Banega Crorepati (KBC) Quiz Game**
Project Creator(s): 1.Akanksha Jadhav 2.Avdhoot Nakod<br>
College: Prof. Ramkrishna More College, Akurdi<br>
Class: Bachelor of Computer Science (2nd Year)<br>
Email: nakodavdhoot@gmail.com?<br>
GitHub Profile: https://www.github.com/Avdhoot1574<br>
Linkedin Profile: https://www.linkedin.com/Avdhoot_Nakod<br>

## **Project Overview:**<br>

*Chalo Kehlte Hain* is a console-based quiz game inspired by the popular Indian TV game show *Kaun Banega Crorepati (KBC)*. In this game, players answer multiple-choice questions to win prize money. The game features lifelines, a timer for each question, and an exciting game-over scenario if the player answers incorrectly or runs out of time.<br>

### **Key Features:**
- **Multiple Choice Questions**: Players are presented with multiple-choice questions and need to select the correct option.
- **Lifelines**: The game includes two lifelines:
  1. **50/50 (Fifty-Fifty)**: Eliminates two incorrect options.
  2. **Skip**: Skips the current question.
- **Timer**: Each question has a time limit. If the player doesn't answer in time, the game ends.
- **Prize Money**: Players earn prize money for each correct answer.
- **Game Over**: The game ends when the player answers incorrectly or runs out of time.

---

## **Project Details:**

- **Project Name**: Chalo Kehlte Hain: Kaun Banega Crorepati (KBC) Quiz Game
- **Programming Language**: C
- **Features**:
  - Console-based interactive UI.
  - Read questions from an external file (`questions.txt`).
  - Handles player input, lifelines, and timeouts.
  - Colorful terminal output with ANSI escape codes for enhanced UI.

---

## **File Structure:**
├── quiz.c # Main program logic<br>
├── questions.txt # Text file containing quiz questions, options, answers, and prize money<br>
└── README.md # Project description and instructions<br>


---

## **How to Run the Game:**

1. **Clone the repository**:
   ```bash
   git clone <repository-url>

## **Question File format**
<QUESTION TEXT>
<OPTION A>
<OPTION B>
<OPTION C>
<OPTION D>
<CORRECT OPTION> (A, B, C, or D)
<TIMEOUT> (in seconds)
<PRIZE MONEY> (in rupees)


