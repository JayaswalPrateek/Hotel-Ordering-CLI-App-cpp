# PPS Project

## Group Details

|       Name        |   SAP ID    | Roll No. |
| :---------------: | :---------: | :------: |
| Prateek Jayaswal  | 70412200052 |   I036   |
| Vedant Maheshwari | 70412200053 |   I051   |


## Problem Statement

> **The objective of the project is to demonstrate a rubust and full proof programming logic for a menu based ordering system written in c++**


## Code

```cpp
#include "rang.hpp"
using namespace rang;
```

- rang is a single header-only library which is used for coloring the output and adding fancy effects like blinking, inverting, etc.

```cpp
#include <ctime> // to show current day of the week in greet()
#include <map>
```

- ctime is used to show the name of the day of the week in greet() function.
- map is a data type used to make the data structure of menu and bill, both of which are a map of int and a struct.

```cpp
void clearScr()
{
    cout << "\033[2J\033[1;1H";
}
void hideCursor()
{
    cout << "\e[?25l";
}
void showCursor()
{
    cout << "\e[?25h";
}
```

- clearScr() is a function to clear the console screen by printing ANSI escape code.
- hideCursor() and showCursor() are used to hide and show the console cursor respectively by printing ANSI escape code.

```cpp
void crash(string loc)
{
    cout << style::bold << rang::fg::red << style::reversed << "The program encountered unexpected behaviour at " << loc << style::reset << "\n\n";
    exit(404);
}
```

- for debugging crashes and locating the function which caused unexpected behaviour(if any).

```cpp
string trimmer(string x)
{
    if (x[0] == ' ')
    {
        x.erase(0, 1);
        return trimmer(x);
    }
    if (x[x.length() - 1] == ' ')
    {
        x.erase(x.length() - 1, x.length());
        return trimmer(x);
    }
    else
        return x;
}
string fetchVar()
{
    string str;
    hideCursor();
    getline(cin, str);
    return trimmer(str);
}
string lowerCaser(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}
```

- code for normalizing user input throughout the program.
- trimmer() removes leading and trailing spaces from a string.
- getline is alternative to cin. The delimiter for cin is a whitespace and not for getline.
- lowerCaser() returns string in lower case.

```cpp
int stoic(string snum)
{
    int ctr = 1, num = 0;
    for (int i = snum.length() - 1; i >= 0; i--)
        if ((int)(snum.at(i)) >= 48 && (int)(snum.at(i)) <= 57) // checks if char is a number
        {
            int dig = (int)(snum.at(i)) - 48;
            num += dig * ctr;
            ctr *= 10;
        }
        else
            return errCode;
    return num;
}
```

- string to int converter. Similar func available in STL, but needs try-catch. Pun intended(stoicism)

```cpp
string comma(string s)
{
    int l = s.length();
    if (l <= 3)
        return (s);
    string s2 = "," + s.substr(l - 3, 3);
    s = s.substr(0, l - 3);
    int n = s.length();
    if (l % 2 == 1)
    {
        while (n)
        {
            s2 = "," + s.substr(n - 2, 2) + s2;
            s = s.substr(0, n - 2);
            n = s.length();
        }
        return (s2.substr(1, s2.length()));
    }
    while (n > 1)
    {
        s2 = "," + s.substr(n - 2, 2) + s2;
        s = s.substr(0, n - 2);
        n = s.length();
    }
    return (s + s2);
}
```

- adds commas to numbers, so "10000" becomes "10,000"

```cpp
struct menu
{
    string type;
    string name;
    int cost;
};
struct bill
{
    string type;
    string name;
    int cost;
    int qty;
};
```

- structs for menu and bill

```cpp
char *date() // returns current day of the week, depends on <ctime>. Returns pointer to variable date which is an array of chars which is a string
{
    // creating variables using structs defined under <ctime>
    time_t curr_time;
    tm *curr_tm;

    // date is static, so that it can be returned. src:method 2 on https://www.geeksforgeeks.org/how-to-return-a-local-array-from-a-cpp-function/
    static char date[100];

    // stores current date+time at location of variable curr_tm
    time(&curr_time);                // store time at curr_time
    curr_tm = localtime(&curr_time); // localize the time and store it in curr_tm

    // format curr_tm to show only day of the week and store it inside variable date
    strftime(date, 50, "%A", curr_tm);
    return date;
}
```

- date() returns day of the week as a string.

