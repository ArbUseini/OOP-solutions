#include <iostream>
#include <cstring>
using namespace std;

class Patnik{
    char name[101];
    int carriage;
    bool bicycle;
public:
    Patnik(const char* name="", int carriage=1, bool bicycle=false){
        strcpy(this->name, name);
        this->carriage = carriage;
        this->bicycle = bicycle;
    }
    Patnik(const Patnik& p){
        strcpy(this->name, p.name);
        this->carriage = p.carriage;
        this->bicycle = p.bicycle;
    }
    Patnik& operator=(const Patnik& p){
        if (this != &p){
            strcpy(this->name, p.name);
            this->carriage = p.carriage;
            this->bicycle = p.bicycle;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Patnik& p){
        return out << p.name << endl << p.carriage << endl << p.bicycle << endl;
    }

    bool isBicycle() const {
        return bicycle;
    }

    int getCarriage() const {
        return carriage;
    }
};

class Voz{
    char destination[101];
    Patnik* patniks;
    int n;
    int allowed;
public:
    Voz(const char* destination="", int allowed=0){
        strcpy(this->destination, destination);
        this->allowed = allowed;
        this->n = 0;
        patniks = nullptr;
    }
    ~Voz(){
        delete[] patniks;
    }
    Voz& operator+=(const Patnik& p){
        if (allowed == 0 && p.isBicycle()){
            return *this;
        }
        Patnik* temp = new Patnik[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = patniks[i];
        }
        temp[n++] = p;
        delete[] patniks;
        patniks = temp;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Voz& v){
        out << v.destination << endl;
        for (int i  = 0; i < v.n; i++){
            out << v.patniks[i] << endl;
        }
        return out;
    }
    void patniciNemaMesto(){
        int f(0), s(0);
        for (int i = 0; i < n; i++){
            if (patniks[i].isBicycle() && patniks[i].getCarriage() == 1){
                allowed--;
                if (allowed < 0){
                    f++;
                    Patnik* temp = new Patnik[n-1];
                    int size(0);
                    for (int j = 0; j < n; j++){
                        if (i != j){
                            temp[size++] = patniks[j];
                        }
                    }
                    delete[] patniks;
                    patniks = temp;
                    n--;
                    i--;
                }
            }
        }
        for (int i = 0; i < n; i++){
            if (patniks[i].isBicycle() && patniks[i].getCarriage() == 2){
                allowed--;
                if (allowed < 0){
                    s++;
                    Patnik* temp = new Patnik[n-1];
                    int size(0);
                    for (int j = 0; j < n; j++){
                        if (i != j){
                            temp[size++] = patniks[j];
                        }
                    }
                    delete[] patniks;
                    patniks = temp;
                    n--;
                    i--;
                }
            }
        }
        cout << "Brojot na patnici od 1-va klasa koi ostanale bez mesto e: " << f << endl;
        cout << "Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: " << s << endl;
    }
};

int main(){
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}