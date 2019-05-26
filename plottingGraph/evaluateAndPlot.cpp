#include "evaluateAndPlot.h"

double eval(string f, double x) {
	if (f == "sin(x)")
		return sin(x);
	if (f == "cos(x)")
		return cos(x);
	if (f == "tan(x)")
		return tan(x);
	if (f == "cot(x)")
		return 1 / tan(x);
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
		if (isLog) 
			if (c == '(')
				isLog = false;
		if (c == 'x' || c == 'X')
			pushStack(stackNumber, x);
		else
			if (c >= '0' && c <= '9' && !isLog)
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
							if (!flag) {
								calculate2(stackNumber, subFunc);
								subFunc = "";
							}
							popStack(stackOperator);
						}
						else {
							subFunc += c;
							if (subFunc == "log")
								isLog = true;
						}
							
	}
	return topStack(stackNumber);
}

bool stop[2] = { false, false };
bool duplicateColor[600][400] = {0};
COLORREF recColor = whiteColor;
COLORREF gridColor = greyColor;
HWND consoleWindow = GetConsoleWindow();
int recXstart = 50;						//
int recYstart = 40;						//	Tọa độ đỉnh hình chữ nhật
int recXend = 650;						//
int recYend = 440;

void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step) {				//	//	Cận Y
	double spaceX = step;						//	Độ chia nhỏ nhất của trục X
	double spaceY = step;
	int length = recXend - recXstart;		//Chiều dài hình chữ nhật
	int width = recYend - recYstart;		//Chiều rộng hình chữ nhật
	double nX = (lastX - firstX) / spaceX;	//Số đoạn trên trục X
	double nY = (lastY - firstY) / spaceY;	//Số đoạn trên trục Y
	double spacePixelX = length / nX;		//Độ chia nhỏ nhất tính theo pixel của trục X
	double spacePixelY = width / nY;
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop[0]) {
		//Vẽ khung hình chữ nhật theo chiều ngang
		for (int i = recXstart; i <= recXend; i++) {
			SetPixel(consoleDC, i, recYstart, recColor);			//Vẽ cạnh trên
			SetPixel(consoleDC, i, recYend, recColor);				//Vẽ cạnh dưới
			if ((i - recXstart) % (int)spacePixelX == 0 && (i != recXstart) && (i != recXend)) 		//Kiểm tra xem tại pixel i có được chia đoạn hay không
				for (int j = recYstart + 1; j < recYend; j++) {
					if (duplicateColor[i - recXstart][j - recYstart] == 0)
						SetPixel(consoleDC, i, j, gridColor);
				}
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void drawVertical(double firstX, double lastX, double firstY, double lastY, double step) {
					//	//	Cận Y
	double spaceX = step;						//	Độ chia nhỏ nhất của trục X
	double spaceY = step;
	int length = recXend - recXstart;		//Chiều dài hình chữ nhật
	int width = recYend - recYstart;		//Chiều rộng hình chữ nhật
	double nX = (lastX - firstX) / spaceX;	//Số đoạn trên trục X
	double nY = (lastY - firstY) / spaceY;	//Số đoạn trên trục Y
	double spacePixelX = length / nX;		//Độ chia nhỏ nhất tính theo pixel của trục X
	double spacePixelY = width / nY;
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop[0]) {
		for (int i = recYstart; i <= recYend; i++) {
			SetPixel(consoleDC, recXstart, i, recColor);			//Vẽ cạnh trái
			SetPixel(consoleDC, recXend, i, recColor);				//Vẽ cạnh phải
			if ((i - recYstart) % (int)spacePixelY == 0 && (i != recYstart) && (i != recYend)) 			//Kiểm tra xem tại pixel i có được chia đoạn hay không
				for (int j = recXstart + 1; j < recXend; j++) {
					if (duplicateColor[j - recXstart][i - recYstart] == 0)
						SetPixel(consoleDC, j, i, gridColor);
				}
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void labelling(string fs[], int n) {
	HANDLE hStdout;
	COORD destCoord;
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	int a[3] = {10, 11, 12};
	//
	destCoord.X = recXend / 8 + 4;
	destCoord.Y = recYstart / 16;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "FUNCTION(S):" << endl;
	CONSOLE_SCREEN_BUFFER_INFO csInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csInfo);
	WORD oldColor = csInfo.wAttributes;
	for (int i = 0; i < n; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), a[i]);
		destCoord.Y += 2;
		SetConsoleCursorPosition(hStdout, destCoord);
		cout << "y = " << fs[i];
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), oldColor);
	destCoord.Y += 5;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "INSTRUCTION:";
	destCoord.Y += 2;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Press WSAD to move the graph(s)";
	destCoord.Y++;
	SetConsoleCursorPosition(hStdout, destCoord);
	cout << "Press +/- to Zoom-in/out";	
}
void numberline(double firstX, double lastX, double firstY, double lastY, double step) {
	double spaceX = step;						//	Độ chia nhỏ nhất của trục X
	double spaceY = step;
	int length = recXend - recXstart;		//Chiều dài hình chữ nhật
	int width = recYend - recYstart;		//Chiều rộng hình chữ nhật
	double nX = (lastX - firstX) / spaceX;	//Số đoạn trên trục X
	double nY = (lastY - firstY) / spaceY;	//Số đoạn trên trục Y
	double spacePixelX = length / nX;		//Độ chia nhỏ nhất tính theo pixel của trục X
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
			destCoord.Y = i / 16;						//Tính tọa độ con trỏ dựa vào vị trí pixel được chia đoạn
			SetConsoleCursorPosition(hStdout, destCoord); //Di chuyển con trỏ đến vị trí cần thiết
			cout << tempY;								//Đánh số
			tempY -= spaceY;							//Do đánh số từ trên xuống và lúc đầu tempY = lastY nên mỗi lần lặp thì giảm tempY đi bằng độ chia nhỏ nhất
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
			SetConsoleCursorPosition(hStdout, destCoord); //Di chuyển con trỏ
			cout << tempX;
			tempX += spaceX;							//Đánh số từ trái sang phải nên mỗi lần lặp tăng tempX lên
		}
}

