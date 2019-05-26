#pragma once
#include <string>
#include <cmath>
#include "Stack.h"

using namespace std;

int stringToInt(string s);
int prior(char a, char b);
void calculate(Node<double>*& stackNumber, char oPerator);
void calculate2(Node<double>*& stackNumber, string subFunction);