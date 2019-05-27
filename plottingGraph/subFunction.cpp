#include "subFunction.h"

int stringToInt(string s) {
	int number = 0;
	for (int i = 0; i < (int)s.length(); i++)
		number += (s[i] - '0') * (int)pow(10, s.length() - i - 1);
	return number;
}

int prior(char a, char b) {
	int t1, t2;
	switch (a) {
	case '+': t1 = 1; break;
	case '-': t1 = 2; break;
	case '*': t1 = 3; break;
	case '/': t1 = 4; break;
	case '^': t1 = 5; break;
	default: t1 = 0; break;
	}
	switch (b) {
	case '+': t2 = 1; break;
	case '-': t2 = 2; break;
	case '*': t2 = 3; break;
	case '/': t2 = 4; break;
	case '^': t2 = 5; break;
	default: t2 = 0; break;
	}
	if (t1 > t2)
		return 1;
	else
		if (t1 < t2)
			return -1;
		else
			return 0;
}

void calculate(Node<double>*& stackNumber, char oPerator) {
	if (oPerator == '+' || oPerator == '-' || oPerator == '*' || oPerator == '/' || oPerator == '^' || oPerator == '~') {
		double number2 = topStack(stackNumber);
		popStack(stackNumber);
		double number1;
		if (emptyStack(stackNumber))
			number1 = 0;
		else {
			number1 = topStack(stackNumber);
			popStack(stackNumber);
		}
		switch (oPerator) {
		case '+': pushStack(stackNumber, number1 + number2); break;
		case '-': pushStack(stackNumber, number1 - number2); break;
		case '*': pushStack(stackNumber, number1 * number2); break;
		case '/': pushStack(stackNumber, number1 / number2); break;
		case '^': pushStack(stackNumber, pow(number1, number2)); break;
		case '~': pushStack(stackNumber, log(number2) / log(number1)); break;
		}
	}
	else {
		double x = topStack(stackNumber);
		popStack(stackNumber);
		switch (oPerator) {
		case '!': pushStack(stackNumber, sqrt(x)); break;
		case '@': pushStack(stackNumber, sin(x)); break;
		case '#': pushStack(stackNumber, cos(x)); break;
		case '$': pushStack(stackNumber, tan(x)); break;
		case '%': pushStack(stackNumber, cos(x) / sin(x)); break;
		}
	}
}
