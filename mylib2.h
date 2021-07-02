#pragma once
#include <iostream>
#include <Shlwapi.h>
#include <Windows.h>
#include <conio.h>
#include "Marcro.h"

HANDLE hConsoleOutput;
HANDLE hConsoleInput;

// thay doi kich thuoc cua so console
void resizeConsole(int width, int height);
//tra ve vi tri toa do x hien tai cua con tro dang dung(tren cot doc)
int wherex(void);
// tra ve vi tri toa do y hien tai cua con tro dang dung(tren cot ngang)
int wherey(void);
// ....... set mau cua nen chu....................
void SetBGColor(WORD color);
// dua con tro den toa do x:y
void gotoxy(int x, int y);
// An/ Hien con tro nhap nhay trong console
void Cursor(BOOL bVisible, DWORD dwSize);
// Dat mau cho chu
void SetColor(WORD color);
//Xoa toan bo noi dung cua so console
void cls(HANDLE hConsole);
void clrscr();
// chu chuyen ve mau vang
void normalTextColor();
// nen chu chuyen ve xanh  va chu chuyen ve mau vang
void normalBGColor();
/// Function which returns character on console's cursor position 
char getCursorChar();    
/// Function which reads character at specific coordinates
char readChar(int x, int y); 



void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
	
	COORD crd;
	crd.X = width;
	crd.Y = height;
	SMALL_RECT rec;
	rec.Left = 0;
	rec.Top = 0;
	rec.Right = width - 1;
	rec.Bottom = height - 1;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &rec);
	SetConsoleScreenBufferSize(hConsoleOutput, crd);
}

int wherex(void)
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.X;
}

int wherey(void)
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
	return screen_buffer_info.dwCursorPosition.Y;
}

// HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Cursor(BOOL bVisible, DWORD dwSize)
{
	CONSOLE_CURSOR_INFO ConsoleCursorInfo;
	ConsoleCursorInfo.bVisible = bVisible;
	ConsoleCursorInfo.dwSize = dwSize; // Phan tram bao trum o cua con tro chuot
	SetConsoleCursorInfo(hConsoleOutput, &ConsoleCursorInfo);
}

void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void SetBGColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4;
	wAttributes &= 0xff0f;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void cls(HANDLE hConsole)
{
	COORD coordScreen = { 0, 0 };    // home for the cursor 
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;

	// Get the number of character cells in the current buffer. 

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

	// Fill the entire screen with blanks.

	if (!FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Get the current text attribute.
	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
		return;

	// Set the buffer's attributes accordingly.
	if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
		dwConSize, coordScreen, &cCharsWritten))
		return;

	// Put the cursor at its home coordinates.
	SetConsoleCursorPosition(hConsole, coordScreen);
}

void clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	COORD Home = { 0, 0 };
	DWORD dummy;

	hConsoleOutput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	FillConsoleOutputCharacter(hConsoleOutput, ' ', screen_buffer_info.dwSize.X * screen_buffer_info.dwSize.Y, Home, &dummy);
	screen_buffer_info.dwCursorPosition.X = 0;
	screen_buffer_info.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOutput, screen_buffer_info.dwCursorPosition);
}

//bool GetKey(int key)
//{
//	return GetAsyncKeyState(key);
//}

void normalTextColor() {
	SetColor(WHITE);
}

void normalBGColor()
{
	SetColor(WHITE);
}

char getCursorChar()    /// Function which returns character on console's cursor position 
{
	char c = '\0';
	CONSOLE_SCREEN_BUFFER_INFO con;
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hcon != INVALID_HANDLE_VALUE &&
		GetConsoleScreenBufferInfo(hcon, &con))
	{
		DWORD read = 0;
		if (!ReadConsoleOutputCharacterA(hcon, &c, 1,
			con.dwCursorPosition, &read) || read != 1
			)
			c = '\0';
	}
	return c;
}

char readChar(int x, int y)  /// Function which reads character at specific coordinates
{
	gotoxy(x, y);
	char ccccc = getCursorChar();
	return ccccc;
}
