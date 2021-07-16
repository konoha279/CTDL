#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h>
#define MAX_NV 500
#define MAX_HO 32
#define MAX_TEN 10
#define MAX_LIST 10000
#define MAX_MAVT 10
#define MAX_TENVT 50
#define MAX_DVT 10
#define MAX_SL_TON 6
int sizeVatTu = 0;
struct VatTu
{
	char maVT[11];
	char tenVT[51];
	char dvt[11];
	int soLuongTon;
};

struct NodeVatTu
{
	VatTu vatTu;
	NodeVatTu *left;
	NodeVatTu *right;
};

typedef NodeVatTu* PTRVatTu;

struct mangVatTu
{
	int n =0;
	PTRVatTu arr[MAX_LIST];
};

int InsertVatTu(PTRVatTu &p, VatTu vt);
int SoSanhVatTu(VatTu vt1, VatTu vt2);
void remove_case_3(PTRVatTu &r);
void remove(VatTu vt, PTRVatTu &p);
PTRVatTu Search(PTRVatTu root, VatTu vt);
bool isExistVatTu(char *maVT, PTRVatTu p);
void InorderVatTu(PTRVatTu p);
void InorderVatTuWithCount(PTRVatTu p, int i);
void InChiTiet(PTRVatTu p, FILE *f);
void InFile(PTRVatTu Head);
void ReadFile(PTRVatTu &Head);
void add(mangVatTu &arr, PTRVatTu p);
void ListToArray(PTRVatTu p, mangVatTu &arr);
void swapVatTu(PTRVatTu p1, PTRVatTu p2);
int SoSanhTenVatTu(PTRVatTu p1, PTRVatTu p2);
int partition (mangVatTu arr, int low, int high);
int QuicksortVatTu(mangVatTu arr, int low, int high);

int InsertVatTu(PTRVatTu &p, VatTu vt) //tham vat tu
{
	if (isExistVatTu(vt.maVT, p))
	{
		return 0;
	}
	if (p == NULL)
	{
		p = new NodeVatTu;
		p->vatTu = vt;
		p->left = NULL;
		p->right = NULL;
		return 1;
	}
	else
	{
		if (SoSanhVatTu(p->vatTu, vt) == 1)
		{
			return InsertVatTu(p->left, vt);
		}
		else if (SoSanhVatTu(p->vatTu, vt) == -1)
		{
			return InsertVatTu(p->right, vt);
		}
	}
}

