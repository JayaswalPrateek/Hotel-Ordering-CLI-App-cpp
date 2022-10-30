#include <iostream>
#include <string>
using namespace std;
string comma(string s)
{


   int l = s.length();
   if(l<=3)
    return(s);
   string s2 = ","+s.substr(l-3,3);
   s = s.substr(0,l-3);
   int n = s.length();
   if(l%2==1)
   {
   while(n)
   {
        s2 = ","+s.substr(n-2,2)+s2;
        s = s.substr(0,n-2);
        n = s.length();
   }
   return (s2.substr(1,s2.length()));
   }
   while(n>1)
   {
        s2 = ","+s.substr(n-2,2)+s2;
        s = s.substr(0,n-2);
        n = s.length();

   }
   return (s+s2);
}
int main()
{
    string s;
    cout<<"ENTER STRING: ";
    cin>>s;
    cout<<comma(s);


}
