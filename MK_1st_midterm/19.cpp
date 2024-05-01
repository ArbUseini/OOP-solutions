#include <iostream>
#include <cstring>
using namespace std;

class IceCream{
    char* name;
    char composition[101];
    double price;
    int discount;
public:
    IceCream(const char* name="", const char* composition="", double price=0){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        strcpy(this->composition, composition);
        this->price = price;
        this->discount = 0;
    }
    IceCream(const IceCream& ic){
        this->name = new char[strlen(ic.name) + 1];
        strcpy(this->name, ic.name);
        strcpy(this->composition, ic.composition);
        this->price = ic.price;
        this->discount = ic.discount;
    }
    ~IceCream(){
        delete[] name;
    }
    void setName(char* name){
        delete[] this->name;
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
    }
    void setDiscount(int discount){
        if(discount >= 0 && discount <= 100)this->discount = discount;
    }
    friend ostream& operator<<(ostream& out, const IceCream ic){
        out << ic.name << ": " << ic.composition << " " << ic.price;
        if (ic.discount!=0){
            out << " (" << ic.price-ic.discount/100.0*ic.price << ")";
        }
        return out;
    }
    IceCream& operator++(){
        this->discount+=5;
        return *this;
    }
    IceCream& operator+(const char* name){
        char* nname = new char[strlen(this->name)+1];
        strcpy(nname, this->name);
        delete[] this->name;
        this->name = new char[strlen(name)+strlen(nname)+4];
        for (int i = 0; i < strlen(nname); i++){
            this->name[i] = nname[i];
        }
        this->name[strlen(nname)] = ' ';
        this->name[strlen(nname)+1] = '+';
        this->name[strlen(nname)+2] = ' ';
        for (int i = 0; i < strlen(name); i++){
            this->name[i+strlen(nname)+3] = name[i];
        }
        this->name[strlen(name)+strlen(nname)+3] = '\0';
        this->price += 10;
        return *this;
    }
    IceCream& operator=(const IceCream& ic){
        if (this != &ic){
            delete[] this->name;
            this->name = new char[strlen(ic.name) + 1];
            strcpy(this->name, ic.name);
            strcpy(this->composition, ic.composition);
            this->price = ic.price;
            this->discount = ic.discount;
        }
        return *this;
    }
};

class IceCreamShop{
    char name[51];
    IceCream* iceCream;
    int n;
public:
    IceCreamShop(const char* name=""){
        strcpy(this->name, name);
        iceCream = nullptr;
        this->n = 0;
    }
    IceCreamShop(const IceCreamShop& ics) : n(ics.n) {
        strcpy(name, ics.name);
        iceCream = new IceCream[n];
        for (int i = 0; i < n; ++i) {
            iceCream[i] = ics.iceCream[i];
        }
    }
    ~IceCreamShop(){
        delete[] iceCream;
    }
    IceCreamShop& operator+=(const IceCream& ic){
        IceCream *temp = new IceCream[this->n+1];
        for (int i = 0; i < this->n; i++){
            temp[i] = this->iceCream[i];
        }
        temp[this->n++] = ic;
        delete[] this->iceCream;
        this->iceCream = new IceCream[this->n];
        for (int i = 0; i < this->n; i++){
            this->iceCream[i] = temp[i];
        }
        delete[] temp;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const IceCreamShop& ics){
        out << ics.name << endl;
        for (int i = 0; i < ics.n; i++){
            out << ics.iceCream[i] << endl;
        }
        return out;
    }
    IceCreamShop& operator=(const IceCreamShop& ics){
        if (this != &ics){
            delete[] this->iceCream;
            this->iceCream = new IceCream[ics.n];
            for (int i = 0; i < ics.n; i++){
                this->iceCream[i] = ics.iceCream[i];
            }
            this->n = ics.n;
            strcpy(this->name, name);
        }
        return *this;
    }
};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }

    return 0;
}