```cpp
map<int, menu> setMenuVeg()
{
    // src:https://www.geeksforgeeks.org/c-map-key-user-define-data-type/
    map<int, menu> vegMenu;
    vegMenu[1] = {"veg", "Burger", 250};
    vegMenu[2] = {"veg", "Fries", 100};
    vegMenu[3] = {"veg", "Pizza", 350};
    vegMenu[4] = {"veg", "Sandwich", 150};
    vegMenu[5] = {"veg", "Soup", 200};
    vegMenu[6] = {"veg", "Noodles", 350};
    vegMenu[7] = {"veg", "Curry", 300};
    vegMenu[8] = {"veg", "Rice", 250};
    // vegMenu[9] = {"veg", "<Name>", <Cost>};
    return vegMenu;
map<int, menu> setMenuNonVeg()
{
    map<int, menu> nonVegMenu = setMenuVeg(); // inherit the veg menu in non veg menu
    int vegLen = nonVegMenu.size();           // store the last key of veg menu src:https://www.tutorialspoint.com/map-size-in-cplusplus-stl
    // append non veg dishes:
    nonVegMenu[vegLen + 1] = {"nonveg", "Chicken Burger", 300};
    nonVegMenu[vegLen + 2] = {"nonveg", "Chicken Wings", 200};
    nonVegMenu[vegLen + 3] = {"nonveg", "Chicken Pizza", 400};
    nonVegMenu[vegLen + 4] = {"nonveg", "Chicken Sandwich", 200};
    nonVegMenu[vegLen + 5] = {"nonveg", "Chicken Curry", 350};
    return nonVegMenu; // src:https://stackoverflow.com/a/50146252
}
```

- creating a map with int as key and struct menu as value

```cpp
map<int, bill> takeOrder(map<int, menu> menumap)
{
    map<int, bill> billmap;
    cout << style::italic << style::reversed << " Instructions: " << style::reset << endl;
    cout << "  ● Enter " << style::bold << "DISH NUMBER" << style::reset << "\tto add the dish to the cart" << endl;
    cout << "  ● Enter " << style::bold << "DONE" << style::reset << "\t\tto checkout" << endl;
    cout << "  ● Press " << style::bold << "q" << style::reset << "\t\tto quit\n\n"
         << style::reset;
    while (true)
    {
        int choice = userInputHandler02(menumap.size());
        if (choice == 0)
            continue;
        if (choice == 1)
            if (billmap.size() != 0) // dont checkout with empty cart
                return billmap;
            else
                cout << style::bold << rang::fgB::red << style::reversed << "Cart is empty!, add something or press 'q' to quit\n\n"
                     << style::reset;
        else
        {
            choice -= 1234; // remove magic
            int howMany;
            while (true)
            {
                cout << style::italic << "How many " << menumap.at(choice).name << " do you want? " << style::reset << style::bold << "--> " << style::reset;
                howMany = userInputHandler03();
                if (howMany == 0)
                    continue;
                howMany -= 1234; // remove magic
                break;
            }
            bool skipflag = false;
            map<int, bill>::iterator i;
            for (i = billmap.begin(); i != billmap.end(); i++)
            {
                if ((*i).second.name == menumap.at(choice).name) // if item already in bill, dont create new entry
                {
                    if (howMany == 0)
                    {
                        cout << style::bold << rang::fgB::yellow << style::reversed << menumap.at(choice).name << " was not added to cart, already " << billmap.at(choice).qty << " in cart\n\n"
                             << style::reset;
                        skipflag = true;
                        break;
                    }
                    if (howMany + (*i).second.qty > 99)
                    {
                        cout << style::bold << rang::fgB::red << style::reversed << "Maximum 99 dishes per person!\n\n"
                             << style::reset;
                        skipflag = true;
                        break;
                    }
                    (*i).second.qty += howMany;
                    (*i).second.cost = (*i).second.qty * menumap.at(choice).cost;
                    cout << rang::fgB::blue << style::reversed << "Added " << howMany << " " << menumap.at(choice).name << " in cart, now " << (*i).second.qty << " in cart\n\n"
                         << style::reset;
                    skipflag = true;
                    break;
                }
            }
            if (skipflag)
                continue;
            if (howMany != 0) // create new entry if item not in bill already and howmany =/= 0
            {
                billmap[billmap.size() + 1] = {menumap.at(choice).type, menumap.at(choice).name, (menumap.at(choice).cost * howMany), howMany};
                cout << style::italic << rang::fgB::blue << style::reversed << "Added " << howMany << " " << menumap.at(choice).name << " to cart\n\n"
                     << style::reset;
            }
            else if (howMany == 0) // dont create new entry if item not in bill already but howmany==0
                cout << style::bold << rang::fgB::yellow << style::reversed << menumap.at(choice).name << " was not added to cart\n\n"
                     << style::reset;
        }
    }
}
```

- robust logic for adding items to cart.
- doesn't let user checkout the cart if items in cart is 0.
- when user enters choice of dish, it checks if the same dish already exists in cart.
- if user enters qty=0, no items is added; when qty<0, error is shown and when qty>0 then updated qty is shown.

