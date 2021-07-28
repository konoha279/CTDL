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
//	cout<<"Tao CT_HD:\n";
//	CT_HD ct0 = createCT_HD("DE|1|700|0");
//	cout<<toString(ct0)<<endl;
//	CT_HD ct1 = createCT_HD("AK|1|2700|1");
//	cout<<toString(ct1)<<endl;
//	CT_HD ct2 = createCT_HD("FLASH|1|200|2");
//	cout<<toString(ct2)<<endl;
//	cout<<"Tao listCT_HD:\n";
//	ListCT_HD listct;
//	add(listct, ct0); add(listct, ct1); add(listct, ct2);
//	for(int i=0; i<listct.n; i++) cout<<toString(listct.ct[i])<<endl;
//	cout<<"Tao Info:\n";
//	Info info = createInfo("HD1|12/7/2021|N|3");
//	cout<<toString(info)<<endl;
//	for (int i=0; i<info.listct->n; i++) info.listct->ct[i] = listct.ct[i];
//	for (int i=0; i<info.listct->n; i++) cout<<toString(listct.ct[i])<<endl;
//	
//	cout<<"\nTao listNhanVien (createNhanVien da tao ListHoaDon):\n";
//	ListNhanVien listNhanVien;
//	srand((unsigned int) time(NULL));
//	for (int i=0; i<50; i++) {
//		string ho="", ten="";
//		for (int j=0; j<30; j++){
//			ho+=char(Random(65,90));
//			if (j<10) ten+=char(Random(65,90));
//		}
//		NhanVien nv = createNhanVien(i, ho, ten, i%2);
//		addTail(*nv.hoaDons, info);
//		addTail(*nv.hoaDons, info);
//		add(listNhanVien, nv);
//		cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//		cout<<toString(*listNhanVien.nhanViens[i]->hoaDons)<<endl;
//	}
//	quicksort(listNhanVien, 0, listNhanVien.n-1, 1);
//	listNhanVien.sort = 1;
//	cout<<"\nLay phan tu theo maNV 12:\n";
//	cout<<toString(get(listNhanVien,50));
//	cout<<"\nThay doi phan tu 12:\n";
//	NhanVien nv = get(listNhanVien, 12); nv.ho = "Hoag";
//	exchange(listNhanVien, nv);
//	cout<<toString(get(listNhanVien,12));
//	cout<<"\nXoa phan tu maNV 12:";
//	quicksort(listNhanVien, 0, listNhanVien.n-1, 1);
//	listNhanVien.sort = 1;
//	remove(listNhanVien, 12);
//	cout<<"\nThem phan tu thu 12:";
//	quicksort(listNhanVien, 0, listNhanVien.n-1, 1);
//	listNhanVien.sort = 1;
//	exchange(listNhanVien, nv);
//	for (int i=0; i<listNhanVien.n; i++) cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	cout<<listNhanVien.n;
//	cout<<"\nSap xep theo ten:\n";
//	quicksort(listNhanVien, 0, listNhanVien.n-1, 1);
//	for (int i=0; i<listNhanVien.n; i++) cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	cout<<"\nSap xep lai theo maNV:\n";
//	quicksort(listNhanVien, 0, listNhanVien.n-1, 0);
//	for (int i=0; i<listNhanVien.n; i++) cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	cout<<"\nThem nhan vien 12 = nhanvien 8:\n";
//	NhanVien nv = get(listNhanVien, 8); nv.maNV=12; nv.ten="LONG";
//	insertOrder(listNhanVien, nv);
//	for (int i=0; i<listNhanVien.n; i++) cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	cout<<listNhanVien.n;
//	cout<<"\nCat chuoi:\n";
//	string temp = toString(*listNhanVien.nhanViens[8]);
//	vector<string> v = split(temp, "|");
//	for (int i=0; i<v.size(); i++) cout<<v[i]<<" ";
//	cout<<v[0];
//	cout<<"\nDoc string:\n";
//	cout<<toString(createNhanVien(temp))<<endl;
//	cout<<"\nGhi file:\n";
//	if (writeFileNV(listNhanVien, DEFAULT_NVFILE)==-1) cout<<"\nLoi ghi file!";
//	else {
//		cout<<"\nGhi file dc";
//		ListNhanVien listNhanVien2;
//		if(readFileNV(listNhanVien2, DEFAULT_NVFILE)==-1) cout<<"\nLoi doc file!";
//		cout<<listNhanVien2.n<<endl;
//		for(int i=0; i<listNhanVien2.n; i++) {
//			cout<<toString(*listNhanVien2.nhanViens[i])<<endl;
//			cout<<toString(*listNhanVien2.nhanViens[i]->hoaDons)<<endl;
//		}
//	}
//	cout<<"\nSearch: 'AC'\n";
//	ListNhanVien list2 = search(listNhanVien, "AC");
//	for (int i=0; i<list2.n; i++) cout<<toString(*list2.nhanViens[i])<<endl;
	
//	for (int i=0; i<list.phead->info.listct->n; i++) cout<<toString(list.phead->info.listct->ct[i])<<endl;
////	cout<<"Ghi file listHoaDon:\n";
////	if(!writeFileHD(list, DEFAULT_CTFILE)) cout<<"Loi ghi file\n";
//	cout<<"Doc file listHoaDon:\n";
//	ListHoaDon list2;
//	if(!readFileHD(list2, DEFAULT_CTFILE)) cout<<"Loi doc file\n";
//	for (int i=0; i<list2.phead->info.listct->n; i++) cout<<toString(list2.phead->info.listct->ct[i])<<endl;
//	cout<<"Truyen listHoaDon vao ham:\n"<<toString(list);
//	cout<<"So phan tu cua listHoaDon:\n"<<list.n;
//	char soHD[20]; strcpy(soHD, list.phead->info.soHD);
//	cout<<"Xoa hoadon thu nhat:\n"<<remove(list2, soHD)<<endl<<list.n;
//	Listdata1 list1;
//	Listdata2 list2;
//	Date date1;
//	Date date2;
//	date1=convertStringToDate("1/1/2021");
//	date2=convertStringToDate("23/7/2021");
//	xuli(list1, list2, date1, date2);
//	int i;
//	cout<<"list1.n="<<list1.n<<endl;
//	for (i=0; i<list1.n; i++)
//		cout<<toString(list1.data1s[i]->info) + "|" + list1.data1s[i]->hoten + "|" + to_string(list1.data1s[i]->trigia) + "\n";
//	cout<<"list2.n="<<list2.n<<endl;
//	for (i=0; i<list2.n; i++){
//		cout<<list2.data2s[i]->vt.tenVT;
//		cout<<"|" + to_string(list2.data2s[i]->doanhthu) + "\n";
//	}
//	quicksort(list2,0, list2.n-1, 1);
//	cout<<"list2.n="<<list2.n<<endl;
//	for (i=0; i<list2.n; i++){
//		cout<<list2.data2s[i]->vt.tenVT;
//		cout<<"|" + to_string(list2.data2s[i]->doanhthu) + "\n";
//	}
	return 0;
}
