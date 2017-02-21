//
//  main.cpp
//  BullCowGame
//
//  Created by leftovertacos on 2/12/17.
//  Copyright © 2017 leftovertacos. All rights reserved.
//

#include <iostream>
#include "FBullCowGame.hpp"

using FText = std::string;
using int32 = int;

const FText BALLS = "8";
const FText HEAD  = "D";

void PrintIntro();
FText GetValidGuess();
FText GetShaft(int32);
FText RenderPenis();
void ShowGuess(FText);
void PrintGameSummary();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame;

int main() {

    do {
        PrintIntro();
        PlayGame();
    }
    
    while (AskToPlayAgain());
    
    return 0;
}

void PrintIntro() {
    std::cout << "\nWelcome to Bulls and Cows\n\n";
    std::cout << "          }   {            ___ "<< std::endl;
    std::cout << "          (o o)           (o O)  "<< std::endl;
    std::cout << "  /--------\\ /             \\ /-------\\"<< std::endl;
    std::cout << " / |       |O               O|       | \\ "<< std::endl;
    std::cout << "*  |-" << RenderPenis() << "-|                 |-------|  *"<< std::endl;
    std::cout << "   ^       ^                 ^       ^"<< std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram?\n\n";
}

FText RenderPenis() {
    FText Shaft = GetShaft(BCGame.GetHiddenWordLength());
    return BALLS + Shaft + HEAD + FText(3 - Shaft.length(), '-');
}

FText GetShaft(int32 InterestLevel) {
    if (InterestLevel > 7) {
        return "===";
    } else if (InterestLevel > 5) {
        return "==";
    } else {
        return "=";
    }
}

FText GetValidGuess() {
    EGuessStatus Status = EGuessStatus::Invalid_Guess;
    FText guess;
    
    do {
        std::cout << "\nTry (" << BCGame.GetCurrentTry() << "/";
        std::cout << BCGame.GetMaxTries() << ") ";
        std::cout <<"Enter your guess: ";
        std::getline(std::cin, guess);
        
        Status = BCGame.IsGuessValid(guess);
        
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please use only lower case letters\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters\n";
                break;
            default:
                break; // assume valid
        }
    } while (Status != EGuessStatus::OK);
    return guess;
}

void ShowCount(FBullCowCount Count) {
    std::cout << "Bulls = " << Count.Bulls;
    std::cout << ". Cows = " << Count.Cows << std::endl;
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "\nGreat job, you won!\n\n";
    } else {
        std::cout << "\nBetter luck next time!\n\n";
    }
};

void PlayGame() {
    while (!BCGame.IsGameWon() && BCGame.GetMaxTries() > BCGame.GetCurrentTry()) {
        FText guess = GetValidGuess();
        
        FBullCowCount Count = BCGame.SubmitValidGuess(guess);
        ShowCount(Count);
    }
    PrintGameSummary();
    BCGame.Reset();
}

bool AskToPlayAgain() {
    FText PlayAgain;
    std::cout << "Want to play again? (y/n): ";
    std::getline(std::cin, PlayAgain);
    return PlayAgain[0] == 'y' || PlayAgain[0] == 'Y';
}
