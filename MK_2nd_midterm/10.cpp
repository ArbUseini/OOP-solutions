#include <iostream>
#include <string.h>
#include <cstdlib>

using namespace std;

class NegativnaVrednost{
    char msg[100];
public:
    NegativnaVrednost(const char* msg=""){
        strcpy(this->msg, msg);
    }
    void print(){
        cout << msg << endl;
    }
};

class Oglas{
    char title[51];
    char category[31];
    char description[101];
    double price;
public:
    Oglas(const char *title="", const char *category="", const char *description="", double price=0):price(price) {
        strcpy(this->title, title);
        strcpy(this->description, description);
        strcpy(this->category, category);
    }
    Oglas& operator=(const Oglas& o){
        if (this!=&o){
            strcpy(this->title, o.title);
            strcpy(this->description, o.description);
            strcpy(this->category, o.category);
            this->price = o.price;
        }
        return *this;
    }
    double getPrice() const {
        return price;
    }

    bool operator>(const Oglas& o)const{
        return price > o.price;
    }

    bool operator==(const char *k)const{
        return strcmp(category, k)==0;
    }

    friend ostream& operator<<(ostream& out, const Oglas& o){
        out << o.title << endl;
        out << o.description << endl;
        out << o.price << " evra" << endl;
        return out;
    }
};

class Oglasnik{
    char name[21];
    Oglas* os;
    int n;
public:
    Oglasnik(const char* name=""):os(nullptr), n(0){
        strcpy(this->name, name);
    }
    ~Oglasnik(){
        delete[] os;
    }
    Oglasnik& operator+=(const Oglas& o){
        try{
            if (o.getPrice() < 0){
                throw NegativnaVrednost("Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!");
            }
        }catch(NegativnaVrednost& nv){
            nv.print();
            return *this;
        }
        Oglas* temp = new Oglas[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = os[i];
        }
        temp[n++] = o;
        delete[] os;
        os = temp;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Oglasnik& ob){
        out << ob.name << endl;
        for (int i = 0; i < ob.n; i++){
            cout << ob.os[i] << endl;
        }
        return out;
    }
    void oglasiOdKategorija(const char *k){
        for (int i = 0; i < n; i++){
            if (os[i] == k){
                cout << os[i] << endl;
            }
        }
    }
    void najniskaCena(){
        double min(os[0].getPrice());
        int idx(0);
        for (int i = 0; i < n; i++){
            if (min > os[i].getPrice()){
                min = os[i].getPrice();
                idx = i;
            }
        }
        cout << os[idx] << endl;
    }
};

int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
