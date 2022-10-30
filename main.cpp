#include <iostream>
#include <string>
#include <ctime>
#include <map>
#include "dep/rang.hpp"
using namespace std;
using namespace rang;

// #### SHORT & REUSABLE FUNCTIONS STARTED ####
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
    exit(0); // stop program with exit code = 0, ie. program stopped without any crashes
}
void crash(string loc) // for debugging crashes and finding function which caused unexpected behaviour
{
    cout << "The program encountered unexpected behaviour at " << loc;
    exit(404);
}
string fetchVar() // standard function for normalizing inputs
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
string lowerCaser(string str) // returns string in lower case
{
    for (int i = 0; i < str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}
int stoic(string snum) // converts string to int. Similar func available in STL, but needs try-catch. Pun intended(stoicism)
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
            return -2147483647; // returns magic number to signal error(largest value of an int)
    return num;
}
string isItVeg(string checkDish)
{
    if (checkDish == "veg")
        return "🟢";
    else if (checkDish == "nonveg")
        return "🔴";
    else
        crash("isItVeg()"); // probably misplled veg/nonveg in "type" member of struct
}
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
// #### SHORT & REUSABLE FUNCTIONS OVER ####

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

    // format curr_tm to show only day of the week and store it inside date
    strftime(date, 50, "%A", curr_tm);
    return date;
}
void greet()
{
    // cout << bg::green
    //      << "This text has green background." << bg::reset << endl
    //      << bg::red << "This text has red background." << bg::reset << endl
    //      << bg::black << "This text has black background." << bg::reset << endl
    //      << bg::yellow << "This text has yellow background." << bg::reset
    //      << endl
    //      << bg::blue << "This text has blue background." << bg::reset << endl
    //      << bg::magenta << "This text has magenta background." << bg::reset
    //      << endl
    //      << bg::cyan << "This text has cyan background." << bg::reset << endl
    //      << bg::gray << fg::black << "This text has gray background."
    //      << bg::reset << style::reset << endl;
    cout << "WELCOME\n\n";
    char *today;
    today = date();
    cout << "🎊️ " << today << " Exclusive Offers! 🎊️\n\n";
    cout << "Enjoy discounts on all dishes every " << today << "\n\n";
}

// struct is a set of properties for one dish and maps are a set of dishes with their own unique set of properties
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

int userInputHandler01() // yes/no/q
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

// creating 2 maps with int as key and struct menu as value
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
    // vegMenu[9] = {"veg", "<Name>", Cost};
    return vegMenu; // src:https://stackoverflow.com/a/50146252
}
map<int, menu> setMenuNonVeg()

{
    map<int, menu> nonVegMenu = setMenuVeg(); // inherit the veg menu
    int vegLen = nonVegMenu.size();           // store the last key of veg menu src:https://www.tutorialspoint.com/map-size-in-cplusplus-stl
    // append non veg dishes to vegmenu:
    nonVegMenu[vegLen + 1] = {"nonveg", "Chicken Burger", 300};
    nonVegMenu[vegLen + 2] = {"nonveg", "Chicken Wings", 200};
    nonVegMenu[vegLen + 3] = {"nonveg", "Chicken Pizza", 400};
    nonVegMenu[vegLen + 4] = {"nonveg", "Chicken Sandwich", 200};
    nonVegMenu[vegLen + 5] = {"nonveg", "Chicken Curry", 350};
    return nonVegMenu;
}
map<int, menu> decideMenu()
{
    while (true)
    {
        cout << "Are you Vegan? Answer with 'yes' / 'no', Press 'q' to quit" << endl;
        int choice = userInputHandler01();
        if (choice == 1)
            return setMenuVeg();
        else if (choice == 2)
            return setMenuNonVeg();
    }
}
void printMenu(map<int, menu> menumap) // CAUTION : very large dish name COULD break alignment :(
{
    map<int, menu>::iterator i;
    cout << "╔═══════════════════════════════════════╗" << endl;
    cout << "║                                       ║" << endl;
    cout << "║            🤤 Our Menu 🤤             ║" << endl;
    cout << "║                                       ║" << endl;
    cout << "║═══════════════════════════════════════║" << endl;
    for (i = menumap.begin(); i != menumap.end(); i++)
    {
        if ((*i).first < 10)                    // align dish number
            if ((*i).second.name.length() < 11) // align dish name
                cout << "║ " << (*i).first << "  ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t\t║ ₹ " << (*i).second.cost << " ║";
            else
                cout << "║ " << (*i).first << "  ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t║ ₹ " << (*i).second.cost << " ║";
        else if ((*i).second.name.length() < 11) // align dish number & dish name
            cout << "║ " << (*i).first << " ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t\t║ ₹ " << (*i).second.cost << " ║";
        else
            cout << "║ " << (*i).first << " ║ " << isItVeg((*i).second.type) << "  " << (*i).second.name << " \t║ ₹ " << (*i).second.cost << " ║";
        cout << "\n";
    }
    cout << "╚═══════════════════════════════════════╝\n\n";
}

