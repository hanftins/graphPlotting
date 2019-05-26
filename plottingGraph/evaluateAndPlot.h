#pragma once
#include "subFunction.h"
#include <Windows.h>
#include <conio.h>
#include <thread>

static COLORREF redColor = RGB(255, 51, 0);			//
static COLORREF blueColor = RGB(0, 255, 255);		// Khai báo màu
static COLORREF greenColor = RGB(51, 255, 51);		//
static COLORREF whiteColor = RGB(255, 255, 255);	//
static COLORREF greyColor = RGB(128, 128, 128);		//

static COLORREF recColor = whiteColor;				//
static COLORREF gridColor = greyColor;				//

static bool stop = false;							//Biến dừng thread
static bool duplicateColor[600][400] = { 0 };		//Biến dùng để kiểm tra pixel đã được vẽ trước đó hay chưa

static HWND consoleWindow = GetConsoleWindow();		//Lấy handle
static int recXstart = 50;							//
static int recYstart = 40;							//Tọa độ khung hình chữ nhật
static int recXend = 650;							//
static int recYend = 440;							//
static int length = recXend - recXstart;			//Chiều dài hình chữ nhật
static int width = recYend - recYstart;				//Chiều rộng hình chữ nhật

double eval(string originStr, double x);			//Hàm tính giá trị của hàm số
void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step);	//Hàm vẽ đường nằm ngang
void drawVertical(double firstX, double lastX, double firstY, double lastY, double step);	//Hàm vẽ đường thẳng đứng
void labelling(string fs[], int n);		//Hàm xuất ra thông tin đồ thị
void numberline(double firstX, double lastX, double firstY, double lastY, double step);		//Hàm đánh số trục số
void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor);	//Hàm vẽ đồ thị hàm số
void exitThread(thread* thread);	//Hàm thoát thread	
void plotGraph(string fs[], int n);	//Hàm xử lí vấn đề di chuyển và phóng to, nhỏ của đồ thị