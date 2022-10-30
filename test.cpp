#include "dep/rang.hpp"
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace rang;
using namespace std;



void greet()
{
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(),SW_MAXIMIZE);
    SendMessage(GetConsoleWindow(),WM_SYSKEYDOWN,VK_RETURN,0x20000000);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    cout<<"\n\n";

    for(int i=0;i<columns;i++)
    cout<<fg::red<<"=";

    cout<<"\n";
    int c=columns-46;

    for(int i=0;i<c/2;i++)
        cout<<bg::yellow<<fg::black<<" ";
    cout<<" _    _ _____ _     _____ ________  ___ _____ ";
    for(int i=c/2+46;i<columns;i++)
        cout<<" ";
        cout<<"\n";

    for(int i=0;i<c/2;i++)
        cout<<" ";
    cout<<"| |  | |  ___| |   /  __ \\  _  |  \\/  ||  ___|";
    for(int i=c/2+46;i<columns;i++)
        cout<<" ";
        cout<<"\n";

    for(int i=0;i<c/2;i++)
        cout<<" ";
    cout<<"| |  | | |__ | |   | /  \\/ | | | .  . || |__  ";
    for(int i=c/2+46;i<columns;i++)
        cout<<" ";
        cout<<"\n";

    for(int i=0;i<c/2;i++)
        cout<<" ";
    cout<<"| |/\\| |  __|| |   | |   | | | | |\\/| ||  __| ";
    for(int i=c/2+46;i<columns;i++)
        cout<<" ";
        cout<<"\n";

    for(int i=0;i<c/2;i++)
        cout<<" ";
    cout<<"\\  /\\  / |___| |___| \\__/\\ \\_/ / |  | || |___ ";
    for(int i=c/2+46;i<columns;i++)
        cout<<" ";
        cout<<"\n";

    for(int i=0;i<c/2;i++)
        cout<<" ";
    cout<<" \\/  \\/\\____/\\_____/\\____/\\___/\\_|  |_/\\____/ ";
    for(int i=c/2+46;i<columns;i++)
        cout<<" ";
        cout<<"\n";

    for(int i=0;i<columns;i++)
    cout<<fg::red<<bg::reset<<"=";
    cout<<fg::reset<<"\n";
    int c2 = columns-23;//23 can be replaced by length of new string generated when actual day is specfied
     for(int i=0;i<c2/2;i++)
            cout<<" ";
    cout<<fg::green<<style::blink<<"SPECIAL DISCOUNT TODAY!"<<fg::reset<<endl;




}











int main()
{

greet();
getchar();

}