int SoSanhVatTu(VatTu vt1, VatTu vt2)
{
	if (!strcmp(vt1.maVT, vt2.maVT))
	{
		if (!strcmp(vt1.tenVT, vt2.tenVT))
		{
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

void remove_case_3(PTRVatTu &r)
{
	if (r->left == NULL)
		remove_case_3(r->left);
	else
	{
		PTRVatTu rp = r;
		rp->vatTu = r->vatTu;
		rp = r;
		r = rp->right;
	}
}

void remove(VatTu vt, PTRVatTu &p) //xoa vat tu
{
	if (p == NULL)
		printf("Khong tim thay");
	else
		if (SoSanhVatTu(vt, p->vatTu) == -1) remove(vt, p->left);
		else if (SoSanhVatTu(vt, p->vatTu) == 1) remove(vt, p->right);
		else
		{
			PTRVatTu rp = p;
			if (rp->right == NULL) p = rp->left;
			else if (rp->left == NULL) p = rp->right;
			else remove_case_3(rp->right);
			delete rp;
		}
}

PTRVatTu Search(PTRVatTu root, VatTu vt) //tim kiem vat tu
{
	PTRVatTu p;
	p = root;

	while (p != NULL && !SoSanhVatTu(vt, p->vatTu))
		if (SoSanhVatTu(vt, p->vatTu) < 0)
			p = p->left;
		else
			p = p->right;

	return p;
}

bool isExistVatTu(char *maVT, PTRVatTu p) //kiem tra su ton tai cua ma vat tu
{
	if (p == NULL)
	{
		return false;
	}
	else
	{
		if (strcmp(maVT, p->vatTu.maVT) > 0)
			return isExistVatTu(maVT, p->left);
		else if (strcmp(maVT, p->vatTu.maVT) < 0)
			return isExistVatTu(maVT, p->right);
		else if (!strcmp(maVT, p->vatTu.maVT))
			return true;
	}
}

//--------------------------------------------- xuat ra man hinh ---------------------------------------------------

void InorderVatTu(PTRVatTu p)
{
	if (p != NULL)
	{
		InorderVatTu(p->left);
		printf(" %5s | %-50s | %-5s | %d \n", p->vatTu.maVT, p->vatTu.tenVT, p->vatTu.dvt, p->vatTu.soLuongTon);
		
		InorderVatTu(p->right);
	}
}

void InorderVatTuWithCount(PTRVatTu p, int i)
{
	if (p != NULL && i - 1 >=0)
	{
		i--;
		InorderVatTuWithCount(p->left, i);
		printf(" %5s | %-50s | %-5s | %d \n", p->vatTu.maVT, p->vatTu.tenVT, p->vatTu.dvt, p->vatTu.soLuongTon);
		InorderVatTuWithCount(p->right, i);
	}
}

// ------------------------------------------------------- in file doc file ----------------------------------------

void InChiTiet(PTRVatTu p, FILE *f)
{
	if (p != NULL)
	{
		InChiTiet(p->left, f);
		fwrite(&p->vatTu, sizeof(struct VatTu), 1, f);
		
		InChiTiet(p->right, f);
	}
}

void InFile(PTRVatTu Head)
{
	FILE *f = fopen("vattu.dat", "wb");
	InChiTiet(Head,f);
	fclose(f);	
}


void ReadFile(PTRVatTu &Head)
{
	FILE *f;
	f = fopen("vattu.dat", "rb");
	VatTu vt;
	while (!feof(f))
	{
		fread(&vt, sizeof(struct VatTu), 1, f);
		if (InsertVatTu(Head, vt)) sizeVatTu++;
	}
	fclose(f);
}

//------------------------------------------------- chuyen danh sach vao mang ------------------------------

void add(mangVatTu &arr, PTRVatTu p)
{
	arr.arr[arr.n] = p;
	arr.n++;
}

void ListToArray(PTRVatTu p, mangVatTu &arr)
{
	if (p!= NULL)
	{
		ListToArray(p->left, arr);
		add(arr,p);
		ListToArray(p->right, arr);
	}
}

//-------------------------------------------------sap xep-------------------------------------------------

void swapVatTu(PTRVatTu p1, PTRVatTu p2)
{
	VatTu tmp = p1->vatTu;
	p1->vatTu = p2->vatTu;
	p2->vatTu = tmp;
}

int SoSanhTenVatTu(PTRVatTu p1, PTRVatTu p2)
{
	if (strcmp(p1->vatTu.tenVT, p2->vatTu.tenVT) < 0)
		return -1;
	else if (strcmp(p1->vatTu.tenVT, p2->vatTu.tenVT) > 0)
		return 1;
	else
		return 0;
}

int partition (mangVatTu arr, int low, int high)
{
    PTRVatTu pivot = arr.arr[high];
    int left = low;
    int right = high - 1;
    while(true){
        while(left <= right && SoSanhTenVatTu(arr.arr[left], pivot)  == -1 ) left++;
        while(right >= left && SoSanhTenVatTu(arr.arr[left], pivot)  == 1) right--;
        if (left >= right) break;	
        swapVatTu(arr.arr[left], arr.arr[right]);
        left++;
        right--;
    }
    swapVatTu(arr.arr[left], arr.arr[high]);
    return left;
}

int QuicksortVatTu(mangVatTu arr, int low, int high)
{
	if (arr.n <= 0)
		return -1;
	if (low < high)
    {
        int pi = partition(arr, low, high);
        QuicksortVatTu(arr, low, pi - 1);
        QuicksortVatTu(arr, pi + 1, high);
    }
}

//--------------------------------------------------------------------------------------------------
