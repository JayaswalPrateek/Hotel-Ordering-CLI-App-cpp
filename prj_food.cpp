#include<iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
using namespace std;
void setcolor(WORD color);
int main (int argc, char *argv[])
{
    //to make console full screen
    system("mode con COLS=700");
ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000);

    //to calculate console size for alignment
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
   GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;


   //prints welcome
   cout<<"\n\n";
   for(int i=0;i<columns;i++)
    cout<<"=";
    cout<<"\n";
    int c=columns-7;

        for(int i=0;i<c/2;i++)
            cout<<" ";
        cout<<"WELCOME"<<endl;
         for(int i=0;i<columns;i++)
    cout<<"=";
    cout<<"\n\n";
    setcolor(10);//uses function defined below
    int c2 = c-23;//23 can be replaced by length of new string generated when actual day is specfied
     for(int i=0;i<c2/2;i++)
            cout<<" ";
            cout<<"SPECIAL DISCOUNT TODAY!"<<endl;
              cout<<"\n\n";






   //removing details like time etc
   getchar();


   return(0);
}
void setcolor(WORD color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}
