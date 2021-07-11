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
