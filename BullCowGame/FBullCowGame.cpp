//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by leftovertacos on 2/12/17.
//  Copyright © 2017 leftovertacos. All rights reserved.
//

#include "FBullCowGame.hpp"
#include <map>
#include <ctype.h>

#define TMap std::map

using int32 = int;

FBullCowGame::FBullCowGame() {
    Reset();
};

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; };
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; };

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset() {
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "bungalo";
    MyHiddenWord = HIDDEN_WORD;
    MyMaxTries = MAX_TRIES;
    MyCurrentTry = 1;
    bIsGameWon = false;
};

bool FBullCowGame::IsGameWon() const {
    return bIsGameWon;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
    TMap<char, bool> SeenLetters;
    for (auto Letter : Guess) {
        Letter = tolower(Letter);
        if (SeenLetters[Letter]) {
            return false;
        } else {
            SeenLetters[Letter] = true;
        }
    }
    return true;
};

bool FBullCowGame::IsAllLower(FString Guess) const {
    for (auto Letter : Guess) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
};

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const {
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    } else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    } else if (!IsAllLower(Guess)) {
        return EGuessStatus::Not_Lowercase;
    } else {
        return EGuessStatus::OK;
    }
};

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    MyCurrentTry++;
    FBullCowCount BullCowCount;

    int32 HiddenWordLength = MyHiddenWord.length();

    for (int32 i = 0; i < HiddenWordLength; ++i) {
        char GuessChar = Guess[i];
        for (int32 j = 0; j < HiddenWordLength; ++j) {
            char HiddenChar = MyHiddenWord[j];
            if (HiddenChar == GuessChar) {
                if (i == j) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }

    if (MyHiddenWord == Guess) {
        bIsGameWon = true;
    }

    return BullCowCount;
};
