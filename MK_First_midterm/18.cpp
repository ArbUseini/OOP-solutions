#include <iostream>
#include <cstring>
using namespace std;

class SkiLift{
    char name[16];
    int capacity;
    bool operate;
public:
    SkiLift(const char* name="", int capacity=0, bool operate=false){
        strcpy(this->name, name);
        this->capacity = capacity;
        this->operate = operate;
    }
    SkiLift(const SkiLift& sl){
        strcpy(this->name, sl.name);
        this->capacity = sl.capacity;
        this->operate = sl.operate;
    }
    SkiLift& operator=(const SkiLift& sl){
        strcpy(this->name, sl.name);
        this->capacity = sl.capacity;
        this->operate = sl.operate;
        return *this;
    }

    const char *getName() const {
        return name;
    }

    int getCapacity() const {
        return capacity;
    }

    bool isOperate() const {
        return operate;
    }
};

class SkiCenter{
    char* name;
    char country[21];
    SkiLift skiLifts[20];
    int n;
public:
    SkiCenter(const char* name="", const char* country=""){
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->n = 0;
    }
    SkiCenter(const SkiCenter& sc){
        this->name = new char[strlen(sc.name) + 1];
        strcpy(this->name, sc.name);
        strcpy(this->country, sc.country);
        this->n = sc.n;
    }
    SkiCenter& operator+=(const SkiLift& sl){
        skiLifts[n++] = sl;
        return *this;
    }

    char *getName() const {
        return name;
    }

    const char *getCountry() const {
        return country;
    }

    SkiLift getSkiLift(int i) const {
        return skiLifts[i];
    }

    int getN() const {
        return n;
    }
};

void najgolemKapacitet(SkiCenter *sc, int n){
    int max(-1), idx(0), greater(-1);
    for (int i = 0; i < n; i++){
        int relative(0), r_greater(0);
        for (int j = 0; j < sc[i].getN(); j++){
            if (sc[i].getSkiLift(j).isOperate()){
                relative += sc[i].getSkiLift(j).getCapacity();
                r_greater++;
            }
        }
        if (relative > max){
            max = relative;
            idx = i;
            greater = r_greater;
        }else if (relative == max){
            if (greater < r_greater){
                idx = i;
                greater = r_greater;
            }
        }
    }
    cout << sc[idx].getName() << endl << sc[idx].getCountry() << endl << max << endl;
}

int main(){
    int n;
    cin >> n;
    SkiCenter* skiCenters = new SkiCenter[n];
    for (int i = 0 ; i < n; i++){
        char name[100], country[21];
        cin >> name >> country;
        skiCenters[i] = SkiCenter(name, country);
        int m;
        cin >> m;
        for (int j = 0; j < m; j++){
            int capacity;
            bool operate;
            cin.get();
            cin >> name;
            cin >> capacity >> operate;
            SkiLift skiLift(name, capacity, operate);
            skiCenters[i]+=skiLift;
        }
    }
    najgolemKapacitet(skiCenters, n);
}
