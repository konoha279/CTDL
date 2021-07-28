#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
#include <thread>
#include <iomanip>
#include <vector>
#include "ThongKe.h"
#include "mylib2.h"
#include "ChuanHoa.h"
#define LOGO  "logo.txt"
#define LOGO2 "logo2.txt"
#define LOGOHEIGHT 20
#define BUTTONWIDTH 17
#define BUTTONHEIGHT 3
#define FIRSTMAINBUTTON 22
#define MAXTABLEROW 30
#define YTABLE 5
#define YTABLE2 22
#define XTABLE 1
#define VTTABLELENGTH 91
#define VTFORMLENGTH 66
using namespace std;
string mainbutton[] = {"VATTU", "NHAN VIEN", "HOA DON", "THONGKE", "THOAT"};
int mainbuttonn = 5;
string buttomButton[] = {"ESC", "CTRL+F", "CTRL+N", "ENTER", "DELETE", "CTRL+S", "CTRL+V", "CTRL+L", "PAGE", "CTRL+P"};
string buttomCommand[] = {"QUAY LAI", "TIM KIEM", "THEM MOI", "CHON", "XOA", 
					"SAVE FILE", "SAP XEP", "LOAD FILE","TRANG", "XUAT HOA DON"};
int buttomCommandn = 9;
//=====Ten Ham=====//
string toString(int f, int size);
string toString(float f, int size);
string toString(string str, int size);
// khoi tao menu chinh
void createWindow();
//ve tieu de
void drawTittle(const string &filename);
//to danh dau
void highlight(int x, int y, int length, int color);
//mainMenu
int mainMenu();
//ve nut
void drawButton(int line);
//thong bao
void thongbao(int x, int y, string title, string tb, int length, int color, int BGcolor);
//lua chon
int luachon(int x, int y, string tb, int length);
//Huong dan nhap
void HuongDanNhap(int x, int y, string hd[], int n, int row, int length);
//Bang search
string searchBox(int x, int y, int length, string search);
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
	vector<string> v = split(str, ".");
	str = v[0] + "." + v[1][0];
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
	int x = (MAXLINE - BUTTONWIDTH)/2 - 1;
	int y = FIRSTMAINBUTTON;
	for (int i = 0; i<mainbuttonn; i++){
		string xspace=" ";
		for (int j = 1; j<(BUTTONWIDTH - mainbutton[i].size())/2; j++) xspace+=" ";
		string button = xspace + mainbutton[i] + xspace;
		CreateBox(x, y, button, BUTTONWIDTH); 
		y+=4;
	}
	Cursor(false, 100);
};
void drawTittle(const string &filename){
	ifstream f;
	f.open(filename);
	if(f.bad()||f.fail()) cout<<"loi";
	int n=-1, y=wherey();
	string str[10];
	while(!f.eof()) getline(f, str[++n]);
	SetColor(RED);
	int x = (MAXLINE-str[n/2].size())/2;
	for (int i=0; i<=n; i++){
		gotoxy(x,++y);
		cout<<str[i];
	}
	
	f.close();
	normalTextColor();
	cout<<endl;
};
void highlight(int x, int y, int length, int color){
	gotoxy(x, y);
	string str="";
	for (int i=0; i<length; i++) str+=readChar(x+i,y);
	SetBGColor(color);
	gotoxy(x,y);
	cout<<str;
	SetBGColor(BLACK);
	SetColor(WHITE);
};
int mainMenu(){
	clrscr(); 
	createWindow();
	//highlight vi tri nut dau, nut dau co 3 dong
	int x = (MAXLINE - BUTTONWIDTH)/2 - 1, y = FIRSTMAINBUTTON;
	highlight(x, y-1, BUTTONWIDTH + 2, YELLOW);
	highlight(x, y, BUTTONWIDTH + 2, YELLOW);
	highlight(x, y+1, BUTTONWIDTH + 2, YELLOW);
	char c;
	int button = 1;
	SetColor(WHITE);
	while (true) {
		gotoxy(155,42); cout<<"button: "<<button;
		c=_getch();
		switch(c){
			case KEY_UP:{
				if (button == 1) continue;
				//tat highlight nut hien tai
				y = FIRSTMAINBUTTON + 4*(button-1);
				highlight(x, y-1, BUTTONWIDTH+2, BLACK);
				highlight(x, y, BUTTONWIDTH+2, BLACK);
				highlight(x, y+1, BUTTONWIDTH+2, BLACK);
				//highlight nut tren, giam 
				y-=4;
				highlight(x, y-1, BUTTONWIDTH+2, YELLOW);
				highlight(x, y, BUTTONWIDTH+2, YELLOW);
				highlight(x, y+1, BUTTONWIDTH+2, YELLOW);
				button--;
				continue;
			}
			case KEY_DOWN:{
				if (button == mainbuttonn) continue;
				y = FIRSTMAINBUTTON + 4*(button-1);
				highlight(x, y-1, BUTTONWIDTH+2, BLACK);
				highlight(x, y, BUTTONWIDTH+2, BLACK);
				highlight(x, y+1, BUTTONWIDTH+2, BLACK);
				y+=4;
				highlight(x, y-1, BUTTONWIDTH+2, YELLOW);
				highlight(x, y, BUTTONWIDTH+2, YELLOW);
				highlight(x, y+1, BUTTONWIDTH+2, YELLOW);
				button++;
				continue;
			}
			case ENTER: return button;
			case ESC: return 0;
		}
	}
};
void drawButton(int line){
	int i;
	for (i=0; i<buttomCommandn-1; i++){
		CreateBox(XTABLE+11*i, MAXROW-6, buttomButton[i], buttomButton[i].length());
		gotoxy(XTABLE+11*i, MAXROW-4); cout<<buttomCommand[i];
	}
	if (line == 3) {
		CreateBox(XTABLE+11*i, MAXROW-6, buttomButton[i], buttomButton[i].length());
		gotoxy(XTABLE+11*i, MAXROW-4); cout<<buttomCommand[i];
	}
};
void thongbao(int x, int y, string title, string tb, int length, int color, int BGcolor){
	if (length<tb.length()||x<0||y<1) return;
	for (int i=0; i<5; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
	}
	SetBGColor(BGcolor);
	SetColor(color);
	gotoxy(x,y-1);
	cout << char(201) << setw(length+3) << setfill(char(205)) << char(187);
	gotoxy(x, y);
	cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	gotoxy(x, y+1);
	cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	gotoxy(x, y+2);
	cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	gotoxy(x, y+3);
	cout << char(200) << setw(length+3) << setfill(char(205)) << char(188);
	gotoxy(x+1 + (length-title.length())/2, y); cout<<title;
	gotoxy(x+1 + (length-tb.length())/2, y+1); cout<<tb;
	Cursor(true, 1);
	_getch();
	Cursor(false, 100);
	SetBGColor(BLACK);
	SetColor(WHITE);
	for (int i=0; i<5; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
	}
};
void thongbao(int x, int y, string title, string tb[], int n, int length, int color, int BGcolor){
    int maxlength = tb[0].length();
    int i;
    for (i=1; i<n; i++)
        if(maxlength<tb[i].length()) maxlength = tb[i].length();
    
    if (length<maxlength||x<0||y<1) return;
    //xoa vung
    for (i=0; i<n+3; i++){
        gotoxy(x, y-1+i);
        cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
    }
    //xet mau
    SetBGColor(BGcolor);
    SetColor(color);
    //ve o
    gotoxy(x,y-1);
    cout << char(201) << setw(length+3) << setfill(char(205)) << char(187);
    for (i=0; i<n+1; i++){
        gotoxy(x, y+i);
        cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
    }
    gotoxy(x, y+n+1);
    cout << char(200) << setw(length+3) << setfill(char(205)) << char(188);
    //in chu
    gotoxy(x+1 + (length-title.length())/2, y); cout<<title;
    for (i=0; i<n; i++){
        gotoxy(x+1 + (length-tb[i].length())/2, y+1+i); cout<<tb[i];
    }
    //bat phim, xet mau lai nhu cu, xoa vung
    Cursor(true, 1);
    _getch();
    Cursor(false, 100);
    SetBGColor(BLACK);
    SetColor(WHITE);
    for (i=0; i<n+3; i++){
        gotoxy(x, y-1+i);
        cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
    }
};
int luachon(int x, int y, string tb, int length){
	if (length<tb.length()||x<0||y<1) return 0;
	for (int i=0; i<5; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
	}
	SetBGColor(LIGHT_YELLOW);
	SetColor(BLUE);
	string title="CANH BAO!";
	gotoxy(x,y-1);
	cout << char(201) << setw(length+3) << setfill(char(205)) << char(187);
	gotoxy(x, y);
	cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	gotoxy(x, y+1);
	cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	gotoxy(x, y+2);
	cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	gotoxy(x, y+3);
	cout << char(200) << setw(length+3) << setfill(char(205)) << char(188);
	gotoxy(x+1+(length-title.length())/2, y); cout<<title;
	gotoxy(x+1+(length-tb.length())/2, y+1); cout<<tb;
	gotoxy(x+1, y+2); cout<<"CO(1)";
	gotoxy(x+1+length/2,y+2); cout<<"KHONG(0)";
	Sleep(100); 
	char c;
	int choose = 1;
	highlight(x+1, y+2, length/2, LIGHT_AQUA);
	while (true){
		c = _getch();
		switch(c){
			case ENTER: {
				SetBGColor(BLACK); SetColor(WHITE);
				for (int i=0; i<5; i++){
					gotoxy(x, y-1+i);
					cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
				}
				return choose;
			}
			case KEY_LEFT:{
				if(choose==1) continue;
				highlight(x+1+length/2, y+2, length/2, LIGHT_YELLOW);
				highlight(x+1, y+2, length/2, LIGHT_AQUA);
				choose++;
				continue;
			}
			case KEY_RIGHT:{
				if(choose==0) continue;
				highlight(x+1, y+2, length/2, LIGHT_YELLOW);
				highlight(x+1+length/2, y+2, length/2, LIGHT_AQUA);
				choose--;
				continue;
			}
			case 48: {
				SetBGColor(BLACK); SetColor(WHITE);
				for (int i=0; i<5; i++){
					gotoxy(x, y-1+i);
					cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
				}
				return 0;
			}
			case 49: {
				SetBGColor(BLACK); SetColor(WHITE);
				for (int i=0; i<5; i++){
					gotoxy(x, y-1+i);
					cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
				}
				return 1;
			}
		}
	}
};
void HuongDanNhap(int x, int y, string hd[], int n, int row, int length){
	if(x<0||y<1) return;
	int i;
	gotoxy(x,y-1);
	cout << char(201) << setw(length+1) << setfill(char(205)) << char(187);	
	for(i=0; i<row; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(length) << setfill(' ') << char(186);
	}
	gotoxy(x, y+i);
	cout << char(200) << setw(length+1) << setfill(char(205)) << char(188);		
	for (i=0; i<n; i++){
		gotoxy(x+2, y+i);
		cout<<hd[i];
	}
};
string searchBox(int x, int y, int length, string search){
	if(x<0||y<1) return "";
	int i;
	gotoxy(x,y-1);
	cout << char(201) << setw(length+3) << setfill(char(205)) << char(187);	
	for(i=0; i<4; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(length+2) << setfill(' ') << char(186);
	}
	gotoxy(x, y+i);
	cout << char(200) << setw(length+3) << setfill(char(205)) << char(188);
	gotoxy(x + (length+3-search.length())/2, y); cout<<search;
	CreateBox(x+1, y+2, "", length);
	gotoxy(x+2,y+2); Cursor(true, 100);
	getline(cin, search);
	fflush(stdin);
	for (i=0; i<search.length(); i++) search[i] = toupper(search[i]);
	for(i=-1; i<=4; i++){
		gotoxy(x, y+i);
		cout << " " << setw(length+3) << setfill(' ') << " ";
	}
	Cursor(false, 100);
	return search;
};
