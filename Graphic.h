#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
#include <thread>
#include "mylib2.h"
#define LOGO  "logo.txt"
#define LOGO2 "logo2.txt"
#define LOGOHEIGHT 20
#define BUTTONWIDTH 17
#define BUTTONHEIGHT 3
using namespace std;
string mainbutton[] = {"VATTU", "NHAN VIEN", "HOA DON", "THOAT"};
int mainbuttonn = 4;
//=====Ten Ham=====//
string toString(int f, int size);
string toString(float f, int size);
string toString(string str, int size);
void createWindow();
void drawTittle(const string &filename);
//=====Ham=====//
string toString(int f, int size){
	string str = to_string(f);
	if(str.size()>size) return "";
	string space = "";
	for (int i=str.size(); i<size; i++) space += " ";
	return space + str;
};
string toString(float f, int size){
	string str = to_string(f);
	if(str.size()>size) return "";
	string space = "";
	for (int i=str.size(); i<size; i++) space += " ";
	return space + str;
};
string toString(string str, int size){
	if(str.size()>size) return "";
	string space = "";
	for (int i=str.size(); i<size; i++) space += " ";
	return space + str;
};
void createWindow(){
	resizeConsole(WIDTH, HEIGHT);
	SetConsoleTitle(TEXT("QUAN LI VAT TU"));
	drawTittle(LOGO);
	drawTittle(LOGO2);
	int x = (MAXLINE - BUTTONWIDTH - 10)/2;
	int y = wherey();
	string yspace=" ";
	for (int j = 1; j<BUTTONWIDTH; j++) yspace+=" ";
	for (int i = 0; i<mainbuttonn; i++){
		SetBGColor(LIGHT_YELLOW);
		SetColor(LIGHT_RED);
		for (int j = 0; j<BUTTONHEIGHT/2; j++) {
			gotoxy(x,++y);
			cout<<yspace;
		}
		string xspace=" ";
		for (int j = 1; j<(BUTTONWIDTH - mainbutton[i].size())/2; j++) xspace+=" ";
		string button = xspace + mainbutton[i] + xspace;
		gotoxy(x, ++y);
		cout<<button;
		for (int j = 0; j<BUTTONHEIGHT/2; j++) {
			gotoxy(x,++y);
			cout<<yspace;
		}
		gotoxy(x,++y);
		SetBGColor(BLACK);
		cout<<endl;
	}
};
void drawTittle(const string &filename){
	ifstream f;
	f.open(filename);
	if(f.bad()||f.fail()) cout<<"loi";
	string temp;
	int i=wherey();
	SetColor(RED);
	while(!f.eof()) {
		getline(f, temp);
		int x = (MAXLINE - temp.size() - 10)/2 + 1;
		gotoxy(x,++i);
		cout<<temp<<endl;
	}
	f.close();
	normalTextColor();
}
