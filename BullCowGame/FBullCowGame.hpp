//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by leftovertacos on 2/12/17.
//  Copyright © 2017 leftovertacos. All rights reserved.
//

#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

using FString = std::string;
using int32 = int;

enum EGuessStatus {
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase,
    Invalid_Guess
};

struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

class FBullCowGame {
public:
    FBullCowGame();

    void Reset(); // TODO make a richer return value
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus IsGuessValid(FString) const;
    FBullCowCount SubmitValidGuess(FString);

private:
    int32 MyCurrentTry = 1;
    int32 MyMaxTries = 5;
    FString MyHiddenWord;
    bool bIsGameWon = false;
    bool IsIsogram(FString) const;
    bool IsAllLower(FString) const;
};

#endif /* FBullCowGame_hpp */
