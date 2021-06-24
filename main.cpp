#include "NhanVien.h"
int main(){
	NhanVien nv;
	nv.maNV = 1;
	nv.ho = "Hoang";
	nv.ten = "Long";
	nv.phai = 0;
	nv.hoaDons = new ListHoaDon;
	cout<<toString(nv);
	return 0;
}
