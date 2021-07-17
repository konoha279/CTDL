#include "NhanVienView.h"
#include "HoaDonView.h"
#include "VattuView.h"
#include "Graphic.h"
#include <ctime>
#include <cstdlib>
#include <thread>
int Random(int min, int max)
{ 
    if(min >= max)
        return 0;
    int d = max - min;
    return (rand() % (d+1) + min);
}
int main(){
	Cursor(false, 100);
	while (true){
		switch (mainMenu()){
			case 2: {
				NhanVienMenu();
				continue;
			}
			case 3:{
				HoaDonMenu();
				continue;
			}
			case 5: return 0;
		}
	}
//	cout<<"\nTao list:\n";
//	ListNhanVien listNhanVien;
//	srand((unsigned int) time(NULL));
//	string source = "";
//	for (long i = 0; i < 10000; i++) {
//    	char c = Random(65,90);
//        source+=c;
//    }
//    int p;
//	for (int i=0; i<50; i++) {
//		string ho="", ten="";
//		for (int i=0; i<30; i++){
//			ho+=source[p++];
//			if (i<10) ten+=source[p++];
//		}
//		NhanVien nv = createNhanVien(i, ho, ten, i%2);
//		add(listNhanVien, nv);
//		cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	}
//	cout<<"\nLay phan tu theo maNV:\n";
//	cout<<toString(get(listNhanVien,12));
//	cout<<"\nXoa phan tu 12:\n";
//	remove(listNhanVien, 12);
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
//	if (writeFileAll(listNhanVien, DEFAULT_NVFILE)==-1) cout<<"\nLoi ghi file!";
//	else {
//		cout<<"\nGhi file dc";
//		ListNhanVien listNhanVien2; listNhanVien2.n = 0;
//		if(readFile(listNhanVien2, DEFAULT_NVFILE)==-1) cout<<"\nLoi doc file!";
//		cout<<listNhanVien2.n;
//		for(int i=0; i<listNhanVien2.n; i++) cout<<toString(*listNhanVien2.nhanViens[i])<<endl;
//	}
//	cout<<"\nSearch: 'AC'\n";
//	ListNhanVien list2 = search(listNhanVien, "AC");
//	for (int i=0; i<list2.n; i++) cout<<toString(*list2.nhanViens[i])<<endl;
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
//	Info info = createInfo("HD1|NV1|12/7/2021|N|3");
//	cout<<toString(info)<<endl;
//	for (int i=0; i<info.listct->n; i++) info.listct->ct[i] = listct.ct[i];
//	for (int i=0; i<info.listct->n; i++) cout<<toString(listct.ct[i])<<endl;
//	cout<<"Tao listHoaDon:\n";
//	ListHoaDon list;
//	addTail(list, info);
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
	return 0;
}
