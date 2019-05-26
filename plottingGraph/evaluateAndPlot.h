#pragma once
#include "subFunction.h"
#include <Windows.h>
#include <conio.h>
#include <thread>

static COLORREF redColor = RGB(255, 0, 0);	//
static COLORREF blueColor = RGB(0, 0, 255);	// Khai báo màu
static COLORREF greenColor = RGB(0, 205, 0);//
static COLORREF whiteColor = RGB(255, 255, 255);//
static COLORREF greyColor = RGB(128, 128, 128);//

double eval(string originStr, double x);
void plot(string f, double firstX, double lastX, double firstY, double lastY, double step);
void exitThread(thread* thread);
void plotGraph(string f);