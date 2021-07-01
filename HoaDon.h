#pragma once
#include "Date.h"
#include <string.h>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
using namespace std;

#define MAXLIST_CT 20
#define MAX_SO_HD 20
#define MAX_MAVT 10
#define DEFAULT_CTFILE "CB.bin"
#define NHAP 78
#define XUAT 88
//=====struct=====//
struct CT_HoaDon{
	string soHD;
	string maVT;
	int soLuong;
	float donGia;
	float VAT;
};
struct ListCT_HoaDon{
	int soVatTu = 0;
	CT_HoaDon *ct[MAXLIST_CT];
};
struct InfoHoaDon{
	string soHD;
	int maNV;
	Date ngayLap;
	char loai; //chi nhan gia tri 'N'hoac'X'
	ListCT_HoaDon *listct;
};
struct hoadon{
	InfoHoaDon info;
	hoadon *next;
};
typedef struct hoadon *HoaDon;
struct DSHoaDon{
	HoaDon phead = NULL;
	HoaDon ptail = NULL;
};
//=====Ten Ham=====//
//=====CT_HoaDon=====//
bool empty(ListCT_HoaDon &ds);
bool full(ListCT_HoaDon &ds);
int insert_CTHD(ListCT_HoaDon &ds,CT_HoaDon &ct,int i);
int insert_CTHDTail(ListCT_HoaDon &ds,CT_HoaDon &ct);
//con loi
int delete_CTHD(ListCT_HoaDon &ds,string maVT);
int readFileListCT(ListCT_HoaDon &list, const string &filename);
int writeFileListCT(const ListCT_HoaDon &listCT, const string &filename);
int checkSoHD(string soHD);
int checkMaVT(string maVT);
float doanhthu(const CT_HoaDon &ct);
string toString(const CT_HoaDon &ct);
//=====HoaDon=====//
float doanhthu(const HoaDon &hd);
//=====Ham=====//
//=====CT_HoaDon=====//
//tra ve 1 la rong,0 la ko rong
bool empty(ListCT_HoaDon &ds){
	return ds.soVatTu == 0;
};
//tra ve 1 la full,0 la chua full
bool full(ListCT_HoaDon &ds){
	return ds.soVatTu == MAXLIST_CT;
};
//them 1 ct vao ds, tra ve 0 la ko them duoc, 1 la them thanh cong
int insert_CTHD(ListCT_HoaDon &ds,CT_HoaDon &ct,int i){
	int j;
	if(i < 0 || i > ds.soVatTu || full(ds)) 
		return 0;
	for(j = ds.soVatTu - 1; j >= i; j--)
		ds.ct[j+1] = ds.ct[j];
	ds.ct[i] = &ct;
	ds.soVatTu++;
	return 1; 
};
//them 1 ct vao cuoi ds, tra ve 0 la ko them duoc, 1 la them thanh cong
int insert_CTHDTail(ListCT_HoaDon &ds,CT_HoaDon &ct){
	int j;
	if(full(ds)) 
		return 0;
	if(empty(ds)){
		ds.ct[0] = &ct;
		ds.soVatTu++;
		return 1;
	}
	for(j = 0; j < ds.soVatTu; j++);
	ds.ct[j] = &ct;
	ds.soVatTu++;
	return 1;
};
//xoa 1 ct trong ListCT_HoaDon, ham nay chua KT viec ds nay da duoc luu hay chua
//ham nay co loi
int delete_CTHD(ListCT_HoaDon &ds,string maVT){
	int i;
	if(ds.soVatTu == 0)
		return 0;
	for(i = 0; i < ds.soVatTu || ds.ct[i]->maVT.compare(maVT) == 0; i++);
	for(int j = i+1;  j < ds.soVatTu ; j++)
		ds.ct[j-1] = ds.ct[j];
	ds.soVatTu--;
	return 1;		
};
//ghi vao file 1 ListCT_HoaDon, tra ve 0 la loi, 1 la ghi thanh cong 
int writeFileListCT(const ListCT_HoaDon &listCT, const string &filename){
	FILE *fptr;
	if ((fptr = fopen(filename.c_str(),"wb")) == NULL) return 0;
	fwrite(&listCT.soVatTu, sizeof(int), 1, fptr);
	for(int i =0; i < listCT.soVatTu; i++){
		fwrite("\n", sizeof(char), 1, fptr);
		fwrite(&listCT.ct[i], sizeof(CT_HoaDon), 1, fptr);
	}
	fclose(fptr);
	return 1;
};
//doc file ListCT_HoaDon va tra ve 1 ListCT_HoaDon 
int readFileListCT(ListCT_HoaDon &list, const string &filename){
	int soLuong;
	char temp;
	FILE *fptr;
	if ((fptr = fopen(filename.c_str(),"rb")) == NULL) return 0;
	fread(&soLuong, sizeof(int), 1, fptr);
	for(int i = 0; i < soLuong; i++){
		fread(&temp, sizeof(char), 1, fptr);
		fread(&list.ct[i], sizeof(CT_HoaDon), 1, fptr);
	}
	fclose(fptr);
	list.soVatTu = soLuong;
	return 1;
};
//tra 1 la soHD dat gioi han do dai, 0 la chua
int checkSoHD(string soHD){
	return soHD.length() == MAX_SO_HD;
};
//tra 1 la MaVT dat gioi han do dai, 0 la chua
int checkMaVT(string maVT){
	return maVT.length() == MAX_MAVT;
};

float doanhthu(const CT_HoaDon &ct){
	return (100 - ct.VAT)/100 * ct.donGia * (float) ct.soLuong;
};
float doanhthu(const HoaDon &hd){
	if(hd->info.loai==NHAP) return -1;
	float dt = 0;
	ListCT_HoaDon* listct = hd->info.listct;
	for (int i=0; i<listct->soVatTu; i++)
		dt += doanhthu(*listct->ct[i]);
	return dt;
};
string toString(const CT_HoaDon &ct){
	return ct.soHD + "|" + ct.maVT + "|" + to_string((int)ct.donGia) + "|" + 
		to_string((int)ct.VAT) + "|" + to_string((int) ct.soLuong) + "|" + to_string((int)doanhthu(ct));
};
//=====HoaDon=====//
