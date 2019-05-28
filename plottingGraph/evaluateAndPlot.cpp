#include "evaluateAndPlot.h"

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
		if (subFunc == "sqrt" || subFunc == "sin" || subFunc == "cos" || subFunc == "tan" || subFunc == "cot" || subFunc == "ln")
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


void resetColor(bool a[length + 1][width + 1]) {
	for (int i = 0; i <= length; i++)
		for (int j = 0; j <= width; j++)
			a[i][j] = 0;
}

void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step) {	//Hàm vẽ đường nằm ngang
	double nX = (lastX - firstX) / step;	//Số đoạn trên trục Ox
	double nY = (lastY - firstY) / step;	//Số đoạn trên trục Oy
	double spacePixelX = length / nX;		//Độ chia nhỏ nhất trên trục Ox tính bằng pixel
	double spacePixelY = width / nY;		//Độ chia nhỏ nhất trên trục Oy tính bằng pixel
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop) 
		for (int i = recXstart; i <= recXend; i++) {		//Vòng lặp chạy trên cạnh của hình chữ nhật
			SetPixel(consoleDC, i, recYstart, recColor);	//Vẽ cạnh trên	
			SetPixel(consoleDC, i, recYend, recColor);		//Vẽ cạnh dưới
			if ((i - recXstart) % (int)spacePixelX == 0 && (i != recXstart) && (i != recXend)) 	//Kiểm tra tọa độ để vẽ lưới	
				for (int j = recYstart + 1; j < recYend; j++) //Vẽ lưới theo chiều từ trên xuống dưới
					if (duplicateColor[i - recXstart][j - recYstart] == 0) //Kiểm tra pixel đã được vẽ bằng hàm vẽ đồ thị chưa
						SetPixel(consoleDC, i, j, gridColor);
		}
	ReleaseDC(consoleWindow, consoleDC);
}

void drawVertical(double firstX, double lastX, double firstY, double lastY, double step) {	 //Tương tự như vẽ đường nằm ngang
	double nX = (lastX - firstX) / step;	
	double nY = (lastY - firstY) / step;	
	double spacePixelX = length / nX;		
	double spacePixelY = width / nY;
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop) {
		for (int i = recYstart; i <= recYend; i++) {
			SetPixel(consoleDC, recXstart, i, recColor);		
			SetPixel(consoleDC, recXend, i, recColor);				
			if ((i - recYstart) % (int)spacePixelY == 0 && (i != recYstart) && (i != recYend)) 			
				for (int j = recXstart + 1; j < recXend; j++) 
					if (duplicateColor[j - recXstart][i - recYstart] == 0)
						SetPixel(consoleDC, j, i, gridColor);
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void labelling(string fs[], int n, string type[]) { //Hàm xuất ra thông tin đồ thị
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csInfo); //Lấy thông tin console
	WORD oldColor = csInfo.wAttributes; //Lưu màu cũ
	int a[4] = { 10, 11, 12, 14};	//Mảng màu
	destCoord.X = recXend / 8 + 4;	//Vị trí thích hợp
	destCoord.Y = recYstart / 16;	//
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "CHUONG TRINH VE HINH VA DO THI HAM SO" << endl;
	int i = 0;
	int j = 0;
	while (i < n) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a[j]); 
		destCoord.Y += 2;
		SetConsoleCursorPosition(hStdout, destCoord);
		if (type[i] == "") 
			cout << "y = " << fs[i];
		else 
			cout << type[i];
		i += 2;
		j++;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), oldColor);
	//Phần in ra hướng dẫn
	destCoord.Y += 5;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "HUONG DAN:";
	destCoord.Y += 2;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Nhan WSAD de di chuyen do thi";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Nhan +/- de phong to/thu nho";	
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Nhan U de them do thi";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Nhan I de xoa do thi";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Nhan ESC de tro ve";
}

