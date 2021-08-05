#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
string ChuSo[10]{ " khong", " mot", " hai", " ba"," bon", " nam", " sau", " bay", " tam", " chin" };
string Tien[6]{ "", " nghin", " trieu", " ty", " nghin ty", " trieu ty" };
//=====Ten Ham=====//
bool isNumber(char c);
bool isAlphabet(char c);
bool isBlackchar(char c);
void trim(string &a);
void chuan_hoa_so(string &a);

bool isNumber(char c){
	return (48<=c&&c<=57);
};
bool isAlphabet(char c){
	return ((65<=c&&c<=90)||(97<=c&&c<=122));
};
bool isBlackchar(char c){
	string blacklist= "!@#$%^&*()|=<>:;'+`~{}[]";
	for (int i=0; i<blacklist.length(); i++)
		if(c==blacklist[i]) return true;
	return false;
}
void trim(string &a){
	while(a[0] == ' ') a.erase(a.begin()+0);//xoa space dau
	while(a[a.length()-1] == ' ') a.erase(a.length()-1);//xoa space cuoi
}
void chuan_hoa_so(string &a){
	trim(a);
	while(a[0] == '0') a.erase(a.begin()+0);//xoa so 0 dau
}


string DocSo3ChuSo(int baso)
{
	int tram, chuc, donvi;
	string KetQua = "";
	tram = (int)(baso / 100);
	chuc = (int)((baso % 100) / 10);
	donvi = baso % 10;
	if ((tram == 0) && (chuc == 0) && (donvi == 0)) return "";
	if (tram != 0)
	{
		KetQua += ChuSo[tram] + " tram";
		if ((chuc == 0) && (donvi != 0)) KetQua += " linh";
	}
	if ((chuc != 0) && (chuc != 1))
	{
		KetQua += ChuSo[chuc] + " muoi";
		if ((chuc == 0) && (donvi != 0)) KetQua = KetQua + " linh";
	}
	if (chuc == 1) KetQua += " muoi";
	switch (donvi)
	{
	case 1:
	{
		if ((chuc != 0) && (chuc != 1))
		{
			KetQua += " mot";
		}
		else
		{
			KetQua += ChuSo[donvi];
		}
		break;
	}
	case 5:
	{
		if (chuc == 0)
		{
			KetQua += ChuSo[donvi];
		}
		else
		{
			KetQua += " lam";
		}
		break;
	}
	default:
	{
		if (donvi != 0)
		{
			KetQua += ChuSo[donvi];
		}
		break;
	}
	}
	return KetQua;
}

string DocTienBangChu(long SoTien, string strTail)
{
	int lan, i;
	long so;
	string KetQua = "", tmp = "";
	int* ViTri = new int[6];
	if (SoTien < 0) return "So am";
	if (SoTien == 0) return "Khong " + strTail;
	if (SoTien > 0)
	{
		so = SoTien;
	}
	else
	{
		so = -SoTien;
	}

	if (SoTien > 8999999999999999)
	{
		SoTien = 0;
		return "";
	}
	ViTri[5] = (int)(so / 1000000000000000);
	so = so - ViTri[5] * 1000000000000000;
	ViTri[4] = (int)(so / 1000000000000);
	so = so - ViTri[4] * +1000000000000;
	ViTri[3] = (int)(so / 1000000000);
	so = so - ViTri[3] * 1000000000;
	ViTri[2] = (int)(so / 1000000);
	ViTri[1] = (int)((so % 1000000) / 1000);
	ViTri[0] = (int)(so % 1000);
	if (ViTri[5] > 0)
	{
		lan = 5;
	}
	else if (ViTri[4] > 0)
	{
		lan = 4;
	}
	else if (ViTri[3] > 0)
	{
		lan = 3;
	}
	else if (ViTri[2] > 0)
	{
		lan = 2;
	}
	else if (ViTri[1] > 0)
	{
		lan = 1;
	}
	else
	{
		lan = 0;
	}
	for (i = lan; i >= 0; i--)
	{
		tmp = DocSo3ChuSo(ViTri[i]);
		KetQua += tmp;
		if (ViTri[i] != 0) KetQua += Tien[i];
		//if ((i > 0) && (!tmp.empty())) KetQua += ",";
	}
	//if (KetQua.substr(KetQua.length() - 1, 1) == ",") KetQua = KetQua.substr(0, KetQua.length() - 1);
	trim(KetQua);
	KetQua = KetQua + " " + strTail;
	return KetQua.substr(0, 1) + KetQua.substr(1);
}
