#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde

class StockRecord{
    char id[13];
    char name[51];
    double price;
    double share;
    int num;
public:
    StockRecord(const char* id="", const char* name="", double price=0, int num=0){
        strcpy(this->id, id);
        strcpy(this->name, name);
        this->price = price;
        this->num = num;
    }
    StockRecord(const StockRecord& sr){
        strcpy(this->id, sr.getId());
        strcpy(this->name, sr.getName());
        this->price = sr.getPrice();
        this->share = sr.getShare();
        this->num = sr.getNum();
    }
    void setNewPrice(double c){
        this->share = c;
    }
    double value()const{
        return share*num;
    }
    double profit()const{
        return num*(share-price);
    }
    friend ostream& operator<<(ostream& out, const StockRecord& sr){
        return out << sr.name << " " << sr.num << " " << sr.price << " " << sr.share << " " << sr.profit();
    }
    StockRecord& operator=(const StockRecord& sr){
        if (this != &sr){
            strcpy(this->id, sr.getId());
            strcpy(this->name, sr.getName());
            this->price = sr.getPrice();
            this->share = sr.getShare();
            this->num = sr.getNum();
        }
        return *this;
    }

    const char *getId() const {
        return id;
    }

    const char *getName() const {
        return name;
    }

    double getPrice() const {
        return price;
    }

    double getShare() const {
        return share;
    }

    int getNum() const {
        return num;
    }
};

class Client{
    char fullName[61];
    int aId;
    StockRecord* capitalist;
    int n;
public:
    Client(char* fullName, int aId){
        strcpy(this->fullName, fullName);
        this->aId = aId;
        this->capitalist = nullptr;
        this->n = 0;
    }
    ~Client(){
        delete[] capitalist;
    }
    double value()const{
        double rich(0);
        for (int i = 0; i < n; i++){
            rich += capitalist[i].value();
        }
        return rich;
    }
    Client& operator+=(const StockRecord& sr){
        StockRecord *temp = new StockRecord[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = this->capitalist[i];
        }
        temp[n++] = sr;
        delete[] this->capitalist;
        this->capitalist = new StockRecord[n];
        for (int i = 0; i < n; i++){
            this->capitalist[i] = temp[i];
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Client& c){
        out << c.aId << " " << c.value() << endl;
        for (int i = 0; i < c.n; i++){
            out << c.capitalist[i] << endl;
        }
        return out;
    }
};

// ne menuvaj vo main-ot

int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr << endl;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}