void wannaBuy()
{
    while (true)
    {
        cout << "Do you want to order anything from our menu? Answer with 'yes' / 'no', Press 'q' to quit" << endl;
        int choice = userInputHandler01();
        if (choice == 1)
            break;
        else if (choice == 2)
            quit();
    }
}

int userInputHandler02(int lim) // done/q/<+ve int less than len of menumap>
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
        if (num == -2147483647 || num == 0)
        {
            cout << "'" << choice << "' is an invalid input!\n\n";
            return 0;
        }
        if (num > lim)
        {
            cout << choice << " is out of range!\n\n";
            return 0;
        }
        return num + 1234; // adding 1234 coz item 1 might be interpreted as DONE
    }
}

int userInputHandler03() //<int grtr than/equal to 0 and less than 100>
{
    string choice = fetchVar();
    int num = stoic(choice);
    if (num == -2147483647)
    {
        cout << choice << " is an invalid input!\n\n";
        return 0;
    }
    if (num > 99)
    {
        cout << "Maximum 99 dishes per person!\n\n";
        return 0;
    }
    return num + 1234; // adding 1234 coz 0 might be misinterpreted
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
            if (billmap.size() != 0) // dont checkout with empty cart
                return billmap;
            else
                cout << "Cart is empty!, add something or press 'q' to quit\n\n";
        else
        {
            choice -= 1234; // remove magic
            int howMany;
            while (true)
            {
                cout << "How many " << menumap.at(choice).name << " do you want? --> ";
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
                        cout << menumap.at(choice).name << " was not added to cart, alrady " << billmap.at(choice).qty << " in cart\n\n";
                        skipflag = true;
                        break;
                    }
                    if (howMany + (*i).second.qty > 99)
                    {
                        cout << "Maximum 99 dishes per person!\n\n";
                        skipflag = true;
                        break;
                    }
                    (*i).second.qty += howMany;
                    (*i).second.cost = (*i).second.qty * menumap.at(choice).cost;
                    cout << "Added " << howMany << " " << menumap.at(choice).name << " in cart, now " << (*i).second.qty << " in cart\n\n";
                    skipflag = true;
                    break;
                }
            }
            if (!skipflag && howMany != 0) // create new entry if item not in bill already and howmany =/= 0
            {
                billmap[billmap.size() + 1] = {menumap.at(choice).type, menumap.at(choice).name, (menumap.at(choice).cost * howMany), howMany};
                cout << "Added " << howMany << " " << menumap.at(choice).name << " to cart\n\n";
            }
            else if (!skipflag && howMany == 0) // dont create new entry if item not in bill already but howmany=0
                cout << menumap.at(choice).name << " was not added to cart\n\n";
        }
    }
}

int printBill(map<int, bill> billmap)
{
    int total;
    map<int, bill>::iterator i;
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║                                              ║" << endl;
    cout << "║                🧂 Your Bill 💰               ║" << endl;
    cout << "║                                              ║" << endl;
    cout << "║══════════════════════════════════════════════║" << endl;
    string print, tab = "\t", sep = "║", ws = " ";
    for (i = billmap.begin(); i != billmap.end(); i++)
    {
        // aligning dish numbers
        if ((*i).first < 10)
            print = sep + ws + to_string((*i).first) + ws + ws + sep + ws + isItVeg((*i).second.type) + ws + (*i).second.name + tab;
        else if ((*i).first >= 10)
            print = sep + ws + to_string((*i).first) + ws + sep + ws + isItVeg((*i).second.type) + ws + (*i).second.name + tab;

        // aligning dish names
        if ((*i).second.name.length() < 5)
            print += tab + tab + ws + sep + ws + "x" + to_string((*i).second.qty);
        else if ((*i).second.name.length() <= 13 && (*i).second.name.length() > 5)
            print += tab + ws + sep + ws + "x" + to_string((*i).second.qty);
        else if ((*i).second.name.length() > 13)
            print += ws + sep + ws + "x" + to_string((*i).second.qty);
        else
            print += tab + tab + ws + sep + ws + "x" + to_string((*i).second.qty);

        // aligning dish qty
        if ((*i).second.qty < 10)
            print += ws + ws + sep;
        else if ((*i).second.qty < 100)
            print += ws + sep;

        // aligning dish qty * dish price
        if ((*i).second.cost < 1000)
            print += ws + to_string((*i).second.cost) + ws + ws + ws + sep;
        else if ((*i).second.cost < 10000)
            print += ws + to_string((*i).second.cost) + ws + ws + sep;
        else if ((*i).second.cost < 100000)
            print += ws + to_string((*i).second.cost) + ws + sep;

        cout << print << endl;
        total += (*i).second.qty * (*i).second.cost;
    }
    cout << "║══════════════════════════════════════════════╝" << endl;
    cout << "║ Total Cost: ₹ " << comma(to_string(total)) << "/-" << endl;
    cout << "╚═══════════════════════════════════════════════" << endl;

    return total;
}

