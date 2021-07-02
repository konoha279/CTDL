#include "NhanVien.h"
#include "HoaDon.h"
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
	createWindow();
	string str;
	while (true) {
		getline(std::cin, str);
		if (str[str.size()-1]==97) break;
	}
//	cout<<"\nTao list:\n";
//	ListNhanVien listNhanVien = creatListNhanVien();
//	srand((unsigned int) time(NULL));
//	string source = "";
//	for (long i = 0; i < 5000; i++) {
//    	char c = Random(65,90);
//        source+=c;
//    }
//    int p;
//	for (int i=0; i<20; i++) {
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
//	sortTen(listNhanVien);
//	for (int i=0; i<listNhanVien.n; i++) cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	cout<<"\nSap xep lai theo maNV:\n";
//	sortmaNV(listNhanVien);
//	for (int i=0; i<listNhanVien.n; i++) cout<<toString(*listNhanVien.nhanViens[i])<<endl;
//	cout<<"\nThem nhan vien 12 = nhanvien 8:\n";
//	NhanVien nv = get(listNhanVien, 8); nv.maNV=12;
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
//		ListNhanVien listNhanVien2;
//		if(readFile(listNhanVien2, DEFAULT_NVFILE)==-1) cout<<"\nLoi doc file!";
//		cout<<listNhanVien2.n;
//		for(int i=0; i<listNhanVien2.n; i++) cout<<toString(*listNhanVien2.nhanViens[i])<<endl;
//	}
//	cout<<"\nTao list hoa don:\n";
//	ListCT_HoaDon listct;
//	CT_HoaDon ct;
//	ct.soHD="000001";
//	ct.maVT="DE";
//	ct.donGia=7000.0;
//	ct.soLuong=1;
//	ct.VAT=5.0;
//	insert_CTHDTail(listct, ct);
//	cout<<toString(*listct.ct[0]);
	return 0;
}
