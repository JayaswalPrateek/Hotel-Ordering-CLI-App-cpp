// todo: userinputhandler03 needs error handling support
#include <iostream>
#include <string>
#include <ctime>
#include <map>
using namespace std;
// int main() is at the end(last function), so no need of multiple function prototypes

void clearScr()
{
    // This is an ANSI Escape Code. It tells the console to flush the screen and reset the cursor. Works on Windows/Linux. src:https://stackoverflow.com/a/32008479
    cout << "\033[2J\033[1;1H";
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
void crash(string loc)
{
    cout << "The program encountered unexpected behaviour at " << loc;
    exit(404);
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
    return str;
}
string lowerCaser(string str)
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}
int stoic(string snum)
{
    int decctr = 1, num = 0;
    for (int i = snum.length() - 1; i >= 0; i--)
    {
        if ((int)(snum.at(i)) >= 48 && (int)(snum.at(i)) <= 57)
        {
            int tar = (int)(snum.at(i));
            int dig = tar - 48;
            num += dig * decctr;
            decctr *= 10;
        }
        else
            return -9132;
    }
    return num;
}
string isItVeg(string checkDish)
{
    int checker = checkDish == "veg" ? 1 : 0;
    checker = checkDish == "nonveg" ? 2 : checker;
    switch (checker)
    {
    case 1:
        return "🟢️";
    case 2:
        return "🔴️";
    default:
        crash("isItVeg()");
    }
}

char *date() // returns current day of the week, depends on <ctime>. Returns address of the variable date which is an array of chars
{
    // creating variables using structs defined under <ctime>
    time_t curr_time;
    tm *curr_tm;

    // date is static, so that it can be returned. src:method 2 on https://www.geeksforgeeks.org/how-to-return-a-local-array-from-a-cpp-function/
    static char date[100];

    // stores current date+time at location of variable curr_tm
    time(&curr_time);                // store time at curr_time
    curr_tm = localtime(&curr_time); // localize the time and store it in curr_tm

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

// struct is a set of properties for one dish and maps are a set of dishes with their own unique set of properties
// src:https://www.w3schools.com/cpp/cpp_structs.asp
struct menu
{                // Structure declaration
    string type; // Member of struct
    string name; // Member of struct
    int cost;    // Member of struct
};
struct bill
{                // Structure declaration
    string type; // Member of struct
    string name; // Member of struct
    int cost;    // Member of struct
    int qty;     // Member of struct
};

int userInputHandler01()
{
    cout << "--> ";
    string choice = lowerCaser(fetchVar());
    if (choice == "yes")
        return 1;
    else if (choice == "no")
        return 2;
    else if (choice == "q")
        quit();
    else
        cout << "Invalid Input!\n\n";
    return 0;
}

map<int, menu> setMenuVeg() // src:https://stackoverflow.com/a/50146252
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
    return vegMenu;
}
map<int, menu> setMenuNonVeg()
{
    map<int, menu> vegMenu = setMenuVeg();
    int vegLen = vegMenu.size(); // src:https://www.tutorialspoint.com/map-size-in-cplusplus-stl
    map<int, menu> nonVegMenu = setMenuVeg();
    nonVegMenu[vegLen + 1] = {"nonveg", "Chicken Burger", 300};
    nonVegMenu[vegLen + 2] = {"nonveg", "Chicken Wings", 200};
    nonVegMenu[vegLen + 3] = {"nonveg", "Chicken Pizza", 400};
    nonVegMenu[vegLen + 4] = {"nonveg", "Chicken Sandwich", 200};
    nonVegMenu[vegLen + 5] = {"nonveg", "Chicken Curry", 350};
    nonVegMenu[vegLen + 6] = {"nonveg", "Fish    Curry", 300};
    return nonVegMenu;
}
map<int, menu> decideMenu()
{
    while (true)
    {
        cout << "Are you Vegan? Answer with 'yes' or 'no', 'q' to quit" << endl;
        int choice = userInputHandler01();
        if (choice == 1)
            return setMenuVeg();
        else if (choice == 2)
            return setMenuNonVeg();
    }
}
void printMenu(map<int, menu> menumap)
{
    map<int, menu>::iterator i;
    cout << "╔═══════════════════════════════════════╗" << endl;
    cout << "║                                       ║" << endl;
    cout << "║              Our Menu 🤤              ║" << endl;
    cout << "║                                       ║" << endl;
    cout << "║═══════════════════════════════════════║" << endl;
    for (i = menumap.begin(); i != menumap.end(); i++)
    {
        if ((*i).first < 10)
            if ((*i).second.name.length() < 11)
                cout << "║ " << (*i).first << "  ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t\t║ ₹ " << (*i).second.cost << " ║";
            else
                cout << "║ " << (*i).first << "  ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t║ ₹ " << (*i).second.cost << " ║";
        else if ((*i).second.name.length() < 11)
            cout << "║ " << (*i).first << " ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t\t║ ₹ " << (*i).second.cost << " ║";
        else
            cout << "║ " << (*i).first << " ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t║ ₹ " << (*i).second.cost << " ║";
        cout << "\n";
    }
    cout << "╚═══════════════════════════════════════╝\n\n";
}