void numberline(double firstX, double lastX, double firstY, double lastY, double step) {	//Hàm đánh số trục số
	double nX = (lastX - firstX) / step;
	double nY = (lastY - firstY) / step;	
	double spacePixelX = length / nX;		
	double spacePixelY = width / nY;
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	//Đánh số trên các trục Y
	double tempY = lastY;								//tempY là các mốc đoạn, khời tạo bằng cận cuối của Y
	for (int i = recYstart; i <= recYend; i++)			//Vòng lặp đánh số trục Y
		if ((i - recYstart) % (int)spacePixelY == 0) {	//Kiểm tra xem tại pixel i có được chia đoạn hay không
			if (tempY >= 0)								//Do đánh số trên trục Y nên hoành độ con trỏ không đổi, nhưng do số âm có dấu - nên phải canh chỉnh lại
				destCoord.X = recXstart / 8 - 4;
			else
				destCoord.X = recXstart / 8 - 5;
			destCoord.Y = i / 16;							//Tính tọa độ con trỏ dựa vào vị trí pixel được chia đoạn
			SetConsoleCursorPosition(hStdout, destCoord);	//Di chuyển con trỏ đến vị trí cần thiết
			cout << tempY;									//Đánh số
			tempY -= step;									//Do đánh số từ trên xuống và lúc đầu tempY = lastY nên mỗi lần lặp thì giảm tempY đi bằng độ chia nhỏ nhất
		}

	//Đánh số trên các trục X
	destCoord.Y = recYend / 16 + 1;						//Do đánh số trên trục X nên tung độ của con trỏ không đổi 
	double tempX = firstX;								//tempY là các mốc đoạn, khời tạo bằng cận đầu của X
	for (int i = recXstart; i <= recXend; i++)			//Vòng lặp đánh số trục X, tương tự như đánh số trên trục Y
		if ((i - recXstart) % (int)spacePixelX == 0) {	//Kiểm tra xem tại pixel i có được chia đoạn hay không
			if (tempX >= 0)								//Canh chỉnh các trường hợp có dấu - 
				destCoord.X = i / 8;					//Tính tọa độ con trỏ dựa vào vị trí pixel được chia đoạn
			else
				destCoord.X = i / 8 - 1;
			SetConsoleCursorPosition(hStdout, destCoord); 
			cout << tempX;
			tempX += step;							//Đánh số từ trái sang phải nên mỗi lần lặp tăng tempX lên
		}
}

