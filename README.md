# WebWordle
Welcome to WebWordle, a browser-based word guessing game inspired by the popular Wordle.

**How to Play**

Start the Game: Open the game in any modern web browser.
Guess the Word: You have six tries to guess a five-letter word.
Color Cues: After each guess, the color of the tiles will change to show how close your guess was to the word.

* Green: Correct letter in the correct position.
* Yellow: Correct letter in the wrong position.
* Gray: Incorrect letter.
Winning: Solve the puzzle in six tries or fewer to win. Fail, and the correct word will be revealed!

Installation
To set up the game locally:

**Running the game:**

1. To setup the environment, install C++ compiler tools, CMake, Boost, and Wt.
2. While on your computers terminal, run the command make while within the application's folder
3. Once the application has been compiled, run the command ./wordle --docroot . --http-listen 0.0.0.0:8080
4. Load up the server link on your browser to start playing the game!

