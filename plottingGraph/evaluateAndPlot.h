#pragma once
#include "subFunction.h"
#include <Windows.h>
#include <conio.h>
#include <thread>

static COLORREF redColor = RGB(255, 51, 0);	//
static COLORREF blueColor = RGB(0, 255, 255);	// Khai báo màu
static COLORREF greenColor = RGB(51, 255, 51);//
static COLORREF whiteColor = RGB(255, 255, 255);//
static COLORREF greyColor = RGB(128, 128, 128);//

double eval(string originStr, double x);
void drawHorizontal(double firstX, double lastX, double firstY, double lastY, double step);
void drawVertical(double firstX, double lastX, double firstY, double lastY, double step);
void labelling(string fs[], int n);
void numberline(double firstX, double lastX, double firstY, double lastY, double step);
void plot(string f, double firstX, double lastX, double firstY, double lastY, double step, COLORREF funcColor);
void exitThread(thread* thread, int i);
void plotGraph(string fs[], int n);