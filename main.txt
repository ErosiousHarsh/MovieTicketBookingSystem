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
            //cout << "\t\tSuccessfully connected to database." << endl;
            //cout << "\n";
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
        rev:
        stringstream fi;
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
                    if(strcmp((fi.str().c_str()),row[0])==0)
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
                cout << "Not Found." << endl;
                goto rev;
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
                            while(st>6||st<1)
                            {
                                cin.clear();
                                cout << "Min number of seats allowed is 1." << endl;
                                cout << "Max number of seats allowed are 6." << endl;
                                cout << "How many seats?" << endl;
                                cin >> st;
                            }
                        }
                        cout << "Here are avialable seats :-" << dir.str().c_str() << endl << endl;
                        fstream fin;
                        fin.open(dir.str().c_str());
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
                            exit(1);
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
                            asdf:
                            cout << "Input " << i+1 << "seat no. [1,2,3,etc]" << endl;
                            cin >> s[i].s_no;
                            if(s[i].s_no==0)
                            {
                                cout << "It's already booked." << endl;
                                goto asdf;
                            }
                            if(s[i].s_no>120)
                            {
                                cout << "Invalid seat.";
                                goto asdf;
                            }
                            if(s[i].s_no>=1&&s[i].s_no<=30)
                            s[i].cost=400;
                            else if(s[i].s_no>=31&&s[i].s_no<=90)
                            s[i].cost=300;
                            else if(s[i].s_no>=91&&s[i].s_no<=120)
                            s[i].cost=200;
                        }
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
        int b_id,sh,fd,smid,stid,f;
        string fsnm,lsnm;
        stringstream bd,so,sp,ss,ssl,nm,ph,em,mid,tid,snm;
        char sem[100],sph[100];
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
                                    r=0;
                                }
                            }
                        }
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
                        break;
                    }
                    case 2:
                    {
                        snm.str("");
                        snm.str("");
                        ph.str("");
                        em.str("");
                        mid.str("");
                        tid.str("");
                        cout << "\t\t\t\t\tData you enter here is case sensitive" << endl << endl;
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
                            cin.clear();
                            fflush(stdin);
                        }
                        if(f==0)
                        {
                            sp.str("");
                            system("cls");
                            /*cout << "Details are :-" << endl;
                            cout << "Name :- " << snm.str().c_str() << endl;
                            cout << "Phone:- " << ph.str().c_str() << endl;
                            cout << "Email :- " << em.str().c_str() << endl;
                            cout << "Movie id :- " << mid.str().c_str() << endl;
                            cout << "Time id :- " << tid.str().c_str() << endl;*/
                            cout << "Ticket found." << endl;
                            sp << "SELECT * FROM booking WHERE name='" << snm.str().c_str() << "' AND phone='" << sph << "' AND email='" << sem << "' AND m_id='" << smid << "' AND time_id='" << stid << "';";
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
        string sdf,m,t;
        if(check()==1)
        {
            char co[1];
            cout << "Input your booking id: ";
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
                            m=row[4];
                            t=row[5];
                        }
                        cout << "------------------------------------------------------------------------------------------------------------------" << endl;
                    }
                    stringstream del;
                    del << "tickets/" << m << "/" << t << "/seats.dat";
                    cout << del.str().c_str();
                    cout << "m is " << m << "\nt is " << t << endl;
                    cout << "Do you really want to cancel your booking.(Y/N)" << endl;
                    cin >> co;
                    int fm;
                    if(strcmp(co,"N")==0||strcmp(co,"n")==0)
                    {
                        cout << "Enjoy your movie...!!!!" << endl;

                    }
                    if(strcmp(co,"Y")==0||strcmp(co,"y")==0)
                    {
                        int ws=0;
                        string exp;
                        stringstream all;
                        all << "SELECT seats FROM booking WHERE ticket_id=" << xr.str().c_str();
                        qstate=mysql_query(conn,all.str().c_str());
                        if(!qstate)
                        {
                            res=mysql_store_result(conn);
                            while(row=mysql_fetch_row(res))
                            {
                                exp=row[0];
                            }
                        }
                        exp="-"+exp;
                        int le=exp.length();
                        char cn[le+1];
                        int sr[le];
                        for(int i=0;i<le;i++)
                        {
                            sr[i]=0;
                        }
                        char so,sq;
                        int cnt=0;
                        strcpy(cn,exp.c_str());
                        for(int i=0;i<le;i++)
                        {
                            if(cn[i-1]=='-'&&cn[i]>='0'&&cn[i+1]=='-')
                            {
                                sr[cnt]=(int)cn[i]-48;
                                cnt++;
                            }
                            else if(cn[i-1]=='-'&&cn[i]>='0'&&cn[i+1]>='0'&&cn[i+2]=='-')
                            {
                                sr[cnt]=(((int)cn[i]-48)*10)+((int)cn[i+1]-48);
                                cnt++;
                            }
                            else if(cn[i-1]=='-'&&cn[i]>='0'&&cn[i+1]>='0'&&cn[i+2]>='0'&&cn[i+3]=='-')
                            {
                                sr[cnt]=(((int)cn[i]-48)*100)+(((int)cn[i+1]-48)*10)+((int)cn[i+2]-48);
                                cnt++;
                            }
                        }
                        fstream fs;
                        fs.open(del.str().c_str(),ios::in);
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
                        int mcnt=0;
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<12;j++)
                            {
                                mcnt++;
                                for(int k=0;k<cnt;k++)
                                {
                                     if(mcnt==sr[k])
                                     {
                                         am[i][j]=mcnt;
                                     }
                                }
                            }
                        }
                        fs.close();
                        fstream bto;
                        bto.open(del.str().c_str(),ios::out);
                        if(!bto)
                        {
                            cout << "Error";
                            exit(1);
                        }
                        for(int i=0;i<8;i++)
                        {
                            for(int j=0;j<15;j++)
                            {
                                bto << am[i][j] << " ";
                            }
                            bto << endl;
                        }
                        bto.close();
                        stringstream wel;
                        wel << "DELETE FROM booking WHERE ticket_id=" << xr.str().c_str() << ";";
                        qstate=mysql_query(conn,wel.str().c_str());
                        if(!qstate)
                        {
                            cout << "Successfully cancelled your ticket bookings." << endl;
                        }
                    }
                }
                if(p==0)
                {
                    cout << "Not found";
                }
            }
        }
    }
    void add_movies()
    {
        system("cls");
        if(check()==1)
        {
            stringstream s_nm,s_rsd,s_mo,s_id,s_tp,s_scrt,s_yr,s_scm,s_sce,s_scn,s_uid;
            s_nm.str("");
            s_rsd.str("");
            s_mo.str("");
            s_id.str("");
            s_tp.str("");
            s_scrt.str("");
            s_yr.str("");
            s_scm.str("");
            s_sce.str("");
            s_scn.str("");
            s_uid.str("");
            string nm,rsd,mo_id,tp,scrt,yr,scc[3];
            cin.ignore(1,'\n');
            cout << "Input name of movie: ";
            getline(cin,nm);
            s_nm << nm;
            cout << "Input release date of movie: ";
            getline(cin,rsd);
            s_rsd << rsd;
            cout << "Input year of movie: ";
            getline(cin,yr);
            s_yr << yr;
            cout << "Input type of movie: ";
            getline(cin,tp);
            s_tp << tp;
            cout << "Input screen time of movie: ";
            getline(cin,scrt);
            s_scrt << scrt;
            cout << "Input 3 show timings of the movie." << endl;
            cout << "1:) Day Show: ";
            getline(cin,scc[0]);
            s_scm << scc[0];
            cout << endl;
            cout << "2:) Noon Show: ";
            getline(cin,scc[1]);
            s_sce << scc[1];
            cout << endl;
            cout << "3:) Night Show: ";
            getline(cin,scc[2]);
            s_scn << scc[2];
            int uid,ui;
            srand(time(0));
            ui=rand();
            uid=((ui+rand()+rand())*rand())/10000;
            s_uid << uid;
            int n_qstate;
            stringstream ins_m,ins_t;
            ins_m.str("");
            ins_t.str("");
            ins_m << "INSERT INTO movies VALUES('" << s_uid.str().c_str() << "','" << s_nm.str().c_str() << "','" << s_yr.str().c_str() << "','" << s_tp.str().c_str() << "','" << s_scrt.str().c_str() << "','" << s_rsd.str().c_str() << "');";
            ins_t << "INSERT INTO timings VALUES('" << s_uid.str().c_str() << "','" << s_scm.str().c_str() << "','" << s_sce.str().c_str() << "','" << s_scn.str().c_str() << "');";
            qstate=mysql_query(conn,ins_m.str().c_str());
            n_qstate=mysql_query(conn,ins_t.str().c_str());
            cout << "MOVIE: " << ins_m.str().c_str() << endl << endl;
            cout << "---------------------------------------------------" << endl;
            cout << "MOVIE: " << ins_t.str().c_str() << endl << endl;
            stringstream s_dir,sym;
            for(int i=1;i<=3;i++)
            {
                s_dir << "tickets/" << s_uid.str().c_str();
                mkdir(s_dir.str().c_str());
            }
            if(!qstate)
            {
                cout << "Successfully updated movies." << endl << endl;
            }
            if(!n_qstate)
            {
                cout << "Successfully updated timings." << endl << endl;
            }
            else
            {
                cout << "Error..!!!!" << endl << "Please try again later." << endl;
            }
        }
    }
    void rem()
    {
        system("cls");
        stringstream delm;
        int lk;
        cout << "Input movie id to remove it.";
        cin >> lk;
        delm.str("");
        delm << "DELETE FROM movies WHERE id=" << lk;
        if(check()==1)
        {
            qstate=mysql_query(conn,delm.str().c_str());
            if(!qstate)
            {
                cout << "Successfully removed movie." << endl;
            }
        }
    }
    /*void add_admin()
    {
        system("cls");
        stringstream admn,s_nme,s_passe;
        string nme,passe1,passe2;
        cout << "\t\t--------------------ADMINS HAVE ACCESS TO ADD AND REMOVE MOVIES--------------" << endl;
        cout << "\t\t-----------------------------NO SPACES ARE ALLOWED---------------------------" << endl;
        cin.ignore(1,'\n');
        cout << "Input username: ";
        getline(cin,nme);
        pas:
        cout << "Input password: ";
        getline(cin,passe1);
        cout << "Input password again: ";
        getline(cin,passe2);
        if(passe1!=passe2)
        {
            cout << "Password does not match." << endl;
            goto pas;
        }
        if(passe1==passe2)
        {
            if(check()==1)
            {
                admn.str("");
                admn << "INSERT INTO admin VALUES('" << nme << "','" << passe2 << "')";
                qstate=mysql_query(conn,admn.str().c_str());
                if(!qstate)
                {
                    cout << "Successfully added admin." << endl << endl;
                }
            }
        }
    }
    void rem_admin()
    {
        system("cls");
        string n_adm;
        cin.ignore(1,'\n');
        cout << "Input username of admin to be removed: ";
        getline(cin,n_adm);
        stringstream remadm;
        if(check()==1)
        {
            remadm << "DELETE FROM admin WHERE username="
        }
    }*/
    void admin()
    {
        int fnd=0;
        system("cls");
        stringstream usrnm_s,pass_s;
        cout << "\t\t\t\t--------------------" << endl;
        cout << "\t\t\t\t| Admin login page |" << endl;
        cout << "\t\t\t\t--------------------" << endl;
        string usrnm,pass;
        cout << "No spaces are allowed." << endl;
        cout << "Input your username: ";
        cin >> usrnm;
        usrnm_s << usrnm;
        cout << "Input your password: ";
        cin >> pass;
        pass_s << pass;
        stringstream adman;
        int chc;
        if(check()==1)
        {
            adman << "SELECT * FROM admin";
            qstate=mysql_query(conn,adman.str().c_str());
            if(!qstate)
            {
                res=mysql_store_result(conn);
                while(row=mysql_fetch_row(res))
                {
                    if(strcmp(usrnm_s.str().c_str(),row[0])==0&&strcmp(pass_s.str().c_str(),row[1])==0)
                    {
                        fnd=1;
                        break;
                    }
                }
            }
            if(fnd==0)
            {
                cout << "Invalid Details" << endl;
            }
            if(fnd==1)
            {
                do
                {
                    cout << "Input '1' to add movies." << endl;
                    cout << "Input '2' to delete movies." << endl;
                    //cout << "Input '3' to add administrators." << endl;
                    //cout << "Input '4' to delete administrator." << endl;
                    cout << "Input '9811' to exit." << endl;
                    cout << "Input your choice.(1/2/3/4)" << endl;
                    cin >> chc;
                    switch(chc)
                    {
                        case 1:
                        add_movies();
                        break;
                        case 2:
                        rem();
                        break;
                        /*case 3:
                        add_admin();
                        break;*/
                        case 9811:
                        system("cls");
                        break;
                    }

                }
                while(chc!=9811);
            }
        }
    }
};
int main()
{
    mein:
    almost al;
    int ch;
    cout << "\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t---------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t\t\t| ----------------------------------------------------------------- |" << endl;
    cout << "\t\t\t\t\t\t| |                       Welcome to Cinema                       | |" << endl;
    cout << "\t\t\t\t\t\t| ----------------------------------------------------------------- |" << endl;
    cout << "\t\t\t\t\t\t---------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t\t\t"; system("pause");
    system("cls");
    do
    {
        cout << "\t\t\t\tHere are the available movies." << endl << endl;
        al.show_movies();
        cout << "\n";
        //cout << "Input '1' to check connection to the database" << endl;
        cout << "Input '1' to book movie tickets." << endl;
        cout << "Input '2' to view booked tickets." << endl;
        cout << "Input '3' to cancel booked tickets." << endl;
        cout << "Input '4' for administrative access." << endl;
        cout << "Input 9811 to exit." << endl;
        cout << "What you wish to do ?" << endl;
        cin >> ch;
        switch(ch)
        {
            /*case 1:
            system("CLS");
            al.check();
            break;*/
            case 1:
            al.book_movies();
            break;
            case 2:
            system("cls");
            al.show_tickets();
            break;
            case 3:
            system("cls");
            al.cancel_tickets();
            break;
            case 4:
            system("cls");
            al.admin();
            break;
            case 9811:
            system("CLS");
            cout << "----------------------------------" << endl;
            cout << "Have a good day.";
            break;
            default:
            system("CLS");
            cout << "Error.";
            break;
        }
    }
    while(ch!=9811);
}
