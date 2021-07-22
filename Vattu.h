#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h>
#define MAX_NV 500
#define MAX_LIST 10000
#define MAX_MAVT 10
#define MAX_TENVT 50
#define MAX_DVT 10
#define MAX_SL_TON 10
int sizeVatTu = 0;
struct VatTu {
	char maVT[11];
	char tenVT[51];
	char dvt[11];
	int soLuongTon;
};
struct NodeVatTu {
	VatTu vatTu;
	NodeVatTu *left;
	NodeVatTu *right;
};
typedef NodeVatTu* PTRVatTu;
struct mangVatTu {
	int n =0;
	VatTu mangVatTu[MAX_LIST];
};
//=====Ten Ham=====//
int InsertVatTu(PTRVatTu &p, VatTu vt);
int SoSanhVatTu(VatTu vt1, VatTu vt2);
int remove_case_3(PTRVatTu &r);
int remove(VatTu vt, PTRVatTu &p);
int remove(PTRVatTu &p, char *mavt);
PTRVatTu Search(PTRVatTu root, VatTu vt);
PTRVatTu Search(PTRVatTu root, char *mavt);
int SuaVatTu(PTRVatTu root, VatTu vtMoi);
bool isExistVatTu(PTRVatTu p, char *maVT);
void InorderVatTu(PTRVatTu p);
void InChiTiet(PTRVatTu p, FILE *f);
int InFile(PTRVatTu Head);
int ReadFile(PTRVatTu &Head);
void freePTRVatTu(PTRVatTu &Head);
void add(mangVatTu &arr, PTRVatTu p);
void ListToArray(PTRVatTu p, mangVatTu &arr);
void InMangVatTu(mangVatTu &arr);
void InMangVatTu(mangVatTu &arr, int n);
void swapVatTu(VatTu &vt1, VatTu &vt2);
int SoSanhTenVatTu(VatTu vt1, VatTu vt2);
int partition (mangVatTu &arr, int low, int high);
int QuicksortVatTu(mangVatTu &arr, int low, int high);
void removeMang(mangVatTu &arr);
//=====Noi dung=====//
int InsertVatTu(PTRVatTu &p, VatTu vt){
	if (isExistVatTu(p, vt.maVT)) return 0;
	if (p == NULL) {
		p = new NodeVatTu;
		p->vatTu = vt;
		p->left = NULL;
		p->right = NULL;
		return 1;
	} else{
		if (SoSanhVatTu(p->vatTu, vt) == 1)
			return InsertVatTu(p->left, vt);
		else if (SoSanhVatTu(p->vatTu, vt) == -1)
			return InsertVatTu(p->right, vt);
	}
}

int SoSanhVatTu(VatTu vt1, VatTu vt2){
	if (!strcmp(vt1.maVT, vt2.maVT)){
		if (!strcmp(vt1.tenVT, vt2.tenVT)){
			if (vt1.soLuongTon == vt2.soLuongTon)
				return 0;
			else if (vt1.soLuongTon > vt2.soLuongTon)
				return 1;
			else if (vt1.soLuongTon < vt2.soLuongTon)
				return -1;
		}
		else if (strcmp(vt1.tenVT, vt2.tenVT) < 0) return -1;
		else if (strcmp(vt1.tenVT, vt2.tenVT) > 0) return 1;
	}
	else if (strcmp(vt1.maVT, vt2.maVT) < 0) return -1;
	else if (strcmp(vt1.maVT, vt2.maVT) > 0) return 1;
}
int remove_case_3(PTRVatTu &r){
	if (r->left == NULL) return remove_case_3(r->left);
	else {
		PTRVatTu rp = r;
		rp->vatTu = r->vatTu;
		rp = r;
		r = rp->right;
		return 1;
	}
}
int remove(VatTu vt, PTRVatTu &p){
	if (p == NULL) return 0;
	else
		if (SoSanhVatTu(vt, p->vatTu) == -1) return remove(vt, p->left);
		else if (SoSanhVatTu(vt, p->vatTu) == 1) return remove(vt, p->right);
		else {
			PTRVatTu rp = p;
			if (rp->right == NULL) p = rp->left;
			else if (rp->left == NULL) p = rp->right;
			else remove_case_3(rp->right);
			delete rp;
			return 1;
		}
}

int remove(PTRVatTu &p, char *mavt) {
	if (p == NULL) return 0;
	else
		if (strcmp(mavt, p->vatTu.maVT) < 0) return remove(p->left, mavt);
		else if (strcmp(mavt, p->vatTu.maVT) > 0) return remove(p->right, mavt);
		else {
			PTRVatTu rp = p;
			if (rp->right == NULL) p = rp->left;
			else if (rp->left == NULL) p = rp->right;
			else remove_case_3(rp->right);
			delete rp;
			return 1;
		}
}
PTRVatTu Search(PTRVatTu root, VatTu vt) {
	PTRVatTu p;
	p = root;
	while (p != NULL && SoSanhVatTu(vt, p->vatTu))
		if (SoSanhVatTu(vt, p->vatTu) < 0) p = p->left;
		else p = p->right;
	return p;
}
PTRVatTu Search(PTRVatTu root, char *mavt) {
	PTRVatTu p;
	p = root;
	while (p != NULL && strcmp(mavt, p->vatTu.maVT) != 0)
		if (strcmp(mavt, p->vatTu.maVT) < 0) p = p->left;
		else p = p->right;
	return p;
}
int SuaVatTu(PTRVatTu root, VatTu vtMoi){
	PTRVatTu p = Search(root, vtMoi.maVT);
	if (p != NULL) {
		p->vatTu = vtMoi; return 1;
	}
	return 0;
}

