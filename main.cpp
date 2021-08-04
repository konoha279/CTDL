#pragma once
#include "HoaDonView.h"
#include "ThongKeView.h"
#include <ctime>
#include <cstdlib>
#include <thread>
using namespace std;
void init(ListNhanVien &list, PTRVatTu &head);
int Random(int min, int max);
int Random(int min, int max){ 
    if(min >= max)
        return 0;
    int d = max - min;
    return (rand() % (d+1) + min);
};
void init(ListNhanVien &list, PTRVatTu &head){
	string str = "LOI DOC FILE ";
	if (!readFileNV(list, DEFAULT_NVFILE)) {
		str+="NHAN VIEN";
		thongbao((MAXLINE-str.length())/2, MAXROW/2-1, "CANH BAO", str, str.length(), YELLOW, RED);
	}
	if(!ReadFile(head)){
		str+="VAT TU";
		thongbao((MAXLINE-str.length())/2, MAXROW/2-1, "CANH BAO", str, str.length(), YELLOW, RED);
	}
};
int main(){
	ListNhanVien list;
	PTRVatTu head = NULL;
	Cursor(false, 100);
	init(list, head);
	while (true){
		switch (mainMenu()){
			case 1: {
				VatTuMenu(head, list);
				continue;
			}
			case 2: {
				NhanVienMenu(list);
				continue;
			}
			case 3:{
				HoaDonMenu(list, head);
				continue;		
			}
			case 4:{
				ThongKeMenu(list, head);
				continue;
			}
			case 5: return 0;
		}
	}
//	cout<<"\nTao Vat Tu:\n";
//	string smaVatTu = "VT";
//	string stenVatTu[] = {"CAP DONG ", "CAP QUANG ", "ONG NHUA ", "GIAY RUT"};
//	string sdvt = "VND";
//	string temp;
//	VatTu vt; 
//	vt.soLuongTon = 100;
//	PTRVatTu head = NULL;
//	for (int i=0; i<30; i++){
//		temp = smaVatTu + to_string(i);
//		strcpy(vt.maVT, temp.c_str());
//		temp = stenVatTu[Random(0,3)] + to_string(i);
//		strcpy(vt.tenVT, temp.c_str());
//		strcpy(vt.dvt, sdvt.c_str());
//		InsertVatTu(head, vt);
//	}
//	InorderVatTu(head);
//	InFile(head);
//	mangVatTu arr;
//	ListToArray(head, arr);
//	Info info[100];
//	CT_HD ct;
//	string ssohd = "HD";
//	for (int i=0; i<100; i++){
//		temp = ssohd + to_string(i);
//		strcpy(info[i].soHD, temp.c_str());
//		info[i].ngayLap = getDateNow();
//		info[i].loai = (i%2==0?'X':'N');
//		info[i].listct = new ListCT_HD;
//		for (int j=0; j<5; j++){
//			strcpy(ct.maVT, arr.mangVatTu[Random(0, 9)].maVT);
//			ct.dongia = Random(10000, 90000);
//			ct.soluong = Random(30, 95);
//			ct.VAT = float(Random(0,5));
//			add(*info[i].listct, ct);
//		}
//	}
//	
//	string ho[] = {"NGUYEN", "TRAN", "LE", "PHAM", "HOANG", "MAI", 
//	"HUYNH", "DO", "BUI", "TANG", "LENH", "VO"};
//	string lotnam[] = {"VAN", "HUYNH", "MINH", "DINH", "TIEN"};
//	string lotnu[] = {"THI", "THANH", "THIEN", "MY", "KHANH"};
//	string ten[] = {"LONG", "TRI", "DUC", "LAN", "HOA", "HUE", "HONG", "DAO", "LE", "MIT", "BUOI", "TIEN"};
//	int phai;
//	cout<<"\nTao listNhanVien (createNhanVien da tao ListHoaDon):\n";
//	ListNhanVien list;
//	srand((unsigned int) time(NULL));
//	for (int i=0; i<50; i++) {
//		phai = i%2;
//		string temp = ho[Random(0, 11)] + " " + (i==1?lotnu[Random(0,4)]:lotnam[Random(0,4)]);
//		NhanVien nv = createNhanVien(i, temp, ten[Random(0,11)], phai);
//		addTail(*nv.hoaDons, info[i*2]);
//		addTail(*nv.hoaDons, info[i*2+1]);
//		add(list, nv);
//		cout<<toString(*list.nhanViens[i])<<endl;
//		cout<<toString(*list.nhanViens[i]->hoaDons)<<endl;
//	}
//	cout<<writeFileNV(list, DEFAULT_NVFILE);
	return 0;
}
