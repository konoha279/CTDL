#include <string>
#include <stdlib.h>
#include <ctime>
using namespace std;
const int DateOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

typedef struct Date{
	int day;
	int month;
	int year;
};

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
	return string(intStrDay) + "/" + string(intStrMonth) + "/" + string(intStrYear);
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


