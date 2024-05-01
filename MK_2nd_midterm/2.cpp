#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Vozac{
protected:
    char name[101];
    int age;
    int races;
    bool veteran;
public:
    Vozac(const char* name="", int age=0, int races=0, bool veteran=false):age(age), races(races), veteran(veteran){
        strcpy(this->name, name);
    }
    virtual double plata()const = 0;
    virtual double danok()const = 0;
    friend ostream& operator<<(ostream& out, const Vozac& v){
        out << v.name << endl << v.age << endl << v.races << endl;
        if (v.veteran){
            out << "VETERAN" << endl;
        }
        return out;
    }
    bool operator==(Vozac& v)const{
        return plata() == v.plata();
    }
};

class Avtomobilist: public Vozac{
    double price;
public:
    Avtomobilist(const char* name="", int age=0, int races=0, bool veteran=false, double price=0)
    : Vozac(name, age, races, veteran), price(price){}
    double plata()const{
        return price/5;
    }
    double danok()const{
        if (races > 10){
            return plata()*0.15;
        }
        else{
            return plata()*0.1;
        }
    }
};
class Motociklist: public Vozac{
    int power;
public:
    Motociklist(const char* name="", int age=0, int races=0, bool veteran=false, int power=0)
            : Vozac(name, age, races, veteran), power(power){}
    double plata()const{
        return power*20;
    }
    double danok()const{
        if (veteran){
            return plata()*0.25;
        }
        else{
            return plata()*0.2;
        }
    }
};

int soIstaZarabotuvachka(Vozac** vs, int n, Vozac* v){
    int count(0);
    for (int i = 0; i < n; i++){
        count += *v == *vs[i];
    }
    return count;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}