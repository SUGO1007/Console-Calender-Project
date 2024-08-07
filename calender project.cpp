#include<iostream>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

#define LT 218
#define RT 191
#define LB 192
#define RB 217
#define LST 195
#define RST 180
#define CROSS 197
#define TT 194
#define BT 193
#define SPACE 32
#define HL 196
#define VL 179
#define WIDTH 5
#define TOTCOL 80
#define TOTROW 25
#define BS 8
#define DIM 7
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80


void gotoxy (int x,int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}


void draw_table()
{
	int row;
	int col;	
	int ctr1;
	int ctr2;
	int ctr3;
	
	row = (TOTROW - (DIM + (DIM + 1)))/2;
	col = (TOTCOL - ((WIDTH * DIM) + (DIM + 1)))/2;
	gotoxy(col,row);
	
	printf("%c",LT);
	
	for(ctr2 = 0; ctr2<DIM; ctr2++)
	{
		for(ctr1 = 0; ctr1<WIDTH; ctr1++)
		{
			printf("%c",HL);
		}
		printf("%c",TT);
	}
	
	printf("%c%c",BS,RT);
	
	for(ctr3 = 0; ctr3<DIM; ctr3++)
	{
		row++;
		gotoxy(col,row);
		printf("%c",VL);
		for(ctr2 =0; ctr2<DIM;ctr2++)
		{
			for(ctr1 =0; ctr1<WIDTH; ctr1++)
			{
				printf("%c",SPACE);
			}
			printf("%c",VL);
		}
		row++;
		gotoxy(col,row);
		printf("%c",LST);
		
		for(ctr1 = 0; ctr1<DIM; ctr1++)
		{
			for(ctr2 = 0; ctr2<WIDTH; ctr2++)
			{
				printf("%c",HL);
			}
			printf("%c",CROSS);
		}
		printf("%c%c",BS,RST);
	}
	
    gotoxy(col,row);
    printf("%c",LB);	
	for(ctr2 = 0; ctr2<DIM; ctr2++)
	{
		for(ctr1 = 0; ctr1<WIDTH; ctr1++)
		{
			printf("%c",HL);
		}
		printf("%c",BT);
	}
	printf("%c%c",BS,RB);
	
	
}

void ColHeadings()
{
	int row;
	int col;
	int ctr1;
	char* days[] = {"SUN","MON","TUE","WED","THU","FRI","SAT"}; 
	
	row = (TOTROW - ((DIM) + (DIM+1)))/2;
	col = (TOTCOL - ((DIM*WIDTH)+DIM+1))/2;
	row+=1;
	col+=2;
	for(ctr1 = 0; ctr1<DIM; ctr1++)
	{
		gotoxy(col,row);
		printf("%s",days[ctr1]);
	 	col+= DIM-1;	
	}
}

int DayOfWeek( int y, int m, int d ) //returns Day of Week:0 = Sunday, 1= Monday...
{
	static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
} //--DayOfWeek( )--------//

void cleaner ()
{
	int row;
	int col;
	int week;
	int ctr;	
	row = (TOTROW - ((DIM) + (DIM+1)))/2;
	col = (TOTCOL - ((DIM*WIDTH)+DIM+1))/2;	
	row+=3;
	col+=3;
	
	for (week = 0; week <6; week += 1)
    {
        for(ctr = 0; ctr <DIM; ctr += 1)
        {
            gotoxy(col + (ctr * (WIDTH+1)) , row);
            printf("  ");
        }
        row+=2;
    }    
}

void Calender (int month, int year)
{
	int row;
	int col;
	row = (TOTROW - ((DIM) + (DIM+1)))/2;
	col = (TOTCOL - ((DIM*WIDTH)+DIM+1))/2;
	int date;
	int ctr;	
	int month_days[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
	char* months[] = {"","January","February","March","April","May","June","July","August","September","October","November","December"};
	gotoxy(30,3);
	printf("%10s %d",months[month],year);
	cleaner();
	
	row +=3;
	col +=3;
	if((year%400==0) ||(year%4==0 && year%100!=0))
	{
		month_days[2] = 29;
	}
	
	for(date = 1,ctr = DayOfWeek(year,month,1) ; date<=month_days[month]; date++,ctr++)
	{		
		gotoxy(col + (WIDTH + 1) * ctr,row);
		printf("%2d",date);
		if(ctr == DIM-1)
		{
			row+=2;
			ctr = -1;
		}
	}
}

int main()
{
	int month = 10;
	int year  = 2003;
	int key;
	draw_table();
	ColHeadings();	
//	getch();
	
	do
	{
	  Calender(month,year);
	  key = getch();
	  if(key == 13)
	  {
	  	break;
	  }
	  key = getch();
	  
	  switch(key)
	  {
	  	case LEFT :
	  		month--;
	  		if(month<1)
	  		{
	  			month = 12;
	  			year--;
			}	  		 
	  		break;
	  	case RIGHT :
		    month++;
		    if(month>12)
		    {
		    	month = 1;
		    	year++;
			}
			break;
		case UP :
		    year--;
			break;
		case DOWN :
		    year++;
		    break;
	  }
	}while(key!=13);	
	
} 
