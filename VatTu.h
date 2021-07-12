#pragma once
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <string.h>
#define MAX_NV 500
#define MAX_HO 32
#define MAX_TEN 10

struct VatTu
{
	char maVT[10];
	char tenVT[50];
	char dvt[10];
	int soLuongTon;
};

struct NodeVatTu
{
	VatTu vatTu;
	NodeVatTu *left;
	NodeVatTu *right;
};
typedef NodeVatTu* PTRVatTu;

void InsertVatTu(PTRVatTu &p, VatTu vt);
int SoSanhVatTu(VatTu vt1, VatTu vt2);
void CreateTree(PTRVatTu &root);
void remove_case_3(PTRVatTu &r);
void remove(VatTu vt, PTRVatTu &p);
PTRVatTu Search(PTRVatTu root, VatTu vt);
bool isExistVatTu(char *maVT, PTRVatTu p);
void Preorder(PTRVatTu p);

void InsertVatTu(PTRVatTu &p, VatTu vt)
{
	if (isExistVatTu(vt.maVT, p))
	{
		printf("[-] San pham da ton tai!\n\n");
		return;
	}
	if (p == NULL)
	{
		p = new NodeVatTu;
		p->vatTu = vt;
		p->left = NULL;
		p->right = NULL;
	}
	else
	{
		if (SoSanhVatTu(p->vatTu, vt) == 1)
		{
			InsertVatTu(p->left, vt);
		}
		else if (SoSanhVatTu(p->vatTu, vt) == -1)
		{
			InsertVatTu(p->right, vt);
		}
		else p->vatTu.soLuongTon += vt.soLuongTon;
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
		else return strcmp(vt1.tenVT, vt2.tenVT);
	}
	else return strcmp(vt1.maVT, vt2.maVT);
}

void CreateTree(PTRVatTu &root)
{


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

void remove(VatTu vt, PTRVatTu &p)
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

PTRVatTu Search(PTRVatTu root, VatTu vt)
{
	PTRVatTu p;
	p = root;

	while (p != NULL && !SoSanhVatTu(vt, p->vatTu))
		if (SoSanhVatTu(vt, p->vatTu) == -1)
			p = p->left;
		else
			p = p->right;

	return p;
}

bool isExistVatTu(char *maVT, PTRVatTu p)
{
	if (p == NULL)
	{
		return false;
	}
	else
	{
		if (strcmp(maVT, p->vatTu.maVT) == -1)
			isExistVatTu(maVT, p->left);
		else if (strcmp(maVT, p->vatTu.maVT) == 1)
			isExistVatTu(maVT, p->right);
		else if (!strcmp(maVT, p->vatTu.maVT))
			return true;
	}
}

void InorderVatTu(PTRVatTu p)
{
	if (p != NULL)
	{
		InorderVatTu(p->left);
		printf(" %5s | %50s | %5s | %d \n", p->vatTu.maVT, p->vatTu.tenVT, p->vatTu.dvt, p->vatTu.soLuongTon);
		
		InorderVatTu(p->right);
	}
}

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
		InsertVatTu(Head, vt);
	}
	fclose(f);
}
