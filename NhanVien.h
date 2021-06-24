#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h>
#include "HoaDon.h"
#define MAX_NV 500
#define MAX_HO 32
#define MAX_TEN 10
using namespace std;
//=====struct=====//
struct NhanVien{
	int maNV;
	string ho;
	string ten;
	int phai;
	ListHoaDon *hoaDons;
};
struct ListNhanVien{
	int n;
	NhanVien *nhanViens[MAX_NV];
};
//=====Ten Ham=====//
NhanVien createNhanVien(int maNV, string ho, string ten, int phai);
NhanVien get(ListNhanVien &list, int maNV);

int indexOf(ListNhanVien &list, int maNV);
int add(ListNhanVien &list, NhanVien &nv);
int insertOrder(ListNhanVien &list, NhanVien &nv);
int remove(ListNhanVien &list, int maNV);

int sortmaNV(ListNhanVien &list);
int sortTen(ListNhanVien &list);
int compareTen(NhanVien *nv1, NhanVien *nv2);
string toString(NhanVien &nv);
//=====Ham=====//
NhanVien createNhanVien(int maNV, string &ho, string &ten, int phai){
	NhanVien nv;
	nv.maNV = maNV;
	nv.ho = ho;
	nv.ten = ten;
	nv.phai = phai;
	nv.hoaDons = new ListHoaDon;
};
NhanVien get(ListNhanVien &list, int maNV){
	for (int i=0; i<list.n; i++)
		if(list.nhanViens[i]->maNV==maNV) return *list.nhanViens[i];
};
int indexOf(ListNhanVien &list, int maNV){
	for (int i=0; i<list.n; i++)
		if(list.nhanViens[i]->maNV==maNV) return i;
	return -1;
};
int add(ListNhanVien &list, NhanVien &nv){
	if(list.n==MAX_NV) return -1;
	list.nhanViens[list.n] = new NhanVien;
	*list.nhanViens[list.n] = nv;
	list.n++;
	return 1;
};
int insertOrder(ListNhanVien &list, NhanVien &nv){
	if(list.n==MAX_NV) return -1;
	int j,k;
	for (j=0;j<list.n&&list.nhanViens[j]->maNV<nv.maNV; j++);
	for (k=list.n-1; k>=j; k--) list.nhanViens[k+1] = list.nhanViens[k];
	list.nhanViens[j] = new NhanVien;
	*list.nhanViens[j] = nv;
	list.n++;
	return 1;
};
int remove(ListNhanVien &list, int maNV){
	int i = indexOf(list, maNV);
	if(i==-1) return -1;
	delete list.nhanViens[i];
	for (int j=i; j<list.n-1; j++) list.nhanViens[i] = list.nhanViens[i+1];
	list.n--;
	return 1;
};
int sortmaNV(ListNhanVien &list){
	for (int i=0; i<list.n-1; i++){
		int min = i;
		for (int j=i+1; j<list.n; j++){
			if(list.nhanViens[min]->maNV>list.nhanViens[j]->maNV) min=j;
		}
		NhanVien* temp = list.nhanViens[i];
		list.nhanViens[i] = list.nhanViens[min];
		list.nhanViens[min] = temp;
	}
};
int compareTen(NhanVien *nv1, NhanVien *nv2){
	if(strcmp(nv1->ten.c_str(), nv2->ten.c_str())!=0) return strcmp(nv1->ten.c_str(), nv2->ten.c_str());
	return strcmp(nv1->ho.c_str(), nv2->ho.c_str());
};
int sortTen(ListNhanVien &list){
	for (int i=0; i<list.n-1; i++){
		int min = i;
		for (int j=i+1; j<list.n; j++){
			if(compareTen(list.nhanViens[min],list.nhanViens[j])) min=j;
		}
		NhanVien* temp = list.nhanViens[i];
		list.nhanViens[i] = list.nhanViens[min];
		list.nhanViens[min] = temp;
	}
};
string toString(NhanVien &nv){
	string str = "";
	if (nv.maNV/10==0) str = "\n|  " + to_string(nv.maNV);
	else if (nv.maNV/100==0) str = "\n| " + to_string(nv.maNV);
	else str = "\n|" + to_string(nv.maNV);
	str+= "|";
	str+= nv.ho; 
	str+= "|";
	str+= nv.ten;
	str+= "|";
	if (nv.phai==0) str+="nam|";
	else str+="nu |";
	return str;
};
