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
	DSHoaDon *hoaDons;//8byte
};
struct ListNhanVien{
	int n;
	NhanVien *nhanViens[MAX_NV];
};
//=====Ten Ham=====//
vector<string> split(const string& str, const string& delim);
NhanVien createNhanVien(int maNV, string ho, string ten, int phai);
NhanVien createNhanVien(string line);
ListNhanVien creatListNhanVien();
NhanVien get(const ListNhanVien &list, int maNV);
int indexOf(const ListNhanVien &list, int maNV);
int add(ListNhanVien &list, NhanVien &nv);
int add(ListNhanVien &list, NhanVien &nv, int vitri);
int insertOrder(ListNhanVien &list, NhanVien &nv);
int remove(ListNhanVien &list, int maNV);
int sortmaNV(ListNhanVien &list);
int sortTen(ListNhanVien &list);
int compareTen(NhanVien *nv1, NhanVien *nv2);
string toString(NhanVien nv);
int readFile(ListNhanVien &list, const string &filename);
int writeFileAll(const ListNhanVien &list, const string &filename);
ListNhanVien copyList(const ListNhanVien &list);
//=====Ham=====//
vector<string> split(const string& str, const string& delim){
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}
NhanVien createNhanVien(int maNV, string ho, string ten, int phai){
	NhanVien nv;
	nv.maNV = maNV;
	for (int i=0; i<32; i++){
		if(i<ho.length()) ho[i] = toupper(ho[i]);
		else ho+= " ";
	}
	nv.ho = ho;
	for (int i=0; i<10; i++){
		if(i<ten.length()) ten[i] = toupper(ten[i]);
		else ten+= " ";
	}
	nv.ten = ten;
	nv.phai = phai;
	nv.hoaDons = new DSHoaDon;
	return nv;
};
NhanVien createNhanVien(string line){
	vector<string> v = split(line, "|");
	NhanVien nv;
	nv.maNV = atoi(v[0].c_str());
	nv.ho = v[1];
	nv.ten = v[2];
	nv.phai = atoi(v[3].c_str());
	nv.hoaDons = new DSHoaDon;
	return nv;
};
ListNhanVien creatListNhanVien(){
	ListNhanVien list;
	list.n = 0;
	return list;
};
NhanVien get(const ListNhanVien &list, int maNV){
	for (int i=0; i<list.n; i++)
		if(list.nhanViens[i]->maNV==maNV) return *list.nhanViens[i];
};
int indexOf(const ListNhanVien &list, int maNV){
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
	for (int j=i+1; j<list.n; j++) list.nhanViens[j-1] = list.nhanViens[j];
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
			if(compareTen(list.nhanViens[min],list.nhanViens[j])>0) min=j;
		}
		NhanVien* temp = list.nhanViens[i];
		list.nhanViens[i] = list.nhanViens[min];
		list.nhanViens[min] = temp;
	}
};
string toString(NhanVien nv){
	string str = to_string(nv.maNV) + "|" + nv.ho + "|" + nv.ten + "|" + to_string(nv.phai) + "|";
	return str;
};
int readFile(ListNhanVien &list, const string &filename){
	FILE *f;
	if ((f=fopen(filename.c_str(), "rb"))==NULL) {
		fclose(f);
		return -1;
	}
	int i=-1;
	while (!feof(f))
		fread(&list.nhanViens[++i], sizeof(NhanVien), 1, f);
	list.n=i;
	fclose(f);
	return 1;
};
int writeFileAll(const ListNhanVien &list, const string &filename){
	FILE *f; 
	if ((f=fopen(filename.c_str(), "wb"))==NULL) {
		fclose(f);
		return -1;	
	}
	for (int i=0; i<list.n; i++)
		fwrite(&list.nhanViens[i], sizeof(NhanVien),1, f);
	fclose(f);
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