void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor) {
	double nX = (lastX - firstX) / step;	//Số đoạn trên trục X
	double nY = (lastY - firstY) / step;	//Số đoạn trên trục Y
	double spacePixelX = length / nX;		//Độ chia nhỏ nhất tính theo pixel của trục X
	double spacePixelY = width / nY;		//Độ chia nhỏ nhất tính theo pixel của trục Y

	//Vẽ đồ thị
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop) {
		//Vẽ đồ thị hàm số 
		double X0, X1, X2;	//Biến hoành độ của đồ thị hàm số, khởi tạo bằng cận trái
		double Y0, Y1, Y2;		//Biến tung độ của đồ thị hàm số, dùng 3 biến để vẽ nối liền các giá trị cách xa nhau
		double j0, j1, j2;			//Biến tung độ pixel của đồ thị
		double dx = (lastX - firstX) / length; //Vi phân 

		for (int i = recXstart + 1; i < recXend; i++) {
			X0 = firstX + dx * (i - (double)recXstart - 1);
			X1 = firstX + dx * (i - (double)recXstart);
			X2 = firstX + dx * (i - (double)recXstart + 1);
			Y0 = eval(f, X0);
			Y1 = eval(f, X1);
			Y2 = eval(f, X2);
			j0 = -Y0 * width / (lastY - firstY);
			j0 = j0 + (recYend + firstY * width / (lastY - firstY));
			j1 = -Y1 * width / (lastY - firstY);
			j1 = j1 + (recYend + firstY * width / (lastY - firstY));
			j2 = -Y2 * width / (lastY - firstY);
			j2 = j2 + (recYend + firstY * width / (lastY - firstY));

			if (j1 < recYend && j1 > recYstart) {
				SetPixel(consoleDC, i, (int)j1, funcColor);
				duplicateColor[i - recXstart][(int)j1 - recYstart] = 1;
			}
			else
				continue;

			if ((j2 <= recYstart || j2 - j0 >= 1) && Y1 > Y0) {
				for (int t = (int)(j1 + j0) / 2; t > recYstart; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if ((j2 >= recYend || j0 - j2 >= 1) && Y1 < Y0) {
				for (int t = (int)(j1 + j0) / 2; t < recYend; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if ((j0 <= recYstart || j0 - j2 >= 1) && Y1 > Y2) {
				for (int t = (int)(j1 + j2) / 2; t > recYstart; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if ((j0 >= recYend ||j2 - j0 >= 1) && Y1 < Y2) {
				for (int t = (int)(j1 + j2) / 2; t < recYend; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
				continue;
			}

			if (j0 > j1 && j0 - j1 <= 500)	//j0 > j1
				for (int t = (int)j1; t <= (j0 + j1) / 2; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}	
				}
			else
				if (j1 > j0 && j1 - j0 <= 500)	//j1 > j0
					for (int t = (int)j1; t >= (j0 + j1) / 2; t--) {
						if (t < recYend && t > recYstart) {
							SetPixel(consoleDC, i, t, funcColor);
							duplicateColor[i - recXstart][t - recYstart] = 1;
						}
					}
			if (j1 > j2 && j1 - j2 <= 500)	//j1 > j2
				for (int t = (int)j1; t >= (j1 + j2) / 2; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
				}
			else
				if (j2 > j1 && j2 - j1 <= 500)	//j2 > j1
					for (int t = (int)j1; t <= (j1 + j2) / 2; t++) {
						if (t < recYend && t > recYstart) {
							SetPixel(consoleDC, i, t, funcColor);
							duplicateColor[i - recXstart][t - recYstart] = 1;
						}
					}
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void exitThread(thread* thread) {
	stop = true;
	thread->join();
}

void addGraph(string& f1, string& f2, string& type, int& n) {
	string fs;
	char opt;
graphOrShape:
	cout << "Nhan ESC de quay ve\n";
	if (n >= 8) {
		cout << "Chuong trinh chi co the ve toi da 4 do thi, hinh!";
		char t;
		do {
			t = _getch();
		} while (t != 27);
	}
	else {
		cout << "Ban muon ve do thi cua ham so hay ve hinh?\n";
		cout << "\t1. Ve do thi ham so\n\t2. Ve hinh\n";
		do {	
			opt = _getch();
			if (opt != '1' && opt != '2' && opt != 27)
				cout << "Lua chon khong hop le, vui long thu lai\n";
		} while (opt != '1' && opt != '2' && opt != 27);
		system("cls");
		if (opt == 27)
			return;
		if (opt == '1') {
			rewind(stdin);
			cout << "Nhap ham f(x): ";
			do {
				getline(cin, fs);
			} while (fs == "");
			f1 = fs;
			f2 = "";
			type = "";
			n = n + 2;
			return;
		}
		else {
			char curveOpt;
			cout << "Nhan ESC de quay ve\n";
			cout << "Ban muon ve hinh gi?\n";
			cout << "\t1. Hinh tron\n\t2. Hinh ellipse\n\t3. Hinh hyberbol\n";
			do {			
				curveOpt = _getch();
				if (curveOpt != '1' && curveOpt != '2' && curveOpt != '3' && curveOpt != 27)
					cout << "Lua chon khong hop le, vui long thu lai\n";
			} while (curveOpt != '1' && curveOpt != '2' && curveOpt != '3' && curveOpt != 27);
			system("cls");
			if (curveOpt == 27)
				goto graphOrShape;
			switch (curveOpt) {
			case '1': {
				string x, y, r;
				cout << "Nhap toa do tam (x, y): ";
				cin >> x >> y;
				cout << "Nhap ban kinh: ";
				cin >> r;
				type = "(x - " + x + ")^2 + (y - " + y + ")^2 = " + r + "^2";
				f1 = "sqrt(" + r + "^2 - " + "(x - " + x + ")^2) + " + y;
				f2 = "-sqrt(" + r + "^2 - " + "(x - " + x + ")^2) + " + y;
				n = n + 2;
				return;
			}
			case '2': {
				string x, y, a, b;
				cout << "Nhap toa do tam (x, y): ";
				cin >> x >> y;
				cout << "Nhap truc lon a va truc nho b: ";
				cin >> a >> b;
				type = "(x - " + x + ")^2/" + a + "^2 + " + "(y - " + y + ")^2/" + b + "^2 = 1";
				f1 = "sqrt(" + b + "^2*(1-(x-" + x + ")^2/" + a + "^2))+" + y;
				f2 = "-sqrt(" + b + "^2*(1-(x-" + x + ")^2/" + a + "^2))+" + y;
				n = n + 2;
				return;
			}
			case '3': {
				string x, y, a, b;
				cout << "Nhap toa do tam (x, y): ";
				cin >> x >> y;
				cout << "Nhap a, b: ";
				cin >> a >> b;
				type = "(x - " + x + ")^2/" + a + "^2 - " + "(y - " + y + ")^2/" + b + "^2 = 1";
				f1 = "sqrt(" + b + "^2*((x-" + x + ")^2/" + a + "^2-1))+" + y;
				f2 = "-sqrt(" + b + "^2*((x-" + x + ")^2/" + a + "^2-1))+" + y;
				n = n + 2;
				return;
			}
			}
		}
	}
}

void deleteGraph(string fs[], string type[], int& n) {
	cout << "Nhan ESC de quay ve\n";
	if (n <= 0) {
		cout << "Khong co do thi nao de xoa";
		char t;
		do {
			t = _getch();
		} while (t != 27);
	}
	else {
		cout << "Ban muon xoa do thi nao?\n";
		int i = 0;
		int j = 0;
		while (i < n) {
			j++;
			if (type[i] == "")
				cout << j << ". y = " << fs[i] << endl;
			else
				cout << j << ". " << type[i] << endl;
			i += 2;
		}
		char t;
		do {
			t = _getch();
			if (t != 27 && (t < '1' || t > j + 48))
				cout << "Lua chon khong hop le, vui long thu lai!\n";
		} while (t != 27 && (t < '1' || t > j + 48));
		if (t == 27)
			return;
		int k = t - 48;
		for (int i = 2 * k - 2; i < n - 2; i++) {
			fs[i] = fs[i + 2];
			type[i] = type[i + 2];
		}
		n -= 2;
	}
}

void plotGraph(string fs[], string type[], int n) {
	COLORREF colors[4] = { greenColor, blueColor, redColor, yellowColor };
	double range = 4;
	double x1 = -range, x2 = range, y1 = -range, y2 = range, step = 1, moveStep = step;
	thread a[8], t1, t2;
step1:
	system("cls");
	labelling(fs, n, type);
	numberline(x1, x2, y1, y2, step);
	stop = false;
	resetColor(duplicateColor);
	t1 = thread(drawHorizontal, x1, x2, y1, y2, step);
	t2 = thread(drawVertical, x1, x2, y1, y2, step);
	int i = 0;
	int j = 0;
	while (i < n) {
		if (type[i] == "") {
			a[i] = thread(plot, fs[i], x1, x2, y1, y2, step, colors[j]);
		}		
		else {
			a[i] = thread(plot, fs[i], x1, x2, y1, y2, step, colors[j]);
			a[i + 1] = thread(plot, fs[i + 1], x1, x2, y1, y2, step, colors[j]);
		}	
		i += 2;
		j += 1;
	}
	while (true) {
		char c = _getch();
		if (c == 119 || c == 115 || c == 97 || c == 100 || c == 45 || c == 43) {
			switch (c) {
			case 87:
			case 119: { //Move up
				y1 = y1 + moveStep;
				y2 = y2 + moveStep;
				break;
			}
			case 83: 
			case 115: { //Move down
				y1 = y1 - moveStep;
				y2 = y2 - moveStep;
				break;
			}
			case 65:
			case 97: { //Move left
				x1 = x1 - moveStep;
				x2 = x2 - moveStep;
				break;
			}
			case 68:
			case 100: { //Move right
				x1 = x1 + moveStep;
				x2 = x2 + moveStep;
				break;
			}
			case 45: {	//Zoom out
				step = step * 2;
				if ((x1 + x2) / 2 / step != round((x1 + x2) / 2 / step)) {
					x1 = x1 - moveStep;
					x2 = x2 - moveStep;
				}
				if ((y1 + y2) / 2 / step != round((y1 + y2) / 2 / step)) {
					y1 = y1 - moveStep;
					y2 = y2 - moveStep;
				}
				double oldx1 = x1, oldy1 = y1;
				x1 = (x1 + x2) / 2 - range * step;
				x2 = (oldx1 + x2) / 2 + range * step;
				y1 = (y1 + y2) / 2 - range * step;
				y2 = (oldy1 + y2) / 2 + range * step;
				moveStep = step;
				break;
			}
			case 43: {	//Zoom in
				step = step / 2;
				double oldx1 = x1, oldy1 = y1;
				x1 = (x1 + x2) / 2 - range * step;
				x2 = (oldx1 + x2) / 2 + range * step;
				y1 = (y1 + y2) / 2 - range * step;
				y2 = (oldy1 + y2) / 2 + range * step;
				moveStep = step;
				break;
			}
			}
			exitThread(&t1);
			exitThread(&t2);
			for (int i = 0; i < n; i++) 
				if (fs[i] != "")
					exitThread(&a[i]);	
			goto step1;
		}
		if (c == 117 || c == 85 || c == 105 || c == 73 || c == 27) {
			exitThread(&t1);
			exitThread(&t2);
			for (int i = 0; i < n; i++) 
				if (fs[i] != "")
					exitThread(&a[i]);
			system("cls");
			if (c == 85 || c == 117) {
				addGraph(fs[n], fs[n + 1], type[n], n);
				goto step1;
			}
			if (c == 105 || c == 73) {
				deleteGraph(fs, type, n);
				goto step1;
			}
			if (c == 27) 
				return;
		}
	}
}