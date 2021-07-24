#pragma once
#include "Vattu.h"
#include "NhanVien.h"
#define MAX_TRIGIA 10
#define MAX_DOANHTHU 10
using namespace std;
struct Data1{
	Info info;
	string hoten;
	float trigia = 0;
};
struct Listdata1{
	int n = 0;
	Data1 *data1s[MAX_LIST];
};
struct Data2{
	VatTu vt;
	float doanhthu = 0;
};
struct Listdata2{
	int sort = 0;
	int n = 0;
	Data2 *data2s[MAX_LIST];
};
//=====Ten Ham=====//
int indexOf(Listdata1 &list, char soHD[]);
int indexOf(Listdata2 &list, char maVT[]);
int addListdata1(Listdata1 &list, Info &info, string hoten);
int addListdata2(Listdata2 &list, const VatTu &vattu, const CT_HD &ct);
void swap(Listdata2 &list, int a, int b);
int partitionmaVT(Listdata2 &list, int low, int high);
int partitiondoanhthu(Listdata2 &list, int low, int high);
void quicksort(Listdata2 &list, int low, int high, int chedo);
void free(Listdata1 &list);
void free(Listdata2 &list);
void xuli(Listdata1 &list1, Listdata2 &list2, const Date &date1, const Date &date2);
//=====Noi dung=====//
int indexOf(Listdata1 &list, char soHD[]){
	int left = 0, right = list.n-1, mid;
	while (left<=right){
		mid = left + (right-left)/2;
		if(!strcmp(list.data1s[mid]->info.soHD,soHD)) return mid;
		if(strcmp(list.data1s[mid]->info.soHD,soHD)<0) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
};
int indexOf(Listdata2 &list, char maVT[]){
	if(list.sort==1){
		quicksort(list, 0, list.n-1, 0);
		list.sort=0;
	}
	int left = 0, right = list.n-1, mid;
	while (left<=right){
		mid = left + (right-left)/2;
		if(!strcmp(list.data2s[mid]->vt.maVT,maVT)) return mid;
		if(strcmp(list.data2s[mid]->vt.maVT,maVT)<0) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
};
int addListdata1(Listdata1 &list, Info &info, string hoten){
	if(list.n==MAX_LIST) return 0;
	int i, j;
	for (i=0; i<list.n&&strcmp(list.data1s[i]->info.soHD,info.soHD)<0; i++);
	for (j=list.n-1; j>=i; j--) list.data1s[j+1] = list.data1s[j];
	list.data1s[i] = new Data1;
	list.data1s[i]->info = info;
	list.data1s[i]->hoten = hoten;
	list.data1s[i]->trigia = trigia(info);
	list.n++;
	return 1;
};
int addListdata2(Listdata2 &list, const VatTu &vattu, const CT_HD &ct){
	if(list.n==MAX_LIST) return 0;
	int i, j;
	for (i=0; i<list.n&&strcmp(list.data2s[i]->vt.maVT,ct.maVT)<0; i++);
	if (i==list.n){
		list.data2s[list.n] = new Data2;
		list.data2s[list.n]->vt = vattu;
		list.data2s[list.n]->doanhthu += float(ct.soluong) * float(ct.dongia) * (1+ct.VAT/100);
		list.n++;
		return 1;
	}
	if (!strcmp(list.data2s[i]->vt.maVT,ct.maVT)){
		list.data2s[i]->doanhthu += float(ct.soluong) * float(ct.dongia) * (1+ct.VAT/100);
		return 1;
	}
	for (j=list.n-1; j>=i; j--) list.data2s[j+1] = list.data2s[j];
	list.data2s[i] = new Data2;
	list.data2s[i]->vt = vattu;
	list.data2s[i]->doanhthu += float(ct.soluong) * float(ct.dongia) * (1+ct.VAT/100);
	list.n++;
	return 1;
};
void swap(Listdata2 &list, int a, int b){
	Data2 temp = *list.data2s[a];
	*list.data2s[a] = *list.data2s[b];
	*list.data2s[b] = temp;
};
int partitionmaVT(Listdata2 &list, int low, int high){
	char pivotmaVT[11];
	strcpy(pivotmaVT, list.data2s[high]->vt.maVT);
	int left = low, right = high-1;
	while (true){
		while (left<=right&&strcmp(list.data2s[left]->vt.maVT,pivotmaVT)<0) left++;
		while (right>=left&&strcmp(list.data2s[right]->vt.maVT,pivotmaVT)>0) right--;
		if (left>=right) break;
		swap(list, left, right);
		left++; right--;
	}
	swap(list, left, high);
	return left;
};
int partitiondoanhthu(Listdata2 &list, int low, int high){
	float pivot = list.data2s[high]->doanhthu;
	int left = low, right = high-1;
	while (true){
		while (left<=right&&list.data2s[left]->doanhthu<pivot) left++;
		while (right>=left&&list.data2s[right]->doanhthu>pivot) right--;
		if(left>=right) break;
		swap(list, left, right);
		left++; right--;
	}
	swap(list, left, high);
	return left;
};
void quicksort(Listdata2 &list, int low, int high, int chedo){
	if(low<high){
		int pi;
		if(chedo==1) pi = partitiondoanhthu(list, low, high);
		else pi = partitionmaVT(list, low, high);
		quicksort(list, low, pi-1, chedo);
		quicksort(list, pi+1, high, chedo);
	}
};
void free(Listdata1 &list){
	for (int i=0; i<list.n; i++)
		delete list.data1s[i];
	list.n = 0;
};
void free(Listdata2 &list){
	for (int i=0; i<list.n; i++)
		delete list.data2s[i];
	list.n = 0;
	list.sort = 0;
};
void xuli(Listdata1 &list1, Listdata2 &list2, const Date &date1, const Date &date2){
	if(list1.n!=0) free(list1);
	if(list2.n!=0) free(list2);
	ListNhanVien list;
	if(readFileNV(list, DEFAULT_NVFILE)!=1) cout<<"Loi doc file";
	PTRVatTu head = NULL, node = NULL;
	if(ReadFile(head)!=1) cout<<"Loi doc file";
	NhanVien nv;
	HoaDon hd;
	CT_HD ct;
	Info info;
	int i,j;
	for (i=0; i<list.n; i++){
		nv = *list.nhanViens[i];
		for (hd = nv.hoaDons->phead; hd!=NULL; hd = hd->next){
			info = hd->info;
			if(cmpDate(info.ngayLap, date1)>=0&&cmpDate(info.ngayLap, date2)<=0){
				addListdata1(list1, info, nv.ho + " " + nv.ten);
				if(info.loai=='X')
					for (j=0; j<info.listct->n; j++){
						ct = info.listct->ct[j];
						node = Search(head, ct.maVT);
						addListdata2(list2, node->vatTu, ct);
					}
			}
		}
	}
	free(list);
	freePTRVatTu(head);
	quicksort(list2, 0, list2.n-1, 1);
	list2.sort=1;
};