void wannabuy()
{
    while (true)
    {
        cout << "Do you want to order anything from the menu? Answer with 'yes' or 'no', Enter 'q' to quit" << endl;
        int choice = userInputHandler01();
        if (choice == 1)
            break;
        else if (choice == 2)
            quit();
    }
}

int userInputHandler02(int lim)
{
    cout << "--> ";
    string choice = lowerCaser(fetchVar());
    if (choice == "done")
        return 1;
    else if (choice == "q")
        quit();
    else
    {
        int num = stoic(choice);
        if (num == -9132)
        {
            cout << "'" << choice << "' is an invalid input!" << endl;
            return 0;
        }
        if (num < 0)
        {
            cout << choice << " is an inappropriate input!" << endl;
            return 0;
        }
        if (num > lim)
        {
            cout << choice << " is out of range!" << endl;
            return 0;
        }
        return num + 1234;
    }
}

int userInputHandler03()
{
    string choice = fetchVar();
    int num = stoic(choice);
    if (num == -9132)
    {
        cout << num << " is an invalid input!" << endl;
        return 0;
    }
    if (num < 0)
    {
        cout << num << " is an inappropriate input!" << endl;
        return 0;
    }
    return num + 1234;
}

map<int, bill> takeOrder(map<int, menu> menumap)
{
    map<int, bill> billmap;
    cout << "Instructions :" << endl;
    cout << " *\tEnter 'DISH NUMBER' to add the dish to the cart" << endl;
    cout << " *\tEnter 'DONE' to checkout" << endl;
    cout << " *\tPress 'q' to quit\n\n";
    while (true)
    {
        int choice = userInputHandler02(menumap.size());
        if (choice == 0)
            continue;
        if (choice == 1)
            if (billmap.size() != 0)
                return billmap;
            else
                cout << "No Dishes ordered, instead press 'q' to quit" << endl;
        else
        {
            choice -= 1234;
            int howMany = 0;
            while (true)
            {
                cout << "How many " << menumap.at(choice).name << " do you want? " << endl;
                howMany = userInputHandler03();
                if (howMany == 0)
                    continue;
                howMany -= 1234;
                break;
            }
            bool skipflag = false;
            map<int, bill>::iterator i;
            for (i = billmap.begin(); i != billmap.end(); i++)
            {
                if ((*i).second.name == menumap.at(choice).name)
                {
                    if (howMany == 0)
                    {
                        cout << menumap.at(choice).name << " was not added to cart, alrady " << billmap.at(choice).qty << " in cart";
                        skipflag = true;
                        break;
                    }
                    (*i).second.qty += howMany;
                    (*i).second.cost = (*i).second.qty * menumap.at(choice).cost;
                    cout << "Added " << howMany << " " << menumap.at(choice).name << " in cart, now " << (*i).second.qty << " in cart" << endl;
                    skipflag = true;
                    break;
                }
            }
            if (!skipflag && howMany != 0)
            {
                billmap[billmap.size() + 1] = {menumap.at(choice).type, menumap.at(choice).name, (menumap.at(choice).cost * howMany), howMany};
                cout << "Added " << howMany << " " << menumap.at(choice).name << " to cart" << endl;
            }
            else if (!skipflag && howMany == 0)
                cout << menumap.at(choice).name << " was not added to cart";
        }
    }
}

int main()
{
    clearScr();
    greet();
    map<int, menu> menumap = decideMenu();
    clearScr();
    printMenu(menumap);
    wannabuy();
    clearScr();
    printMenu(menumap);
    takeOrder(menumap);
    return 0;
}
