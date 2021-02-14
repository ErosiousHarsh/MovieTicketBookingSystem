#include <iostream>
#include<fstream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include<cstdlib>
#include<dir.h>
#include<time.h>
using namespace std;
class almost
{
    public:
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;
    int qstate;
    int check()
    {
        conn=mysql_init(0);
        conn=mysql_real_connect(conn,"127.0.0.1","admin","root","cinema",0,NULL,0);
        if(conn)
        {
            cout << "Successfully connected to database." << endl;
            cout << "\n";
            return 1;
        }
        else
        {
            cout << "Please check your connection to mysql server.";
            return 0;
            exit(0);
        }
    }
    void show_movies()
    {
        if(check()==1)
        {
            qstate=mysql_query(conn,"SELECT * FROM MOVIES");
            if(!qstate)
            {
                res=mysql_store_result(conn);
                printf("-----------------------------------------------------------------------------------------------------\n");
                printf("| %-8s | %-22s | %-5s | %-17s | %-11s | %-19s |\n", "Movie Id", "Name", "Year", "Type", "Screen Time", "Release Date");
                printf("-----------------------------------------------------------------------------------------------------\n");
                while(row=mysql_fetch_row(res))
                {
                    printf("| %-8s | %-22s | %-5s | %-17s | %-11s | %-19s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
                }
                cout << "-----------------------------------------------------------------------------------------------------" << endl;
            }
        }
    }
    void book_movies()
    {
        stringstream fi;
        //fstream fin;
        //fin.open("id.dat",ios::out);
        int f;
        int n,r,s_no;
        cout << "Input movie's 'id' number (ex. 1,2,3 etc)" << endl;
        cin >> n;
        fi << n;
        if(check()==1)
        {
            qstate=mysql_query(conn,"SELECT id FROM MOVIES");
            if(!qstate)
            {
                res=mysql_store_result(conn);
                while(row=mysql_fetch_row(res))
                {
                    //fin << row[0] << endl;
                    if(strcmp((fi.str().c_str()),row[0])==0)
                    {
                        f=0;
                        break;
                    }
                    else
                    {
                        //cout << "HERE   " << row[0] << endl << "bd     " << bd.str().c_str() << endl << endl;
                        f=1;
                    }
                }
            }
            /*fin.close();
            fin.open("id.dat",ios::in);
            while(!fin.eof())
            {
                fin >> r;
                if(r==n)
                {
                    f=0;
                    break;
                }
                else
                {
                    f=1;
                }
            }
            fin.close();*/
            if(f==1)
            {
                cout << "Not Found." << endl;
                exit(0);
            }
            if(f==0)
            {
                system("cls");
                cout << "Movie found." << endl;
                cout << "============" << endl;
                cout << "Details about this movie are: " << endl;
                stringstream sql;
                sql << "SELECT * FROM MOVIES WHERE id=" << n;
                qstate=mysql_query(conn,sql.str().c_str());
                if(!qstate)
                {
                    res=mysql_store_result(conn);
                    printf("-----------------------------------------------------------------------------------------------------\n");
                    printf("| %-8s | %-22s | %-5s | %-17s | %-11s | %-19s |\n", "Movie Id", "Name", "Year", "Type", "Screen Time", "Release Date");
                    printf("-----------------------------------------------------------------------------------------------------\n");
                    while(row=mysql_fetch_row(res))
                    {
                        printf("| %-8s | %-22s | %-5s | %-17s | %-11s | %-19s |\n", row[0], row[1], row[2], row[3], row[4], row[5]);
                    }
                    cout << "-----------------------------------------------------------------------------------------------------" << endl;
                }
                stringstream sql_t;
                cout << "Timings of respective movie are: " << endl;
                sql_t << "SELECT * FROM TIMINGS WHERE time_id= " << n;
                int qstate_t=mysql_query(conn,sql_t.str().c_str());
                if(!qstate_t)
                {
                    res=mysql_store_result(conn);
                    while(row=mysql_fetch_row(res))
                    {
                        int st,tc;
                        cout << "1) Day show : " << row[1] << "\n2) Noon/Afternoon Show : " << row[2] << "\n3) Night Show : " << row[3] << endl << endl;
                        cout << "1) ,2) or 3) ?" << endl;
                        cin >> tc;
                        stringstream dir;
                        //dir << "tickets/" << n;
                        //mkdir(dir.str().c_str());
                        //fin.open(dir.str().c_str());
                        //fin.close();
                        dir << "tickets/" << n << "/" << tc << "/" << "seats.dat";
                        //fin.open(dir.str().c_str(),ios::out);
                        //fin.close();
                        //fin.close();
                        //fin.close();
                        cout << "How many seats?" << endl;
                        cin >> st;
                        if(st>=6||st<1)
                        {
                            while(st>6)
                            {
                                cin.clear();
                                cout << "Max number of seats allowed is 6." << endl;
                                cout << "How many seats?" << endl;
                                cin >> st;
                            }
                        }
                        cout << "Here are avialable seats :-" << dir.str().c_str() << endl << endl;
                        ifstream fin;
                        fin.open(dir.str().c_str(),ios::in);
                        int a[8][15];
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                a[i][j]=1;
                            }
                        }
                        if(!fin)
                        {
                            cout << "Error";
                        }
                        //reading the file
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                fin >> a[i][j];
                            }
                        }
                        //displaying the file
                        cout << "-----------------------------------------------------------------------------------------" << endl;
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                //cout << a[i][j];
                                printf("|%-3d| ",a[i][j]);
                            }
                            cout << endl;
                        }
                        cout << "-----------------------------------------------------------------------------------------" << endl;
                        cout << "--------------------------------------SCREEN HERE----------------------------------------" << endl << endl;
                        cout << "SELECT YOUR PLAN :-" << endl;
                        cout << "PRICING IS AS FOLLOWS :-" << endl;
                        cout << "----------------------------------------" << endl;
                        printf("| %-8s | %-8s | %-6s | %-5s |\n","Plan No.","Seat No.","Type","Price");
                        cout << "----------------------------------------" << endl;
                        printf("| %-8s | %-8s | %-6s | %-5s |\n","1.)","1-30","Gold","400/-");
                        printf("| %-8s | %-8s | %-6s | %-5s |\n","2.)","31-90","Silver","300/-");
                        printf("| %-8s | %-8s | %-6s | %-5s |\n","3.)","91-120","Bronze","200/-");
                        cout << "----------------------------------------" << endl;
                        cout << "Select your seat number/s :-" << endl;
                        string f_name,l_name,email;
                        stringstream name;
                        char ph_no[100];
                        struct seat
                        {
                            int s_no;
                            int cost;
                        };
                        seat s[st];
                        int l=(sizeof(s)/sizeof(*s));
                        for(int i=0;i<st;i++)
                        {
                            s[i].s_no=-99;
                        }
                        for(int i=0;i<st;i++)
                        {
                            cout << "Input " << i+1 << "seat no. [1,2,3,etc]" << endl;
                            cin >> s[i].s_no;
                            if(s[i].s_no==0)
                            {
                                cout << "It's already booked." << endl;
                                exit(1);
                            }
                            /*if(s[i-1].s_no==s[i].s_no||s[i].s_no==s[i+1].s_no)
                            {
                                cout << "One seat cannot be selected twice." << endl;
                                exit(1);
                            }*/
                            if(s[i].s_no>=1&&s[i].s_no<=30)
                            s[i].cost=400;
                            else if(s[i].s_no>=31&&s[i].s_no<=90)
                            s[i].cost=300;
                            else if(s[i].s_no>=91&&s[i].s_no<=120)
                            s[i].cost=200;
                        }
                        cout << "                    DO NOT USE SPACES BETWEEN NAME AND EMAIL              " << endl;
                        cout << "Enter your first name." << endl;
                        cin >> f_name;
                        cout << "Enter your last name." << endl;
                        cin >> l_name;
                        name << f_name << "_" << l_name;
                        cout << endl;
                        cout << "Enter your email address." << endl;
                        cin >> email;
                        cout << endl;
                        cout << "Enter your phone number without country code." << endl;
                        cin >> ph_no;
                        system("cls");
                        cout << "SERVERS ARE CURRENTLE UNAVAILABLE" << endl << "PLEASE PAY BY CASH" << endl;
                        int price=0;
                        for(int i=0;i<st;i++)
                        {
                            price+=s[i].cost;
                        }
                        cout << "Your total cost is :" << price << "/-" << endl << endl;
                        int bid,pn;
                        srand(time(0));
                        pn=rand();
                        bid=pn+rand()+rand()+rand();
                        cout << "Your booking id is :" << bid << endl << endl;
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                for(int k=0;k<st;k++)
                                {
                                if(s[k].s_no==a[i][j])
                                a[i][j]=00;
                                }
                            }
                        }
                        /*cout << "Updated Seats are :-" << endl;
                        cout << "-----------------------------------------------------------------------------------------" << endl;
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                //cout << a[i][j];
                                printf("|%-3d| ",a[i][j]);
                            }
                            cout << endl;
                        }
                        cout << "-----------------------------------------------------------------------------------------" << endl;*/
                        ofstream ion;
                        ion.open(dir.str().c_str(),ios::out);
                        if(!ion)
                        {
                            cout << "Error occured try again later.";
                            exit(1);
                        }
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                ion << a[i][j] << " ";
                            }
                            ion << endl;
                        }
                        stringstream sql_a;
                        stringstream srm;
                        for(int i=0;i<st;i++)
                        {
                            srm << s[i].s_no << "-";
                        }
                        //cout << "name is" << name.str() << "\nphone is" << ph_no; //<< "\nnew phone is:" << ph_no.str().c_str();
                        //sql_d="INSERT INTO booking(ticket_id,name,phone,email,m_id,time_id,seats) VALUES ('"+bid+"','"+(string)name+"','"+ph_no+"','"+email+"','"+n+"','"+tc+"','"+s[0].s_no+"')";
                        sql_a << "INSERT INTO booking VALUES('" << bid << "','" << name.str() << "','" << ph_no << "','" << email << "','" << n << "','" << tc << "','" << srm.str().c_str() << "');";
                        qstate_t=mysql_query(conn,sql_a.str().c_str());
                        if(!qstate_t)
                        {
                            cout << "Successfully updated database." << endl << endl;
                        }
                        else
                        {
                            cout << "Error..!!!!" << endl << "Please try again later." << endl;
                        }
                        cout << "Your ticket is :-" << endl;
                        stringstream sp;
                        sp << "SELECT * FROM booking WHERE ticket_id=" << bid;
                        qstate=mysql_query(conn,sp.str().c_str());
                        if(!qstate)
                        {
                            res=mysql_store_result(conn);
                            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                            printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n","Booking id","Name","Phone number","e-mail","Movie id","Time id","Seat/s");
                            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                            while(row=mysql_fetch_row(res))
                            {
                                printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6]);
                            }
                            cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                        }
                    }
                }
            }
        }
    }
    void show_tickets()
    {
        int b_id,sh,fd;
        stringstream bd;
        stringstream ss,ssl;
        //ifstream fin;
        //ofstream fon;
        if(check()==1)
        {
            do
            {
                cout << "Input '1' to seach tickets by booking id." << endl;
                cout << "Input '2' if you've lost your booking id." << endl;
                cout << "Input 9811 to exit." << endl;
                cin >> sh;
                switch(sh)
                {
                    case 1:
                    {
                        cout << "Enter you booking id :-" << endl;
                        cin >> b_id;
                        bd << b_id;
                        int r;
                        stringstream ssl;
                        //ssl << b_id << "_bid.dat";
                        //fon.open(ssl.str().c_str(),ios::out);
                        ssl << "SELECT ticket_id FROM booking";
                        qstate=mysql_query(conn,ssl.str().c_str());
                        if(!qstate)
                        {
                            res=mysql_store_result(conn);
                            while(row=mysql_fetch_row(res))
                            {
                                if(strcmp((bd.str().c_str()),row[0])==0)
                                {
                                    r=1;
                                    break;
                                }
                                else
                                {
                                    //cout << "HERE   " << row[0] << endl << "bd     " << bd.str().c_str() << endl << endl;
                                    r=0;
                                }
                            }
                        }
                        //cout << "bd is:- " << bd.str().c_str() << endl;
                        //cout << "r outside is: " << r << endl << "ssl is :-" << ssl.str().c_str() << endl;
                        /*fin.open(ssl.str().c_str(),ios::in);
                        while(!fon.eof())
                        {
                            fin >> fd;
                            if(fd==b_id)
                            {
                                r=1;
                                break;
                            }4
                            else
                            {
                                r=0;
                            }
                        }
                        fon.close();*/
                        if(r==0)
                        {
                            cout << "Ticket not found." << endl << "Please try again with another method."<< endl;
                        }
                        if(r==1)
                        {
                            system("cls");
                            cout << "Your ticket is :-" << endl;
                            stringstream sp;
                            sp << "SELECT * FROM booking WHERE ticket_id=" << b_id;
                            qstate=mysql_query(conn,sp.str().c_str());
                            if(!qstate)
                            {
                                res=mysql_store_result(conn);
                                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                                printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n","Booking id","Name","Phone number","e-mail","Movie id","Time id","Seat/s");
                                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                                while(row=mysql_fetch_row(res))
                                {
                                    printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6]);
                                }
                                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                            }
                        }
                        exit(1);
                    }
                    case 2:
                    {
                        stringstream so,sp;
                        string fsnm,lsnm;
                        char sem[100],sph[100];
                        int smid,stid;
                        int f;
                        stringstream nm,ph,em,mid,tid,snm;
                        cout << "Data you enter here is case sensitive" << endl;
                        cout << "Enter your first name." << endl;
                        cin >> fsnm;
                        cout << "Enter your last name." << endl;
                        cin >> lsnm;
                        snm << fsnm << "_" << lsnm;
                        cin.clear();
                        cout << "Enter your phone number." << endl;
                        cin >> sph;
                        ph << sph;
                        cin.clear();
                        cout << "Enter your email address." << endl;
                        cin >> sem;
                        em << sem;
                        cin.clear();
                        cout << "Enter your selected movie id." << endl;
                        cin >> smid;
                        mid << smid;
                        cin.clear();
                        cout << "Enter your selected movie time id." << endl;
                        cin >> stid;
                        tid << stid;
                        cout << "Details are :-" << endl;
                        cout << "Name :- " << snm.str().c_str() << endl;
                        cout << "Phone:- " << ph.str().c_str() << endl;
                        cout << "Email :- " << em.str().c_str() << endl;
                        cout << "Movie id :- " << mid.str().c_str() << endl;
                        cout << "Time id :- " << tid.str().c_str() << endl;
                        //so << "SELECT * FROM booking WHERE name='" << nm << "' AND phone='" << ph << "' AND email=" << em << "' AND m_id='" << mid << "' AND time_id='" << tid << "';";
                        so << "SELECT * FROM booking";
                        qstate=mysql_query(conn,so.str().c_str());
                        if(!qstate)
                        {
                            res=mysql_store_result(conn);
                            while(row=mysql_fetch_row(res))
                            {
                                if(strcmp(snm.str().c_str(),row[1])==0&&(strcmp(ph.str().c_str(),row[2])==0)&&(strcmp(em.str().c_str(),row[3])==0)&&(strcmp(mid.str().c_str(),row[4])==0)&&(strcmp(tid.str().c_str(),row[5])==0))
                                {
                                    f=0;
                                    break;
                                }
                                else
                                {
                                    f=1;
                                }
                            }
                        }
                        if(f==1)
                        {
                            cout << "Ticket not found." << endl;
                        }
                        if(f==0)
                        {
                            system("cls");
                            cout << "Ticket found." << endl;
                            sp << "SELECT * FROM booking WHERE name='" << snm.str().c_str() << "' AND phone='" << sph << "' AND email='" << sem << "' AND m_id='" << smid << "' AND time_id='" << stid << "';";
                            //cout << "FIND ERROR    " << sp.str().c_str();
                            qstate=mysql_query(conn,sp.str().c_str());
                            if(!qstate)
                            {
                                res=mysql_store_result(conn);
                                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                                printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n","Booking id","Name","Phone number","e-mail","Movie id","Time id","Seat/s");
                                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                                while(row=mysql_fetch_row(res))
                                {
                                    printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6]);
                                }
                                cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                            }
                        }
                    }
                    break;
                }
            }
            while(sh!=9811);
        }
    }
    void cancel_tickets()
    {
        int p=0;
        string sdf;
        if(check()==1)
        {
            char co[1];
            cout << "Input your booking id";
            cin >> sdf;
            stringstream xr;
            xr << sdf;
            stringstream qr;
            qr << "SELECT ticket_id FROM booking;";
            qstate=mysql_query(conn,qr.str().c_str());
            if(!qstate)
            {
                res=mysql_store_result(conn);
                while(row=mysql_fetch_row(res))
                {
                    if(strcmp(xr.str().c_str(),row[0])==0)
                    {
                        p=1;
                        break;
                    }
                    else
                    p=0;
                }
                if(p==1)
                {
                    cout << "Ticket found" << endl;
                    stringstream pm99;
                    pm99 << "SELECT * FROM booking WHERE ticket_id=" << xr.str().c_str();
                    qstate=mysql_query(conn,pm99.str().c_str());
                    if(!qstate)
                    {
                        res=mysql_store_result(conn);
                        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                        printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n","Booking id","Name","Phone number","e-mail","Movie id","Time id","Seat/s");
                        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                        while(row=mysql_fetch_row(res))
                        {
                            printf("| %-10s | %-17s | %-12s | %-25s | %-8s | %-8s | %-12s |\n",row[0],row[1],row[2],row[3],row[4],row[5],row[6]);
                        }
                        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                    }
                    cout << "Do you really want to cancel your booking.(Y/N)" << endl;
                    cin >> co;
                    int fm;
                    if(co=="N"||co=="n")
                    {
                        cout << "Enjoy your movie...!!!!" << endl;
                    }
                    if(co=="Y"||co=="y")
                    {
                        int ws=0;
                        cout << "HUMAN VERIFICATION" << endl << endl;
                        cout << "How many seats did you booked ?" << endl;
                        cin >> fm;
                        int pq[fm];
                        cout << "Input your selected seat numbers one at a time." << endl;
                        for(int i=0;i<fm;i++)
                        {
                            cout << "Input your " << i+1 << " seat number." << endl;
                            cin >> pq[i];
                        }
                        stringstream ll;
                        for(int i=0;i<fm;i++)
                        {
                            ll << pq[i] << "-";
                        }
                        stringstream a1;
                        a1 << "SELECT seats FROM booking WHERE ticket_id=" << xr.str().c_str();
                        qstate=mysql_query(conn,a1.str().c_str());
                        string m,t;
                        if(!qstate)
                        {
                            res=mysql_store_result(conn);
                            while(row=mysql_fetch_row(res))
                            {
                                if(strcmp(row[6],a1.str().c_str())==0)
                                {
                                    m=row[4];
                                    t=row[5];
                                    ws=1;
                                    break;
                                }
                                else
                                ws=0;
                            }
                        }
                        stringstream del;
                        del << "tickets/" << m << "/" << t << "/seats.dat";
                        ifstream fs;
                        fs.open(del.str().c_str());
                        int am[8][15];
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                am[i][j]=0;
                            }
                        }
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                fs >> am[i][j];
                            }
                        }
                        if(ws==0)
                        {
                            cout << "Invalid Deatails" << "\nYour booking cannot be cancelled unless you enter corrrect information." << endl;
                            exit(1);
                        }
                        if(ws==1)
                        {
                            for(int i=0;i<8;i++)
                            {
                                for(int j=0;j<12;j++)
                                {
                                    /*for(int k=0;k<fmk++)
                                    {
                                         if((i*j)==)
                                    }*/
                                }
                            }
                        }
                    }
                }
                if(p==0)
                {
                    cout << "Not found";
                }
                cout << "\np is " << p << endl;
            }
        }
    }
};
int main()
{
    almost al;
    int ch;
    cout << "--------------------------------------------------------------------" << endl;
    cout <<"|                        Welcome to Cinema.                          |" << endl;
    cout << "--------------------------------------------------------------------" << endl << endl;
    system("pause");
    system("cls");
    do
    {
        cout << "Input '1' to check connection to the database" << endl;
        cout << "Input '2' to view available movies." << endl;
        cout << "Input '3' to book movie tickets." << endl;
        cout << "Input '4' to view booked tickets." << endl;
        cout << "Input '5' to cancel booked tickets." << endl;
        cout << "Input 9811 to exit." << endl;
        cout << "What you wish to do ?" << endl;
        cin >> ch;
        switch(ch)
        {
            case 1:
            system("CLS");
            cout << "----------------------------------" << endl;
            al.check();
            break;
            case 2:
            system("CLS");
            al.show_movies();
            break;
            case 9811:
            system("CLS");
            cout << "----------------------------------" << endl;
            cout << "Have a good day.";
            break;
            case 3:
            al.book_movies();
            break;
            case 4:
            system("cls");
            al.show_tickets();
            break;
            case 5:
            al.cancel_tickets();
            break;
            default:
            system("CLS");
            cout << "Error.";
            break;
        }
    }
    while(ch!=9811);
}
