#pragma once
#include "Counter.h"
#include "iostream"
using namespace std;
class CharacterCounter : public Counter
{
public:
    void count(string text, int startIndex, int endIndex, int& count) {
        count = 0;
        for (int i = startIndex; i < endIndex; i++) {
            if (text[i] != ' ' && text[i] != '\n' && text[i] != '\r') {
                count++;
            }
        }
    }


};

