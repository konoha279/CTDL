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
#include "VatTu.h"
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
#define NVTABLELENGTH 61
#define HDTABLELENGTH 53
#define NVFORMLENGTH 60
#define HDFORMLENGTH 60
#define VTTABLELENGTH 87
#define VTFORMLENGTH 66
#define CTTABLELENGTH 36
using namespace std;
string mainbutton[] = {"VATTU", "NHAN VIEN", "HOA DON", "THONGKE", "THOAT"};
int mainbuttonn = 5;
string nvTittle = "  QUAN LI NHAN VIEN  ";
string hdTittle = "  QUAN LI HOA DON  ";
string vtTittle = "  QUAN LI VAT TU  ";
string buttomButton[] = {"ESC", "CTRL+F", "CTRL+N", "ENTER", "CTRL+S", "CTRL+V", "PAGE", "CTRL+P"};
string buttomCommand[] = {"QUAY LAI", "TIM KIEM", "THEM MOI", "CHINH SUA", 
					"SAVE FILE", "SAP XEP", "TRANG", "XUAT HOA DON"};
int buttomCommandn = 8;
string nvHeader[] = {" MANV ", " HO ", " TEN ", " PHAI "};
string hdHeader[] = {" SOHD ", " MANVLAP ", " NGAYLAP ", " LOAI "};
string vtHeader[] = {" MAVATTU ", " TENVATTU ", " DONVITINH ", " SL_TON "};
string ctHeader[] = {" MAVATTU ", "   SL ", " DONGIA ", " %VAT "};
string hdNhapNV[] = {"1. MANV chi nhap so nguyen khong dau",
					"2. HO khong qua 32 ki tu in va khong chua ki tu dac biet",
					"3. TEN khong qua 11 ki tu in va khong chua ki tu dac biet",
					"4. PHAI chi nhap 'NAM' hoac 'NU'",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapNVn = 6;
string hdNhapHD[] = {"1. SOHD khong qua 20 ki tu in va khong chua ki tu dac biet",		
					"2. MANV chi nhap so nguyen khong dau",
					"3. Nhap dung dinh dang NGAYTHANG",
					"4. LOAI chi nhap 'NHAP' hoac 'XUAT'",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapHDn = 6;
string hdNhapVT[] = {"1. MAVATTU khong qua 10 ki tu in va khong chua ki tu dac biet",		
					"2. TENVATTU khong qua 50 ki tu in va khong chua ki tu dac biet",
					"3. DONVITINH khong qua 10 ki tu in va khong chua ki tu dac biet",
					"4. SOLUONGTON chi nhap so nguyen khong dau",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapVTn = 6;
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
void drawButton(int line);
//bang hoa don
void HoaDonTable(int x, int y, const ListNhanVien &list, int page);
//thong bao
void thongbao(int x, int y, string title, string tb, int length, int color, int BGcolor);
//lua chon
int luachon(int x, int y, string tb, int length);
//Huong dan nhap NhanVien
void HuongDanNhap(int x, int y, string hd[], int n, int row, int length);
//FormNhanVien
void NhanVienForm(int x, int y);
//FormThemNhanVien
void addNhanVienForm(int x, int y, ListNhanVien& list, int page);
//menu HoaDon
int HoaDonMenu();
//HoaDon view
void HoaDonView(const ListNhanVien &list, int page);
//HoaDon form
void HoaDonForm(int x, int y);
//VatTu table
void VatTuTable(int x, int y, PTRVatTu head, int page);
//VatTu view
int VatTuMenu();
void showListVatTu(int x, int y, PTRVatTu node, int page, int &i);
void VatTuView(const PTRVatTu &head, int page);
void VatTuForm(int x, int y);
void CT_HDTable(int x, int y, ListCT_HD list);
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
}
void NhanVienView(const ListNhanVien &list, int page){
	clrscr();
	resizeConsole(WIDTH, HEIGHT);
	//tieu de
	CreateBox(XTABLE + 16, 1, "", NVFORMLENGTH+NVTABLELENGTH+2);
	gotoxy((MAXLINE - nvTittle.length())/2,1); cout<<nvTittle;
	//nut
	drawButton(2);
	//ve bang + showlist
	string tenbang = "||  DANH SACH NHAN VIEN  ||";
	gotoxy(XTABLE + 16 + (NVTABLELENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t1 (NhanVienTable, XTABLE + 16, YTABLE, list, page);
	t1.join();
	tenbang = "|| BANG HUONG DAN ||";
	gotoxy(XTABLE + 16 + NVTABLELENGTH + 2 + (NVFORMLENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2 (HuongDanNhap, XTABLE + 16 + NVTABLELENGTH + 2, YTABLE, 
		hdNhapNV, hdNhapNVn, MAXTABLEROW/2, NVFORMLENGTH);
	t2.join();
	thread t3 (NhanVienForm, XTABLE + 16 + NVTABLELENGTH + 2, YTABLE2);
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
	for (int i=0; i<MAXTABLEROW; i++){
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
	for (int i=0; i<3; i++){
		gotoxy(x+NVTABLELENGTH+NVFORMLENGTH/2-5, y+MAXTABLEROW+3+i);
		cout<<" "<<setw(13)<<setfill(' ')<<" "; 
	}
	CreateBox(x+NVTABLELENGTH+NVFORMLENGTH/2-6, y+MAXTABLEROW+4, p, 11);
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
	int y = YTABLE + 2, x = XTABLE+17;
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
			case PAGE_DOWN:{
				int n;
				if(list.n%MAXTABLEROW==0) n=list.n/MAXTABLEROW;
				else n=list.n/MAXTABLEROW+1;
				if (page+1>n) continue;
				page++;
				NhanVienTable(XTABLE + 16, YTABLE, list, page);
				line = 0;
				highlight(x, y, NVTABLELENGTH, YELLOW);
				continue;
			}
			case PAGE_UP:{
				if(page==1) continue;
				page--;
				NhanVienTable(XTABLE + 16, YTABLE, list, page);
				line = 0;
				highlight(x, y, NVTABLELENGTH, YELLOW);
				continue;
			}
			case ENTER: return line;
			case CTRL_N:{
				addNhanVienForm(XTABLE + 16 + NVFORMLENGTH + 2, YTABLE2, list, page);
				continue;
			}
			case ESC: return -1;
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
void NhanVienForm(int x, int y){
	if(x<0||y<1) return ;
	//xoa vung
	int i;
	for (i=0; i<MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(NVFORMLENGTH+3)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x,y-1);
	cout << char(201) << setw(NVFORMLENGTH+1) << setfill(char(205)) << char(187);
	//khoang trong	
	for(i=0; i<MAXTABLEROW/2; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(NVFORMLENGTH) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+i);
	cout << char(200) << setw(NVFORMLENGTH+1) << setfill(char(205)) << char(188);
	string title = "--NHAN VIEN FORM--";
	gotoxy(x + (NVFORMLENGTH-title.length()+1)/2, y);
	cout<<title;
	gotoxy(x+5, y+2); cout<<"MANV:";
	gotoxy(x+5, y+5); cout<<"HO:";
	gotoxy(x+5, y+8); cout<<"TEN:";
	gotoxy(x+5, y+11); cout<<"PHAI:";
	for (int i=0; i<4; i++) CreateBox(x+15, y+2+i*3, " ", MAX_HO+2);
	gotoxy(x+5, y+14); cout<<"HOAN THANH:";
};
void addNhanVienForm(int defaultx, int defaulty, ListNhanVien& list, int page){
	char c;
	int line = 1;
	//Lay tao do o thu nhat
	int x = defaultx + 17, y = defaulty + 2;
	while (true){
		//debug
		gotoxy(135, 43); cout<<"x:"<<x;  gotoxy(141, 43); cout<<"y:"<<y; gotoxy(146, 43); cout<<"list.n:"<<list.n;
		//nhay den vi tri can den
		gotoxy(x, y);
		//bat con tro
		Cursor(true, 100);
		c=_getch();
		//Neu la phim dieu huong
		if(c==-32){
			c=_getch();
			switch (c){
				case KEY_UP:{
					if(line==1) continue;
					x = defaultx + 17; y-=3;
					line--;
					continue;
				}
				case KEY_DOWN:{
					if(line==5) continue;
					x = defaultx + 17; y+=3;
					line++;
					continue;
				}
				case KEY_LEFT:{
					if(x == defaultx + 17) continue;
					x--;
					continue;
				}
				case KEY_RIGHT:{
					if(x == defaultx + 17 + 32) continue;
					x++;
					continue;
				}
				case PAGE_DOWN:{
					int n;
					if(list.n%MAXTABLEROW==0) n=list.n/MAXTABLEROW;
					else n=list.n/MAXTABLEROW+1;
					if (page+1>n) continue;
					page++;
					NhanVienTable(XTABLE + 16, YTABLE, list, page);
					line = 0;
					highlight(x, y, NVTABLELENGTH, YELLOW);
					continue;
				}
				case PAGE_UP:{
					if(page==1) continue;
					page--;
					NhanVienTable(XTABLE + 16, YTABLE, list, page);
					line = 0;
					highlight(x, y, NVTABLELENGTH, YELLOW);
					continue;
				}
			}
		}else
			switch (c){
				case BACKSPACE:{
					x--;
					gotoxy(x,y); cout<<" ";
					continue;
				}
				case ESC: return;
				case ENTER: {
					if (line==5) {
						string str="", ho="", ten="", phai="";
						int maNV, i;
						int xx=defaultx+17, yy=defaulty+2;
						for (i=0; i<32&&readChar(xx+i,yy)!=SPACE; i++) str += readChar(xx+i,yy);
						maNV = atoi(str.c_str());
						if (indexOf(list, maNV)>-1) {
							thongbao(XTABLE + NVTABLELENGTH + 15, MAXROW-5, "CANH BAO",
							"TRUNG MA NHAN VIEN!", NVFORMLENGTH-2, YELLOW, LIGHT_RED);
							NhanVienTable(XTABLE + 16, YTABLE, list, page);
							continue;
						}
						for (i=0; i<32; i++) ho+=readChar(xx+i,yy+3); trim(ho);
						for (i=0; i<32; i++) ten+=readChar(xx+i,yy+6); trim(ten);
						for (i=0; i<32; i++) phai+=readChar(xx+i, yy+9); trim(phai);
						if (!strcmp(phai.c_str(),"NU")) i=1; 
							else if (!strcmp(phai.c_str(),"NAM")) i=0;
							else {
								thongbao(XTABLE + NVTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"PHAI NHAP SAI DINH DANG!", NVFORMLENGTH-2, BLUE, LIGHT_GREEN);
								NhanVienTable(XTABLE + 16, YTABLE, list, page);
								continue;
							}
						NhanVien nv = createNhanVien(maNV, ho, ten, i);
						if (add(list,nv)==1) {
							thongbao (XTABLE + NVTABLELENGTH + 15, MAXROW-5, "THONG BAO",
							"DA THEM NHAN VIEN THANH CONG!", NVFORMLENGTH-2, BLUE, LIGHT_GREEN);
							NhanVienForm (defaultx+1, defaulty);
							NhanVienTable(XTABLE + 16, YTABLE, list, page);
							return;
						}
						else {
							thongbao(XTABLE + NVTABLELENGTH + 15, MAXROW-5, "THONG BAO",
							"DA THEM NHAN VIEN THAT BAI!", NVFORMLENGTH-2, YELLOW, LIGHT_RED);
							NhanVienTable(XTABLE + 16, YTABLE, list, page);
							continue;
						}
					}
					continue;
				}
				default:{
					switch (line){
						case 1:{
							if(isNumber(c)){
								cout<<c; x++;
							} else {
								thongbao(XTABLE + NVTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"KHONG CHI NHAP SO!", NVFORMLENGTH-2, YELLOW, RED);
								NhanVienTable(XTABLE + 16, YTABLE, list, page);
							}
							continue;
						}
						case 2:
						case 3:
						case 4:{
							if(!isBlackchar(c)) {
								cout<<char(toupper(c)); x++;	
							} else {
								thongbao(XTABLE + NVTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"KI TU VUA NHAP KHONG DUOC CHO PHEP!", NVFORMLENGTH-2, YELLOW, RED);
								NhanVienTable(XTABLE + 16, YTABLE, list, page);
							}
							continue;
						}
						case 5: continue;
					}
					continue;
				}
			}
	}
};
int HoaDonMenu(){
	ListNhanVien list;
	if(!readFileNV(list, DEFAULT_NVFILE)) cout<<"Loi doc file!";
	char c;
	string str;
	int line = 0, page = 1;
	int y = YTABLE + 2, x = XTABLE+1;
	HoaDonView(list, page);
	highlight(x, y, HDTABLELENGTH, YELLOW);
	while (true){
		SetBGColor(BLACK);
		gotoxy(155,42); cout<<"line: "<<line;
		gotoxy(155,43); cout<<"page: "<<page;
		c=_getch();
		switch(c){
			case KEY_UP:{
				if (line == 0) continue;
				y = YTABLE + 2 + line;
				highlight(x, y, HDTABLELENGTH, BLACK);
				highlight(x, y-1, HDTABLELENGTH, YELLOW);
				line--;
				continue;
			}
			case KEY_DOWN:{
				if (line == 29 || line == list.n) continue;
				y = YTABLE + 2 + line;
				highlight(x, y, HDTABLELENGTH, BLACK);
				highlight(x, y+1, HDTABLELENGTH, YELLOW);
				line++;
				continue;
			}
			case PAGE_DOWN:{
				int n;
				if(list.n%MAXTABLEROW==0) n=list.n/MAXTABLEROW;
				else n=list.n/MAXTABLEROW+1;
				if (page+1>n) continue;
				page++;
				HoaDonTable(XTABLE, YTABLE, list, page);
				line = 0;
				highlight(x, y, HDTABLELENGTH, YELLOW);
				continue;
			}
			case PAGE_UP:{
				if(page==1) continue;
				page--;
				HoaDonTable(XTABLE, YTABLE, list, page);
				line = 0;
				highlight(x, y, HDTABLELENGTH, YELLOW);
				continue;
			}
			case ENTER: return line;
			case CTRL_N:{
//				addForm(XTABLE + HDFORMLENGTH + 15, YTABLE2, list, page);
				continue;
			}
			case ESC: return -1;
		}
	}
};
void HoaDonView(const ListNhanVien &list, int page){
	clrscr();
	resizeConsole(WIDTH, HEIGHT);
	//tieu de
	CreateBox(XTABLE, 1, "", HDFORMLENGTH+HDTABLELENGTH+2+CTTABLELENGTH+2);
	gotoxy((MAXLINE - hdTittle.length())/2,1); cout<<hdTittle;
	//nut
	drawButton(3);
	//ve bang + showlist
	string tenbang = "||  DANH SACH HOA DON  ||";
	gotoxy(XTABLE + (HDTABLELENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t1 (HoaDonTable, XTABLE, YTABLE, list, page);
	t1.join();
	tenbang = "|| BANG HUONG DAN ||";
	gotoxy(XTABLE + HDTABLELENGTH + 2 + (HDFORMLENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2 (HuongDanNhap, XTABLE + HDTABLELENGTH+2, YTABLE, 
		hdNhapHD, hdNhapHDn, MAXTABLEROW/2, HDFORMLENGTH);
	t2.join();
	thread t3 (HoaDonForm, XTABLE + HDTABLELENGTH+2, YTABLE2);
	t3.join();
	tenbang = "|| DANH SACH CHI TIET TUONG UNG ||";
	gotoxy(XTABLE + HDTABLELENGTH + 2 + HDFORMLENGTH + 2 + (CTTABLELENGTH - tenbang.length())/2, YTABLE-2); 
	cout<<tenbang;
	CT_HDTable(XTABLE+HDTABLELENGTH+2+HDFORMLENGTH+2, YTABLE, *list.nhanViens[0]->hoaDons->phead->info.listct);
};
void HoaDonTable(int x, int y, const ListNhanVien &list, int page){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(HDTABLELENGTH)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x, y-1);
	cout << char(201) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(203);
	cout << setw(10) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << setw(8 + MAX_SOHD - hdHeader[0].length()) << setfill(' ') 
		<< hdHeader[0] << char(186);
	cout << hdHeader[1] << char(186);
	cout << hdHeader[2] << setw(3 + MAX_NGAYLAP - hdHeader[1].length()) << setfill(' ') << char(186);
	cout << hdHeader[3] << setw(3 + MAX_LOAI - hdHeader[2].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(10) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<MAXTABLEROW; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(3 + MAX_SOHD) << setfill(' ') << char(186);
		cout << setw(10) << setfill(' ') << char(186);
		cout << setw(3 + MAX_NGAYLAP) << setfill(' ') << char(186);
		cout << setw(3 + MAX_LOAI) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+MAXTABLEROW+2);
	cout << char(200) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(10) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(188);
	//so trang
	int n; //so dong
	if (list.n<MAXTABLEROW) n = list.n;
	else n = MAXTABLEROW;
	string p = "TRANG: " + to_string(page) + "/";
	if(list.n%MAXTABLEROW!=0) p += to_string(list.n/MAXTABLEROW + 1);
	else p+= to_string(list.n/MAXTABLEROW);
	CreateBox(x+HDTABLELENGTH+HDFORMLENGTH/2-6, y+MAXTABLEROW+1, p, 11);
	int index = (page-1)*MAXTABLEROW;
	//show list
};
void HoaDonForm(int x, int y){
	if(x<0||y<1) return ;
	//xoa vung
	int i;
	for (i=0; i<MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(NVFORMLENGTH+3)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x,y-1);
	cout << char(201) << setw(NVFORMLENGTH+1) << setfill(char(205)) << char(187);
	//khoang trong	
	for(i=0; i<MAXTABLEROW/2; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(NVFORMLENGTH) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+i);
	cout << char(200) << setw(NVFORMLENGTH+1) << setfill(char(205)) << char(188);
	string title = "--HOA DON FORM--";
	gotoxy(x + (NVFORMLENGTH-title.length()+1)/2, y);
	cout<<title;
	gotoxy(x+5, y+2); cout<<"SOHD:";
	gotoxy(x+5, y+5); cout<<"MANV:";
	gotoxy(x+5, y+8); cout<<"NGAYLAP";
	gotoxy(x+5, y+11); cout<<"LOAI:";
	for (int i=0; i<4; i++) CreateBox(x+15, y+2+i*3, " ", MAX_HO+2);
	gotoxy(x+17, y+8); cout<<"__/__/____";
	gotoxy(x+5, y+14); cout<<"HOAN THANH:";
};
int VatTuMenu(){
	PTRVatTu head = NULL;
	ReadFile(head);
	VatTu vattu = head->vatTu;
	char c;
	string str;
	int line = 0, page = 1;
	int y = YTABLE + 2, x = 1+1;
	VatTuView(head, page);
	highlight(x, y, VTTABLELENGTH, YELLOW);
	while (true){
		SetBGColor(BLACK);
		gotoxy(155,41); cout<<"size: "<<sizeVatTu;
		gotoxy(155,42); cout<<"line: "<<line;
		gotoxy(155,43); cout<<"page: "<<page;
		c=_getch();
		switch(c){
			case KEY_UP:{
				if (line == 0) continue;
				y = YTABLE + 2 + line;
				highlight(x, y, VTTABLELENGTH, BLACK);
				highlight(x, y-1, VTTABLELENGTH, YELLOW);
				line--;
				continue;
			}
			case KEY_DOWN:{
				if (line == 29 || line == sizeVatTu-1) continue;
				y = YTABLE + 2 + line;
				highlight(x, y, VTTABLELENGTH, BLACK);
				highlight(x, y+1, VTTABLELENGTH, YELLOW);
				line++;
				continue;
			}
			case PAGE_DOWN:{
				int n;
				if(sizeVatTu%MAXTABLEROW==0) n=sizeVatTu/MAXTABLEROW;
				else n=sizeVatTu/MAXTABLEROW+1;
				if (page+1>n) continue;
				page++;
				VatTuTable(XTABLE, YTABLE, head, page);
				line = 0;
				highlight(x, y, NVTABLELENGTH, YELLOW);
				continue;
			}
			case PAGE_UP:{
				if(page==1) continue;
				page--;
				VatTuTable(XTABLE, YTABLE, head, page);
				line = 0;
				highlight(x, y, NVTABLELENGTH, YELLOW);
				continue;
			}
			case ENTER: return line;
			case CTRL_N:{
//				addVatTuForm(XTABLE + NVFORMLENGTH + 15, YTABLE2, head, page);
				continue;
			}
			case ESC: return -1;
		}
	}
};
void VatTuTable(int x, int y, PTRVatTu head, int page){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(VTTABLELENGTH)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x, y-1);
	cout << char(201) << setw(3 + MAX_MAVT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_TENVT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_DVT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_SL_TON) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << vtHeader[0] << setw(3 + MAX_MAVT - vtHeader[0].length()) << setfill(' ') << char(186);
	cout << vtHeader[1] << setw(3 + MAX_TENVT - vtHeader[1].length()) << setfill(' ') << char(186);
	cout << vtHeader[2] << setw(3 + MAX_DVT - vtHeader[2].length()) << setfill(' ') << char(186);
	cout << vtHeader[3] << setw(3 + MAX_SL_TON - vtHeader[3].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(3 + MAX_MAVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TENVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_DVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_SL_TON) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<MAXTABLEROW; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(3 + MAX_MAVT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_TENVT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_DVT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_SL_TON) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+MAXTABLEROW+2);
	cout << char(200) << setw(3 + MAX_MAVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TENVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_DVT) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_SL_TON) << setfill(char(205)) << char(188);
	//so trang
	int n; //so dong
	if (sizeVatTu<MAXTABLEROW) n = sizeVatTu;
	else n = MAXTABLEROW;
	string p = "TRANG: " + to_string(page) + "/";
	if(sizeVatTu%MAXTABLEROW!=0) p += to_string(sizeVatTu/MAXTABLEROW + 1);
	else p+= to_string(sizeVatTu/MAXTABLEROW);
	CreateBox(x+VTTABLELENGTH+2, y+MAXTABLEROW+4, p, 11);
	n=0;
	showListVatTu(x, y, head, page, n);
};

void VatTuView(const PTRVatTu &head, int page){
	clrscr();
	resizeConsole(WIDTH, HEIGHT);
	//tieu de
	CreateBox(XTABLE, 1, "", VTFORMLENGTH+VTTABLELENGTH+2);
	gotoxy((MAXLINE - vtTittle.length())/2,1); cout<<vtTittle;
	//nut
	drawButton(1);
	//ve bang + showlist
	string tenbang = "||  DANH SACH VAT TU  ||";
	gotoxy(XTABLE + (VTTABLELENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t1 (VatTuTable, XTABLE, YTABLE, head, page);
	t1.join();
	tenbang = "|| BANG HUONG DAN ||";
	gotoxy(XTABLE + VTTABLELENGTH + (VTFORMLENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2 (HuongDanNhap, XTABLE+VTTABLELENGTH+2, YTABLE, hdNhapVT, hdNhapVTn, MAXTABLEROW/2, VTFORMLENGTH);
	t2.join();
	thread t3 (VatTuForm, XTABLE+VTTABLELENGTH+2, YTABLE2);
	t3.join();
};
void showListVatTu(int x, int y, PTRVatTu node, int page, int &i){
	if (node!=NULL&&i<30){
		showListVatTu(x, y, node->left, page, i);
			gotoxy(x+2, y+2+i);
			cout<<node->vatTu.maVT;
			gotoxy(x+15, y+2+i);
			cout<<node->vatTu.tenVT;
			gotoxy(x+68, y+2+i);
			cout<<node->vatTu.dvt;
			gotoxy(x+81, y+2+i);
			cout<<node->vatTu.soLuongTon;
			i++;
		showListVatTu(x, y, node->right, page, i);
	}
};
void VatTuForm(int x, int y){
	if(x<0||y<1) return ;
	//xoa vung
	int i;
	for (i=0; i<MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(VTFORMLENGTH+3)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x,y-1);
	cout << char(201) << setw(VTFORMLENGTH+1) << setfill(char(205)) << char(187);
	//khoang trong	
	for(i=0; i<MAXTABLEROW/2; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(VTFORMLENGTH) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+i);
	cout << char(200) << setw(VTFORMLENGTH+1) << setfill(char(205)) << char(188);
	string title = "--VAT TU FORM--";
	gotoxy(x + (VTFORMLENGTH-title.length()+1)/2, y);
	cout<<title;
	gotoxy(x+3, y+2); cout<<"MAVATTU:";
	gotoxy(x+3, y+5); cout<<"TENVATTU:";
	gotoxy(x+3, y+8); cout<<"DONVITINH:";
	gotoxy(x+3, y+11); cout<<"SOLUONGTON:";
	for (int i=0; i<4; i++) CreateBox(x+13, y+2+i*3, " ", MAX_TENVT+1);
	gotoxy(x+3, y+14); cout<<"HOAN THANH:";
};
void CT_HDTable(int x, int y, ListCT_HD list){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(VTTABLELENGTH)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x, y-1);
	cout << char(201) << setw(3 + MAX_MAVT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_SL) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_DONGIA) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_VAT) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << ctHeader[0] << setw(3 + MAX_MAVT - vtHeader[0].length()) << setfill(' ') << char(186);
	cout << ctHeader[1] << setw(3 + MAX_SL - ctHeader[1].length()) << setfill(' ') << char(186);
	cout << ctHeader[2] << setw(3 + MAX_DONGIA - ctHeader[2].length()) << setfill(' ') << char(186);
	cout << ctHeader[3] << setw(3 + MAX_VAT - ctHeader[3].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(3 + MAX_MAVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_SL) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_DONGIA) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_VAT) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<20; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(3 + MAX_MAVT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_SL) << setfill(' ') << char(186);
		cout << setw(3 + MAX_DONGIA) << setfill(' ') << char(186);
		cout << setw(3 + MAX_VAT) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+20+2);
	cout << char(200) << setw(3 + MAX_MAVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_SL) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_DONGIA) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_VAT) << setfill(char(205)) << char(188);
	for (int i=0; i<list.n; i++){
		gotoxy(x+2, y+2+i); cout<<list.ct[i].maVT;
		gotoxy(x+2+MAX_MAVT+3, y+2+i); cout<<toString(list.ct[i].soluong, MAX_SL) ;
		gotoxy(x+2+MAX_MAVT+3+MAX_SL+3, y+2+i); cout<<toString(list.ct[i].dongia, MAX_DONGIA) ;
		gotoxy(x+2+MAX_MAVT+3+MAX_SL+3+MAX_DONGIA+3, y+2+i); cout<<toString(list.ct[i].VAT, MAX_VAT);
	}
};
