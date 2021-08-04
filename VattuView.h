#pragma once
#include "Graphic.h"
using namespace std;
string vtTittle = "  QUAN LI VAT TU  ";
string vtHeader[] = {" MAVATTU ", " TENVATTU ", " DONVITINH ", " SOLUONGTON "};
string hdNhapVT[] = {"1. MAVATTU khong qua 10 ki tu in va khong khoang trang",		
					"2. TENVATTU khong qua 50 ki tu in va khong chua ki tu dac biet",
					"3. DONVITINH khong qua 10 ki tu in va khong chua ki tu dac biet",
					"4. SOLUONGTON chi nhap so nguyen khong dau",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh",
					"7. CTRL_F va nhap chuoi rong de thoat khoi tim kiem"};
int hdNhapVTn = 6;
//=====Ten Ham=====//
//VatTu table
void VatTuTable(int x, int y, const mangVatTu &arr, int page);
//VatTu view
int VatTuMenu(PTRVatTu &head, ListNhanVien &list);
void showListVatTu(int x, int y, const mangVatTu &arr, int page);
void VatTuView(const mangVatTu &arr, int page);
void VatTuForm(int x, int y);
int addVatTuForm(int xform, int yform, PTRVatTu root, int page);
int editVatTuForm(int xform, int yform, PTRVatTu root, int page, int xtable, int ytable, int tline);
string getMaVTTable(int x, int y, int line);
//=====Noi dung=====//
int VatTuMenu(PTRVatTu &head, ListNhanVien &list){
	mangVatTu arr;
	ListToArray(head, arr);
	char c;
	int line = 0, page = 1;
	int y = YTABLE + 2, x = XTABLE+1;
	VatTuView(arr, page);
	highlight(x, y, VTTABLELENGTH, YELLOW);
	SetBGColor(BLACK);
	while (true){
		Cursor(false, 100);
//		gotoxy(155,41); cout<<"size: "<<sizeVatTu;
//		gotoxy(155,42); cout<<"line: "<<line;
//		gotoxy(155,43); cout<<"page: "<<page;
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
				if (line == 29 || line + (page-1)*30 == arr.n-1) continue;
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
				VatTuTable(XTABLE, YTABLE, arr, page);
				highlight(x, y, VTTABLELENGTH, BLACK);
				line = 0; y = YTABLE + 2;
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case PAGE_UP:{
				if(page==1) continue;
				page--;
				VatTuTable(XTABLE, YTABLE, arr, page);
				highlight(x, y, VTTABLELENGTH, BLACK);
				line = 0; y = YTABLE + 2;
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case ENTER: {
				highlight(x, y, VTTABLELENGTH, BLACK);
				if(editVatTuForm(XTABLE + VTTABLELENGTH + 4, YTABLE2, head, page, 
				XTABLE + 1, YTABLE + 2, line)==1){
					removeMang(arr);
					ListToArray(head, arr);
				}
				line = 0; y = YTABLE + 2;
				VatTuTable(XTABLE, YTABLE, arr, page);
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case CTRL_N:{
				highlight(x, y, VTTABLELENGTH, BLACK);
				if(addVatTuForm(XTABLE + VTTABLELENGTH + 4, YTABLE2, head, page)==1) {
					sizeVatTu++;
					removeMang(arr);
					ListToArray(head, arr);
				}
				VatTuTable(XTABLE, YTABLE, arr, page);
				line = 0; y = YTABLE + 2;
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case CTRL_V:{
				QuicksortVatTu(arr, 0, arr.n-1);
				highlight(x, y, VTTABLELENGTH, BLACK);
				VatTuTable(XTABLE, YTABLE, arr, page);
				line = 0; y = YTABLE + 2;
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case CTRL_S:{
				if(luachon(XTABLE + VTTABLELENGTH + 2, MAXROW-6,
				"Neu save file, du lieu hien tai khong the sua, ban chac chan muon save file?", 80)==1){
					InFile(head);
					thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6,"THONG BAO",
					"FILE DA DUOC SAVE!", VTFORMLENGTH-2, BLUE, LIGHT_GREEN);
				}
				VatTuTable(XTABLE, YTABLE, arr, page);
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case CTRL_L:{
				if(luachon(XTABLE + VTTABLELENGTH + 3, MAXROW-5,
				"Neu load file, du lieu chua duoc luu se mat, ban chac chan muon load file?", 80)==1){
					freePTRVatTu(head);
					removeMang(arr);
					sizeVatTu=0;
					head = NULL;
					ReadFile(head);
					ListToArray(head, arr);
					highlight(x, y, VTTABLELENGTH, BLACK);
					thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6,"THONG BAO",
					"FILE DA DUOC LOAD!", VTFORMLENGTH-2, BLUE, LIGHT_GREEN);
					VatTuTable(XTABLE, YTABLE, arr, page);
					line = 0; y = YTABLE + 2;
					highlight(x, y, VTTABLELENGTH, YELLOW);
				}
				continue;
			}
			case 8:{
				string str = getMaVTTable(XTABLE + 1, YTABLE + 2, line);
				char mavt[11];
				strcpy(mavt, str.c_str());
				CT_HD ct = getCT_HD(list, mavt);
				if(ct.soluong!=0) {
					thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6,"CANH BAO",
					"VAT TU DA DUOC LAP HOA DON, KHONG DUOC QUYEN XOA!", VTFORMLENGTH-2, YELLOW, RED);
				}
				else if(luachon(XTABLE + VTTABLELENGTH + 2, MAXROW-6,
				"Ban chac chan muon xoa?", VTFORMLENGTH-2)==1){					
					remove(head, mavt);
					removeMang(arr);
					ListToArray(head, arr);
					thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6,"THANH CONG",
					"VAT TU DA DUOC XOA!", VTFORMLENGTH-2, BLUE, LIGHT_GREEN);
				}
				VatTuTable(XTABLE, YTABLE, arr, page);
				line = 0; y = YTABLE + 2;
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case CTRL_F:{
				string str = searchBox(XTABLE, YTABLE+6, VTTABLELENGTH-2, "NHAP SO HD");
				if(str=="") {
					removeMang(arr);
					ListToArray(head, arr);
				} else {
					char maVT[MAX_MAVT]; strcpy(maVT, str.c_str());
					PTRVatTu node = Search(head, maVT);
					if(node==NULL){
						thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
						"KHONG TIM THAY HOA DON!", VTFORMLENGTH-2, YELLOW, RED);
						continue;
					}
					removeMang(arr);
					add(arr, node);
				}
				VatTuTable(XTABLE, YTABLE, arr, page);
				line = 0; y = YTABLE + 2;
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
			case ESC: {
				if (luachon(XTABLE + VTTABLELENGTH + 2, MAXROW-6, 
				"Neu thoat du lieu cua ban se khong duoc luu lai. Ban chac chan muon thoat?",80)==1) return 1;
				VatTuTable(XTABLE, YTABLE, arr, page);
				highlight(x, y, VTTABLELENGTH, YELLOW);
				continue;
			}
		}
	}
};
void VatTuTable(int x, int y, const mangVatTu &arr, int page){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW+3; i++){
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
	if (arr.n<MAXTABLEROW) n = arr.n;
	else n = MAXTABLEROW;
	string p = "TRANG: " + to_string(page) + "/";
	if(arr.n % MAXTABLEROW!=0) p += to_string(arr.n/MAXTABLEROW + 1);
	else p+= to_string(arr.n/MAXTABLEROW);
	CreateBox(x+VTTABLELENGTH+2, y+MAXTABLEROW+4, p, 11);
	showListVatTu(x, y, arr, page);
};

void VatTuView(const mangVatTu &arr, int page){
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
	thread t1 (VatTuTable, XTABLE, YTABLE, arr, page);
	t1.join();
	tenbang = "|| BANG HUONG DAN ||";
	gotoxy(XTABLE + VTTABLELENGTH + (VTFORMLENGTH - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2 (HuongDanNhap, XTABLE+VTTABLELENGTH+2, YTABLE, hdNhapVT, hdNhapVTn, MAXTABLEROW/2, VTFORMLENGTH);
	t2.join();
	thread t3 (VatTuForm, XTABLE+VTTABLELENGTH+2, YTABLE2);
	t3.join();
};
void showListVatTu(int x, int y, const mangVatTu &arr, int page){
	int index = (page-1)*MAXTABLEROW;
	for (int i=0; i<MAXTABLEROW&&i+index<arr.n; i++){
		gotoxy(x+2, y+2+i);
		cout<<arr.mangVatTu[i+index].maVT;
		gotoxy(x+15, y+2+i);
		cout<<arr.mangVatTu[i+index].tenVT;
		gotoxy(x+68, y+2+i);
		cout<<arr.mangVatTu[i+index].dvt;
		gotoxy(x+81, y+2+i);
		cout<<toString(arr.mangVatTu[i+index].soLuongTon, MAX_SL_TON);
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
int addVatTuForm(int xform, int yform, PTRVatTu root, int page){
	mangVatTu arr; ListToArray(root, arr);
	char c;
	int line = 1;
	//Lay toa do o thu nhat
	int x = xform + 12, y = yform + 2;
	while (true){
		//debug
//		gotoxy(135, 43); cout<<"x:"<<x;  gotoxy(141, 43); cout<<"y:"<<y; gotoxy(146, 43); cout<<"n:"<<sizeVatTu;
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
					x = xform + 12; y-=3;
					line--;
					continue;
				}
				case KEY_DOWN:{
					if(line==5) continue;
					x = xform + 12; y+=3;
					line++;
					continue;
				}
				case KEY_LEFT:{
					if(x == xform + 12) continue;
					x--;
					continue;
				}
				case KEY_RIGHT:{
					if(x == xform + 12 + MAX_TENVT) continue;
					x++;
					continue;
				}
				case PAGE_DOWN:{
					int n;
					if(sizeVatTu%MAXTABLEROW==0) n=sizeVatTu/MAXTABLEROW;
					else n=sizeVatTu/MAXTABLEROW+1;
					if (page+1>n) continue;
					page++;
					VatTuTable(XTABLE, YTABLE, arr, page);
					continue;
				}
				case PAGE_UP:{
					if(page==1) continue;
					page--;
					VatTuTable(XTABLE, YTABLE, arr, page);
					continue;
				}
			}
		}else
			switch (c){
				case BACKSPACE:{
					if(x <= xform + 12) continue;
					x--;
					gotoxy(x,y); cout<<" ";
					continue;
				}
				case ESC: {
					VatTuForm(xform-2, yform);
					return 0;
				}
				case ENTER: {
					if (line==5) {
						string str="";
						VatTu vt;
						int xx=xform+12, yy=yform+2, i;
						for (i=0; i<MAX_TENVT&&readChar(xx+i,yy)!=SPACE; i++) str += readChar(xx+i,yy);
						trim(str);
						if (str.length()>MAX_MAVT){
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
							"MA VAT TU KHONG QUA 10 KI TU!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
						strcpy(vt.maVT, str.c_str());
						if (isExistVatTu(root, vt.maVT)) {
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
							"TRUNG MA VAT TU!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
						str="";
						for (i=0; i<MAX_TENVT; i++) str += readChar(xx+i,yy+3);
						trim(str);
						strcpy(vt.tenVT, str.c_str());
						str="";
						for (i=0; i<MAX_TENVT; i++) str += readChar(xx+i,yy+6);
						trim(str);
						if (str.length()>MAX_DVT){
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
							"DON VI TINH KHONG QUA 10 KI TU!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
						strcpy(vt.dvt, str.c_str());
						str="";
						for (i=0; i<MAX_TENVT&&readChar(xx+i,yy+9)!=SPACE; i++) str += readChar(xx+i,yy+9);
						chuan_hoa_so(str);
						vt.soLuongTon = atoi(str.c_str());
						if (vt.soLuongTon==0){
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
							"SO LUONG TON KHONG DUOC DE TRONG!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
						if (InsertVatTu(root, vt)) {
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "THANH CONG",
							"VAT TU DA DUOC THEM!", VTFORMLENGTH-2, BLUE, LIGHT_GREEN);
							VatTuForm(XTABLE+VTTABLELENGTH+2, YTABLE2);
							return 1;
						}else{
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "THAT BAI",
							"VAT TU CHUA DUOC THEM, HAY KIEM TRA LAI!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
					}
					continue;
				}
				default:{
					switch (line){
						case 1:{
							if(!isBlackchar(c)&&c!=SPACE&&x<xform + 12 + MAX_TENVT){
								cout<<char(toupper(c)); x++;
							} else if (isBlackchar(c)){
								thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
								"KI TU VUA NHAP KHONG DUOC CHO PHEP!", VTFORMLENGTH-2, YELLOW, RED);
								VatTuTable(XTABLE, YTABLE, arr, page);
							} else if (c==SPACE) {
								thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
								"MAVATTU KHONG NHAP KHOANG TRANG!", VTFORMLENGTH-2, YELLOW, RED);
								VatTuTable(XTABLE, YTABLE, arr, page);
							}
							continue;
						}
						case 2:
						case 3:{
							if(!isBlackchar(c)&&x<xform + 12 + MAX_TENVT) {
								cout<<char(toupper(c)); x++;	
							} else {
								thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
								"KI TU VUA NHAP KHONG DUOC CHO PHEP!", VTFORMLENGTH-2, YELLOW, RED);
								VatTuTable(XTABLE, YTABLE, arr, page);
							}
							continue;
						}
						case 4:{
							if (isNumber(c)&&x<xform + 12 + MAX_TENVT) {
								cout<<c; x++;
							} else {
								thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
								"CHI NHAP SO NGUYEN KHONG DAU", VTFORMLENGTH-2, YELLOW, RED);
								VatTuTable(XTABLE, YTABLE, arr, page);
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
string getMaVTTable(int x, int y, int line){
	string str="";
	char c;
	for (int i=0; i<MAX_MAVT&&readChar(x+1+i,y+line)!=SPACE; i++)
		str+=readChar(x+1+i,y+line);
	return str;
};
int editVatTuForm(int xform, int yform, PTRVatTu root, int page, int xtable, int ytable, int tline){
	mangVatTu arr; ListToArray(root, arr);
	string str = getMaVTTable(xtable, ytable, tline);
	gotoxy(135, 44); cout<<"mavt:"<<str;
	char mavt[MAX_MAVT]; strcpy(mavt, str.c_str());
	PTRVatTu temp = Search(root, mavt);
	char c;
	int line = 2;
	int x = xform+12, y = yform+2;
	gotoxy(x,y); cout<<temp->vatTu.maVT;
	gotoxy(x,y+3); cout<<temp->vatTu.tenVT;
	gotoxy(x, y+6); cout<<temp->vatTu.dvt;
	gotoxy(x, y+9); cout<<temp->vatTu.soLuongTon;
	y+=3;
	while (true){
		//debug
//		gotoxy(135, 43); cout<<"x:"<<x;  gotoxy(141, 43); cout<<"y:"<<y; gotoxy(146, 43); cout<<"n:"<<sizeVatTu;
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
					if(line==2) {
						thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
						"KHONG DUOC SU MA VAT TU", VTFORMLENGTH-2, YELLOW, RED);
						VatTuTable(XTABLE, YTABLE, arr, page);
						continue;
					}
					x = xform + 12; y-=3;
					line--;
					continue;
				}
				case KEY_DOWN:{
					if(line==5) continue;
					x = xform + 12; y+=3;
					line++;
					continue;
				}
				case KEY_LEFT:{
					if(x == xform + 12) continue;
					x--;
					continue;
				}
				case KEY_RIGHT:{
					if(x == xform + 12 + MAX_TENVT) continue;
					x++;
					continue;
				}
				case PAGE_DOWN:{
					int n;
					if(sizeVatTu%MAXTABLEROW==0) n=sizeVatTu/MAXTABLEROW;
					else n=sizeVatTu/MAXTABLEROW+1;
					if (page+1>n) continue;
					page++;
					VatTuTable(XTABLE, YTABLE, arr, page);
					continue;
				}
				case PAGE_UP:{
					if(page==1) continue;
					page--;
					VatTuTable(XTABLE, YTABLE, arr, page);
					continue;
				}
			}
		}else
			switch (c){
				case BACKSPACE:{
					if(x == x + 12) continue;
					x--;
					gotoxy(x,y); cout<<" ";
					continue;
				}
				case ESC: {
					VatTuForm(xform-2, yform);
					return 0;
				}
				case ENTER: {
					if (line==5) {
						string str="";
						VatTu vt;
						int xx=xform+12, yy=yform+2, i;
						for (i=0; i<MAX_TENVT&&readChar(xx+i,yy)!=SPACE; i++) str += readChar(xx+i,yy);
						trim(str);
						strcpy(vt.maVT, str.c_str());
						str="";
						for (i=0; i<MAX_TENVT; i++) str += readChar(xx+i,yy+3);
						trim(str);
						strcpy(vt.tenVT, str.c_str());
						str="";
						for (i=0; i<MAX_TENVT; i++) str += readChar(xx+i,yy+6);
						trim(str);
						if (str.length()>MAX_DVT){
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
							"DON VI TINH KHONG QUA 10 KI TU!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
						strcpy(vt.dvt, str.c_str());
						str="";
						for (i=0; i<MAX_TENVT&&readChar(xx+i,yy+9)!=SPACE; i++) str += readChar(xx+i,yy+9);
						chuan_hoa_so(str);
						vt.soLuongTon = atoi(str.c_str());
						if (SuaVatTu(root, vt)) {
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "THANH CONG",
							"VAT TU DA DUOC SUA!", VTFORMLENGTH-2, BLUE, LIGHT_GREEN);
							VatTuForm(XTABLE+VTTABLELENGTH+2, YTABLE2);
							return 1;
						}else{
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "THAT BAI",
							"VAT TU CHUA DUOC SUA, HAY KIEM TRA LAI!", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
					}
					continue;
				}
				default:{
					switch (line){
						case 2:
						case 3:{
							if(!isBlackchar(c)) {
								cout<<char(toupper(c)); x++;	
							} else {
								thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
								"KI TU VUA NHAP KHONG DUOC CHO PHEP!", VTFORMLENGTH-2, YELLOW, RED);
								VatTuTable(XTABLE, YTABLE, arr, page);
							}
							continue;
						}
						case 4:{
							thongbao(XTABLE + VTTABLELENGTH + 2, MAXROW-6, "CANH BAO",
							"KHONG DUOC CHINH SUA O NAY", VTFORMLENGTH-2, YELLOW, RED);
							VatTuTable(XTABLE, YTABLE, arr, page);
							continue;
						}
						case 5: continue;
					}
					continue;
				}
			}
	}
};
