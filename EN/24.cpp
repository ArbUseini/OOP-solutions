#include<iostream>
#include<string.h>
using namespace std;

//your code here

class InvalidTimeException{
public:
    void print(){
        cout << "Invalid Time" << endl;
    }
};

class Race{
protected:
    char city[41];
    int year;
    int month;
    double seconds;
    double length;
public:
    Race(const char *city="", int year=0, int month=0, double seconds=0, double length=0) : year(year), month(month),
                                                                           seconds(seconds), length(length) {
        strcpy(this->city, city);
    }
    virtual double complexity()const{
        return seconds/length;
    }
    void print(ostream& out)const{
        out << city << " " << month << "." << year << " " << complexity() << endl;
    }
    friend ostream& operator<<(ostream& out, const Race& r){
        r.print(out);
        return out;
    }
};

class MotoGPRace: public Race{
    float* best_times;
    int n;
    int laps;
    static double coefficient;
public:
    MotoGPRace(const char *city="", int year=0, int month=0, double seconds=0, double length=0,
               float *bestTimes= nullptr, int n=0, int laps=0)
            : Race(city, year, month, seconds, length), n(n), laps(laps) {
        this->best_times = new float[n];
        for (int i = 0; i < n; i++){
            this->best_times[i] = bestTimes[i];
        }
    }

    double avg()const{
        double a(0);
        for (int i = 0; i < n; i++){
            a += best_times[i];
        }
        return a/n;
    }

    double complexity() const override {
        return (Race::complexity() + avg()*coefficient) * ((laps > 22)? 1.2 : 1);
    }

    void setNumberLaps(int laps) {
        MotoGPRace::laps = laps;
    }

    static void setK(double coefficient) {
        MotoGPRace::coefficient = coefficient;
    }

    MotoGPRace& operator+= (float num){
        if (num < 9.5){
            throw InvalidTimeException();
        }
        float* temp = new float[n+1];
        for (int i = 0 ; i < n; i++){
            temp[i] = best_times[i];
        }
        temp[n++] = num;
        delete[] best_times;
        best_times = temp;
        return *this;
    }
    MotoGPRace operator++(int) {
        MotoGPRace temp(*this);
        laps++;
        return temp;
    }

    int getNumberLaps()const{
        return laps;
    }

};

double MotoGPRace::coefficient=0.4;

int main(){
    int testCase;
    cin >> testCase;
    char city[50];
    int year;
    int month;
    float bestTime;
    float length;
    float bestTimes[50];
    int n;
    int m;
    int choice;
    int numberLaps;

    if (testCase == 1){
        cout << "===== Testing - classes ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        Race t(city, year, month, bestTime, length);
        cout<<t;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];
        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes, n, numberLaps);
        cout << mgt;
        MotoGPRace mgt2;
    }
    if (testCase == 2){
        cout << "===== Testing - operatorot += ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        // add a new best time
        float best;
        cin >> best;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace* nn = dynamic_cast<MotoGPRace*>(rArray[i]);
            if (nn != 0){
                flag = 0;
                (*nn) += best;
                break;
            }
        }

        // print the races
        cout << "\nLista na site Trki:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }
    if (testCase == 3){
        cout << "===== Testing - exceptions ======" << endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        MotoGPRace mgt(city, year, month, bestTime, length);
        mgt.setNumberLaps(numberLaps);
        float time1,time2;
        cin>>time1>>time2;
        try {
            mgt += time1;
            mgt += time2;
        }catch (InvalidTimeException e){
            e.print();
        }
        cout<<mgt;
    }
    if (testCase == 4){
        cout <<"===== Testing - operator++ ======"<<endl;
        cin >> city;
        cin >> year;
        cin >> month;
        cin >> bestTime;
        cin>>length;
        cin>>numberLaps;
        cin>>n;
        for (int j = 0; j < n; j++)
            cin >> bestTimes[j];

        MotoGPRace mgt(city, year, month, bestTime, length,bestTimes,n,numberLaps);
        float v,koef2;
        cout<<(mgt++).getNumberLaps()<<endl;
        cout<<mgt;
        mgt++;
        cout<<mgt;
    }
    if (testCase == 5){
        cout << "===== Testing - coefficient ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];

        MotoGPRace::setK(0.7);
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    if (testCase == 6){
        cout << "===== Testing - full functionality ======" << endl;
        Race **rArray;
        cin >> m;
        rArray = new Race *[m];
        for (int i = 0; i<m; i++){
            cin >> choice;
            cin >> city;
            cin >> year;
            cin >> month;
            cin >> bestTime;
            cin >>length;
            if (choice == 1){
                rArray[i] = new Race(city, year, month, bestTime, length);
            }
            else{
                cin>>numberLaps;
                cin>>n;
                for (int j = 0; j < n; j++)
                    cin >> bestTimes[j];
                rArray[i] = new MotoGPRace(city, year, month, bestTime, length,bestTimes, n, numberLaps);
            }
        }
        // print the races
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        float newCoef;
        cin>>newCoef;
        MotoGPRace::setK(newCoef);
        cout << "\nList of all races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
        // print the races
        float newBest;
        cin>>newBest;
        int flag = 1;
        for (int i = 0; i < m; i++){
            MotoGPRace * pok= dynamic_cast<MotoGPRace *>(rArray[i]);
            if(pok!=0)
            {
                (*pok)++;
                try{
                    (*pok)+=newBest;
                }
                catch (InvalidTimeException e){
                    e.print();
                }
                if(flag==1)
                {
                    flag = 0;
                    try{
                        *pok+=1.4;
                    }
                    catch (InvalidTimeException e){
                        e.print();
                    }
                    

                }
            }
        }
        cout << "\nList of the races:\n";
        for (int i = 0; i < m; i++)
            cout << *rArray[i];
    }

    return 0;
}
