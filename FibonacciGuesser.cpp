// FibonacciGuesser.cpp : This file contains the 'main' function. Program execution begins and ends there.
// It also contains the computeNum() function.

/*Include iostream*/
#include <iostream>
/*Include algorithms*/
#include<algorithm>
/*Include strings*/
#include<string>
/*Include exceptions*/
#include<stdexcept>

/*Set the namespace*/
using namespace std;

/*Exception class--throw exceptions later.  Not in a seperate file.*/
class BadInputException : public std::runtime_error {
public:
    /*This is the constructor for the exception.*/
    BadInputException() : std::runtime_error{"The user entered a character that was not an int."} {}
};

/*Fibonacci function*/
int computeNum(int baseNum) {
    /*Base case*/
    if (baseNum < 2) {
        return baseNum;
    }
    /*Recursion*/
    return computeNum(baseNum - 1) + computeNum(baseNum - 2);
}

/*Check input function*/
int checkInput(string myString) {
    int badDigitCount = 0;
    for (int i = 0; i < int(myString.size()); i++) {
        if (!(isdigit(myString.at(i)))) {
            badDigitCount++;
        }
    }
    if (badDigitCount > 0) {
        /*Throw an exception*/
        /*Keeping this out of the for loop ensures the exception is only thrown once.*/
        throw BadInputException{};
    }
    else {
        return stoi(myString);
    }
    return 0;
}

/*Main*/
int main()
{
  
    string userNum;

    cout << "Welcome to the Fibonacci guessing game.  " << endl;
    cout << "Please enter a number to compute the final number in the Fibonacci sequence of.  ";
    cout << "If you guess the number correctly, you win.  You have 3 guesses.  Enter the number to compute the sequence of (must be an int between 1 and 50): ";

    /*Input a string for error checking, and later turn the string into an int.*/
    cin >> userNum;

    /*Get the string's size.*/
    int size = int(userNum.size());
   
    /*Remove white spaces.*/  
    userNum.erase(remove_if(userNum.begin(), userNum.end(), isspace), userNum.end());

    //boolean variable check.
    bool keepRunning = true;

    /*User num input error checking.*/
    while (keepRunning)  {
        if (userNum.size() == 1 && isdigit(userNum.at(0)) && int(userNum.at(0)) >= 0 ) {
            cout << "Got a valid number, " << stoi(userNum) << "!" << endl;
            keepRunning = false;
          
        }
        else if (userNum.size() == 2 && isdigit(userNum.at(0)) && isdigit(userNum.at(1)) && stoi(userNum) <= 50 && stoi(userNum) >= 0) {
            cout << "Got a valid number, " << stoi(userNum) << "!" << endl;
            keepRunning = false;
          
        }
        else {
            cout << "BAD INPUT.  Please enter an integer again.  The integer must be between 0 and 50: ";
            cin >> userNum;
            keepRunning = true;
        } 
    }

    /* Variables needed for playing the game, declared here. */
    //this is the cast int version
    int saveF = computeNum(stoi(userNum));

    /*End the loop after three valid tries.*/
    int endLoop = 3;

    /*Set a boolean to check for the correct input.*/
    bool isCorrect = true;

    /*The user's guess is now a string.*/
    string userGuess;

    /*Save the number the user enters after checking.*/
    int saveInput = 0;

    /*Set a bool to keep track of throwing exceptions.*/
    bool threwException = false;

    /*Lets the user enter guesses and error checks them in the same loop by calling a function.*/
    while (endLoop != 0 && !(endLoop < 0)) {
        cout << "Please enter your guess.  You have " << endLoop << " guesses left: ";
        cin >> userGuess;

        /*Remove white spaces.*/
        userGuess.erase(remove_if(userGuess.begin(), userGuess.end(), isspace), userGuess.end());

            try {
                saveInput = checkInput(userGuess);
                threwException = false;
            }
            catch (const BadInputException& badInputException) {
                cout << "There was an exception, and the details of that exception are: " << badInputException.what() << endl;
                threwException = true;
                endLoop++;
                /*add another try if the guess is invalid*/
                /*If there is one bad character, the loop continues and skips the bad input.*/
                //Do not use a break statement.
            }
     
        /*Check if the input is equal to the correct answer.*/
        if (saveInput == saveF) {
            cout << "\nYou win!  You guessed " << saveF << " correctly with " << endLoop << " tries left!" << endl;
            break;
        }
        else if (endLoop != 0 && threwException == false) {
                cout << userGuess << " was incorrect.  ";
                isCorrect = false;
        } 
        else if(threwException == true) {
            cout << "Threw an exception.  Take another guess." << endl;
        }
        endLoop--;
    }/*end while loop contents.*/

    /*Output the final outcome of the game.*/
    cout << "The final number of the fibonacci sequence is " << saveF << "." << endl;
    if (!isCorrect) {
        cout << "Sorry, the computer won the guessing game.  Run again to play again." << endl;
    }
  
}
//End MAIN
