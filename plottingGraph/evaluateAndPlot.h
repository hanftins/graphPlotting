#pragma once
#include "subFunction.h"
#include <Windows.h>
#include <conio.h>
#include <thread>

static COLORREF redColor = RGB(255, 51, 0);			//
static COLORREF blueColor = RGB(0, 255, 255);		// Khai báo màu
static COLORREF greenColor = RGB(51, 255, 51);
static COLORREF yellowColor = RGB(255, 255, 0);	//
static COLORREF whiteColor = RGB(255, 255, 255);	//
static COLORREF greyColor = RGB(128, 128, 128);		//
static COLORREF recColor = whiteColor;				//
static COLORREF gridColor = greyColor;				//

static const int recXstart = 50;					//
static const int recYstart = 40;				//Tọa độ khung hình chữ nhật
static const int recXend = 450;			//
static const int recYend = 440;				//
static const int length = recXend - recXstart;			//Chiều dài hình chữ nhật
static const int width = recYend - recYstart;		//Chiều rộng hình chữ nhật

static bool stop = false;							//Biến dừng thread
static bool duplicateColor[length + 1][width + 1] = { 0 };		//Biến dùng để kiểm tra pixel đã được vẽ trước đó hay chưa
static HWND consoleWindow = GetConsoleWindow();		//Lấy handle

double eval(string originStr, double x);			//Hàm tính giá trị của hàm số
void resetColor(bool a[length + 1][width + 1]);
void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step);	//Hàm vẽ đường nằm ngang
void drawVertical(double firstX, double lastX, double firstY, double lastY, double step);	//Hàm vẽ đường thẳng đứng
void labelling(string fs[], int n, string type[]);		//Hàm xuất ra thông tin đồ thị
void numberline(double firstX, double lastX, double firstY, double lastY, double step);		//Hàm đánh số trục số
void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor);	//Hàm vẽ đồ thị hàm số
void exitThread(thread* thread);	//Hàm thoát thread	
void addGraph(string& f1, string& f2, string& type, int &n);
void deleteGraph(string fs[], string type[], int& n);
void plotGraph(string fs[], int n, string type[]);	//Hàm xử lí vấn đề di chuyển và phóng to, nhỏ của đồ thị