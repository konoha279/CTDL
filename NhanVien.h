#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h> 
#include <vector>
#include <cstdlib>
#include "HoaDon.h"
#define MAX_NV 500
#define MAX_MANV 4
#define MAX_HO 32
#define MAX_TEN 10
#define MAX_NVTOSTRING 4
#define DEFAULT_NVFILE "NhanVien.txt"
using namespace std;
//=====struct=====//
struct NhanVien{
	int maNV; //2byte
	string ho;//32byte
	string ten;//10byte
	int phai;//2byte
	ListHoaDon *hoaDons;//8byte
};
struct ListNhanVien{
	int n = 0;
	int sort = 0;
	NhanVien *nhanViens[MAX_NV];
};
//=====Ten Ham=====//
NhanVien createNhanVien(int maNV, string ho, string ten, int phai);
NhanVien createNhanVien(string line);
NhanVien get(ListNhanVien &list, int maNV);
int indexOf(ListNhanVien &list, int left, int right, int maNV);
int add(ListNhanVien &list, NhanVien &nv);
int add(ListNhanVien &list, NhanVien &nv, int vitri);
int insertOrder(ListNhanVien &list, NhanVien &nv);
int remove(ListNhanVien &list, int maNV);
int exchange(ListNhanVien &list, NhanVien nv);
int compareTen(NhanVien *nv1, NhanVien *nv2);
string toString(NhanVien nv);
int readFileNV(ListNhanVien &list, const string &filename);
int writeFileNV(const ListNhanVien &list, const string &filename);
ListNhanVien copyList(const ListNhanVien &list);
ListNhanVien search(const ListNhanVien &list, const string &delim);
int partitionmaNV(ListNhanVien &list, int low, int high);
int partitiontenNV(ListNhanVien &list, int low, int high);
void quicksort(ListNhanVien &list, int low, int high, int chedo);
void swap(ListNhanVien &list, int a, int b);
ListHoaDon getListHoaDon(ListNhanVien list);
void free(ListNhanVien &list);
//=====Ham=====//
NhanVien createNhanVien(int maNV, string ho, string ten, int phai){
	NhanVien nv;
	nv.maNV = maNV;
	nv.ho = ho;
	nv.ten = ten;
	nv.phai = phai;
	nv.hoaDons = new ListHoaDon;
	return nv;
};
NhanVien createNhanVien(string line){
	vector<string> v = split(line, "|");
	NhanVien nv;
	nv.maNV = atoi(v[0].c_str());
	nv.ho = v[1];
	nv.ten = v[2];
	nv.phai = atoi(v[3].c_str());
	nv.hoaDons = new ListHoaDon;
	nv.hoaDons->n = atoi(v[4].c_str());
	return nv;
};
NhanVien get(ListNhanVien &list, int maNV){
	int index = indexOf(list, 0, list.n-1, maNV);
	if (index>=0) return *list.nhanViens[index];
	NhanVien nv;
	return nv;
};
int indexOf(ListNhanVien &list, int left, int right, int maNV){
	if (list.sort==1){
		list.sort=0;
		quicksort(list,0,list.n-1,0);
	}
	int mid;
	while(left<=right){
		mid = left + (right - left)/2;
		if (list.nhanViens[mid]->maNV==maNV) return mid;
		if (list.nhanViens[mid]->maNV < maNV) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
};
int add(ListNhanVien &list, NhanVien &nv){
	if(list.n==MAX_NV) return -1;
	list.nhanViens[list.n] = new NhanVien;
	*list.nhanViens[list.n] = nv;
	list.n++;
	return 1;
};
int add(ListNhanVien &list, NhanVien &nv, int vitri){
	if(vitri<0||MAX_NV<vitri||list.n==MAX_NV) return -1;
	for (int i=list.n-1; i>=vitri; i--) list.nhanViens[i+1] = list.nhanViens[i];
	list.nhanViens[vitri] = new NhanVien;
	*list.nhanViens[vitri] = nv;
	list.n++;
	return 1;
};
int insertOrder(ListNhanVien &list, NhanVien &nv){
	if(list.n==MAX_NV) return -1;
	if (list.sort==1){
		list.sort=0;
		quicksort(list,0,list.n-1,0);
	}
	int j,k;
	for (j=0;j<list.n&&list.nhanViens[j]->maNV<nv.maNV; j++);
	for (k=list.n-1; k>=j; k--) list.nhanViens[k+1] = list.nhanViens[k];
	list.nhanViens[j] = new NhanVien;
	*list.nhanViens[j] = nv;
	list.n++;
	return 1;
};
int remove(ListNhanVien &list, int maNV){
	int i = indexOf(list, 0, list.n-1, maNV);
	if(i==-1) return -1;
	delete list.nhanViens[i];
	for (int j=i+1; j<list.n; j++) list.nhanViens[j-1] = list.nhanViens[j];
	list.n--;
	return 1;
};
int exchange(ListNhanVien &list, NhanVien nv){
	int i = indexOf(list, 0, list.n-1, nv.maNV);
	if(i==-1) return i;
	delete list.nhanViens[i];
	list.nhanViens[i] = new NhanVien;
	*list.nhanViens[i] = nv;
	return 1;
};
int compareTen(NhanVien *nv1, NhanVien *nv2){
	string tennv1 = nv1->ten + nv1->ho;
	string tennv2 = nv2->ten + nv2->ho;
	return strcmp(tennv1.c_str(), tennv2.c_str());
};
string toString(NhanVien nv){
	string str = to_string(nv.maNV) + "|" + nv.ho + "|" + nv.ten + "|" + to_string(nv.phai) + "|" + to_string(nv.hoaDons->n);
	return str;
};
int readFileNV(ListNhanVien &list, const string &filename){
	fstream f;
	f.open(filename);
	if(f.bad()||f.fail()) return 0;
	string str;
	NhanVien nv;
	Info info;
	while(!f.eof()){
		getline(f, str);
		if(str.length()<5) break;
		//Tao nhan vien
		nv = createNhanVien(str);
		//Them listhoadon
		for (int i=0; i<nv.hoaDons->n; i++){
			getline(f, str);
			info = createInfo(str);
			for (int j=0; j<info.listct->n; j++){
				getline(f, str);
				info.listct->ct[j] = createCT_HD(str);
			}
			addTail(*nv.hoaDons, info);
			nv.hoaDons->n--;
		}
		add(list, nv);
	}
	return 1;
};
int writeFileNV(const ListNhanVien &list, const string &filename){
	fstream f;
	f.open(filename);
	if(f.fail()) return -1;
	for (int i=0; i<list.n; i++){
		f<<toString(*list.nhanViens[i])<<endl;
		f<<toString(*list.nhanViens[i]->hoaDons);
	}
	return 1;
};

ListNhanVien copyList(const ListNhanVien &list){
	ListNhanVien index;
	index.n = list.n;
	for (int i=0; i<list.n; i++){
		index.nhanViens[i] = new NhanVien;
		*index.nhanViens[i] = *list.nhanViens[i];
	}
	return index;
};
ListNhanVien search(const ListNhanVien &list, const string &delim){	
	ListNhanVien list2;
	if (delim=="") return list2;
	string str;
	for (int i=0; i<list.n; i++){
		str = toString(*list.nhanViens[i]);
		vector<string> v = split(str, delim);
		if(v[0].size() < str.size()) add(list2, *list.nhanViens[i]);
	}
	return list2;
};
void swap(ListNhanVien &list, int a, int b){
	NhanVien temp = *list.nhanViens[a];
	*list.nhanViens[a] = *list.nhanViens[b];
	*list.nhanViens[b] = temp;
};
int partitionmaNV(ListNhanVien &list, int low, int high){
	//chon pivot la phan tu cuoi phai
	int pivotmaNV = list.nhanViens[high]->maNV;
	int left = low, right = high-1;
	while (true){
		while(left<=right && list.nhanViens[left]->maNV<pivotmaNV) left++;
		while(right>=left && list.nhanViens[right]->maNV>pivotmaNV) right--;
		if (left>=right) break;
		swap(list, left, right);
		left++; right--;
	}
	swap(list, left, high);
	return left;
};
int partitiontenNV(ListNhanVien &list, int low, int high){
	NhanVien* pivot = list.nhanViens[high];
	int left = low, right = high-1;
	while (true){
		while (left<=right && compareTen(list.nhanViens[left], pivot)<0) left++;
		while (right>=left && compareTen(list.nhanViens[right], pivot)>0) right--;
		if(left>=right) break;
		swap(list, left, right);
		left++; right--;
	}
	swap(list, left, high);
	return left;
};
void quicksort(ListNhanVien &list, int low, int high, int chedo){
	if(low<high){
		//pi là phan tu da dung dung vi tri, chia mang ra lam 2 mang con trai phai
		int pi;
		if (chedo==1) pi = partitiontenNV(list, low, high);
		else pi = partitionmaNV(list, low, high);
		quicksort(list, low, pi-1, chedo);
		quicksort(list, pi+1, high, chedo);
	}
};
ListHoaDon getListHoaDon(ListNhanVien list){
    int soNV = list.n,i;
    HoaDon hd;
    ListHoaDon listHD;
    for(i = 0; i < soNV; i++){
        for(hd = list.nhanViens[i]->hoaDons->phead; hd != NULL; hd = hd->next)
            addTail(listHD, hd->info);
    }
    return listHD;
};
void free(ListNhanVien &list){
	for (int i=0; i<list.n; i++){
		delete list.nhanViens[i];
	};
	list.n = 0;
};
