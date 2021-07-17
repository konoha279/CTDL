#pragma once
#include "Graphic.h"
using namespace std;
string vtTittle = "  QUAN LI VAT TU  ";
string vtHeader[] = {" MAVATTU ", " TENVATTU ", " DONVITINH ", " SL_TON "};
string hdNhapVT[] = {"1. MAVATTU khong qua 10 ki tu in va khong chua ki tu dac biet",		
					"2. TENVATTU khong qua 50 ki tu in va khong chua ki tu dac biet",
					"3. DONVITINH khong qua 10 ki tu in va khong chua ki tu dac biet",
					"4. SOLUONGTON chi nhap so nguyen khong dau",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapVTn = 6;
//=====Ten Ham=====//
//VatTu table
void VatTuTable(int x, int y, PTRVatTu head, int page);
//VatTu view
int VatTuMenu();
void showListVatTu(int x, int y, PTRVatTu node, int page, int &i);
void VatTuView(const PTRVatTu &head, int page);
void VatTuForm(int x, int y);
//=====Noi dung=====//
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
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case PAGE_UP:{
				if(page==1) continue;
				page--;
				VatTuTable(XTABLE, YTABLE, head, page);
				line = 0;
				highlight(x, y, VTTABLELENGTH, YELLOW);
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
