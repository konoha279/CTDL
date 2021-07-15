#pragma once
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
//=====Ten Ham=====//
bool isNumber(char c);
bool isAlphabet(char c);
bool isBlackchar(char c);
void trim(string &a);
void chuan_hoa(string &a);
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
void chuan_hoa(string &a){
	trim(a);
	//xoa space giua (n space -> 1 space)
	for(int i=0; i<a.length(); i++){
		if(a[i]==' ' && a[i+1]==' ') {
			a.erase(a.begin()+i+1);
			i--;
		}
	}
}
