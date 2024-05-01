#include <iostream>
#include <cstring>
using namespace std;


// YOUR CODE HERE

class AlcoholicDrink{
protected:
    char name[101]; //101 because \0
    char country[101];
    double percent;
    double price;
    static int discount;
public:
    const char *getName() const {
        return name;
    }
    const char *getCountry() const {
        return country;
    }
    double getPercent() const {
        return percent;
    }
    double getPrice() const {
        return price;
    }
    virtual double computePrice() const = 0;

    friend ostream& operator<<(ostream& out, const AlcoholicDrink& alcoholicdrink){
        out << alcoholicdrink.name << " " << alcoholicdrink.country << " " << alcoholicdrink.computePrice();
        return out;
    }
    bool operator<(const AlcoholicDrink& alcoholicDrink) const{
        if (this->computePrice() < alcoholicDrink.computePrice()){
            return 1;
        }
        return 0;
    }
    static void changeDiscount(int d){
        discount = d;
    }
    static void total(AlcoholicDrink** drinks, int n){
        double sum(0);
        for (int i = 0; i < n; i++){
            sum += drinks[i]->computePrice();
        }
        cout << "Total price: " << sum << endl;
        cout << "Total price with discount: " << sum * (100 - discount) / 100 << endl;
    }
};

class Beer :public AlcoholicDrink{
private:
    bool ingredient; // barley=1/wheat=0
public:
    Beer(double percent, char *name, char *country, double price, bool ingredient){
        this->percent = percent;
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->price = price;
        this->ingredient = ingredient;
    }
    ~Beer(){}

    double computePrice() const{
        double add(0);
        if (strcmp(country, "Germany") == 0){
            add += price/20;
        }
        if (!ingredient){
            add += price/10;
        }
        return add+price;
    }
};

class Wine :public AlcoholicDrink{
private:
    int year;
    char grape[21];
public:
    Wine(double percent, char *name, char *country, double price, int year, char *grape){
        this->percent = percent;
        strcpy(this->name, name);
        strcpy(this->country, country);
        this->price = price;
        this->year = year;
        strcpy(this->grape, grape);
    }
    ~Wine() {}

    double computePrice() const{
        double add(0);
        if (strcmp(country, "Italy") == 0){
            add += price/20;
        }
        if (year < 2005){
            add += price*0.15;
        }
        return add+price;
    }
};

void lowestPrice(AlcoholicDrink ** drink, int n){
    int idx=0;
    for (int i = 0; i < n; i++){
        if (drink[i]->computePrice() < drink[idx]->computePrice()){
            idx = i;
        }
    }
    cout << *drink[idx] << endl;
}

int AlcoholicDrink::discount = 5;

// DO NOT CHANGE THE MAIN FUNCTION
int main() {
    int testCase;
    cin >> testCase;
    float p;
    char name[100];
    char country[100];
    float price;
    bool mainI;
    int year;
    char grape [20];
    if(testCase == 1) {
        cout << "===== TESTING CONSTRUCTORS ======" << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> mainI;
        Beer b(p, name, country, price, mainI);
        cout << b << endl;
        cin >> p;
        cin >> name;
        cin >> country;
        cin >> price;
        cin >> year;
        cin >> grape;
        Wine w(p, name, country, price, year, grape);
        cout << w << endl;

    } else if(testCase == 2) {
        cout << "===== TESTING LOWEST PRICE ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;

            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }

        lowestPrice(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    } else if(testCase == 3) {
        cout << "===== TESTING DISCOUNT STATIC ======" << endl;
        int n;
        cin >> n;
        AlcoholicDrink** ad = new AlcoholicDrink*[n];
        for(int i = 0; i < n; ++i) {
            cin >> p;
            cin >> name;
            cin >> country;
            cin >> price;
            if(i % 2 == 1){
                cin >> mainI;
                ad[i] = new Beer(p, name, country, price, mainI);
            }
            else {
                cin >> year;
                cin >> grape;
                ad[i] = new Wine(p, name, country, price, year, grape);
            }
        }
        AlcoholicDrink::total(ad, n);
        int d;
        cin >> d;
        AlcoholicDrink::changeDiscount(d);
        AlcoholicDrink::total(ad, n);
        for(int i = 0; i < n; ++i) {
            delete ad[i];
        }
        delete [] ad;
    }

}