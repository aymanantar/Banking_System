#include<bits/stdc++.h>
#include<fstream>
using namespace std;
class BankApp
{
public:
    void run () ;
    virtual void abs () = 0 ;
    virtual long long GetBal () = 0 ;
    virtual string GetID () = 0 ;
    virtual string  GetName () = 0 ;
    virtual string  GetAddress () = 0 ;
    virtual string GetPhone () = 0 ;
    virtual void displayClient () = 0 ;

};

class Client : public BankApp
{
private :
    string name ;
    string address ;
    string phone ;
    BankApp *AccountPtr ;
public:
    void abs () {};
    Client ( string n , string add , string p )
    {
        name = n ;
        address = add ;
        phone = p ;
    }
    Client ( string I ){
        string s;
        fstream ss ;
        ss.open("data.txt",ios::in);
        while (!ss.eof())
        {
            getline(ss,s,'|');
            if (I==s)
            {
                getline(ss,s,'|');
                getline(ss,s,'|');
                name=s;
                getline(ss,s,'|');
                address = s;
                getline(ss,s,'|');
                phone = s;
                getline(ss,s,'|');
            }
            else
            {
                getline(ss,s);
            }

        }
    }
    long long GetBal () {} ;
    string GetID () {} ;
    string GetName ()
    {
        return  name ;
    }
    string GetAddress ()
    {
        return address ;
    }
    string GetPhone ()
    {
        return  phone ;
    }
    void displayClient ()
    {
        cout<<name<<' '<<address<<' '<<phone<<endl;
    }
    void connect ( BankApp *Acc )
    {
        AccountPtr = Acc ;

    }
    BankApp *Accptr()
    {
        return AccountPtr ;
    }
};
class BankAccount : public BankApp {
private:
    string AccountID;
    long long Balance;
    BankApp *ClientPtr ;
    bool savings ;
public:
    string GetID ()
    {
        return  AccountID;
    }
    void SetSav (bool b){savings=b;}
    string GetName () { } ;
    string GetAddress () {} ;
    string GetPhone () {};
    void displayClient () {};
    void abs () {};
    BankAccount( ) {
        savings =0;
        AccountID = "FCAI";
        AccountID +="NOR";
        AccountID += to_string(Balance);
        Balance = 0;
        fstream f ;
        f.open("data.txt",ios::app);
        f<<AccountID<<endl;
    }

    BankAccount( long long B)
    {
        savings =0;
        AccountID= "FCAI";
        AccountID+="NOR";
        AccountID+=to_string(B);
        Balance = B;
        fstream f ;
        f.open("data.txt",ios::app);
        f<<AccountID<<endl;
        f.close();
    }
    BankAccount (string I ){
        bool exist = 0;
        savings =0;
        string s;
        fstream ss ;
        ss.open("data.txt",ios::in);
        while (!ss.eof())
        {
            getline(ss,s,'|');
            if (I==s)
            {
                AccountID = s;
                getline(ss,s,'|');
                Balance=stoi(s);
                getline(ss,s);
                exist = 1;

            }
            else
            {
                getline(ss,s);
            }
        }
        if (!exist)
        {
            cout<<"sorry, this id does't exist\n";
        }
    }

    void SetBal(long long B) {
        Balance = B;
    }

    long long GetBal() {
        return Balance;
    }
    void connect ( BankApp *Acc )
    {
        ClientPtr = Acc ;
    }
    void setID (string id)
    {
        AccountID = id ;
    }
    BankApp *ClPtr ()
    {
        return ClientPtr ;
    }
    int GetType ()
    {
        return 0;
    }
    ~BankAccount ( )
    {
        string s;
        fstream from , to ;
        to.open("temp.txt",ios::out);
        to.clear();
        to.close();
        from.open("data.txt",ios::in);
        to.open("temp.txt",ios::app);
        while (getline(from,s))
        {
            to<<s<<endl;
        }
        from.close();
        to.close ();
        to.open("data.txt",ios::out);
        to.clear();
        to.close();
        from.open("temp.txt",ios::in);
        to.open("data.txt",ios::app);
        while (getline(from,s))
        {
            string id = "";
            int i = 0 ;
            while (i<s.size()&&s[i]!='|'){id+=s[i]; i++;}
            if (id == AccountID)
            {
                to<<AccountID<<'|'<<Balance<<'|'<<(this->ClPtr())->GetName()<<'|'<<(this->ClPtr())->GetAddress()<<'|'<<(this->ClPtr())->GetPhone()<<'|'<<savings<<endl;
            }
            else
            {
                to<<s<<endl;
            }
        }

    }

    /*void withdraw (long long wd)
    {
        if (Balance >= wd )
        {
            Balance -= wd ;
            cout<<"withdraw done, your new balance is "<<Balance<<endl;
        }
        else
        {
            cout<<"no enough balance to do such operation\n";
        }
    }
    void deposit (long long de )
    {
        Balance += de ;
        cout<<"deposit done, your new balance is "<<Balance<<endl;
    }*/
};
class SavingsBankAccount : public BankAccount
{

public:
    SavingsBankAccount (long long bal = 0)
    {
        SetBal(bal-1000);
        SetSav(1);
    }
    SavingsBankAccount ( string I ) : BankAccount (I) {}
    void SetBal(long long B)
    {
        BankAccount::SetBal(B);
        SetSav(1);
    }
    int GetType ()
    {
        return 1;
    }

