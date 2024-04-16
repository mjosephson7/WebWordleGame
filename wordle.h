//Author: Matthew Josephson
//Description: Header file declares functions and variables
//Oct 4, 2023

//header file
#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>


class wordle : public Wt::WApplication {
public:
    wordle(const Wt::WEnvironment& env);

//private functions from wordle.cpp
private:
    void checkGuess();
    void CompareWords(const std::string& targetWord, const std::string& guessedWord);
    void resetGame();
    std::string chooseWord();
    bool isWordValid(std::string& guessedWord);
    
    //wt widgets
    std::string wordToGuess;
    Wt::WText* welcomeText;
    Wt::WLineEdit* inputBox;
    Wt::WPushButton* submitButton;
    Wt::WPushButton* resetButton;
    Wt::WText* resultText;
    
    int remainingGuesses;
    
};




