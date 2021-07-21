#pragma once
#include "VattuView.h"
#include "NhanVienView.h"
#define HDTABLELENGTH 95
#define HDFORMLENGTH 40
#define CTTABLELENGTH 36
#define CTFORMLENGTH 42
using namespace std;
string hdTittle = "  QUAN LI HOA DON  ";
string hdHeader[] = {" SOHD ", " MANV ", " HOTEN "," NGAYLAP ", " LOAI "};
string ctHeader[] = {" MAVATTU ", "   SL ", " DONGIA ", " %VAT "};
string hdNhapHD[] = {"1. SOHD khong qua 20 ki tu in",
					 "   va khong chua ki tu dac biet",	
					 "   VD: HD1, HD32, HD10...",	
					"2. MANV chi nhap so nguyen khong dau",
					"3. Nhap dung dinh dang NGAYTHANG",
					"4. LOAI chi nhap 'NHAP'(N) hoac", 
					"   'XUAT'(X)",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapHDn = 9;
string hdNhapCT[] = {"1. ENTER de chon Vat tu muon them",		
					"2. SOLUONG chi nhap so nguyen khong dau",
					"3. DONGIA chi nhap so nguyen khong dau",
					"4. VAT chi nhap thap phan khong dau",
					"va 1 so phan thap phan",
					"5. ESC de quay lai",
					"6. ENTER tai dong thu 5 de hoan thanh"};
int hdNhapCTn = 7;
//=====Ten Ham=====//
int countHoaDon(ListNhanVien list);
Date getInputDate(int x, int y);
void nhapNgay();
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
void addHoaDonForm(int defaultx, int defaulty, ListNhanVien &list, int soHD, int page);
//=====CT_HD=====//
void CT_HDTable(int x, int y, ListCT_HD list);
int addCT_HDMenu(Info &info);
void addCT_HDView(const Info &info, PTRVatTu head, int page);
void CT_HDForm(int x, int y);
//====Noi dung=====//
void nhapNgay(){
	char key;
	int x = wherex();
	int temp = x;
	int y = wherey();
    int bound = 0;
    do{
            key = getch();
            switch (key){
				case KEY_RIGHT:
				{
					if(x == (9+temp))
						continue;
					gotoxy(x+1,y);
					x++;
					continue;
				}
				case KEY_LEFT:
				{
					if(x == temp)
						continue;
					gotoxy(x-1,y);
					x--;
					continue;
				}
				case ENTER:
				{
					return;
				}
			} 
            if(key >= 48 && key <= 57){
                if(x != (2+temp) && x != (5+temp)){
                	if(x == (9+temp)){
                		cout << key;
                		gotoxy(x,y);
						continue;
					}
                	cout << key;
					x++;
					continue;
				}
            }
	}while(1);
};
Date getInputDate(int x, int y){
	string input = "";
	for (int i = 1; i <= 10; i++) 
		input += readChar(x+i,y);
	return convertStringToDate(input);
};
int countHoaDon(ListNhanVien list){
  int count = 0;
  for (int i=0; i<list.n; i++)
    count+=list.nhanViens[i]->hoaDons->n;
  return count;
};
int HoaDonMenu(){
	ListNhanVien list;
	HoaDon hd;
	string strSearch;
	if(!readFileNV(list, DEFAULT_NVFILE)) cout<<"Loi doc file!";
	char c, cSearch[21];
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
				int soHD = countHoaDon(list);
				addHoaDonForm(XTABLE + HDFORMLENGTH + 55, YTABLE2, list, soHD, page);
				continue;
			}
			case CTRL_F:{
				strSearch = searchBox(XTABLE + HDTABLELENGTH + 3 + HDFORMLENGTH + 3,  YTABLE+6, HDFORMLENGTH-3, "NHAP SODH");
				strcpy(cSearch, strSearch.c_str());
				hd = getHD(list,cSearch);
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
	CreateBox(XTABLE, 1, "", HDFORMLENGTH+HDTABLELENGTH+2);
	gotoxy((HDFORMLENGTH+HDTABLELENGTH+2 - hdTittle.length())/2,1); cout<<hdTittle;
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
};
void HoaDonTable(int x, int y, const ListNhanVien &list, int page){
	if(x<0||y<4) return;
	//xoa vung ve bang
	for (int i=0; i<=MAXTABLEROW+3; i++){
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
    for (int i=0; i<3; i++){
		gotoxy(x+HDTABLELENGTH+HDFORMLENGTH/2-5, y+MAXTABLEROW+3+i);
		cout<<" "<<setw(13)<<setfill(' ')<<" "; 
	}
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
void addHoaDonForm(int defaultx, int defaulty, ListNhanVien &list, int soHD, int page){
	char c;
	int xx=defaultx+17, yy=defaulty+5;
	int n,pageNV=1;
	if(list.n%MAXTABLEROW==0) n=list.n/MAXTABLEROW;
	else n=list.n/MAXTABLEROW+1;
	int line = 2;
	int tongPage = countHoaDon(list);
	if(tongPage%MAXTABLEROW==0) tongPage=list.n/MAXTABLEROW;
	else tongPage=tongPage/MAXTABLEROW+1;
	Date d1 = getDateNow(); //lay ngay hien tai
	string strDate = convertDateToString(d1);
	//Lay tao do o thu nhat
	int x = defaultx + 17, y = defaulty + 2;
	gotoxy(x, y);
	cout << "HD" << soHD+1;
	gotoxy(x,y+6);
	cout << strDate;
	y = y+3;
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
					if(line==2) continue;
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
					if(line == 4){
						cout << "<<Phieu xuat 'X'>>";
						continue;
					}
					if(x == defaultx + 17) continue;
//					x--;
					continue;
				}
				case KEY_RIGHT:{
					if(line == 4){
						cout << "<<Phieu nhap 'N'>>";
						continue;
					}
//					x++;
					continue;
				}
//				case PAGE_DOWN:{
//					if (page+1>tongPage) continue;
//					page++;
//					HoaDonTable(XTABLE + 16, YTABLE, list, page);
//					line = 0;
//					highlight(x, y, HDTABLELENGTH, YELLOW);
//					continue;
//				}
//				case PAGE_UP:{
//					if(page==1) continue;
//					page--;
//					HoaDonTable(XTABLE + 16, YTABLE, list, page);
//					line = 0;
//					highlight(x, y, HDTABLELENGTH, YELLOW);
//					continue;
//				}
			}
		}else
			switch (c){
				case CTRL_F:{
					//xoa vung ve bang
					for (int i=0; i<=MAXTABLEROW+3; i++){
						gotoxy(XTABLE, YTABLE-1+i);
						cout<<" "<<setw(HDTABLELENGTH)<<setfill(' ')<<" ";
					}
//					xoa khung trang
					for (int i=0; i<3; i++){
				        gotoxy(xx-3, yy+11+i);
				        cout<<" "<<setw(13)<<setfill(' ')<<" "; 
				    }
					NhanVienTable(XTABLE+16, YTABLE, list, pageNV);
					do{
						c = _getch();
						switch(c){
							case PAGE_DOWN:{								
								if (pageNV+1>n) continue;
								pageNV++;
								NhanVienTable(XTABLE + 16, YTABLE, list, pageNV);
								continue;
							}
							case PAGE_UP:{
								if(pageNV==1) continue;
								pageNV--;
								NhanVienTable(XTABLE + 16, YTABLE, list, pageNV);
								continue;
							}
						}	
					}while(c != TAB);
//					xoa khung trang
					for (int i=0; i<3; i++){
				        gotoxy(xx-12, yy+11+i);
				        cout<<" "<<setw(13)<<setfill(' ')<<" "; 
				    }
					HoaDonTable(XTABLE, YTABLE, list, page);
					continue;
				}
				case ESC:{
					HoaDonForm(defaultx+2,defaulty);
					return;
				}
				case ENTER: {
					if (line==5) {
						string str = "";
						string p = "TRANG: ";
						p += to_string(page)+ "/" + to_string(tongPage);
						Date date;
						int maNV, i;
						for (i=0; i<32 && readChar(xx+i,yy) != SPACE; i++) 
							str += readChar(xx+i,yy);
						maNV = atoi(str.c_str());
						if(str == "") {
							thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
							"KHONG DUOC DE TRONG MA NHAN VIEN!", HDFORMLENGTH-2, BLUE, RED);
							CreateBox(xx-3, yy+12, p, 11);
							gotoxy(xx,yy+3);
							continue;
						}
						if (indexOf(list, 0, list.n-1,maNV) == -1) {
							thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
							"KHONG TON TAI MA NHAN VIEN NAY!", HDFORMLENGTH-2, BLUE, RED);
							CreateBox(xx-3, yy+12, p, 11);
							gotoxy(xx,yy+3);
							continue;
						}
						date = getInputDate(xx-1,yy+3);
						switch(ktDate(date)){
							case 0: // case 0 la ngay thang hop le
							{
//								thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
//								"HOP LE!", HDFORMLENGTH-2, YELLOW, LIGHT_RED);
//								CreateBox(xx-3, yy+12, p, 11);
//								gotoxy(xx,yy+3);
								break;
							}
							case 1:
							{
								thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"NAM KHONG HOP LE!", HDFORMLENGTH-2, BLUE, RED);
								CreateBox(xx-3, yy+12, p, 11);
								gotoxy(xx,yy+3);
								break;
							}
							case 2:
							{
								thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"THANG KHONG HOP LE!", HDFORMLENGTH-2, BLUE, RED);
								CreateBox(xx-3, yy+12, p, 11);
								gotoxy(xx,yy+3);
								break;
							}
							case 3:
							{
								thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"NGAY KHONG HOP LE!", HDFORMLENGTH-2, BLUE, RED);
								CreateBox(xx-3, yy+12, p, 11);
								gotoxy(xx,yy+3);
								break;
							}
							case 4:
							{
								thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
								"NGAY NHAP NHO HON HIEN TAI!", HDFORMLENGTH-2, BLUE, RED);
								CreateBox(xx-3, yy+12, p, 11);
								gotoxy(xx,yy+3);
							}
						}
						char loai = readChar(xx,yy+6);
						if(loai == SPACE){
							thongbao(XTABLE + HDTABLELENGTH + 15, MAXROW-5, "CANH BAO",
							"KHONG DUOC DE TRONG LOAI!", HDFORMLENGTH-2, BLUE, RED);
							CreateBox(xx-3, yy+12, p, 11);
							continue;
						}
					}
					continue;
				}
				case TAB:{
					char key;					
					switch (line){
						case 2:{
							while(1){
								key=_getch();
								if(key == ENTER) break;
								if(key == BACKSPACE) {
									if(x == (defaultx + 17)) continue;
									x--;
									gotoxy(x,y);
									cout<<" ";
									gotoxy(x,y);
									continue;
								}
								if(x == (defaultx+20)) continue;
								if(key >= 48 && key <= 57){
					                	cout << key;
					                	if(x == (defaultx+20)) continue;
										x++;
								}
							}
							break;
						}
						case 3:{
							nhapNgay();
							break;
						}
						case 5: continue;
					}
					continue;
				}
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
	PTRVatTu head = NULL;
	ReadFile(head);
	char c;
	string str;
	int line = 0, page = 1;
	int y = YTABLE + 2, x = 1+1;
	addCT_HDView(info, head, page);
	highlight(x, y, VTTABLELENGTH, YELLOW);
	while (true){
		SetBGColor(BLACK);
		gotoxy(155,41); cout<<"size: "<<sizeVatTu;
		gotoxy(155,42); cout<<"line: "<<line;
		gotoxy(155,43); cout<<"page: "<<page;
		c=_getch();
		switch(c){
			case ENTER: return line;
			case ESC: return -1;
		}
	}
	return 1;
};
void addCT_HDView(const Info &info, PTRVatTu head, int page){
	clrscr();
	resizeConsole(WIDTH, HEIGHT);
	gotoxy(XTABLE, 0); cout<<char(186)<<"SOHD   :"<<info.soHD;
	gotoxy(XTABLE, 1); cout<<char(186)<<"NGAYLAP:"<<convertDateToString(info.ngayLap);
	gotoxy(XTABLE, 2); cout<<char(186)<<"LOAI   :"<<info.loai;
	//ve bang + showlist
	string tenbang = "||  DANH SACH VAT TU  ||";
	gotoxy(XTABLE + (VTTABLELENGTH + 2 - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t1 (VatTuTable, XTABLE, YTABLE, head, page);
	t1.join();
	tenbang = "|| BANG HUONG DAN ||";
	gotoxy(XTABLE + VTTABLELENGTH + (CTFORMLENGTH + 2 - tenbang.length())/2, YTABLE-2); cout<<tenbang;
	thread t2(HuongDanNhap, XTABLE+VTTABLELENGTH+2, YTABLE, hdNhapCT, hdNhapCTn, MAXTABLEROW/2, CTFORMLENGTH);
	t2.join();
	thread t3 (CT_HDForm, XTABLE+VTTABLELENGTH+2, YTABLE2);
	t3.join();
	tenbang = "|| DANH SACH CHI TIET TUONG UNG ||";
	gotoxy(XTABLE + VTTABLELENGTH + 2 + CTFORMLENGTH + 2 + (CTTABLELENGTH + 2 - tenbang.length())/2, YTABLE-2); 
	cout<<tenbang;
	CT_HDTable(XTABLE+VTTABLELENGTH+2+CTFORMLENGTH+2, YTABLE, *info.	listct);
};
void CT_HDForm(int x, int y){
	if(x<0||y<1) return ;
	//xoa vung
	int i;
	for (i=0; i<MAXTABLEROW/2+2; i++){
		gotoxy(x, y-1+i);
		cout<<" "<<setw(CTFORMLENGTH+3)<<setfill(' ')<<" ";
	}
	//vien tren
	gotoxy(x,y-1);
	cout << char(201) << setw(CTFORMLENGTH+1) << setfill(char(205)) << char(187);
	//khoang trong	
	for(i=0; i<MAXTABLEROW/2; i++){
		gotoxy(x, y+i);
		cout << char(186) << " " << setw(CTFORMLENGTH) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+i);
	cout << char(200) << setw(CTFORMLENGTH+1) << setfill(char(205)) << char(188);
	string title = "--THEM CHI TIET HOA DON--";
	gotoxy(x + (CTFORMLENGTH-title.length()+1)/2, y);
	cout<<title;
	gotoxy(x+3, y+2); cout<<"MAVATTU:";
	gotoxy(x+3, y+5); cout<<"DONGIA:";
	gotoxy(x+3, y+8); cout<<"SOLUONG:";
	gotoxy(x+3, y+11); cout<<"%VAT:";
	for (int i=0; i<4; i++) CreateBox(x+13, y+2+i*3, " ", 27);
	gotoxy(x+3, y+14); cout<<"HOAN THANH:";
};
