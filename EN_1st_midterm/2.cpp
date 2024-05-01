#include<iostream>
#include<cstring>
#include <string>
using namespace std;

// Your code here
class Bill{
    char* number;
    int price;
    char issue[8];
    bool payed;
public:
    Bill(char* number, int price, char* issue, bool status){
        this->number = new char[sizeof(number)];
        strcpy(this->number, number);
        this->price = price;
        strcpy(this->issue, issue);
        payed = status;
    }
    bool operator==(const Bill& other) const{
        if (strcmp(number, other.number)==0){
            return true;
        }
        return false;
    }
    friend ostream& operator<<(ostream &out, const Bill& bill){
        out << bill.number << "(" << bill.issue << ") - " << bill.price;
        return out;
    }

    bool isPayed() const {
        return payed;
    }

    const char *getIssue() const {
        return issue;
    }

    int getMonth() const{
        return (issue[0]-'0')*10 + issue[1]-'0';
    }
    int getYear() const{
        return (issue[3]-'0')*1000 + (issue[4]-'0')*100 + (issue[5]-'0')*10 + issue[6]-'0';
    }

    int getPrice() const {
        return price;
    }
};

class UserProfile{
    char username[31];
    Bill *bills[30];
    int n;
public:
    UserProfile(char* name){
        strcpy(username, name);
        n = 0;
        for (int i = 0; i < 30; i++){
            bills[i] = NULL;
        }
    }
    UserProfile& operator+=(const Bill& bill){
        if (n >= 30){
            return *this;
        }
        for (int i = 0; i < n; i++){
            if (*bills[i] == bill){
                cout << "The bill already exists" << endl;
                return *this;
            }
        }
        bills[n] = new Bill(bill);
        n++;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const UserProfile& up){
        out << "Unpaid bills of user " << up.username << " are:\n";
        for (int i = 0; i < up.n; i++){
            if (!up.bills[i]->isPayed()){
                out << *up.bills[i] << endl;
            }
        }
        return out;
    }
    int totalDue(int month, int year){
        int sum(0);
        for (int i = 0; i < n; i++){
            int m = bills[i]->getMonth();
            int y = bills[i]->getYear();
            if (month == m && year == y){
                sum += bills[i]->getPrice();
            }
        }
        return sum;
    }
};

int main() {
    char number[50], month[8], name[50];
    int price, n;
    bool status;


    int type;
    cin >> type;

    if (type == 1) {
        cout << "-----Test Bill & operator &lt;&lt;-----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b(number, price, month, status);
        cout << b;
    } else if (type == 2) {
        cout << "-----Test Bill & operator == -----" << endl ;
        cin >> number >> price >> month >> status;
        Bill b1(number, price, month, status);
        cin >> number >> price >> month >> status;
        Bill b2(number, price, month, status);
        if (b1 == b2) cout << "Equal" << endl;
        else cout << "Not equal" << endl;
    } else if (type == 3) {
        cout << "-----Test UserProfile & operator += &&lt;&lt; -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
    } else if (type == 4) {
        cout << "-----Test UserProfile & operator += & totalDue -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    } else if (type == 5) {
        cout << "-----Test all -----" << endl ;
        cin >> name >> n;
        UserProfile up(name);
        for (int i = 0; i < n; i++) {
            cin >> number >> price >> month >> status;
            Bill s(number, price, month, status);
            up += s;
        }
        cout << up;
        int m, y;
        cin >> m >> y;
        cout << "Total due for month " << m << " and year " << y << " is:";
        cout << up.totalDue(m, y) << endl;
    }

    return 0;
}