void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor) {
	//////////////// TÙY CHỈNH  //////////////					//	//	Cận Y
	double spaceX = step;						//	Độ chia nhỏ nhất của trục X
	double spaceY = step;						//	Độ chia nhỏ nhất của trục Y
	//////////////////////////////////////////
		
	int length = recXend - recXstart;		//Chiều dài hình chữ nhật
	int width = recYend - recYstart;		//Chiều rộng hình chữ nhật
	double nX = (lastX - firstX) / spaceX;	//Số đoạn trên trục X
	double nY = (lastY - firstY) / spaceY;	//Số đoạn trên trục Y
	double spacePixelX = length / nX;		//Độ chia nhỏ nhất tính theo pixel của trục X
	double spacePixelY = width / nY;		//Độ chia nhỏ nhất tính theo pixel của trục Y

	//Vẽ đồ thị
	HDC consoleDC = GetDC(consoleWindow);
	while (!stop[1]) {
		//Vẽ đồ thị hàm số 
		double X = firstX;	//Biến hoành độ của đồ thị hàm số, khởi tạo bằng cận trái
		double Y0, Y1 = eval(f, X), Y2 = eval(f, X);			//Biến tung độ của đồ thị hàm số
		double j0, j1, j2;			//Biến tung độ pixel của đồ thị
		j1 = -Y1 * width / (lastY - firstY);
		j1 = j1 + (recYend + firstY * width / (lastY - firstY));
		j2 = j1;
		double dx = (lastX - firstX) / length;
		for (int i = recXstart; i <= recXend; i++) {
			Y0 = Y1;
			Y1 = Y2;
			X = firstX + dx * (i - (double)recXstart + 1);
			Y2 = eval(f, X);
			j0 = j1;
			j1 = j2;
			j2 = -Y2 * width / (lastY - firstY);
			j2 = j2 + (recYend + firstY * width / (lastY - firstY));
			if (j1 < recYend && j1 > recYstart) {
				SetPixel(consoleDC, i, (int)j1, funcColor);
				duplicateColor[i - recXstart][(int)j1 - recYstart] = 1;
			}
				
			if ((int)j0 - (int)j1 >= 1 && (int)j0 - (int)j1 <= 10000)
				for (int t = (int)j1; t <= ((int)j0 + (int)j1) / 2; t++) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}	
				}
			else
				if ((int)j1 - (int)j0 >= 1 && (int)j1 - (int)j0 <= 10000)
					for (int t = (int)j1; t >= ((int)j0 + (int)j1) / 2; t--) {
						if (t < recYend && t > recYstart) {
							SetPixel(consoleDC, i, t, funcColor);
							duplicateColor[i - recXstart][t - recYstart] = 1;
						}
							
					}
			if ((int)j1 - (int)j2 >= 1 && (int)j1 - (int)j2 <= 10000)
				for (int t = (int)j1; t >= ((int)j1 + (int)j2) / 2; t--) {
					if (t < recYend && t > recYstart) {
						SetPixel(consoleDC, i, t, funcColor);
						duplicateColor[i - recXstart][t - recYstart] = 1;
					}
						
				}
			else
				if ((int)j2 - (int)j1 >= 1 && (int)j2 - (int)j1 <= 10000)
					for (int t = (int)j1; t <= ((int)j1 + (int)j2) / 2; t++) {
						if (t < recYend && t > recYstart) {
							SetPixel(consoleDC, i, t, funcColor);
							duplicateColor[i - recXstart][t - recYstart] = 1;
						}
					}
		}
	}
	ReleaseDC(consoleWindow, consoleDC);
}

