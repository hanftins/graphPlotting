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
	double number2 = topStack(stackNumber);
	popStack(stackNumber);
	double number1 = topStack(stackNumber);
	popStack(stackNumber);
	switch (oPerator) {
	case '+': pushStack(stackNumber, number1 + number2); break;
	case '-': pushStack(stackNumber, number1 - number2); break;
	case '*': pushStack(stackNumber, number1 * number2); break;
	case '/': pushStack(stackNumber, number1 / number2); break;
	case '^': pushStack(stackNumber, pow(number1, number2)); break;
	}
}

void calculate2(Node<double>*& stackNumber, string subFunction) {
	double a = topStack(stackNumber);
	if (subFunction == "sqrt") {
		popStack(stackNumber);
		pushStack(stackNumber, sqrt(a));
	}
	if (subFunction == "abs") {
		popStack(stackNumber);
		pushStack(stackNumber, abs(a));
	}
	if (subFunction == "ln") {
		popStack(stackNumber);
		pushStack(stackNumber, log(a));
	}
	if (subFunction[0] == 'l' && subFunction[1] == 'o' && subFunction[2] == 'g') {
		string t;
		for (int i = 3; i < subFunction.length(); i++)
			t += subFunction[i];
		int base;
		if (t == "")
			base = 10;
		else
			base = stringToInt(t);
		popStack(stackNumber);
		pushStack(stackNumber, log(a)/log(base));
	}
}