#pragma once
#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;
const int DateOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
//=====struct====//
struct Date{
	int day;
	int month;
	int year;
};
//=====Ten Ham=====//
bool ktNamNhuan(int year);
bool ktNamNhuan(Date date);
string convertDateToString(Date date);
Date convertStringToDate(string strDate);
Date getDateNow();
int cmpDate(Date d1,Date d2);
int ktDate(Date date);
//=====Ham=====//
//chia het cho 4 va ko het cho 100 hoac chia het cho 400 la nam nhuan
bool ktNamNhuan(int year){
    return (((year % 4 == 0) && (year % 100 != 0)) || 
        (year % 400 == 0)); 
}

bool ktNamNhuan(Date date){
    return (((date.year  % 4 == 0) && (date.year % 100 != 0)) || 
        (date.year % 400 == 0)); 
}

string convertDateToString(Date date){
    char bufferDay[5];
    char bufferMonth[5];
    char bufferYear[5];
    char *intStrDay = itoa(date.day,bufferDay,10);
    char *intStrMonth = itoa(date.month,bufferMonth,10);
    char *intStrYear = itoa(date.year,bufferYear,10);
    string strDay = string(intStrDay);
    string strMonth = string(intStrMonth);
    if(strDay.length() < 2 )
        strDay = "0"+strDay;
    if(strMonth.length() < 2 )
        strMonth = "0"+strMonth;    
    return strDay + "/" + strMonth + "/" + string(intStrYear);
}

Date convertStringToDate(string strDate){
	Date date;
	int indexDay = strDate.find("/");
	string strDay = strDate.substr(0,indexDay);
	int indexMonth = strDate.find("/",indexDay+1); 
	string strMonth;
	switch(indexMonth-indexDay){
		case 2:
		{
			strMonth = strDate.substr(indexDay+1,1);		
			break;
		}
		case 3:
		{
			strMonth = strDate.substr(indexDay+1,2);		
			break;
		}
	}
	string strYear = strDate.substr(indexMonth+1,4);
	date.day = atoi(strDay.c_str());
	date.month = atoi(strMonth.c_str());
	date.year = atoi(strYear.c_str());
	return date;
}

Date getDateNow(){
	time_t now = time(0);
	tm *ltm = localtime(&now);
	Date date;
	date.day = ltm->tm_mday;
	date.month = 1 + ltm->tm_mon;
	date.year = 1900 + ltm->tm_year;
	return date;
}

int cmpDate(Date d1,Date d2){
	if(d1.year > d2.year) 
		return 1;
	else if(d1.year == d2.year)
		if(d1.month > d2.month) 
			return 1;
		else if(d1.month == d2.month)
			if(d1.day > d2.day) 
				return 1;
			else if(d1.day == d2.day) 
				return 0;
	return -1;
}

int ktDate(Date date){
    if(date.year < 2000)
        return 1;// 1 la loi sai nam
    if(ktNamNhuan(date.year)){
        if(date.month == 2 && (date.day <= 0 || date.day > 29))
            return 3; // 3 la loi sai ngay
        else if(date.month == 2 && (date.day > 0 && date.day <= 29))
            return 0; // 0 la hop le
    }    
    else{
        if(date.month == 2 && (date.day <= 0 || date.day > 28))
            return 3; // 3 la loi sai ngay
        else if(date.month == 2 && (date.day > 0 && date.day <= 28))
            return 0;
    }    
    switch(date.month){
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
        {
            if(date.day <= 0 || date.day > 31)
                return 3;
            break;
        }
        case 4:
        case 6:
        case 9:
        case 11:
        {
            if(date.day <= 0 || date.day > 30)
                return 3;
            break;
        }
        default :
            return 2; // 2 la sai thang
    }
    return 0; // 0 la hop le
}