```cpp
map<int, bill> letsDel(map<int, bill> billmap, int lim)
{
    clearScr();
    printBill(billmap);
    int history[lim], appendCtr = 0;
    int billLen = billmap.size();
    cout << style::italic << style::reversed << "\nInstructions " << style::reset << endl;
    cout << "  ● Enter " << style::bold << "DISH NUMBER" << style::reset << "\tto remove the dish from the cart" << endl;
    cout << "  ● Enter " << style::bold << "DONE" << style::reset << "\t\tto save" << endl;
    cout << "  ● Press " << style::bold << "q" << style::reset << "\t\tto quit\n\n";
    while (true)
    {
        int choice = userInputHandler02(billLen);
        if (choice == 0)
            continue;
        if (choice == 1)
        {
            if (billmap.size() != 0) // proceed only if all items are not removed
                return resetKeys(billmap);
            else
            {
                clearScr();
                cout << style::blink << "😭️ " << style::reset << style::bold << "All Items Removed from cart" << style::reset << style::blink << " 😭️" << style::reset << endl;
                cout << style::blink << "☺️  " << style::reset << style::bold << "Thanks for visiting us, do come back later" << style::reset << style::blink << " ☺️" << style::reset << endl;
                showCursor();
                exit(0);
            }
        }
        else
        {
            choice -= 1234;
            bool skipLoop = false;
            for (int i = 0; i < lim; i++)
                if (history[i] == choice)
                {
                    cout << style::bold << rang::fgB::yellow << style::reversed << "dish " << choice << " was already removed from the bill, enter 'DONE' to save and print new bill\n\n"
                         << style::reset;
                    skipLoop = true;
                    break;
                }
            if (skipLoop)
                continue;
            if (billmap.at(choice).qty == 1)
            {
                cout << style::italic << rang::fgB::red << style::reversed << billmap.at(choice).name << " removed from cart\n\n"
                     << style::reset;
                history[appendCtr] = choice;
                billmap.erase(choice); // src:https://www.geeksforgeeks.org/map-erase-function-in-c-stl/
                appendCtr++;
            }
            else
                while (true)
                {
                    cout << style::italic << "There are " << billmap.at(choice).qty << "x " << billmap.at(choice).name << " in cart, how many to remove? " << style::reset << style::bold << "--> ";
                    int howMany = userInputHandler04(billmap.at(choice).qty);
                    if (howMany == 0)
                        continue;
                    howMany -= 1234;
                    if (howMany == 0)
                        cout << style::bold << rang::fgB::yellow << style::reversed << "Qunatity of " << billmap.at(choice).name << " not modified\n\n"
                             << style::reset;
                    else if (howMany == billmap.at(choice).qty)
                    {
                        cout << style::italic << rang::fgB::red << style::reversed << billmap.at(choice).name << " removed from cart\n\n"
                             << style::reset;
                        history[appendCtr] = choice;
                        billmap.erase(choice); // src:https://www.geeksforgeeks.org/map-erase-function-in-c-stl/
                        appendCtr++;
                    }
                    else
                    {
                        billmap.at(choice).cost -= (billmap.at(choice).cost / billmap.at(choice).qty) * howMany;
                        billmap.at(choice).qty -= howMany;
                        cout << style::italic << rang::fgB::blue << style::reversed << billmap.at(choice).qty << "x " << billmap.at(choice).name << " left in cart\n\n"
                             << style::reset;
                    }
                    break;
                }
        }
    }
}
```

- robust logic for removing items from cart.

```cpp
map<int, bill> resetKeys(map<int, bill> billmap) // if dishes 2,3,4 are ordered the bill shows them as 1 2 3, if 1 is removed, new bill shows 2 3 instead of 1 2. Fix:
{
    map<int, bill> newbillmap;
    map<int, bill>::iterator i;
    int assign = 1;
    for (i = billmap.begin(); i != billmap.end(); i++, assign++)
        newbillmap[assign] = {(*i).second.type, (*i).second.name, (*i).second.cost, (*i).second.qty};
    return newbillmap;
}
```

- reset order of keys of maps after deletion

## Code
[Our code is available on github.com](https://github.com/JayaswalPrateek/ppsSem1project/blob/main/main.cpp "main.cpp")

## Tech Used

- Markdown
- Github
- VSCode
- Linter
- [Rang](https://github.com/agauniyal/rang)


## Algorithm

1. START
2. DISPLAY WELCOME MESSAGE
3. INPUT MENU CHOICE
4. DISPLAY RELEVANT MENU
5. USER ENTERS ITEM NUMBER AND QUANTITY
6. ENTERED ITEMS AND QUANTITY ARE ADDED TO CART
7. USER WANTS TO DELETE ITEMS?
8. If yes
9. ENTER ITEMS AND QUANTITY USER WANTS TO DELETE
10. DELETE ITEMS AND QUANTITY FROM CART
11. DISPLAY BILL
12. If no
13. go to step 11
14. STOP

## Flowchart

![alt text](https://raw.githubusercontent.com/JayaswalPrateek/ppsSem1project/main/flowchart.png)

## Demo

![](https://raw.githubusercontent.com/JayaswalPrateek/ppsSem1project/main/demo.gif)

## Conclusion

> **Thus a interactive food ordering, menu based rubust program has been written in c++**
