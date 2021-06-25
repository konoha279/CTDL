#include "MyDate.h"
using namespace std;

#define MAXLIST 20
#define MAX_SO_HD 20
#define MAX_MAVT 10

typedef struct CT_HoaDon{
	string soHD;
	string maVT;
	int soLuong;
	int donGia;
	int VAT;
};

typedef struct InfoHoaDon{
	string soHD;
	int maNV;
	Date ngayLap;
	char loai; //chi nhan gia tri 'N'hoac'X'
	CT_HoaDon *ct;
};

typedef struct hoadon{
	InfoHoaDon info;
	hoadon *next;
}; 

typedef struct hoadon *HoaDon;

typedef struct DSHoaDon{
	HoaDon phead = NULL;
	HoaDon ptail = NULL;
};

typedef struct ListCT_HoaDon{
	int soVatTu = 0;
	CT_HoaDon *list[MAXLIST];
};

/*==============================================================================*\
						/*phuong thuc cua CT_HoaDon*/

//tra ve 1 la rong,0 la ko rong
int empty(ListCT_HoaDon &ds){
	return ds.soVatTu == 0;
}

//tra ve 1 la full,0 la chua full
int full(ListCT_HoaDon &ds){
	return ds.soVatTu == MAXLIST;
}

//them 1 ct vao ds, tra ve 0 la ko them duoc, 1 la them thanh cong
int insert_CTHD(ListCT_HoaDon &ds,CT_HoaDon &ct,int i){
	int j;
	if(i < 0 || i > ds.soVatTu || full(ds)) 
		return 0;
	for(j = ds.soVatTu - 1; j >= i; j--)
		ds.list[j+1] = ds.list[j];
	ds.list[i] = &ct;
	ds.soVatTu++;
	return 1; 
}
//them 1 ct vao cuoi ds, tra ve 0 la ko them duoc, 1 la them thanh cong
int insert_CTHDTail(ListCT_HoaDon &ds,CT_HoaDon &ct){
	int j;
	if(full(ds)) 
		return 0;
	if(empty(ds)){
		ds.list[0] = &ct;
		ds.soVatTu++;
		return 1;
	}
	for(j = 0; j < ds.soVatTu; j++);
	ds.list[j] = &ct;
	ds.soVatTu++;
	return 1; 
}

//xoa 1 ct trong ListCT_HoaDon, ham nay chua KT viec ds nay da duoc luu hay chua
//ham nay co loi
int delete_CTHD(ListCT_HoaDon &ds,string maVT){
	int i;
	if(ds.soVatTu == 0)
		return 0;
	for(i = 0; i < ds.soVatTu || ds.list[i]->maVT.compare(maVT) == 0; i++);
	for(int j = i+1;  j < ds.soVatTu ; j++)
		ds.list[j-1] = ds.list[j];
	ds.soVatTu--;
	return 1;		
}

//ghi vao file 1 ListCT_HoaDon, tra ve 0 la loi, 1 la ghi thanh cong 
int writeFileListCT(ListCT_HoaDon &listCT){
	FILE *fptr;
	if ((fptr = fopen("CT.bin","wb")) == NULL){
		printf("Error! opening file");
		return 0;
	}
	fwrite(&listCT.soVatTu, sizeof(int), 1, fptr);
	for(int i =0; i < listCT.soVatTu; i++){
		fwrite("\n", sizeof(char), 1, fptr);
		fwrite(&listCT.list[i], sizeof(CT_HoaDon), 1, fptr);
	}
		
	fclose(fptr);
	return 1;
}

//doc file ListCT_HoaDon va tra ve 1 ListCT_HoaDon 
ListCT_HoaDon readFileListCT(){
	ListCT_HoaDon list;
	int soLuong;
	char temp;
	FILE *fptr;
	if ((fptr = fopen("CT.bin","rb")) == NULL){
		printf("Error! opening file");
		return list;
	}
	fread(&soLuong, sizeof(int), 1, fptr);
	for(int i = 0; i < soLuong; i++){
		fread(&temp, sizeof(char), 1, fptr);
		fread(&list.list[i], sizeof(CT_HoaDon), 1, fptr);
	}
	fclose(fptr);
	list.soVatTu = soLuong;
	return list;
}

//tra 1 la soHD dat gioi han do dai, 0 la chua
int checkSoHD(string soHD){
	return soHD.length() == MAX_SO_HD;
}
//tra 1 la MaVT dat gioi han do dai, 0 la chua
int checkMaVT(string maVT){
	return maVT.length() == MAX_MAVT;
}

