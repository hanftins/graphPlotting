#pragma once
#include <string>
#include <cmath>
#include "Stack(plot).h"

using namespace std;

int stringToInt(string s);
int prior(char a, char b);
void calculate(Node<double>*& stackNumber, char oPerator);
double eval(string f, double x);