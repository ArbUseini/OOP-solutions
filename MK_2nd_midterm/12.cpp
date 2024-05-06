#include <iostream>
#include <cstring>

using namespace std;

enum tip{
    smartphone, computer
};

class InvalidProductionDate{
    char msg[100];
public:
    InvalidProductionDate(const char* msg=""){
        strcpy(this->msg, msg);
    }
    void print(){
        cout << msg << endl;
    }
};

class Device{
    char model[101];
    tip type;
    static double inspection;
    int year;
public:
    Device(const char* model="", tip type=smartphone, int year=2000):type(type), year(year){
        strcpy(this->model, model);
    }
    Device(const Device& d):type(d.type), year(d.year){
        strcpy(this->model, d.model);
    }
    Device& operator=(const Device& d){
        if (this != &d){
            strcpy(this->model, d.model);
            this->type = d.type;
            this->year = d.year;
        }
        return *this;
    }

    static void setPocetniCasovi(int inspection){
        Device::inspection = inspection;
    }

    int getYear() const {
        return year;
    }

    double time()const{
        double sum(0);
        if (year > 2015){
            sum += 2;
        }
        if (type == computer){
            sum += 2;
        }
        return inspection+sum;
    }
    friend ostream& operator<<(ostream& out, const Device& d){
        return out << d.model << endl << ((d.type==smartphone)? "Mobilen ":"Laptop ") << d.time() << endl;
    }

};

class MobileServis{
    char name[101];
    Device* ds;
    int n;
public:
    MobileServis(const char *name=""):ds(nullptr), n(0){
        strcpy(this->name, name);
    }
    MobileServis& operator+=(const Device& d){
        try{
            if (d.getYear() > 2019 || d.getYear() < 2000){
                throw InvalidProductionDate("Невалидна година на производство");
            }
        }catch (InvalidProductionDate& i){
            i.print();
            return *this;
        }
        Device* temp = new Device[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = ds[i];
        }
        temp[n++] = d;
        delete[] ds;
        ds = temp;
        return *this;
    }
    void pecatiCasovi(){
        cout << "Ime: " << name << endl;
        for (int i = 0; i < n; i++){
            cout << ds[i];
        }
    }
};

double Device::inspection=1;

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}