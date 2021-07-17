#pragma once
#include "Graphic.h"
#define HDTABLELENGTH 95
#define HDFORMLENGTH 40
#define CTTABLELENGTH 36
using namespace std;
string hdTittle = "  QUAN LI HOA DON  ";
string hdHeader[] = {" SOHD ", " MANV ", " HOTEN "," NGAYLAP ", " LOAI "};
string ctHeader[] = {" MAVATTU ", "   SL ", " DONGIA ", " %VAT "};
string hdNhapHD[] = {"1. SOHD khong qua 20 ki tu in",
						"va khong chua ki tu dac biet",		
					"2. MANV chi nhap so nguyen khong dau",
					"3. Nhap dung dinh dang NGAYTHANG",
					"4. LOAI chi nhap 'NHAP' hoac 'XUAT'",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapHDn = 7;
//=====Ten Ham=====//
//=====HoaDon=====//
//bang hoa don
void HoaDonTable(int x, int y, const ListNhanVien &list, int page);
//menu HoaDon
int HoaDonMenu();
//HoaDon view
void HoaDonView(const ListNhanVien &list, int page);
//HoaDon form
void HoaDonForm(int x, int y);
void showListHoaDon(int x, int y, ListHoaDon list, int page, int row);
void showListHoaDon(int x, int y, ListNhanVien list, int page, int index);
//=====CT_HD=====//
void CT_HDTable(int x, int y, ListCT_HD list);
int addCT_HDMenu(Info &info);
void addCT_HDView(Info &info);
int countHoaDon(ListNhanVien list);
//====Noi dung=====//
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
				int count = countHoaDon(list);
				int n; //n la tong so trang
				if(count%MAXTABLEROW==0) n=count/MAXTABLEROW;
				else n=count/MAXTABLEROW+1;
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
	gotoxy(XTABLE + (HDTABLELENGTH + 2 - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t1 (HoaDonTable, XTABLE, YTABLE, list, page);
	t1.join();
	tenbang = "|| BANG HUONG DAN ||";
	gotoxy(XTABLE + HDTABLELENGTH + 2 + (HDFORMLENGTH + 2 - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2 (HuongDanNhap, XTABLE + HDTABLELENGTH+2, YTABLE, 
		hdNhapHD, hdNhapHDn, MAXTABLEROW/2, HDFORMLENGTH);
	t2.join();
	thread t3 (HoaDonForm, XTABLE + HDTABLELENGTH+2, YTABLE2);
	t3.join();
	tenbang = "|| DANH SACH CHI TIET TUONG UNG ||";
	gotoxy(XTABLE + HDTABLELENGTH + 2 + HDFORMLENGTH + 2 + (CTTABLELENGTH + 2 - tenbang.length())/2, YTABLE-2); 
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
	cout << setw(3 + MAX_MANV) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << setw(8 + MAX_SOHD - hdHeader[0].length()) << setfill(' ') << hdHeader[0] << char(186);
	cout << hdHeader[1] << setw(3 + MAX_MANV - hdHeader[1].length()) << setfill(' ') << char(186);
	cout << hdHeader[2] << setw(3 + MAX_HO + 1 + MAX_TEN - hdHeader[2].length()) << setfill(' ') << char(186);
	cout << hdHeader[3] << setw(3 + MAX_NGAYLAP - hdHeader[3].length()) << setfill(' ') << char(186);
	cout << hdHeader[4] << setw(3 + MAX_LOAI - hdHeader[4].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_MANV) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<MAXTABLEROW; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(3 + MAX_SOHD) << setfill(' ') << char(186);
		cout << setw(3 + MAX_MANV) << setfill(' ') << char(186);
		cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(' ') << char(186);
		cout << setw(3 + MAX_NGAYLAP) << setfill(' ') << char(186);
		cout << setw(3 + MAX_LOAI) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+MAXTABLEROW+2);
	cout << char(200) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_MANV) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(188);
	//so trang
    ListHoaDon listHD = getListHoaDon(list);
    int n; //so dong
    if (listHD.n<MAXTABLEROW) n = listHD.n;
    else n = MAXTABLEROW;
    string p = "TRANG: " + to_string(page) + "/";
    if(listHD.n%MAXTABLEROW!=0) p += to_string(listHD.n/MAXTABLEROW + 1);
    else p+= to_string(listHD.n/MAXTABLEROW);
    CreateBox(x+HDTABLELENGTH+HDFORMLENGTH/2-6, y+MAXTABLEROW+4, p, 11);
    int index = (page-1)*MAXTABLEROW;
    //show list
    showListHoaDon(x, y, list, page, index);

};
void HoaDonForm(int x, int y){
	if(x<0||y<1) return ;
	//xoa vung
	int i;
	for (i=0; i<MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(HDFORMLENGTH+3)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x,y-1);
	cout << char(201) << setw(HDFORMLENGTH+1) << setfill(char(205)) << char(187);
	//khoang trong	
	for(i=0; i<MAXTABLEROW/2; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(HDFORMLENGTH) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+i);
	cout << char(200) << setw(HDFORMLENGTH+1) << setfill(char(205)) << char(188);
	string title = "--HOA DON FORM--";
	gotoxy(x + (HDFORMLENGTH-title.length()+1)/2, y);
	cout<<title;
	gotoxy(x+4, y+2); cout<<"SOHD:";
	gotoxy(x+4, y+5); cout<<"MANV:";
	gotoxy(x+4, y+8); cout<<"NGAYLAP";
	gotoxy(x+4, y+11); cout<<"LOAI:";
	for (int i=0; i<4; i++) CreateBox(x+14, y+2+i*3, " ", MAX_SOHD+2);
	gotoxy(x+15, y+8); cout<<"__/__/____";
	gotoxy(x+4, y+14); cout<<"HOAN THANH:";
};
void showListHoaDon(int x, int y, ListHoaDon list, int page, int row){
    HoaDon hd;
    for(hd = list.phead; hd != NULL&&row < 30; hd = hd->next){
        gotoxy(x+2, y+2+row);
        cout << hd->info.soHD;
        gotoxy(x+2+24,y+2+row);
        cout << hd->info.soHD;
        gotoxy(x+2+24+11,y+2+row);
        cout << convertDateToString(hd->info.ngayLap);
        gotoxy(x+2+24+11+15,y+2+row);
        cout << hd->info.loai;
        row++;
    }
};
void showListHoaDon(int x, int y, ListNhanVien list, int page, int index){
    HoaDon hd;
    int i,soNV = list.n;
    int row = 0, count = 0;
    for(i = 0; i < soNV; i++){
        for(hd = list.nhanViens[i]->hoaDons->phead; hd!=NULL&&row<30; hd = hd->next){
            if (count>=index){
            	gotoxy(x+2, y+2+row);
	            cout << hd->info.soHD;
	            gotoxy(x+2+MAX_SOHD+3,y+2+row);
	            cout << list.nhanViens[i]->maNV;
	            gotoxy(x+2+MAX_SOHD+3+MAX_MANV+3,y+2+row);
	            cout << list.nhanViens[i]->ho + " " + list.nhanViens[i]->ten;
	            gotoxy(x+2+MAX_SOHD+3+MAX_MANV+3+MAX_HO+1+MAX_TEN+3, y+2+row);
	            cout << convertDateToString(hd->info.ngayLap);
	            gotoxy(x+2+MAX_SOHD+3+MAX_MANV+3+MAX_HO+1+MAX_TEN+3+MAX_NGAYLAP+3, y+2+row);
	            cout << hd->info.loai;
				row++;
			}
			count++;
        }
    }
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
	cout << char(186) << ctHeader[0] << setw(3 + MAX_MAVT - ctHeader[0].length()) << setfill(' ') << char(186);
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
	//show list
	for (int i=0; i<list.n; i++){
		gotoxy(x+2, y+2+i); cout<<list.ct[i].maVT;
		gotoxy(x+2+MAX_MAVT+3, y+2+i); cout<<toString(list.ct[i].soluong, MAX_SL) ;
		gotoxy(x+2+MAX_MAVT+3+MAX_SL+3, y+2+i); cout<<toString(list.ct[i].dongia, MAX_DONGIA) ;
		gotoxy(x+2+MAX_MAVT+3+MAX_SL+3+MAX_DONGIA+3, y+2+i); cout<<toString(list.ct[i].VAT, MAX_VAT);
	}
};
int addCT_HDMenu(Info &info){
	addCT_HDView(info);
	return 1;
};
void addCT_HDView(Info &info){
	gotoxy(XTABLE, 0); cout<<char(186)<<"SOHD   :";
	gotoxy(XTABLE, 1); cout<<char(186)<<"NGAYLAP:";
	gotoxy(XTABLE, 2); cout<<char(186)<<"LOAI   :";
};
int countHoaDon(ListNhanVien list){
  int count = 0;
  for (int i=0; i<list.n; i++)
    count+=list.nhanViens[i]->hoaDons->n;
  return count;
};
