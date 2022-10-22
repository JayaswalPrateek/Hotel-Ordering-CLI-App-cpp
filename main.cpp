#include <iostream>
#include <ctime> // to print banner on greet(), eg: <current-day> exclusive offers / sale
using namespace std;
// int main() is at the end(last function), so no need of multiple function prototypes

void clearScr()
{
    // This is an ANSI Escape Code. It tells the console to flush the screen and reset the cursor. Works on Windows/Linux. src:https://stackoverflow.com/a/32008479
    cout << "\033[2J\033[1;1H";
}

char *date() // returns today's day of the week, depends on <ctime>. Returns address of the variable date which is an array of chars
{
    // creating variables using structs defined under <ctime>
    time_t curr_time;
    tm *curr_tm;

    // date is static, so that it can be returned. src:method 2 on https://www.geeksforgeeks.org/how-to-return-a-local-array-from-a-cpp-function/
    static char date[100];

    // stores current date+time at location of variable curr_tm
    time(&curr_time);
    curr_tm = localtime(&curr_time);

    // format curr_tm to show only day of the week and store it inside date
    strftime(date, 50, "%A", curr_tm);
    return date;
}
void greet()
{
    cout << "WELCOME\n\n";
    char *today;
    today = date();
    cout << "🎊️ " << today << " Exclusive Offers! 🎊️\n\n";
    cout << "Enjoy discounts on all dishes every " << today << "\n\n";
}

void hideCursor() // src:https://stackoverflow.com/a/55313602
{
    cout << "\e[?25l";
}
void showCursor() // src:https://stackoverflow.com/a/55313602
{
    cout << "\e[?25h";
}

void quit()
{
    clearScr();
    cout << "Thanks for visiting us, do come back later 😚️";
    showCursor();
    exit(0); // stop program with exit code = 0, ie. program stopped without crashes
}

string fetchVar()
{
    string str;
    hideCursor();
    cin >> str;
    // trimming input
    int i = 0, j = 0;
    while (str[i])
    {
        if (str[i] != ' ')
            str[j++] = str[i];
        i++;
    }
    str[j] = '\0';
    // todo:convert to lowercase
    return str;
}

string isItVeg(string checkDish)
{
    int checker = 0;
    checker = checkDish == "veg" ? 1 : 2;
    switch (checker)
    {
    case 1:
        return "🟢️";
    case 2:
        return "🔴️";
    default:
        return "  ";
    }
}

// src:https://www.w3schools.com/cpp/cpp_structs.asp
struct
{                // Structure declaration
    string type; // Member of struct
    string name; // Member of struct
    int cost;    // Member of struct
} menu;          // Structure variable
struct
{                // Structure declaration
    string type; // Member of struct
    string name; // Member of struct
    int cost;    // Member of struct
    int qty;     // Member of struct
} bill;          // Structure variable

int main()
{
    clearScr(); // clear pre-existing text on console(if any)
    greet();
    return 0;
}
