#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <conio.h>
#include <thread>
#include <iomanip>
#include "mylib2.h"
#include "NhanVien.h"
#define LOGO  "logo.txt"
#define LOGO2 "logo2.txt"
#define LOGOHEIGHT 20
#define BUTTONWIDTH 17
#define BUTTONHEIGHT 3
#define FIRSTMAINBUTTON 22
#define MAXTABLEROW 30
#define YTABLE 6
#define YTABLE2 24
#define XNVTABLE 2
#define NVTABLELENGTH 61
#define HDTABLELENGTH 43
using namespace std;
string mainbutton[] = {"VATTU", "NHAN VIEN", "HOA DON", "THOAT"};
int mainbuttonn = 4;
string nvTittle = "  QUAN LI NHAN VIEN  ";
string rightButton[] = {"^", "<", "v", ">", "NUT DIEU HUONG"};
string buttomButton[] = {"ESC", "CTRL+F", "CTRL+N", "ENTER", "CTRL+S"};
string buttomCommand[] = {"QUAY LAI", "TIM KIEM", "THEM MOI", "CHINH SUA", "SAVE FILE"};
int buttomCommandn = 5;
string nvHeader[] = {" MANV ", " HO ", " TEN ", " PHAI "};
string hdHeader[] = {" SOHD ", " NGAYLAP ", " LOAI "};
string huongdannhapnv[]={"1. ENTER vao o can nhap de thuc hien qua trinh nhap",
						"2. ENTER de ket thuc qua trinh nhap",
						"3. Su dung phim KEY_UP, KEY_DOWN de lua chon o nhap",
						"4. Su dung phim 1 de hoan thanh form nhap",
						"5. Su dung phim 0 de quay lai",
						"6. MANV la so nguyen khong am",
						"7. HO la chuoi khong qua 32 ki tu",
						"8. TEN la chuoi khong qua 10 ki tu",
						"9. PHAI chi nhan 2 gia tri la 'NAM' hoac 'NU'",
						"10. Khong duoc de trong!"};
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
//view NhanVien
void NhanVienView(const ListNhanVien &list, int page);
//bang nhanvien
void NhanVienTable(int x, int y, const ListNhanVien &list, int page);
//menu cua nhan vien
int NhanVienMenu();
//ve nut
void drawButton();
//bang hoa don
void HoaDonTable(int x, int y, int maxrow, const NhanVien &nv, int page);
//thong bao
void thongbao(int x, int y, string title, string tb, int length, int color, int BGcolor);
//lua chon
int luachon(int x, int y, string tb, int length);
//FormNhanVien
void NhanVienForm(int x, int y, int length);
//FormThemNhanVien
int addForm(int x, int y, int length, ListNhanVien& list);
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
	str = v[0] + "." + v[1][0] + v[1][1];
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
		y+=3;
		gotoxy(x,++y);
		SetBGColor(BLACK);
		cout<<endl;
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
	while (true) {
		SetBGColor(BLACK); SetColor(WHITE);
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
				if (button == 4) continue;
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
}
void NhanVienView(const ListNhanVien &list, int page){
	clrscr();
	resizeConsole(WIDTH, HEIGHT);
	//tieu de
	CreateBox((MAXLINE - nvTittle.length())/2, 1, nvTittle, nvTittle.length());
	//nut
	drawButton();
	//ve bang + showlist
	string tenbang = "||  DANH SACH NHAN VIEN  ||";
	gotoxy(XNVTABLE + (NVTABLELENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t1 (NhanVienTable, XNVTABLE, YTABLE, list, page);
	t1.join();
	tenbang = "||  1 SO HOA DON DA LAP GAN DAY  ||";
	gotoxy(XNVTABLE + NVTABLELENGTH + 14 + (HDTABLELENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2 (HoaDonTable, XNVTABLE + NVTABLELENGTH + 15, YTABLE, MAXTABLEROW/2-1,*list.nhanViens[0], page);
	t2.join();
	thread t3 (NhanVienForm, XNVTABLE + NVTABLELENGTH + 15, YTABLE2, HDTABLELENGTH);
	t3.join();
};
void NhanVienTable(int x, int y, const ListNhanVien &list, int page){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(NVTABLELENGTH)<<setfill(' ')<<" "; 
	}
	//vien tren
	gotoxy(x, y-1);
	cout << char(201) << setw(7) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_HO) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_TEN) << setfill(char(205)) << char(203);
	cout << setw(7) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << nvHeader[0] << char(186);
	cout << nvHeader[1] << setw(3 + MAX_HO - nvHeader[1].length()) << setfill(' ') << char(186);
	cout << nvHeader[2] << setw(3 + MAX_TEN - nvHeader[2].length()) << setfill(' ') << char(186);
	cout << nvHeader[3] << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(7) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_HO) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TEN) << setfill(char(205)) << char(202);
	cout << setw(7) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<30; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(7) << setfill(' ') << char(186);
		cout << setw(3 + MAX_HO) << setfill(' ') << char(186);
		cout << setw(3 + MAX_TEN) << setfill(' ') << char(186);
		cout << setw(7) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+MAXTABLEROW+2);
	cout << char(200) << setw(7) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_HO) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TEN) << setfill(char(205)) << char(202);
	cout << setw(7) << setfill(char(205)) << char(188);
	//so trang
	int n; //so dong
	if (list.n<MAXTABLEROW) n = list.n;
	else n = MAXTABLEROW;
	string p = "TRANG: " + to_string(page) + "/";
	if(list.n%MAXTABLEROW!=0) p += to_string(list.n/MAXTABLEROW + 1);
	else p+= to_string(list.n/MAXTABLEROW);
	CreateBox(x+NVTABLELENGTH+2, y+MAXTABLEROW+1, p, 11);
	int index = (page-1)*MAXTABLEROW;
	//show listnhanvien
	for (int i=0; i<n && i+index<list.n; i++){
		gotoxy(x+2, y+2+i);
		cout<<toString(list.nhanViens[i+index]->maNV, 4);
		gotoxy(x+9, y+2+i);
		cout<<list.nhanViens[i+index]->ho;
		gotoxy(x+12+MAX_HO, y+2+i);
		cout<<list.nhanViens[i+index]->ten;
		gotoxy(x+47+MAX_TEN, y+2+i);
		if(list.nhanViens[i+index]->phai) cout<<"NU"; else cout<<"NAM";
	}
};
int NhanVienMenu(){
	ListNhanVien list; list.n=0;
	if(readFileNV(list, DEFAULT_NVFILE)) cout<<"\nLoi doc file";
	quicksort(list, 0, list.n - 1, 0);
	char c;
	string str;
	int line = 0, page = 1;
	int y = YTABLE + 2, x = XNVTABLE+1;
	NhanVienView(list, page);
	highlight(x, y, NVTABLELENGTH, YELLOW);
	while (true){
		SetBGColor(BLACK);
		gotoxy(155,42); cout<<"line: "<<line;
		gotoxy(155,43); cout<<"page: "<<page;
		c=_getch();
		switch(c){
			case KEY_UP:{
				if (line == 0) continue;
				y = YTABLE + 2 + line;
				highlight(x, y, NVTABLELENGTH, BLACK);
				highlight(x, y-1, NVTABLELENGTH, YELLOW);
				line--;
				continue;
			}
			case KEY_DOWN:{
				if (line == 29 || line == list.n) continue;
				y = YTABLE + 2 + line;
				highlight(x, y, NVTABLELENGTH, BLACK);
				highlight(x, y+1, NVTABLELENGTH, YELLOW);
				line++;
				continue;
			}
			case ENTER: return line;
			case PAGE_DOWN:{
				int n;
				if(list.n%MAXTABLEROW==0) n=list.n/MAXTABLEROW;
				else n=list.n/MAXTABLEROW+1;
				if (page+1>n) continue;
				page++;
				NhanVienView(list, page);
				line = 0;
				highlight(x, y, NVTABLELENGTH, YELLOW);
				continue;
			}
			case PAGE_UP:{
				if(page==1) continue;
				page--;
				NhanVienView(list, page);
				line = 0;
				highlight(x, y, NVTABLELENGTH, YELLOW);
				continue;
			}
			case ESC: return -1;
		}
	}
};
void drawButton(){
	//nut dieu khien
	int xright = MAXLINE - 14, y = 10;
	CreateBox(xright+4, y, rightButton[0], 1);
	for (int i=1; i<4; i++){
		CreateBox(xright + (i-1)*4, y+4, rightButton[i], 1);
	}
	CreateBox(xright - rightButton[4].length()/2 + 5, y+7, rightButton[4], rightButton[4].length());
	for (int i=0; i<buttomCommandn; i++){
		CreateBox(2+12*i, MAXROW-5, buttomButton[i], buttomButton[i].length());
		gotoxy(2+12*i, MAXROW-3); cout<<buttomCommand[i];
	}
};
void HoaDonTable(int x, int y, int maxrow, const NhanVien &nv, int page){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(HDTABLELENGTH)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x, y-1);
	cout << char(201) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << setw(8 + MAX_SOHD - hdHeader[0].length()) << setfill(' ') 
		<< hdHeader[0] << char(186);
	cout << hdHeader[1] << setw(3 + MAX_NGAYLAP - hdHeader[1].length()) << setfill(' ') << char(186);
	cout << hdHeader[2] << setw(3 + MAX_LOAI - hdHeader[2].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<maxrow; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(3 + MAX_SOHD) << setfill(' ') << char(186);
		cout << setw(3 + MAX_NGAYLAP) << setfill(' ') << char(186);
		cout << setw(3 + MAX_LOAI) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+maxrow+2);
	cout << char(200) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(188);
};
void thongbao(int x, int y, string title, string tb, int length, int color, int BGcolor){
	if (length<tb.length()||x<0||y<1) return;
	for (int i=0; i<5; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
	}
	SetBGColor(BGcolor);
	SetColor(color);
	for (int i=0; i<(length - title.length())/2; i++) title = " " + title;
	for (int i=0; i<(length - tb.length())/2; i++) tb = " " + tb;
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
	gotoxy(x+1, y); cout<<title;
	gotoxy(x+1, y+1); cout<<tb;
	gotoxy(x+1, y+2); cout<<"ENTER DE TIEP TUC...";
	Sleep(100);
	_getch();
	SetBGColor(BLACK);
	SetColor(WHITE);
	for (int i=0; i<5; i++){
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
void NhanVienForm(int x, int y, int length){
	if(x<0||y<1) return ;
	int i;
	for (i=0; i<MAXTABLEROW/2+3; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(length+3)<<setfill(' ')<<" ";
	}
	gotoxy(x,y-1);
	cout << char(201) << setw(length+1) << setfill(char(205)) << char(187);	
	for(i=0; i<MAXTABLEROW/2-1; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(length) << setfill(' ') << char(186);
	}
	gotoxy(x, y+i);
	cout << char(200) << setw(length+1) << setfill(char(205)) << char(188);
	string title = "--NHAN VIEN FORM--";
	gotoxy(x + (length-title.length()+1)/2, y);
	cout<<title;
	gotoxy(x+2, y+2); cout<<"MANV:";
	gotoxy(x+2, y+5); cout<<"HO:";
	gotoxy(x+2, y+8); cout<<"TEN:";
	gotoxy(x+2, y+11); cout<<"PHAI:";
	for (int i=0; i<4; i++) CreateBox(x+8, y+2+i*3, " ", 32);
	gotoxy(x+2, y+13); cout<<"HOAN THANH(1)";
	gotoxy(x+2+(length+2)/2, y+13); cout<<"QUAY LAI(0)"; 
};
int addForm(int x, int y, int length, ListNhanVien& list){
	char c;
	int manv, phai, line = 0;
	string ho, ten;
	gotoxy(x+9, y+1);
	Cursor(true, 100);
	return 1;
};
