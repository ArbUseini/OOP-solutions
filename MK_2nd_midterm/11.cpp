#include<iostream>
#include<string.h>
using namespace std;

//место за вашиот код

class Delo{
    char name[51];
    int year;
    char country[51];
public:
    Delo(const char* name="", int year=2000, const char* country=""):year(year){
        strcpy(this->name, name);
        strcpy(this->country, country);
    }
    Delo(const Delo& d):year(d.year){
        strcpy(this->name, d.name);
        strcpy(this->country, d.country);
    }

    bool operator==(const Delo& d)const{
        return strcmp(d.name, name)==0;
    }

    const char *getIme() const {
        return name;
    }

    int getYear() const {
        return year;
    }

    const char *getCountry() const {
        return country;
    }
};

class Pretstava{
protected:
    Delo d;
    int ticket;
    char date[16];
public:
    Pretstava(const Delo& d=NULL, int ticket=0, const char* date=""):d(d), ticket(ticket){
        strcpy(this->date, date);
    }

    const Delo &getDelo() const {
        return d;
    }

    int getTicket() const {
        return ticket;
    }

    virtual int cena()const{
        int sum(80);
        if (d.getYear() > 1900){
            sum += 50;
        }else if (d.getYear() > 1800){
            sum += 75;
        }else{
            sum += 100;
        }
        if (strcmp(d.getCountry(), "Italija")==0){
            sum += 20;
        }
        else if (strcmp(d.getCountry(), "Rusija")==0){
            sum += 70;
        }
        return sum;
    }

    
};

class Balet: public Pretstava{
    static int cost;
public:
    Balet(const Delo& d=NULL, int ticket=0, const char* date=""): Pretstava(d, ticket, date){}
    int cena()const{
        return cost+Pretstava::cena();
    }

    static void setCenaBalet(int cost) {
        Balet::cost = cost;
    }
};
class Opera: public Pretstava{
public:
    Opera(const Delo& d=NULL, int ticket=0, const char* date=""): Pretstava(d, ticket, date){}
};

int Balet::cost=150;

//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}

int prihod(Pretstava** ps, int n){
    int sum(0);
    for (int i = 0; i < n; i++){
        sum += ps[i]->cena()*ps[i]->getTicket();
    }
    return sum;
}

int brojPretstaviNaDelo(Pretstava** ps, int n, const Delo& d){
    int count(0);
    for (int i = 0; i < n; i++){
        if (ps[i]->getDelo() == d){
            count++;
        }
    }
    return count;
}

int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
