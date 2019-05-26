#include "evaluateAndPlot.h"

int main() {
	string fs[3], n;
	do {
		cout << "Ban muon ve do thi cua bao nhieu ham so? (max = 3): ";
		getline(cin, n);
		if (n != "1" && n != "2" && n != "3")
			cout << "So luong do thi khong hop le!\n";
	} while (n != "1" && n != "2" && n != "3");
	rewind(stdin);
	int number = n[0] - '0';
	for (int i = 0; i < number; i++) {
		cout << "Nhap ham f" << i + 1 << "(x): ";
		getline(cin, fs[i]);
	}
	plotGraph(fs, number);
}	