    long long GetBal()
    {
        return BankAccount::GetBal();
    }

};
int main() {
int c = 1;
while (c)
{
    cout<<"Welcome to FCAI Banking Application\n"
    <<"1. Create a New Account\n"
    <<"2. List Clients and Accounts\n"
    <<"3. Withdraw Money\n"
    <<"4. Deposit Money\n"
    <<"0. Exit\n";
    cin>>c;
    switch (c)
    {
    case 1 :
        {
            string name, address, phone ;
            bool savings ;
            long long balance;
            cout<<"Please Enter Client Name\n";
            cin.clear(); cin.sync(); getline(cin,name);
            cout<<"Please Enter Client Address\n";
            cin.clear(); cin.sync(); getline(cin,address);
            cout<<"Please Enter Client Phone\n";
            cin.clear(); cin.sync(); getline(cin,phone);
            cout<<"What Type of Account Do You Like\n 0.normal account \n 1.savings account \n";
            cin>>savings;
            cout<<"Please Enter the Starting Balance\n";
            cin>>balance;
            Client cl (name, address, phone);
            if (savings)
            {
                if (balance>=1000)
                {
                    SavingsBankAccount acc (balance);
                    acc.connect(&cl);
                    cout<<"An account was created with ID "<<acc.GetID()<<" and Starting Balance "<<acc.GetBal()<<" L.E.\n";
                }
                else
                {
                    cout<<"To create SavingsAccount, minimum balance should be 1000 \n";
                }

            }
            else
            {
                BankAccount acc (balance);
                acc.connect(&cl);
                cout<<"An account was created with ID "<<acc.GetID()<<" and Starting Balance "<<acc.GetBal()<<" L.E.\n";

            }
            break ;
        }
    case 2 :
        {
            fstream f;
            f.open("data.txt",ios::in);
            while(!f.eof())
            {
                string s;
                cout<<"...........................................................................................\n";
                getline(f,s,'|');
                if (s==""){break;}
                cout<<"id : "<<s<<endl;
                getline(f,s,'|');
                cout<<"balance : "<<s<<endl;
                getline(f,s,'|');
                cout<<"name : "<<s<<endl;
                getline(f,s,'|');
                cout<<"adress : "<<s<<endl;
                getline(f,s,'|');
                cout<<"phone number : "<<s<<endl;
                getline(f,s,'\n');
                cout<<"account type : "<<( (s=="1")? "SavingsAccount" : "NormalAccount" )<<endl;
            }
            break;
        }
    case 3 :
        {
            cout<<"enter account id\n";
            bool savings ;
            string id ;
            int amount ;
            cin>>id ;
            cout<<"What Type of Account Do You Like\n 0.normal account \n 1.savings account \n";
            cin>>savings;
            cout<<"enter the amount "<<endl;
            cin>>amount;
            if (savings)
            {
                SavingsBankAccount acc (id) ;
                Client cl (id);
                acc.connect(&cl);
                cout<<"welcome,  "<<cl.GetName()<<endl;
                if (acc.GetBal() >= amount )
                {
                    acc.SetBal(acc.GetBal()-amount);
                    cout<<"done, your new balance is "<<acc.GetBal()<<endl;
                }
                else
                {
                    cout<<"not enough balance in your account\n";
                }
            }
           else
            {
                BankAccount acc (id) ;
                Client cl (id);
                acc.connect(&cl);
                cout<<"welcome,  "<<cl.GetName()<<endl;
                if (acc.GetBal() >= amount )
                {

                    acc.SetBal(acc.GetBal()-amount);
                    cout<<"done, your new balance is "<<acc.GetBal()<<endl;
                }
                else
                {
                    cout<<"not enough money in your account\n";
                }
            }
            break;
        }
    case 4 :
        {
            cout<<"enter account id\n";
            bool savings ;
            string id ;
            int amount ;
            cin>>id ;
            cout<<"What Type of Account Do You Like\n 0.normal account \n 1.savings account \n";
            cin>>savings;
            cout<<"enter the amount "<<endl;
            cin>>amount;
            if (savings)
            {
                SavingsBankAccount acc (id) ;
                Client cl (id);
                acc.connect(&cl);
                cout<<"welcome,  "<<cl.GetName()<<endl;
                if (100 <= amount )
                {
                    acc.SetBal(acc.GetBal()+amount);
                    cout<<"done, your new balance is "<<acc.GetBal()<<endl;
                }
                else
                {
                    cout<<"minimum number to be added in SavingsAccounts is 100 \n";
                }
            }
            else
            {
                 BankAccount acc (id) ;
                 Client cl (id);
                 acc.connect(&cl);
                 cout<<"welcome,  "<<cl.GetName()<<endl;
                 acc.SetBal(acc.GetBal()+amount);
                 cout<<"done, your new balance is "<<acc.GetBal()<<endl;
            }
            break;
        }
    default :
        {
            if(!c)cout<<"wrong number was picked\n";
        }
    }
}

}

