#include<stdio.h>
#include<stdlib.h>
int is_leap_year(int year);
int dayofweek(int year,int month);
void pri_cal(int year, int month,int week);
int each_month_last_date[]={31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//それぞれの月の最終日
int main()
{
	int year,month;
	int week;
	
	printf("年を西暦4桁(1860〜9999)、月を1桁または2桁(1〜12)で入力\n");
	printf("年==>");
	scanf("%d", &year);
	printf("月==>");
	scanf("%d",&month);
	
	week = dayofweek(year, month);
	
    pri_cal(year,month,week);

  	return 0;
}
// うるう年の判定関数(1:うるう年 0:平年)
int is_leap_year(int year)
{
	if(year%100 != 0 && year%4 == 0) 
	{
		return 1;
	}
    else if(year%400 == 0) 
	{
        return 1;
	}
    else 
	{
    	return 0;
  	}
}
//曜日判定関数
int dayofweek(int year, int month){
	int i;
	int year_days = 0;
	int month_days;
   	for (i = 1860; i < year; i++)//年の経過日数を求める		
	{
	   	if (is_leap_year(i)==1)
		{
			year_days=year_days+366;
		}
		else if (is_leap_year(i)==0)
		{
			year_days=year_days+365;	
		}
   	}
   	for (i = 1; i < month; i++)//月の経過日数を求める
	{
	   	month_days = each_month_last_date[ i - 1 ];
	   	if (i == 2 && is_leap_year(year) == 1)
		{ 
			month_days = 29;
		}
		year_days = year_days + month_days;
	}
	year_days = year_days % 7;
	if(year>9999 || year<1860 || month>12 || month<1)
	{
      	return -1;
    }
   	return year_days;
}
//カレンダー出力関数
void pri_cal(int year,int month,int week){
	
	int i;
	int calendar_blank_part;//カレンダーの空白部分
   	int days = each_month_last_date[ month - 1 ];//配列は0からなので-1
	
	if(week==-1)
	{
		printf("入力された数値は誤っています．もう一度実行してください．");
		printf("\n");
		exit(1);
	}
	
	printf("\n  %d年　%d月\n",year,month);
	printf( "\n  日 月 火 水 木 金 土\n" );
	if (is_leap_year(year) == 1 && month == 2)
	{
		days = 29;
	}
	for (i = 0; i < week; i++)//余りの数だけハイフンを出力 
	{
		printf("  -");
	}
	for (i = 1; i <= days; i++)//7文字出力したら改行
	{
		printf( "%3d", i );
		week = (week + 1) % 7;
		if (week == 0) 
		{
			printf("\n");
		}
	} 
	//空白が残っていたら空白の数だけハイフンを出力
	 if(week!=0)
	 {
		 for(calendar_blank_part=0;calendar_blank_part<(7-week);calendar_blank_part++)
		 {
			printf("  -");
		 }
		 printf("\n");
	 }
	 printf( "\n" );
}