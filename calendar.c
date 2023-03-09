#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#define LT 218
#define LB 192
#define RT 191
#define RB 217
#define LST 195
#define RST 180
#define TT 194
#define BT 193
#define CROSS 197
#define VL 179
#define HL 196
#define SP 32
#define BS 8
#define TOTCOLS 80
#define TOTROWS 25
#define DIM 7
#define WIDTH 5

int isLeap(int year)
{
    return (((year%4==0)&&(year%100!=0))||(year%400==0))?1:0;
}
int DayOfWeek( int y, int m, int d ) /* returns Day of Week:
0 = Sunday, 1= Monday...
*/
{
static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
y -= m < 3;
return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
} /*--DayOfWeek( )--------*/
void gotoxy(int x, int y);
void drawDabba()
{

    int row;
    int col;
    int ctr1;
    int ctr2;
    int ctr3;
    col = (TOTCOLS - ( (DIM * WIDTH) + (DIM+1) ))/2;
    row = (TOTROWS - (DIM * 2 + 1))/2;
    gotoxy(col, row);
    printf("%c", LT);
    for( ctr2 = 0; ctr2 < DIM ; ctr2+=1)
    {
         for( ctr1 = 0; ctr1 < WIDTH ; ctr1+=1)
              printf("%c", HL);

          printf("%c", TT);

    }
    printf("%c",BS);
    printf("%c", RT);
    for( ctr3 = 0 ; ctr3 < DIM; ctr3 +=1)
    {
        row+=1;
    gotoxy(col, row);
    for( ctr2 = 0; ctr2 <= DIM; ctr2+=1)
    {

        printf("%c", VL);
        for( ctr1 = 0; ctr1 < WIDTH ; ctr1+=1)
              printf("%c", SP);

    }
    row+=1;
    gotoxy(col, row);
    printf("%c", LST);
    for(ctr2 = 0; ctr2 < DIM; ctr2 +=1)
    {
        for( ctr1 = 0; ctr1 < WIDTH ; ctr1+=1)
              printf("%c", HL);
         printf("%c", CROSS);

    }
    printf("%c",BS);
    printf("%c", RST);
    }
    gotoxy(col, row);
    printf("%c", LB);
    for( ctr2 = 0; ctr2 < DIM ; ctr2+=1)
    {
         for( ctr1 = 0; ctr1 < WIDTH ; ctr1+=1)
              printf("%c", HL);

          printf("%c", BT);

    }
    printf("%c",BS);
    printf("%c", RB);

}
void colHeading()
{
    int row;
    int col;
    int ctr;
    char *day_names [] = {"SUN","MON","TUE","WED","THU","FRI","SAT"};
    col = (TOTCOLS - ( (DIM * WIDTH) + (DIM+1) ))/2;
    row = (TOTROWS - (DIM * 2 + 1))/2;
    row+=1;
    col+=2;
    for(ctr = 0 ; ctr < 7; ctr+=1)
    {
        gotoxy(col+(ctr * (WIDTH+1)), row);
        printf("%s", day_names[ctr]);
    }

}
void printCalendar(int yyyy, int mm)
{

    int row;
    int col;
    int month_day_ctr;
    int week_day_ctr;
    int max_days;
    char *month_names [] = {"","January","February","March","April","May","June",\
    "July","August","September","October","November","December"};
     int nod_in_month[ ] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    col = (TOTCOLS - ( (DIM * WIDTH) + (DIM+1) ))/2;
    row = (TOTROWS - (DIM * 2 + 1))/2;
    row+=3;
    col+=3;
    gotoxy(32, 3);
    printf("%10s , %d", month_names [ mm ], yyyy);
    if ( isLeap(yyyy) == 1)
        nod_in_month [ 2] = 29;
    week_day_ctr = DayOfWeek(yyyy,mm,1);
    max_days = nod_in_month [ mm ];
    for( month_day_ctr = 1; month_day_ctr <= max_days; month_day_ctr +=1, week_day_ctr+=1)
    {
        if ( week_day_ctr == DIM)
        {
            week_day_ctr = 0;
            row+=2;
        }
         gotoxy(col + (6 * week_day_ctr), row);

        printf("%02d", month_day_ctr);
    }





}
void cleanCalendar()
{

    int row;
    int col;
    col = (TOTCOLS - ( (DIM * WIDTH) + (DIM+1) ))/2;
    row = (TOTROWS - (DIM * 2 + 1))/2;

    row+=3;
    col+=3;
    int r;
    int c;
    for( r= 0 ; r < DIM; r+=1,row+=2)
    {
        for( c= 0; c < DIM; c +=1)
        {
            gotoxy(col + (c*6), row);
            printf("  ");
        }
    }




}

int main()
{
    int year;
    int month;
    int key1;
    int key2;
    year = 2023;
    month = 3;

   drawDabba();
   colHeading();
   while ( 1 )
   {
   printCalendar(year, month);
   key1 = getch();
   if ( key1 == 27 ) break;
   key2 = getch();
   cleanCalendar();
   switch(key2)
   {
       case 75 : month-=1; break;
       case 77 : month+=1; break;
       case 80 : year += 1; break;
       case 72 : year -= 1; break;
       case 71 : month = 1; break;
       case 79 : month = 12; break;
   }
   if ( month < 0)
   {
       year-=1;
       month=12;
   }
   if ( month > 12)
   {
       month = 1;
       year+=1;
   }
}
    return EXIT_SUCCESS;
}

void gotoxy(int x, int y)
{
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

