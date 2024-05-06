#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

#define MAX 50

enum typeC{
    standard, loyal, VIP
};

class Customer{
    char name[51];
    char email[51];
    typeC tc;
    int num;
    static int discount;
    const static int extra;
public:
    Customer(const char* name="", const char* email="", typeC tc=standard, int num=0):tc(tc), num(num){
        strcpy(this->name, name);
        strcpy(this->email, email);
    }
    Customer(const Customer& c):tc(c.tc), num(c.num){
        strcpy(this->name, c.name);
        strcpy(this->email, c.email);
    }
    Customer& operator=(const Customer& c){
        if (this != &c){
            strcpy(this->name, c.name);
            strcpy(this->email, c.email);
            tc = c.tc;
            num =c.num;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Customer& c){
        return out << c.name << endl << c.email << endl << c.num << endl << ((c.tc==standard)? "standard ":
        (c.tc==loyal)? "loyal ":"vip ") << ((c.tc==standard)? 0: (c.tc==loyal)? c.discount:c.discount+c.extra) << endl;
    }
    bool operator==(const Customer& c)const{
        return strcmp(this->email, c.email)==0;
    }

    int getNum() const{
        return num;
    }

    typeC getTc() const{
        return tc;
    }

    static void setDiscount1(int dis){
        discount = dis;
    }

    void setTc(typeC tc){
        Customer::tc = tc;
    }

};

class FINKI_bookstore{
    Customer* cs;
    int n;
public:
    FINKI_bookstore():cs(nullptr), n(0){}
    FINKI_bookstore& operator+=(const Customer& c){
        for (int i = 0; i < n; i++){
            if (cs[i] == c){
                cout << "The user already exists in the list!" << endl;
                return *this;
            }
        }
        Customer* temp = new Customer[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = cs[i];
        }
        temp[n++] = c;
        delete[] cs;
        cs = temp;
        return *this;
    }
    void update(){
        for (int i = 0; i < n; i++){
            if (cs[i].getTc() == standard && cs[i].getNum() >= 5){
                cs[i].setTc(loyal);
            }else if (cs[i].getTc() == loyal && cs[i].getNum() >= 10){
                cs[i].setTc(VIP);
            }
        }
    }
    friend ostream& operator<<(ostream& out, const FINKI_bookstore& fb){
        for (int i = 0; i < fb.n; i++){
            out << fb.cs[i];
        }
        return out;
    }

    void setCustomers(Customer *cs, int n) {
        this->n = n;
        delete[] this->cs;
        this->cs = new Customer[n];
        for (int i = 0; i < n; i++){
            this->cs[i] = cs[i];
        }
    }
};

int Customer::discount=10;
const int Customer::extra=20;


int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
