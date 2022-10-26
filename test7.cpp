#include <iostream>
using namespace std;
int main()
{
    int flag =0;

    //Array A
    int r1,c1;
    cout<<"ENTER NO. OF ROWS IN MATRIX A: ";
    cin>>r1;
    cout<<"ENTER NO. OF COLUMNS IN MATRIX A: ";
    cin>>c1;
      int a[r1][c1];
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c1;j++)
        {
           int n;
           cout<<"ENTER VALUE: ";
           cin>>n;
           a[i][j]=n;

        }
    }
    cout<<"\n"<<"MATRIX A: "<<endl;
    for(int i=0;i<r1;i++)
    {
        for(int j=0;j<c1;j++)
        {
           cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    //Array B
    int r2,c2;
    cout<<"ENTER NO. OF ROWS IN MATRIX B: ";
    cin>>r2;
    cout<<"ENTER NO. OF COLUMNS IN MATRIX B: ";
    cin>>c2;
      int b[r2][c2];
    for(int i=0;i<r2;i++)
    {
        for(int j=0;j<c2;j++)
        {
           int n;
           cout<<"ENTER VALUE: ";
           cin>>n;
           b[j][i]=n;

        }
    }
    cout<<"\n"<<"MATRIX B: "<<endl;
    for(int i=0;i<r2;i++)
    {
        for(int j=0;j<c2;j++)
        {
           cout<<b[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n";

    //compatibility check
    if(c1==r2)
    {
        cout<<"MATRICES ARE COMPATIBLE FOR MULTIPLICATION"<<endl;
        flag=1;
    }
    else
    {
        cout<<"MATRICES ARE  NOT COMPATIBLE FOR MULTIPLICATION"<<endl;
    }

    //multiplication
    if(flag)
    {
         int m[r1][c2];
        for(int i = 0; i < r1; ++i)
            for(int j = 0; j < c2; ++j)
            {
                m[i][j]=0;
            }
        for(int i = 0; i < r1; ++i)
        {
            for(int j = 0; j < c2; ++j)
            {
                for(int k = 0; k < c1; ++k)
                {
                    m[i][j] += a[i][k] * b[k][j];
                }
            }
        }
         cout<<"\n"<<"MATRIX M: "<<endl;
        for(int i=0;i<r1;i++)
        {
            for(int j=0;j<c2;j++)
            {
            cout<<m[i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";

    }
    return 0;
}

