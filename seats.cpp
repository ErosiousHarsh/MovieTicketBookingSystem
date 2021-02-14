#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    int a[8][15];
    ofstream fin;
    fin.open("seats.dat",ios::out);
    if(!fin)
    {
        cout << "Error";
    }
    int c=1;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<15;j++)
        {
            a[i][j]=c;
            cout << c << " ";
            c++;
        }
        cout << endl;
    }

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<15;j++)
        {
            fin << a[i][j] << " ";
        }
        fin << endl;
    }
    cout << "-----------------------------------------------------------------------------------------" << endl;
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<15;j++)
        {
            //cout << a[i][j] << "   ";
            printf("|%-3d| ",a[i][j]);
        }
        cout << endl;
    }
        cout << "-----------------------------------------------------------------------------------------" << endl;
    fin.close();
}
