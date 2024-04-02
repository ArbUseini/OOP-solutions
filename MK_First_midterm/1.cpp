#include <iostream>
#include <cstring>

using namespace std;

enum tip { POP, RAP, ROCK };

class Pesna{
    char* name;
    int duration;
    tip type;
public:
    Pesna(const char* name = "", int duration = 0, tip type=POP){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->duration = duration;
        this->type = type;
    }
    Pesna(const Pesna& p){
        this->name = new char[strlen(p.getName())+1];
        strcpy(this->name, p.getName());
        this->duration = p.getDuration();
        this->type = p.getType();
    }
    ~Pesna(){
        delete[] name;
    }
    
    Pesna& operator=(const Pesna& p) {
        if (this != &p) {
            delete[] name;
            this->name = new char[strlen(p.name) + 1];
            strcpy(this->name, p.name);
            this->duration = p.duration;
            this->type = p.type;
        }
        return *this;
    }

    void pecati(){
        cout << "\"" << name << "\"-" << duration <<"min" << endl;
    }

    char *getName() const {
        return name;
    }

    int getDuration() const {
        return duration;
    }

    tip getType() const {
        return type;
    }
};
class CD{
    Pesna pesni[10];
    int n;
    int max_d;
public:
    CD(int maxD=0) : max_d(maxD), n(0) {}

    CD& dodadiPesna(Pesna p) {
        if (n == 10 || max_d < p.getDuration()) {
            return *this;
        }
        pesni[n++] = p;
        max_d -= p.getDuration();
        return *this;
    }

    void pecatiPesniPoTip(tip t){
        for (int i = 0; i < n; i++){
            if (t == pesni[i].getType()){
                pesni[i].pecati();
            }
        }
    }
    Pesna getPesna(int i){
        return pesni[i];
    }
    int getBroj(){
        return n;
    }
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}