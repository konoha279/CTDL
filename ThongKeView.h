#pragma once
#include "Graphic.h"
#define XDATE1 5
#define XDATE2 80
#define YDATE 5
#define TKTABLELENGTH 100
#define TKFORMLENGTH 60
#define DATELENGTH 15
#define MAX_STT 5
using namespace std;
string tkHeader1[] = {" SODH ", " NGAY LAP ", " LOAI ", " HO TEN NV LAP ", " TRI GIA "};
string tkHeader2[] = {" STT ", " MA VAT TU ", " TEN VAT TU ", " DOANH THU "};
//=====Ten Ham=====//
int ThongKeMenu();
void ThongKeView();
void ThongKe1Table(int x, int y, const Listdata1 &list, const Date &date1, const Date &date2, int page);
void ThongKe2Table(int x, int y, const Listdata2 &list);
int NhapNgay(Date &date1, Date &date2);
//=====Noi dung=====//
int ThongKeMenu(){
	Listdata1 list1; 
	Listdata2 list2;
	Date date1;
	Date date2;
	ThongKeView();
	char c;
	int chedo = 0, page=1;
	if (!NhapNgay(date1, date2)) return 0;
	xuli(list1, list2, date1, date2);
	ThongKe1Table(XTABLE, YDATE+4, list1, date1, date2, page);
	while (true){
		gotoxy(MAXLINE-10, MAXROW-6); cout<<"list1.n="<<list1.n<<" list2.n="<<list2.n;
		Cursor(false, 100);
		c=_getch();
		switch (c){
			case KEY_LEFT:{
				if (chedo==1) {
					chedo=0;
					ThongKe1Table(XTABLE, YDATE+4, list1, date1, date2, page);
				}
				continue;
			}
			case KEY_RIGHT:{
				if (chedo==0) chedo=1;
				if(list2.sort==0){
					quicksort(list2, 0, list2.n-1, 1);
					list2.sort=1;
				}
				ThongKe2Table(XTABLE, YDATE+4, list2);
				continue;
			}
			case PAGE_UP:{
				if(chedo!=0||page==1) continue;
				page--;
				ThongKe1Table(XTABLE, YDATE+4, list1, date1, date2, page);
				continue;
			}
			case PAGE_DOWN:{
				if(chedo==0){
					int n;
					if(list1.n%MAXTABLEROW==0) n=list1.n/MAXTABLEROW;
					else n=list1.n/MAXTABLEROW + 1;
					if(page==n) continue;
					page++;
					ThongKe1Table(XTABLE, YDATE+4, list1, date1, date2, page);
				}
				continue;
			}
			case CTRL_F:{
				if (!NhapNgay(date1, date2)) continue;
				xuli(list1, list2, date1, date2);
				chedo=0; page=1;
				ThongKe1Table(XTABLE, YDATE+4, list1, date1, date2, page);
				continue;
			}
			case ESC: return 0;
			case ENTER: return 1;
		}
	}
	return 1;
};
void ThongKeView(){
	clrscr();
	resizeConsole(WIDTH, HEIGHT);
	string title = "TRANG THONG KE";
	CreateBox(XTABLE, 1, "", TKTABLELENGTH + TKFORMLENGTH);
	gotoxy(XTABLE + (TKTABLELENGTH + TKFORMLENGTH - title.length())/2, 1); cout<<title;
	gotoxy(XDATE1, YDATE-2); cout<<"TU NGAY:";
	gotoxy(XDATE2, YDATE-2); cout<<"DEN NGAY:";
	CreateBox(XDATE1, YTABLE, "", DATELENGTH);
	CreateBox(XDATE2, YTABLE, "", DATELENGTH);
	string button[] = {"ESC", " < ", " > ", "PAGE", "CTRL+F", "ENTER"};
	string command[] = {"QUAY LAI", "HOA DON", "VAT TU", "TRANG", "NHAP LAI", "HOAN THANH"};
	int n=6, i;
	for (i=0; i<n; i++){
		CreateBox(XTABLE+TKTABLELENGTH+3+i*10, MAXTABLEROW/2+11, button[i], button[i].length());
		gotoxy(XTABLE+TKTABLELENGTH+3+i*10, MAXTABLEROW/2+13); cout<<command[i];
	}
	string hdNhapNgay[] = {"1. KEY_LEFT/RIGHT de di chuyen,",
						"2. Chi nhap so va ki tu '/'",
						"3. Khong nhap truoc ngay 1/1/2021",
						"4. Khong nhap qua sau hien tai",
						"5. ESC de quay lai",
						"6. ENTER de hoan thanh"};
	n=6;
	HuongDanNhap(XTABLE+TKTABLELENGTH+3, YDATE+4, hdNhapNgay, n, MAXTABLEROW/2, TKFORMLENGTH);
};
int NhapNgay(Date &date1, Date &date2){
	int x = XDATE1 + 1, y = YDATE;
	char c;
	while (true){
		gotoxy(x, y);
		Cursor(true, 100);
		c=_getch();
		if (c==-32){
			c=_getch();
			switch (c){
				case KEY_LEFT:{
					if(x==XDATE1+1) continue;
					if(x==XDATE2+1){
						x=XDATE1+1;
						continue;
					}
					x--;
					break;
				}
				case KEY_RIGHT:{
					if(x==XDATE2+1+10) continue;
					if(x==XDATE1+1+10){
						x=XDATE2+1;
						continue;
					}
					x++;
					continue;
				}
			}
		}else switch (c){
				case BACKSPACE:{
					if(x==XDATE1+1||x==XDATE2+1) continue;
					x--;
					gotoxy(x,y); cout<<" ";
					continue;
				}
				case ESC: return 0;
				case ENTER: {
					string str1="", str2="";
					for (int i=0; i<10; i++){
						str1+=readChar(XDATE1+1+i, YDATE);
						str2+=readChar(XDATE2+1+i, YDATE);
					}
					trim(str1); trim(str2);
					vector<string> v1 = split(str1, "/");
					vector<string> v2 = split(str2, "/");
					Date datetemp1=convertStringToDate(str1);
					Date datetemp2=convertStringToDate(str2);
					if(v1.size()!=3||v2.size()!=3||ktDate(datetemp1)!=0||ktDate(datetemp2)!=0){
						thongbao(TKTABLELENGTH+3, MAXROW-6, "CANH BAO", 
						"NGAY BAN NHAP KHONG HOP LE!", TKFORMLENGTH, YELLOW, RED);
						continue;
					}
					Date now = getDateNow();
					if(cmpDate(datetemp1, now)>0||cmpDate(datetemp2,now)>0){
						thongbao(TKTABLELENGTH+3, MAXROW-6, "CANH BAO", 
						"KHONG NHAP QUA NGAY HIEN TAI!", TKFORMLENGTH, YELLOW, RED);
						continue;
					}
					if(cmpDate(datetemp1, datetemp2)>0){
						thongbao(TKTABLELENGTH+3, MAXROW-6, "CANH BAO", 
						"NGAY BAT DAU PHAI TRUOC NGAY KET THUC!", TKFORMLENGTH, YELLOW, RED);
						continue;
					}
					date1 = datetemp1;
					date2 = datetemp2;
					return 1;
				}
				default:{
					if(!isNumber(c)&&c!='/') {
						thongbao(TKTABLELENGTH+3, MAXROW-6, "CANH BAO", 
						"CHI NHAP SO VA DAU '/'!", TKFORMLENGTH, YELLOW, RED);
						continue;
					}
					if(x==XDATE1+1+10||x==XDATE2+1+10) continue;
					cout<<c;
					x++;
					continue;
				}
			}
	}
	return 0;
};
void ThongKe1Table(int x, int y, const Listdata1 &list, const Date &date1, const Date &date2, int page){
	for (int i=-1; i<=MAXTABLEROW+1; i++){
		gotoxy(x, y-1+i); cout<<" "<<setw(TKTABLELENGTH+2)<<setfill(' ')<<" ";
	}
	string title = "|| THONG KE HOA DON TU " + convertDateToString(date1)
			+ " DEN " + convertDateToString(date2) + " ||";
	gotoxy(XTABLE+(TKTABLELENGTH-title.length())/2,y-2); cout<<title;
	//vien tren
	gotoxy(x, y-1);
	cout << char(201) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_TRIGIA) << setfill(char(205)) << char(187);
	//header
	gotoxy(x,y);
	cout << char(186) << setw(8 + MAX_SOHD - tkHeader1[0].length()) << setfill(' ') << tkHeader1[0] << char(186);
	cout << tkHeader1[1] << setw(3 + MAX_NGAYLAP - tkHeader1[1].length()) << setfill(' ') << char(186);
	cout << tkHeader1[2] << setw(3 + MAX_LOAI - tkHeader1[2].length()) << setfill(' ') << char(186);
	cout << tkHeader1[3] << setw(3 + MAX_HO + 1 + MAX_TEN - tkHeader1[3].length()) << setfill(' ') << char(186);
	cout << tkHeader1[4] << setw(3 + MAX_TRIGIA - tkHeader1[4].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x,y+1);
	cout << char(204) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TRIGIA) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<MAXTABLEROW; i++){
		gotoxy(x, y+2+i);
		cout << char(186) << setw(3 + MAX_SOHD) << setfill(' ') << char(186);
		cout << setw(3 + MAX_NGAYLAP) << setfill(' ') << char(186);
		cout << setw(3 + MAX_LOAI) << setfill(' ') << char(186);
		cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(' ') << char(186);
		cout << setw(3 + MAX_TRIGIA) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x, y+MAXTABLEROW+2);
	cout << char(200) << setw(3 + MAX_SOHD) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_NGAYLAP) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_LOAI) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_HO + 1 + MAX_TEN) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_TRIGIA) << setfill(char(205)) << char(188);
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
		gotoxy(x+TKTABLELENGTH+3, y+MAXTABLEROW+i);
		cout<<" "<<setw(13)<<setfill(' ')<<" "; 
	}
	CreateBox(x+TKTABLELENGTH+2, y+MAXTABLEROW+1, p, 11);
	if (list.n==0) {
		thongbao(TKTABLELENGTH+3, MAXROW-6, "THONG BAO", 
		"TRONG KHOANG THOI GIAN TREN KHONG CO HOA DON NAO DUOC LAP", TKFORMLENGTH, BLUE, LIGHT_YELLOW);
		return;
	}
	for (int i=0; i<n&&i+index<list.n; i++){
		gotoxy(x+2, y+2+i); cout<<list.data1s[i+index]->info.soHD;
		gotoxy(x+2+MAX_SOHD+3, y+2+i); cout<<convertDateToString(list.data1s[i+index]->info.ngayLap);
		gotoxy(x+2+MAX_SOHD+3+MAX_NGAYLAP+3, y+2+i);
		if (list.data1s[i+index]->info.loai=='X') cout<<"XUAT";
		else cout<<"NHAP";
		gotoxy(x+2+MAX_SOHD+3+MAX_NGAYLAP+3+MAX_LOAI+3, y+2+i); cout<<list.data1s[i+index]->hoten;
		gotoxy(x+2+MAX_SOHD+3+MAX_NGAYLAP+3+MAX_LOAI+3+MAX_HO+1+MAX_TEN+3, y+2+i);
		cout<<toString(list.data1s[i+index]->trigia, MAX_TRIGIA);
	}
};
void ThongKe2Table(int x, int y, const Listdata2 &list){
	for (int i=-1; i<=MAXTABLEROW+3; i++){
		gotoxy(x, y-1+i); cout<<" "<<setw(TKTABLELENGTH+2)<<setfill(' ')<<" ";
	}
	for (int i=0; i<3; i++){
		gotoxy(x+TKTABLELENGTH+3, y+MAXTABLEROW+i);
		cout<<" "<<setw(13)<<setfill(' ')<<" "; 
	}
	string title = "|| TOP 10 VAT TU CO DOANH THU CAO NHAT ||";
	gotoxy(XTABLE+(TKTABLELENGTH-title.length())/2,y-2); cout<<title;
	//vien tren
	gotoxy(x+5, y-1);
	cout << char(201) << setw(3 + MAX_STT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_MAVT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_TENVT) << setfill(char(205)) << char(203);
	cout << setw(3 + MAX_DOANHTHU) << setfill(char(205)) << char(187);
	//header
	gotoxy(x+5,y);
	cout << char(186) << setw(7 + MAX_STT - tkHeader2[0].length()) << setfill(' ') << tkHeader2[0] << char(186);
	cout << tkHeader2[1] << setw(3 + MAX_MAVT - tkHeader2[1].length()) << setfill(' ') << char(186);
	cout << tkHeader2[2] << setw(3 + MAX_TENVT - tkHeader2[2].length()) << setfill(' ') << char(186);
	cout << tkHeader2[3] << setw(3 + MAX_DOANHTHU - tkHeader2[3].length()) << setfill(' ') << char(186);
	//vien duoi header
	gotoxy(x+5,y+1);
	cout << char(204) << setw(3 + MAX_STT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_MAVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TENVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_DOANHTHU) << setfill(char(205)) << char(185);
	//body
	for (int i=0; i<MAXTABLEROW; i++){
		gotoxy(x+5, y+2+i);
		cout << char(186) << setw(3 + MAX_STT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_MAVT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_TENVT) << setfill(' ') << char(186);
		cout << setw(3 + MAX_DOANHTHU) << setfill(' ') << char(186);
	}
	//vien duoi
	gotoxy(x+5, y+MAXTABLEROW+2);
	cout << char(200) << setw(3 + MAX_STT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_MAVT) << setfill(char(205)) << char(202);
	cout << setw(3 + MAX_TENVT) << setfill(char(205)) << char(202);	
	cout << setw(3 + MAX_DOANHTHU) << setfill(char(205)) << char(188);
	if (list.n==0) {
		thongbao(TKTABLELENGTH+3, MAXROW-6, "THONG BAO", 
		"TRONG KHOANG THOI GIAN TREN KHONG CO HOA DON XUAT", TKFORMLENGTH, BLUE, LIGHT_YELLOW);
		return;
	}
	for (int i=0; i<20&&i<list.n; i++){
		gotoxy(x+5+2, y+2+i); cout<<toString(i+1, MAX_STT);
		gotoxy(x+5+2+MAX_STT+3, y+2+i); cout<<list.data2s[list.n-i-1]->vt.maVT;
		gotoxy(x+5+2+MAX_STT+3+MAX_MAVT+3, y+2+i); cout<<list.data2s[list.n-i-1]->vt.tenVT;
		gotoxy(x+5+2+MAX_STT+3+MAX_MAVT+3+MAX_TENVT+3, y+2+i); cout<<toString(list.data2s[list.n-i-1]->doanhthu, MAX_DOANHTHU);
	}
	
}