void exitThread(thread* thread, int i) {
	stop[i] = true;
	thread->join();
}

void plotGraph(string fs[], int n) {
	COLORREF colors[3] = { greenColor , blueColor , redColor };
	system("cls");
	int i = 0;
	double range = 4;
	double x1 = -range, x2 = range, y1 = -range, y2 = range, step = 1, moveStep = step;
	labelling(fs, n);
	numberline(x1, x2, y1, y2, step);
	thread a[3], t1, t2;
	t1 = thread(drawHorizontal, x1, x2, y1, y2, step);
	t2 = thread(drawVertical, x1, x2, y1, y2, step);
	for (int i = 0; i < n; i++) 
		a[i] = thread(plot, fs[i], x1, x2, y1, y2, step, colors[i]);
	while (true) {
		char c = _getch();
		if (c == 119 || c == 115 || c == 97 || c == 100 || c == 45 || c == 43) {
			switch (c) {
			case 119: {
				y1 = y1 + moveStep;
				y2 = y2 + moveStep;
				break;
			}
			case 115: {
				y1 = y1 - moveStep;
				y2 = y2 - moveStep;
				break;
			}
			case 97: {
				x1 = x1 - moveStep;
				x2 = x2 - moveStep;
				break;
			}
			case 100: {
				x1 = x1 + moveStep;
				x2 = x2 + moveStep;
				break;
			}
			case 45: {
				step = step * 2;
				double oldx1 = x1, oldy1 = y1;
				x1 = (x1 + x2) / 2 - range * step;
				x2 = (oldx1 + x2) / 2 + range * step;
				y1 = (y1 + y2) / 2 - range * step;
				y2 = (oldy1 + y2) / 2 + range * step;
				moveStep = step;
				break;
			}
			case 43: {
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
			exitThread(&t1, 0);
			exitThread(&t2, 0);
			for (int i = 0; i < n; i++) 
				exitThread(&a[i], 1);
			for (int i = 0; i < 600; i++)
				for (int j = 0; j < 400; j++)
					duplicateColor[i][j] = 0;
			system("cls");
			labelling(fs, n);
			numberline(x1, x2, y1, y2, step);
			stop[1] = false;
			stop[0] = false;
			t1 = thread(drawHorizontal, x1, x2, y1, y2, step);
			t2 = thread(drawVertical, x1, x2, y1, y2, step);
			for (int i = 0; i < n; i++)
				a[i] = thread(plot, fs[i], x1, x2, y1, y2, step, colors[i]);
		}
		if (c == 27) {
			exitThread(&t1, 0);
			exitThread(&t2, 0);
			for (int i = 0; i < n; i++)
				exitThread(&a[i], 1);
			break;
		}
	}
}