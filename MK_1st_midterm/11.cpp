#include <iostream>
#include <cstring>
using namespace std;
class Ucesnik{
    char* name;
    bool gender;
    int age;
public:
    Ucesnik(const char* name = "", bool gender=true, int age=0){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->gender = gender;
        this->age = age;
    }
    ~Ucesnik(){
        delete[] name;
    }
    bool operator>(const Ucesnik& u) const{
        return this->age > u.age;
    }
    friend ostream& operator<<(ostream& out, const Ucesnik& u){
        return out << u.name << endl << ((u.gender)?"mashki":"zhenski ") << endl << u.age;
    }
    Ucesnik& operator=(const Ucesnik& u){
        if (this != &u){
            delete[] this->name;
            this->name = new char[strlen(u.name)+1];
            strcpy(this->name, u.name);
            this->age = u.age;
            this->gender = u.gender;
        }
        return *this;
    }

    int getAge() const {
        return age;
    }
};

class Maraton{
    char loc[100];
    Ucesnik* students;
    int n;
public:
    Maraton(const char* loc){
        strcpy(this->loc, loc);
        this->students = nullptr;
        this->n = 0;
    }
    ~Maraton(){
        delete[] students;
    }
    Maraton& operator+=(Ucesnik& m){
        Ucesnik *temp = new Ucesnik[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = this->students[i];
        }
        temp[n++] = m;
        delete[] this->students;
        this->students = new Ucesnik[n];
        for (int i = 0; i < n; i++){
            this->students[i] = temp[i];
        }
        delete[] temp;
        return *this;
    }
    double prosecnoVozrast()const{
        double avg(0);
        for (int i = 0; i < n; i++){
            avg += students[i].getAge();
        }
        return avg/n;
    }
    void pecatiPomladi(Ucesnik &u){
        for (int i = 0; i < n; i++){
            if (u.getAge() > students[i].getAge()){
                cout << students[i] << endl;
            }
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}