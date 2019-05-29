#include "evaluating.h"

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

void calculate(Node<double>*& stackNumber, char oPerator) { //Sử dụng stack để tính giá trị
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
		case '&': pushStack(stackNumber, log(x)); break;
		case '_': pushStack(stackNumber, abs(x)); break;
		}
	}
}

double eval(string f, double x) {	//Hàm tính giá trị hàm số, sử dụng stack và thuật toán Ký pháp Ba Lan 
	if (f == "e^x")
		return exp(x);
	string numStr;
	string subFunc;
	f += ')';
	Node<char>* stackOperator = NULL;
	Node<double>* stackNumber = NULL;
	pushStack(stackOperator, '(');
	bool isLog = false;
	for (int i = 0; i < (int)f.length(); i++) {
		char c = f[i];
		if (subFunc == "sqrt" || subFunc == "sin" || subFunc == "cos" || subFunc == "tan" || subFunc == "cot" || subFunc == "ln" || subFunc == "abs")
			if (c == '(') {
				pushStack(stackOperator, c);
				if (subFunc == "sqrt")
					pushStack(stackOperator, '!');
				if (subFunc == "sin")
					pushStack(stackOperator, '@');
				if (subFunc == "cos")
					pushStack(stackOperator, '#');
				if (subFunc == "tan")
					pushStack(stackOperator, '$');
				if (subFunc == "cot")
					pushStack(stackOperator, '%');
				if (subFunc == "ln")
					pushStack(stackOperator, '&');
				if (subFunc == "abs")
					pushStack(stackOperator, '_');
				subFunc = "";
				continue;
			}
		if (isLog)
			if (c == '(') {
				if (numStr != "") {
					pushStack(stackNumber, (double)stringToInt(numStr));
					numStr = "";
				}
				else
					pushStack(stackNumber, (double)10);
				pushStack(stackOperator, c);
				pushStack(stackOperator, '~');
				isLog = false;
				subFunc = "";
				continue;
			}
		if (c == 'x' || c == 'X')
			pushStack(stackNumber, x);
		else
			if (c >= '0' && c <= '9')
				numStr += c;
			else
				if (c == '(')
					pushStack(stackOperator, c);
				else
					if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
						if (numStr != "") {
							pushStack(stackNumber, (double)stringToInt(numStr));
							numStr = "";
						}
						while (prior(topStack(stackOperator), c) == 1) {
							char oPerator = topStack(stackOperator);
							popStack(stackOperator);
							calculate(stackNumber, oPerator);
						}
						pushStack(stackOperator, c);
					}
					else
						if (c == ')') {
							if (numStr != "") {
								pushStack(stackNumber, (double)stringToInt(numStr));
								numStr = "";
							}
							bool flag = false;
							while (topStack(stackOperator) != '(') {
								char oPerator = topStack(stackOperator);
								popStack(stackOperator);
								calculate(stackNumber, oPerator);
								flag = true;
							}
							popStack(stackOperator);
						}
						else
							if (c != ' ') {
								subFunc += c;
								if (subFunc == "log")
									isLog = true;
							}
	}
	return topStack(stackNumber);
}
