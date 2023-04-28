#pragma once
#include "Counter.h"
#include "iostream"


using namespace std;
class WordCounter : public Counter
{
public:
    void countWords(string text, int& count) {
        count = 0;
        bool inWord = false;
        for (int i = 0; i < text.length(); i++) {
            char c = text[i];
            if (isalnum(c)) {
                if (!inWord) {
                    inWord = true;
                    count++;
                }
            }
            else {
                inWord = false;
            }
        }
    }



};

