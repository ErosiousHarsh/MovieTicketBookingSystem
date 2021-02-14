#include<stdio.h>
#include<string.h>
#include<fstream>
#include<iostream>
using namespace std;
class prog
{
	public:
    string n;
	void show_movies()
	{
		ifstream fin;
		string r;
		fin.open("movies.txt",ios::in);
		cout << "Available movies are:" << endl;
		while(!fin.eof())
		{
			getline(fin,r);
			cout << r << endl;
		}
		fin.close();
	}
	void search_movies()
	{
	    int c;
	    ifstream fin;
		string r;
		fin.open("movies.txt",ios::in);
	    cout << "Input movie name to search" << endl;
        getline(cin,n);
        cout << n;
        while(!fin.eof())
		{
			getline(fin,r);
			if(r.compare(n)==1)
            {
                c=1;
                break;
            }
            else
            {
                c=0;
            }
		}
		fin.close();
		if(c==1)
        cout << " Found" << endl;
        if(c==0)
        cout << " Not Found" << endl;
	}
	void book_tickets()
	{

	}
};
int main()
{
	prog pr;
	pr.show_movies();
	pr.search_movies();
	return 0;
}
