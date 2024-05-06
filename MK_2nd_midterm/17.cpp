    #include <iostream>
    #include <cstring>
    using namespace std;

    class FudbalskaEkipa{
    protected:
        char coach[101];
        int goals[10];
    public:
        FudbalskaEkipa(const char* coach="", const int* goals=nullptr){
            strcpy(this->coach, coach);
            for (int i = 0 ; i < 10; i++){
                this->goals[i] = goals[i];
            }
        }
        FudbalskaEkipa& operator+=(int goal){
            for (int i = 0; i < 9; i++){
                goals[i] = goals[i+1];
            }
            goals[9] = goal;
            return *this;
        }
        int scored()const{
            int sum(0);
            for(int i = 0; i < 10; i++){
                sum += goals[i];
            }
            return sum;
        }
        virtual int uspeh()const=0;

        bool operator>(const FudbalskaEkipa& fe)const{
            return this->uspeh() > fe.uspeh();
        }

        virtual void print(ostream& out)const=0;

        friend ostream& operator<<(ostream& out, FudbalskaEkipa& fe){
            fe.print(out);
            return out;
        }
    };

    class Klub:public FudbalskaEkipa{
        char name[100];
        int trophies;
    public:
        Klub(const char* coach="", const int* goals=nullptr, const char* name="", int trophies=0):
                FudbalskaEkipa(coach, goals), trophies(trophies){
            strcpy(this->name, name);
        }
        int uspeh()const{
            int sum = FudbalskaEkipa::scored();
            sum*=3;
            sum += trophies*1000;
            return sum;
        }

        void print(ostream& out)const{
            out << name << endl << coach << endl << uspeh() << endl;
        }
    };

    class Reprezentacija:public FudbalskaEkipa{
        char name[100];
        int appearances;
    public:
        Reprezentacija(const char* coach="", const int* goals=nullptr, const char* name="", int appearances=0):
                FudbalskaEkipa(coach, goals), appearances(appearances){
            strcpy(this->name, name);
        }
        int uspeh()const{
            int sum = FudbalskaEkipa::scored();
            sum*=3;
            sum += appearances*50;
            return sum;
        }
        void print(ostream& out)const{
            out << name << endl << coach << endl << uspeh() << endl;
        }
    };

    void najdobarTrener(FudbalskaEkipa** fes, int n){
        FudbalskaEkipa* fe = fes[0];
        for (int i = 0; i < n; i++){
            if (*fes[i] > *fe){
                fe = fes[i];
            }
        }
        cout << *fe;
    }

    int main() {
        int n;
        cin >> n;
        FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
        char coach[100];
        int goals[10];
        char x[100];
        int tg;
        for (int i = 0; i < n; ++i) {
            int type;
            cin >> type;
            cin.getline(coach, 100);
            cin.getline(coach, 100);
            for (int j = 0; j < 10; ++j) {
                cin >> goals[j];
            }
            cin.getline(x, 100);
            cin.getline(x, 100);
            cin >> tg;
            if (type == 0) {
                ekipi[i] = new Klub(coach, goals, x, tg);
            } else if (type == 1) {
                ekipi[i] = new Reprezentacija(coach, goals, x, tg);
            }
        }
        cout << "===== SITE EKIPI =====" << endl;
        for (int i = 0; i < n; ++i) {
            cout << *ekipi[i];
        }
        cout << "===== DODADI GOLOVI =====" << endl;
        for (int i = 0; i < n; ++i) {
            int p;
            cin >> p;
            cout << "dodavam golovi: " << p << endl;
            *ekipi[i] += p;
        }
        cout << "===== SITE EKIPI =====" << endl;
        for (int i = 0; i < n; ++i) {
            cout << *ekipi[i];
        }
        cout << "===== NAJDOBAR TRENER =====" << endl;
        najdobarTrener(ekipi, n);
        for (int i = 0; i < n; ++i) {
            delete ekipi[i];
        }
        delete [] ekipi;
        return 0;
    }