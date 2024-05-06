#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Exception{
    char msg[50];
public:
    Exception(const char* msg=""){
        strcpy(this->msg, msg);
    }
    void print()const{
        cout << msg << endl;
    }
};

class Trud{
    char paper;
    int year;
public:
    Trud(char paper='c', int year=0):paper(paper), year(year){}
    Trud(const Trud& t):paper(t.paper), year(t.year){}
    Trud operator=(const Trud& t){
        if (this != &t){
            paper = t.paper;
            year = t.year;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Trud& t){
        in.get();
        return in >> t.paper >> t.year;
    }

    char getPaper() const {
        return paper;
    }

    int getYear() const {
        return year;
    }
};

class Student{
    char name[31];
    int index;
    int enroll;
    int grades[100];
    int n;
public:
    Student(const char* name="", int index=0, int enroll=0, const int* grades=nullptr, int n=0):index(index), enroll(enroll), n(n){
        for (int i = 0; i < n; i++) {
            this->grades[i] = grades[i];
        }
        strcpy(this->name, name);
    }
    Student(const Student& s):index(s.index), enroll(s.enroll), n(s.n){
        for (int i = 0; i < n; i++){
            this->grades[i] = grades[i];
        }
        strcpy(this->name, name);
    }
    Student& operator=(const Student& s){
        if(this!=&s){
            index = s.index;
            enroll = s.enroll;
            n = s.n;
            for (int i = 0; i < n; i++) {
                this->grades[i] = grades[i];
            }
            strcpy(this->name, name);
        }
        return *this;
    }
    virtual ~Student(){}
    virtual double rang()const{
        double sum(0);
        for (int i = 0; i < n; i++){
            sum += grades[i];
        }
        return sum/n;
    }
    friend ostream& operator<<(ostream& out, const Student& s){
        return out << s.index << " " << s.name << " " << s.enroll << " " << s.rang() << endl;
    }


    int getEnroll() const {
        return enroll;
    }

    const char *getName() const {
        return name;
    }

    int getIndex() const {
        return index;
    }

    const int *getGrades() const {
        return grades;
    }

    int getN() const {
        return n;
    }
};

class PhDStudent: public Student{
    Trud* ts;
    int num;
    static int c;
    static int j;
public:
    PhDStudent(const char* name="", int index=0, int enroll=0, const int* grades=nullptr, int n=0, const Trud* ts= nullptr, int num=0):
            Student(name, index, enroll, grades, n), num(0){
        if (num == 0){
            this->ts = nullptr;
        }else{
            this->ts = new Trud[num];
            for (int i = 0; i < num; i++){
                this->operator+=(ts[i]);
            }
        }
    }
    PhDStudent(const PhDStudent& ps): Student(ps){
        this->num=0;
        if (ps.num == 0){
            this->ts = nullptr;
        }else{
            this->ts = new Trud[ps.num];
            for (int i = 0; i < ps.num; i++){
                this->operator+=(ts[i]);
            }
        }
    }
    PhDStudent& operator=(const PhDStudent& ps){
        if(this!=&ps){
            Student::operator=(ps);
            this->num=0;
            if (ps.num == 0){
                this->ts = nullptr;
            }else{
                this->ts = new Trud[ps.num];
                for (int i = 0; i < ps.num; i++){
                    this->operator+=(ts[i]);
                }
            }
        }
        return *this;
    }

    ~PhDStudent(){
        delete[] ts;
    }

    double rang()const{
        double sum = Student::rang();
        for (int i = 0; i < num; i++){
            if(tolower(ts[i].getPaper()) == 'c'){
                sum+=c;
            }else{
                sum+=j;
            }
        }
        return sum;
    }
    PhDStudent& operator+=(const Trud& t){
        try{
            if (t.getYear() < this->getEnroll()) {
                throw Exception("Ne moze da se vnese dadeniot trud");
            }
        }catch(Exception &ex){
            ex.print();
            return *this;
        }
        Trud* temp = new Trud[num+1];
        for (int i = 0; i < num; i++){
            temp[i] = ts[i];
        }
        temp[num++] = t;
        delete[] ts;
        ts = temp;
        return *this;
    }

    static void setC(int c) {
        PhDStudent::c = c;
    }

    static void setJ(int j) {
        PhDStudent::j = j;
    }
};

int PhDStudent::c=1;
int PhDStudent::j=3;

int main(){
    int testCase;
    cin >> testCase;

    int god, indeks, n, god_tr, m, n_tr;
    int izbor; //0 za Student, 1 za PhDStudent
    char ime[30];
    int oceni[50];
    char tip;
    Trud trud[50];

    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        Student s(ime, indeks, god, oceni, n);
        cout << s;

        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot +=
        bool pri(true);
        for (int i = 0; i < m; i++){
            PhDStudent *p = dynamic_cast<PhDStudent *>(niza[i]);
            if (p && p->getIndex()==indeks){
                *p += t;
                pri = false;
            }
        }
        if (pri){
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 3){
        cout << "===== Testiranje na operatorot += ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += od Testcase 2


        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 4){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin >> ime;
        cin >> indeks;
        cin >> god;
        cin >> n;
        for (int j = 0; j < n; j++)
            cin >> oceni[j];
        cin >> n_tr;
        for (int j = 0; j < n_tr; j++){
            cin >> tip;
            cin >> god_tr;
            Trud t(tip, god_tr);
            trud[j] = t;
        }
        PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
        cout << phd;
    }
    if (testCase == 5){
        cout << "===== Testiranje na isklucoci ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        // dodavanje nov trud za PhD student spored indeks
        Trud t;
        cin >> indeks;
        cin >> t;

        // vmetnete go kodot za dodavanje nov trud so pomos na operatorot += i spravete se so isklucokot
        bool pri(true);
        for (int i = 0; i < m; i++){
            PhDStudent *p = dynamic_cast<PhDStudent *>(niza[i]);
            if (p && p->getIndex()==indeks){
                *p += t;
                pri = false;
            }
        }
        if (pri){
            cout << "Ne postoi PhD student so indeks " << indeks << endl;
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }
    if (testCase == 6){
        cout << "===== Testiranje na static clenovi ======" << endl;
        Student **niza;
        cin >> m;
        niza = new Student *[m];
        for (int i = 0; i<m; i++){
            cin >> izbor;
            cin >> ime;
            cin >> indeks;
            cin >> god;
            cin >> n;
            for (int j = 0; j < n; j++)
                cin >> oceni[j];

            if (izbor == 0){
                niza[i] = new Student(ime, indeks, god, oceni, n);
            }
            else{
                cin >> n_tr;
                for (int j = 0; j < n_tr; j++){
                    cin >> tip;
                    cin >> god_tr;
                    Trud t(tip, god_tr);
                    trud[j] = t;
                }
                niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
            }
        }
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];

        int conf, journal;
        cin >> conf;
        cin >> journal;

        //postavete gi soodvetnite vrednosti za statickite promenlivi
        PhDStudent::setC(conf);
        PhDStudent::setJ(journal);
        // pecatenje na site studenti
        cout << "\nLista na site studenti:\n";
        for (int i = 0; i < m; i++)
            cout << *niza[i];
    }

    return 0;
}