#pragma once
#include "Date.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>
using namespace std;

#define MAXLIST_CT 20
#define MAX_SOHD 20
#define MAX_NGAYLAP 11
#define MAX_LOAI 4
#define MAX_SL 4
#define MAX_DONGIA 7
#define MAX_VAT 4
#define DEFAULT_CTFILE "HoaDon.txt"
#define NHAP 78
#define XUAT 88
//=====struct=====//
struct CT_HD{
	char maVT[11];
	int soluong;
	int dongia;
	float VAT;
};
struct ListCT_HD{
	int n = 0;
	CT_HD ct[MAXLIST_CT];
};
struct Info{
	char soHD[21];
	Date ngayLap;
	char loai; //chi nhan gia tri 'N'hoac'X'
	ListCT_HD *listct;
};
struct hoadon{
	Info info;
	hoadon *next;
};
typedef struct hoadon *HoaDon;
struct ListHoaDon{
	int n = 0;
	HoaDon phead = NULL;
	HoaDon ptail = NULL;
};
//=====Ten Ham=====//
vector<string> split(const string& str, const string& delim);
//=====CT_HD=====//
CT_HD createCT_HD(string str);
string toString(const CT_HD &ct);
CT_HD get(const ListCT_HD &list, char maVT[]);
int indexOf(const ListCT_HD &list, char maVT[]);
int compareMaVT(const CT_HD &ct1, const CT_HD &ct2);
int add(ListCT_HD &list, const CT_HD &ct);
int remove(ListCT_HD &list, char maVT[]);
void swap(ListCT_HD &list, int a, int b);
//=====HoaDon=====//
HoaDon createHoaDon(const Info &info);
void addHead(ListHoaDon &list, const Info &info);
void addTail(ListHoaDon &list, const Info &info);
int removeHead(ListHoaDon &list);
int removeTail(ListHoaDon &list);
int remove(ListHoaDon &list, char soHD[]);
HoaDon get(const ListHoaDon &list, char soHD[]);
Info createInfo(string str);
string toString(const Info &info);
string toString(const ListHoaDon &list);
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
};
//=====CT_HD=====//
CT_HD createCT_HD(string str){
	CT_HD ct; int i;
	vector<string> v = split(str, "|");
	strcpy(ct.maVT, v[0].c_str());
	ct.soluong = atoi(v[1].c_str());
	ct.dongia = atoi(v[2].c_str());
	ct.VAT = atoi(v[3].c_str());
	return ct;
};
string toString(const CT_HD &ct){
	return string(ct.maVT) + "|" + to_string(ct.soluong) + "|" + to_string(ct.dongia) + "|" + to_string(ct.VAT);
};
CT_HD get(const ListCT_HD &list, char maVT[]){
	for (int i=0; i<list.n; i++)
		if(!strcmp(list.ct[i].maVT, maVT)) return list.ct[i];
};
int indexOf(const ListCT_HD &list, char maVT[]){
	for (int i=0; i<list.n; i++)
		if(!strcmp(list.ct[i].maVT, maVT)) return i;
	return -1;
};
int compareMaVT(const CT_HD &ct1, const CT_HD &ct2){
	return strcmp(ct1.maVT, ct2.maVT);
};
int add(ListCT_HD &list, const CT_HD &ct){
	if(list.n == MAXLIST_CT) return 0;
	int i, j;
	for (i=0; i<list.n && compareMaVT(list.ct[i], ct)<0; i++);
	for (j=list.n; j>i; j--) list.ct[j] = list.ct[j-1];
	list.ct[i] = ct;
	list.n++;
	return 1;
};
int remove(ListCT_HD &list, char maVT[]){
	if(list.n==0) return 0;
	int i = indexOf(list, maVT);
	if(i==-1) return 0;
	for(int j=i+1; j<list.n; j++) list.ct[j-1] = list.ct[j];
	list.n--;
	return 1;
};
void swap(ListCT_HD &list, int a, int b){
	CT_HD temp = list.ct[a];
	list.ct[a] = list.ct[b];
	list.ct[b] = temp;
};
//=====Hoa Don=====//
HoaDon createHoaDon(const Info &info){
	HoaDon hd = new hoadon;
	hd->info = info;
	hd->next = NULL;
	return hd;
};
void addHead(ListHoaDon &list, const Info &info){
	HoaDon temp = createHoaDon(info);
	if(list.phead==NULL){
		list.phead = temp;
		list.ptail = temp;
		list.n++;
		return;
	}
	temp->next = list.phead;
	list.phead = temp;
	list.n++;
	return;
};
void addTail(ListHoaDon &list, const Info &info){
	HoaDon temp = createHoaDon(info);
	if(list.phead==NULL){
		list.phead = temp;
		list.ptail = temp;
		list.n++;
		return;
	}
	list.ptail->next = temp;
	list.ptail = temp;
	list.n++;
	return;
};
int removeHead(ListHoaDon &list){
	if (list.n==0) return 0;
	HoaDon temp = list.phead;
	list.phead = list.phead->next;
	delete temp;
	list.n--;
	return 1;
};
int removeTail(ListHoaDon &list){
	if (list.n==0) return 0;
	HoaDon temp = list.ptail, p = list.phead;
	while (p->next!=temp) p=p->next;
	list.ptail = p;
	delete temp;
	list.n--;
	return 1;
};
int remove(ListHoaDon &list, char soHD[]){
	HoaDon p = list.phead, q=list.ptail;
	if(!strcmp(p->info.soHD, soHD)) return removeHead(list);
	if(!strcmp(q->info.soHD, soHD)) return removeTail(list);
	while(p->next!=q && strcmp(p->next->info.soHD, soHD)) p=p->next;
	if (p->next==q) return 0;
	q = p->next;
	p->next = q->next;
	delete q;
	list.n--;
	return 1;
};
HoaDon get(const ListHoaDon &list, char soHD[]){
	if(list.n==0) return NULL;
	for (HoaDon p = list.phead; p!=NULL; p=p->next)
		if(!strcmp(p->info.soHD, soHD)) return p;
	return NULL;
};
Info createInfo(string str){
	vector<string> v = split(str,"|");
	Info info;
	strcpy(info.soHD, v[0].c_str());
	info.ngayLap = convertStringToDate(v[1]);
	info.loai = v[2][0];
	info.listct = new ListCT_HD;
	info.listct->n = atoi(v[3].c_str());
	return info;
};
string toString(const Info &info){
	return string(info.soHD) + "|" + convertDateToString(info.ngayLap) + "|"
		+ info.loai + "|" + to_string(info.listct->n);
};
string toString(const ListHoaDon &list){
	string str="";
	for (HoaDon hd = list.phead; hd!=NULL; hd=hd->next){
		str += toString(hd->info) + "\n";
		for (int i=0; i<hd->info.listct->n; i++)
			str += toString(hd->info.listct->ct[i]) + "\n";
	}
	return str;
};