map<int, bill> letsDel(map<int, bill> billmap, int lim);
map<int, bill> wannaDel(map<int, bill> billmap, int lim)
{
    while (true)
    {
        cout << "\nDo you want to remove anything from your bill? Answer with 'yes' / 'no', Press 'q' to quit" << endl;
        int choice = userInputHandler01();
        if (choice == 1)
        {
            billmap = letsDel(billmap, lim);
            clearScr();
            printBill(billmap);
        }
        else if (choice == 2)
            return billmap;
    }
}
int userInputHandler04(int lim)
{
    string choice = fetchVar();
    int num = stoic(choice);
    if (num == -2147483647 || num < 0)
    {
        cout << "'" << choice << "' is an invalid input!\n\n";
        return 0;
    }
    if (num > lim)
    {
        cout << choice << " is out of range!\n\n";
        return 0;
    }
    return num + 1234; // adding 1234 coz 0 might be misinterpreted
}
map<int, bill> letsDel(map<int, bill> billmap, int lim)
{
    clearScr();
    printBill(billmap);
    int history[lim], appendCtr = 0;
    int billLen = billmap.size();
    cout << "\nInstructions :" << endl;
    cout << " *\tEnter 'DISH NUMBER' to remove the dish from the cart" << endl;
    cout << " *\tEnter 'DONE' to save" << endl;
    cout << " *\tPress 'q' to quit\n\n";
    bool skipLoop = false;
    while (true)
    {
        int choice = userInputHandler02(billLen);
        if (choice == 0)
            continue;
        if (choice == 1)
        {
            if (billmap.size() != 0)
                return billmap;
            else
            {
                clearScr();
                cout << "😭️ All Items Removed from cart 😭️" << endl;
                cout << "Thanks for visiting us, do come back later 😚️";
                showCursor();
                exit(0);
            }
        }
        else
        {
            choice -= 1234;
            for (int i = 0; i < lim; i++)
                if (history[i] == choice)
                {
                    cout << "dish " << choice << " was already removed from the bill, enter 'DONE' to save and print new bill\n\n";
                    skipLoop = true;
                    break;
                }
            if (skipLoop)
                break;
            if (billmap.at(choice).qty == 1)
            {
                cout << billmap.at(choice).name << " removed from cart\n\n";
                history[appendCtr] = choice;
                billmap.erase(choice); // src:https://www.geeksforgeeks.org/map-erase-function-in-c-stl/
                appendCtr++;
            }
            else
            {
                while (true)
                {
                    cout << "There are " << billmap.at(choice).qty << "x " << billmap.at(choice).name << " in cart, how many to remove? --> ";
                    int howMany = userInputHandler04(billmap.at(choice).qty);
                    if (howMany == 0)
                        continue;
                    howMany -= 1234;
                    if (howMany == 0)
                        cout << "Qunatity of " << billmap.at(choice).name << " not modified\n\n";
                    else if (howMany == billmap.at(choice).qty)
                    {
                        cout << billmap.at(choice).name << " removed from cart\n\n";
                        history[appendCtr] = choice;
                        billmap.erase(choice); // src:https://www.geeksforgeeks.org/map-erase-function-in-c-stl/
                        appendCtr++;
                    }
                    else
                    {
                        billmap.at(choice).cost -= (billmap.at(choice).cost / billmap.at(choice).qty) * howMany;
                        billmap.at(choice).qty -= howMany;
                        cout << billmap.at(choice).qty << "x " << billmap.at(choice).name << " left in cart\n\n";
                    }
                    break;
                }
            }
        }
    }
}

void asktoPay(int amt)
{
    while (true)
    {
        cout << "Proceed to pay ₹" << amt << "? Confirm with 'yes' or 'no', Press 'q' to quit" << endl;
        int choice = userInputHandler01();
        if (choice == 1)
            break;
        else if (choice == 2)
            quit();
    }
}

void logOrder(string name, map<int, bill>, int total)
{
    // code to create order history by creating a file called <name>.txt with billmap and total in it.
}

void transact()
{
}

void thankYou()
{
    cout << "\n\n\n\nThank YOU!";
}

int main()
{
    clearScr();
    greet();
    string name;
    cout << "Enter Your Name: ";
    cin >> name;
    map<int, menu> menumap = decideMenu();
    clearScr();
    printMenu(menumap);
    wannaBuy();
    clearScr();
    printMenu(menumap);
    map<int, bill> billmap = takeOrder(menumap);
    clearScr();
    int total = printBill(billmap);
    billmap = wannaDel(billmap, menumap.size());
    clearScr();
    total = printBill(billmap);
    asktoPay(total);
    transact();
    logOrder(name, billmap, total);
    thankYou();
    return 0;
}
