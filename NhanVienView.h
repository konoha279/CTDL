#pragma once
#include "Graphic.h"
#define NVTABLELENGTH 61
#define NVFORMLENGTH 60
using namespace std;

string nvTittle = "  QUAN LI NHAN VIEN  ";
string nvHeader[] = {" MANV ", " HO ", " TEN ", " PHAI "};
string hdNhapNV[] = {"1. MANV chi nhap so nguyen khong dau",
					"2. HO khong qua 32 ki tu in va khong chua ki tu dac biet",
					"3. TEN khong qua 11 ki tu in va khong chua ki tu dac biet",
					"4. PHAI chi nhap 'NAM' hoac 'NU'",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapNVn = 6;
//=====Ten Ham=====//
//view NhanVien
void NhanVienView(const ListNhanVien &list, int page);
//bang nhanvien
void NhanVienTable(int x, int y, const ListNhanVien &list, int page);
//menu cua nhan vien
int NhanVienMenu();
//FormNhanVien
void NhanVienForm(int x, int y);
//FormThemNhanVien
void addNhanVienForm(int x, int y, ListNhanVien& list, int page);
//=====Noi dung=====//
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
	//=====phan trang=====//
	//vi tri bat dau trong csdl vd: trang 1 bat dau tai 0 / trang 2 bat dau tai 30
	int index = (page-1)*MAXTABLEROW;
	//so phan tu dc in ra
	int n; 
	//Neu csdl it hon 30
	if (list.n<MAXTABLEROW) n = list.n;
	//Neu 30 phan tu nam o vi tri khong qua list.n
	else if(index + MAXTABLEROW - 1 < list.n) n = MAXTABLEROW;
	//Neu 30 phan tu vuot qua list.n
	else n = index + (list.n%MAXTABLEROW);
	//=====print so trang=====//
	string p = "TRANG: " + to_string(page) + "/";
	//dong if nay de lay tong so trang
	if(list.n % MAXTABLEROW!=0) p += to_string(list.n/MAXTABLEROW + 1);
	else p+= to_string(list.n/MAXTABLEROW);
	//vong for nay de xoa vung print so trang
	for (int i=0; i<3; i++){
		gotoxy(x+NVTABLELENGTH+NVFORMLENGTH/2-5, y+MAXTABLEROW+3+i);
		cout<<" "<<setw(13)<<setfill(' ')<<" "; 
	}
	CreateBox(x+NVTABLELENGTH+NVFORMLENGTH/2-6, y+MAXTABLEROW+4, p, 11);
	//=====show listnhanvien=====//
	//Chay tu i den n va kt them truong hop neu i bi lo khoi lisn.n ko bi crash
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