bool isExistVatTu(PTRVatTu p, char *maVT) {
	if (p == NULL) return false;
	else {
		if (strcmp(maVT, p->vatTu.maVT) > 0)
			return isExistVatTu( p->left, maVT);
		else if (strcmp(maVT, p->vatTu.maVT) < 0)
			return isExistVatTu(p->right, maVT);
		else if (!strcmp(maVT, p->vatTu.maVT))
			return true;
	}
}
void InorderVatTu(PTRVatTu p){
	if (p != NULL) {
		InorderVatTu(p->left);
		printf(" %5s | %-50s | %-5s | %d \n", p->vatTu.maVT, p->vatTu.tenVT, p->vatTu.dvt, p->vatTu.soLuongTon);
		InorderVatTu(p->right);
	}
}
void InChiTiet(PTRVatTu p, FILE *f) {
	if (p != NULL) {
		InChiTiet(p->left, f);
		fwrite(&p->vatTu, sizeof(struct VatTu), 1, f);
		InChiTiet(p->right, f);
	}
}
int InFile(PTRVatTu Head) {
	FILE *f = fopen("vattu.dat", "wb");
	InChiTiet(Head,f);
	fclose(f);
	return 1;	
}
int ReadFile(PTRVatTu &Head){
	FILE *f;
	f = fopen("vattu.dat", "rb");
	VatTu vt;
	while (!feof(f)) {
		fread(&vt, sizeof(struct VatTu), 1, f);
		if (InsertVatTu(Head, vt)) sizeVatTu++;
	}
	fclose(f);
	return 1;
}
void freePTRVatTu(PTRVatTu &Head){
	if (Head==NULL) return;
	freePTRVatTu(Head->left);
	freePTRVatTu(Head->right);
	delete Head;
};
void add(mangVatTu &arr, PTRVatTu p){
	arr.mangVatTu[arr.n] = p->vatTu;
	arr.n++;
}
void ListToArray(PTRVatTu p, mangVatTu &arr){
	if (p!= NULL){
		ListToArray(p->left, arr);
		add(arr,p);
		ListToArray(p->right, arr);
	}
}
void removeMang(mangVatTu &arr){
	int i=0;
	for (; i< arr.n; i++) {
		strcpy(arr.mangVatTu[i].maVT, "");
		strcpy(arr.mangVatTu[i].tenVT, "");
		strcpy(arr.mangVatTu[i].dvt, "");
		arr.mangVatTu[i].soLuongTon = 0;
	}
	arr.n = 0;
}
void InMangVatTu(mangVatTu &arr) {
	int i = 0;
	for (;i< arr.n;i++)
		printf(" %5s | %-50s | %-5s | %d \n", 
		arr.mangVatTu[i].maVT, arr.mangVatTu[i].tenVT, arr.mangVatTu[i].dvt, arr.mangVatTu[i].soLuongTon);
}

void InMangVatTu(mangVatTu &arr, int n) {
	int i = 0;
	while (i < arr.n && n > 0){
		printf(" %5s | %-50s | %-5s | %d \n", arr.mangVatTu[i].maVT, arr.mangVatTu[i].tenVT, arr.mangVatTu[i].dvt, arr.mangVatTu[i].soLuongTon);
		i++; n--;
	}
}
void getMangVatTu(mangVatTu &des, mangVatTu src, int n) {
	int i = 0;
	removeMang(des);
	while (i < src.n && n > 0){
		des.mangVatTu[des.n] = src.mangVatTu[i];
		des.n++;
		i++;
		n--;
	}
}
void swapVatTu(VatTu &vt1, VatTu &vt2){
	VatTu tmp = vt1;
	vt1 = vt2;
	vt2 = tmp;
}
int SoSanhTenVatTu(VatTu vt1, VatTu vt2){
	if (strcmp(vt1.tenVT, vt2.tenVT) < 0) return -1;
	else if (strcmp(vt1.tenVT, vt2.tenVT) > 0) return 1;
	else return 0;
}
int partition (mangVatTu &arr, int low, int high) {
    VatTu pivot = arr.mangVatTu[high];
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && SoSanhTenVatTu(arr.mangVatTu[left], pivot)  == -1 ) left++;
        while(right >= left && SoSanhTenVatTu(arr.mangVatTu[right], pivot)  == 1) right--;
        if (left >= right) break;	
        swapVatTu(arr.mangVatTu[left], arr.mangVatTu[right]);
        left++;
        right--;
    }
    swapVatTu(arr.mangVatTu[left], arr.mangVatTu[high]);
    return left;
}
int QuicksortVatTu(mangVatTu &arr, int low, int high){
	if (arr.n <= 0) return -1;
	if (low < high) {
        int pi = partition(arr, low, high);
        QuicksortVatTu(arr, low, pi - 1);
        QuicksortVatTu(arr, pi + 1, high);
    }
}
