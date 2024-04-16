//Author: Matthew Josephson
//Description: Main code for the program
//Oct 4, 2023

#include "wordle.h"
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

wordle::wordle(const Wt::WEnvironment& env) : Wt::WApplication(env) {

    Wt::WContainerWidget* container = root();//initialize the container
    
    root()->addWidget(std::make_unique<Wt::WText>("Enter guess, 5 letters maximum:  ")); // populate the container, with a welmome message
    
    wordToGuess = chooseWord(); // randomly select a word from the wordBank
    remainingGuesses = 5; // set number of guesses remaining
    
    inputBox = container->addWidget(Wt::cpp14::make_unique<Wt::WLineEdit>()); // make the input box for users to type into
    
    submitButton = container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Submit")); // initialize submit button
    resetButton = container->addWidget(Wt::cpp14::make_unique<Wt::WPushButton>("Reset")); // initialize reset button
    resetButton->setHidden(true); // hide the reset button until it is needed
    
    resultText = container->addWidget(Wt::cpp14::make_unique<Wt::WText>("<br />"));// break line, so that the gussed word is printed below

    submitButton->clicked().connect(this, &wordle::checkGuess); // when the submit button is clicked the checkGuess is called 
}

void wordle::checkGuess() {
    std::string guessedWord = inputBox->text().toUTF8(); // reads the guessed word from the input box

    std::transform(guessedWord.begin(), guessedWord.end(), guessedWord.begin(), ::tolower);// make all letters lowercase
    
    if (remainingGuesses > 0) { 
        if (isWordValid(guessedWord) == false) {
            resultText->setText(resultText->text() + "Invalid guess. The word length should be 5 letters and have no numbers.<br />"); // call the function to tell if the guessed word is valid
        } else {
            CompareWords(wordToGuess, guessedWord); // call compare words and see if the words are the same
            remainingGuesses--; // remove a guess as the word was valid
            inputBox->setText(""); // clear any words from the inputBox
            
            if (guessedWord == wordToGuess) { // check if the word is correct, compares the guessed word to the word to guess
                resultText->setText("Congratulations, you guessed the word!");
                
                submitButton->setHidden(true); // game ends, hide the submit button and show the reset button, this allows users to play again
                resetButton->setHidden(false);
                
                resetButton->clicked().connect(this, &wordle::resetGame); // Connect the button to the resetGame function to allow the game to reset
            }
        }
    } else {
        
        if (guessedWord == wordToGuess) { // check if the word is correct, compares the guessed word to the word to guess
            resultText->setText("Congratulations, you guessed the word!");
        }else{
            // does not call the reset function properly
        resultText->setText("<br />Out of attempts. The word was: " + wordToGuess); // end if user is out of attemps, and tell user the word
        }
        
        submitButton->setHidden(true); // game ends, hide the submit button and show the reset button, this allows users to play again
        resetButton->setHidden(false);
                
        resetButton->clicked().connect(this, &wordle::resetGame); // Connect the button to the resetGame function to allow the game to reset
    }
}

void wordle::CompareWords(const std::string& wordToGuess, const std::string& guessedWord) {
 
    std::string letters; // initalize a variable to store the letters from the guessed word 
    
    for (int i = 0; i < wordToGuess.length(); ++i) {
        if (guessedWord[i] == wordToGuess[i]) {
            letters += "<span style='color: green;'>" + std::string(1, guessedWord[i]) + "</span>"; // if the letter is in the right index in the word to guess, change the letter to green and add to the string
        } else if (wordToGuess.find(guessedWord[i]) != std::string::npos) {
            letters += "<span style='color: orange;'>" + std::string(1, guessedWord[i]) + "</span>"; // if the letter is in the wrong index, but is in the word to guess, change the letter to green and add to the string
        } else {
            letters += guessedWord[i]; // if the letter is not in the word, add it back in the same text colour
        }
    }
    resultText->setText(resultText->text() + letters + "<br />"); // print the word on the webpage and break line
}

void wordle::resetGame() {
    
    // reset the game
    wordToGuess = chooseWord(); // pick a new word to guess by calling the chooseWord function
    remainingGuesses = 5; // reset the remaining guesses counter
    resultText->setText(""); // clear the text from around the text box
    submitButton->setHidden(false); // unhide the the submit button so users can use it again
    resetButton->setHidden(true); // hide the rest button until is is needed again
    inputBox->setText(""); // clear any words from the inputBox
    
    resetButton->clicked().connect(this, &wordle::checkGuess); // call the checkGuess to reset the game when the reset button is clicked
    
    resultText->setText(resultText->text() + "<br />"); // print the word on the webpage and break line
}

std::string wordle::chooseWord() {
    //chose a word from the wordBank.txt file for the program to use
    std::vector<std::string> words; // create a vector named words to store the words that are read in
    std::ifstream file("wordBank.txt"); // read in the words from the txt file
    std::string line; // initialize a varible of string type to use
    
    // read in the txt file and store it in the line variable 
    while (getline(file, line)) {
        words.push_back(line); // words are stored in the vector, pusing each word back as the new one is put in
    }
    
    // check to make sure the file is not empty, then choose a random word from the vector by using a random index in the valid range
    if (!words.empty()) {
        int randomIndex = std::rand() % words.size();
        return words[randomIndex]; // return chosen for the program to use
    }
}

bool wordle::isWordValid(std::string& guessedWord){
    if (guessedWord.length() != 5){ // check if the word is invalid if it is not 5 letters in length
        return false;
    }
    else{
        for (int i = 0; i < 5; i++) {
            if(isdigit(guessedWord[i])){
                return false; // return false is there is an int value in the string
            }
        } 
        return true; // otherwise return true as it is  a valid string
    }
}

