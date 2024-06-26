#include <iostream>
#include <cstring>
using namespace std;

// Your code here!!!

class MonthlyInvoice{
protected:
    char name[101];
    int number;
    double price;
    int gigabytes;
public:
    MonthlyInvoice(char *name, int number, double price, int gigabytes) : number(number), price(price),
                                                                          gigabytes(gigabytes) {
        strcpy(this->name, name);
    }
    virtual double total_price()const=0;
    MonthlyInvoice& operator++(int){
        gigabytes++;
        return *this;
    }
    bool operator>(MonthlyInvoice& m)const{
        return total_price() > m.total_price();
    }
    virtual void print(ostream& out)const = 0;
    friend ostream& operator<<(ostream& out, const MonthlyInvoice& m){
        m.print(out);
        return out;
    }
};

class BusinessInvoice: public MonthlyInvoice{
    bool optical;
    int quality;
public:
    BusinessInvoice(char *name, int number, double price, int gigabytes, bool optical, int quality) : MonthlyInvoice(
            name, number, price, gigabytes), optical(optical), quality(quality) {}

    double total_price() const override {
        int m(0);
        if (quality < gigabytes){
            m = gigabytes - quality;
        }
        return (m*100) + price * ((optical)? 1.5:1);
    }
    void print(ostream& out)const{
        out << number << " - " << name << ", " << price << endl;
        if (optical){
            out << "optical link, ";
        }else{
            out << "cable link, ";
        }
        int m(0);
        if (quality < gigabytes){
            m = gigabytes - quality;
        }
        out << m << endl;
    }
};

class PrivateInvoice: public MonthlyInvoice{
    char id[14];
    int *arr;
    int n;
public:
    PrivateInvoice(char *name, int number, double price, int gigabytes) : MonthlyInvoice(
            name, number, price, gigabytes){
        n = 0;
        arr = nullptr;
    }

    int total_gigs()const{
        int size(0);
        for (int i = 0; i < n; i++){
            size += arr[i];
        }
        return size;
    }

    double total_price() const override {
        return price + gigabytes*50 + total_gigs()*10;
    }

    PrivateInvoice& operator+=(int size){
        int* temp = new int[n+1];
        for (int i = 0; i < n; temp[i++]=arr[i]);
        delete[] arr;
        temp[n++] = size;
        arr = temp;
        return *this;
    }

    int& operator[](int i){
        return arr[i];
    }

    void print(ostream& out)const{
        out << number << " - " << name << ", " << price << endl << gigabytes << endl << n << ", " << total_gigs() << endl;
    }

    int getMoviesNo(){
        return n;
    }
};

MonthlyInvoice& biggestInvoice(MonthlyInvoice ** mi, int n){
    MonthlyInvoice* m = mi[0];
    for (int i = 0; i < n; i++){
        if (*mi[i] > *m){
            m = mi[i];
        }
    }
    return *m;
}



// Testing the program!!!
int main(){
    int test_case;
    char username[101];
    int userNumber;
    float basic_price;
    int spent_gigabytes;
    bool optical;
    int free_gigabytes;
    int num_inc;

    cin>>test_case;
    if (test_case == 1){
        // Test Case Business Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;
        cin>>optical>>free_gigabytes;
        BusinessInvoice bi(username, userNumber,basic_price, spent_gigabytes, optical, free_gigabytes);
        cout<<"BusinessInvoice Created:\n";
        cout<<bi;
    }
    else if (test_case == 2) {
        // Test Case Business Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "BusinessInvoice:\n";
        cout << bi;
        cout << "testing operator++\n";

        // Additional spent gigabytes
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            bi++;
        }
        cout << bi;
    }
    else if (test_case == 3) {
        // Test Case Business Invoice - Constructor, total_price, operators <<, ++,
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        cin >> optical >> free_gigabytes;
        BusinessInvoice bi(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
        cout << "Testing total_price()\n";
        cout << bi;
        cout<<bi.total_price()<<endl;
        bi++;
        cout << bi;
        cout<<bi.total_price()<<endl;
    }
    else if (test_case == 4){
        // Test Case Private Invoice - Constructor, operator <<
        cin>>username>>userNumber>>basic_price>>spent_gigabytes;

        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<"Private Invoice Created:\n";
        cout<<pi;
    }
    else if (test_case == 5) {
        // Test Case Private Invoice - Constructor, operators <<, ++
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i) {
            pi++;
        }
        cout << pi;
    }
    else if (test_case == 6) {
        // Test Case Private Invoice - Constructor, operators <<, +=
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
    }
    else if (test_case == 7) {
        // Test Case Private Invoice - Constructor, operators <<, +=, []
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cout << pi;
        cout << "Movie sizes: [";
        for (int i=0; i<pi.getMoviesNo(); ++i){
            cout << pi[i] << " ";
        }
        cout << "]" << endl;
    }
    else if (test_case == 8) {
        // Test Case Private Invoice - Constructor, total_price
        cin >> username >> userNumber >> basic_price >> spent_gigabytes;
        PrivateInvoice pi(username, userNumber,basic_price, spent_gigabytes);
        cout<<pi;
        cout<< pi.total_price() <<endl;
        cin >> num_inc;
        int film_length;
        for (int i=0; i<num_inc; ++i) {
            cin>>film_length;
            pi+=film_length;
        }
        cin >> num_inc;
        for (int i=0; i<num_inc; ++i){
            pi++;
        }
        cout << pi;
        cout<< pi.total_price() <<endl;
    }
    else if (test_case == 9) {
        // Test Case

        int num_invoices;
        int invoice_type;

        cin >>num_invoices;
        MonthlyInvoice ** mi = new MonthlyInvoice*[num_invoices];
        for (int j=0;j<num_invoices; ++j) {

            cin >> invoice_type;
            if (invoice_type == 1){
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                cin >> optical >> free_gigabytes;
                BusinessInvoice * bip;
                bip = new BusinessInvoice(username, userNumber, basic_price, spent_gigabytes, optical, free_gigabytes);
                cin >> num_inc;
                for (int i=0; i<num_inc; ++i) {
                    (*(bip))++;
                }
                cout << *(bip);
                cout<<bip->total_price()<<endl;

                mi[j] = bip;
            }
            if (invoice_type == 2) {
                cin >> username >> userNumber >> basic_price >> spent_gigabytes;
                PrivateInvoice* pip = new PrivateInvoice(username, userNumber, basic_price, spent_gigabytes);
                cin >> num_inc;
                int film_length;
                for (int i = 0; i < num_inc; ++i) {
                    cin >> film_length;
                    (*pip) += film_length;
                }
                cin >> num_inc;
                for (int i = 0; i < num_inc; ++i) {
                    (*pip)++;
                }
                cout << (*pip);
                cout << pip->total_price() << endl;
                mi[j] = pip;
            }
        }

        cout << "The biggest invoice is:\n";
        MonthlyInvoice& invoice = biggestInvoice(mi, num_invoices);

        MonthlyInvoice* m = &invoice;
        BusinessInvoice* bip;
        PrivateInvoice* pip;
        if (dynamic_cast<BusinessInvoice *> (m)){
            bip = dynamic_cast<BusinessInvoice *> (m);
            cout<<*bip << bip->total_price();
        }
        if (dynamic_cast<PrivateInvoice *> (m)){
            pip = dynamic_cast<PrivateInvoice *> (m);
            cout<<*pip << pip->total_price();
        }

    }
    return 0;
}