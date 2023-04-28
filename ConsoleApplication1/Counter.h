#pragma once
#include <iostream>
using namespace std;
class Counter
{

public:
	virtual void count(string text, int startIndex, int endIndex, int& count) = 0;

};

