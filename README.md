Word Quiz
====================
This is a team project for Software English
-------------
   ```bash
   This is a word quiz program made of C.
   There's a wordbook in /wordbooks/. You can add it according to the form if you need it.
   It's very simple and intuitive
   ```
# A short explanation
   ```bash
   1. Choose a wordbook.
   2. Practice words.
   3. Test the words.
   4. Add a wordbook and a word
   ```
   ```Test environment : ``` ![window](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Code](https://img.shields.io/badge/Visual_Studio_Code-0078D4?style=for-the-badge&logo=visual%20studio%20code&logoColor=white)
            ```Build Code : ``` ![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)

   

## How to Install and Run the WordQuiz

**Clone the repository:**
   ```bash
   git clone https://github.com/OPCIO0568/wordquiz.git master
   cd wordquiz
   ```

**Compile the source code:**
   ```bash
   gcc -o wordquiz wordquiz.c
   ```

**Run the program:**
   ```bash
   ./wordquiz
   ```

## How to Play the WordQuiz

**Program Run:**
   ```bash
   ./wordquiz
   ```

**Main Menu:**
   Choose a number corresponding to 1 to 4.
   ```
   *** Word Quiz ***

   1. List all wordbooks
   2. Show the words in a wordbook
   3. Test with a wordbook
   4. Exit
   5. Add a wordbook
   6. Add a word to a wordbook
   > (1 ~ 6) 
   ```

**List wordbooks:**
   You can also add a Wordbook directly to the "workbooks" folder.
   ```
   *** Word Quiz ***

   1. List all wordbooks
   2. Show the words in a wordbook
   3. Test with a wordbook
   4. Exit
   5. Add a wordbook
   6. Add a word to a wordbook
   > 1
   
   ---
   voca1
   voca2
   ---
   ```

**Test with a wordbook:**
   ```
   Type in the name of the Wordbook?
   > (voca1/voca2 or other wordbook)

   -----
   Which type of test do you want to take?
   1. Word -> Meaning
   2. Meaning -> Word
   > (1 or 2)
   Q. deem to be
   ? (Answer)
   ```

**Word Book add**
   ```
   5. Add a wordbook
   >5
   Enter the name of the new wordbook: (name)
   Wordbook (name) has been successfully created.
   ```

**Word add for WordBook**
   ```
   6. Add a word to a wordbook
   >6

   ----
   voca1
   voca2
   ----
   Enter the name of the wordbook to add a word: (wordbook name)
   Enter the word: (word)
   Enter the meaning: (meaning)
   Word (word) has been successfully added to the wordbook (wordbook).
   ```
**Program exit:**
   ```
   *** Word Quiz ***

   1. List all wordbooks
   2. Show the words in a wordbook
   3. Test with a wordbook
   4. Exit
   5. Add a wordbook
   6. Add a word to a wordbook
   > 4
   ```

### Screenshots
- **Main Menu:**   
  ![MainMenu](screenshots/main_menu.PNG)
  
- **Quiz:**   
  ![Quiz](screenshots/quiz_question.PNG)
  
- **Check the score:**   
  ![CheckScore](screenshots/check_score.PNG)

## Credits

- **Team:** Group#202
- **Contributors:** [Wien0128](https://github.com/wien0128), [JeonYeongwoo](https://github.com/JeonYeongwoo), [BumGyo](https://github.com/BumGyo), [OPCIO0568](https://github.com/OPCIO0568)
- **Organization:** Department of Software, Chungbuk National University

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE.md) file for details.
