#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

class Book{
protected:
    char isbn[21];
    char title[51];
    char author[31];
    double cost;
public:
    Book(const char* isbn="", const char* title="", const char* author="", double cost=0):cost(cost){
        strcpy(this->isbn, isbn);
        strcpy(this->title, title);
        strcpy(this->author, author);
    }
    Book(const Book& b):cost(b.cost){
        strcpy(this->isbn, b.isbn);
        strcpy(this->title, b.title);
        strcpy(this->author, b.author);
    }
    Book& operator=(const Book& b){
        if (this != &b){
            strcpy(this->isbn, b.isbn);
            strcpy(this->title, b.title);
            strcpy(this->author, b.author);
            cost = b.cost;
        }
        return *this;
    }
    virtual ~Book(){}
    virtual double bookPricefor() const = 0;
    bool operator>(const Book& b) const{
        return this->bookPricefor() > b.bookPricefor();
    }
    friend ostream& operator<<(ostream& out, const Book& b){
        return out << b.isbn << ": " << b.title << ", " << b.author << " " << b.bookPricefor() << endl;
    }
    void setISBN(const char* isbn){
        strcpy(this->isbn, isbn);
    }
};

class OnlineBook: public Book{
    char* url;
    int size;
public:
    OnlineBook(const char* isbn="", const char* title="",
               const char* author="", double cost=0, const char* url="", int size=0)
            : Book(isbn, title, author, cost), size(size){
        this->url = new char[strlen(url) + 1];
        strcpy(this->url, url);
    }
    OnlineBook(const OnlineBook& ob)
            : Book(ob), size(ob.size) {
        this->url = new char[strlen(ob.url) + 1];
        strcpy(this->url, ob.url);
    }
    OnlineBook& operator=(const OnlineBook& ob){
        if (this != &ob){
            Book::operator=(ob);
            delete[] this->url;
            this->url = new char[strlen(ob.url) + 1];
            strcpy(this->url, ob.url);
        }
        return *this;
    }
    ~OnlineBook(){
        delete[] url;
    }
    double bookPricefor()const{
        if (size > 20){
            return cost*1.2;
        }
        return cost;
    }
};

class PrintBook: public Book{
    double mass;
    bool stonk;
public:
    PrintBook(const char* isbn="", const char* title="",
              const char* author="", double cost=0, double mass=0, bool stonk=false)
            : Book(isbn, title, author, cost), mass(mass), stonk(stonk){}

    PrintBook(const PrintBook& pb)
            : Book(pb), stonk(pb.stonk){}

    PrintBook& operator=(const PrintBook& pb){
        if (this != &pb){
            Book::operator=(pb);
            this->mass = pb.mass;
            this->stonk = pb.stonk;
        }
        return *this;
    }
    ~PrintBook(){}
    double bookPricefor()const{
        if (mass > 0.7){
            return cost*1.15;
        }
        return cost;
    }
};

void mostExpensiveBook (Book** books, int n){
    double max(-1);
    int idx(0), obs(0);
    for (int i = 0; i < n; i++){
        if (max < books[i]->bookPricefor()){
            max = books[i]->bookPricefor();
            idx = i;
        }
        OnlineBook* ob = dynamic_cast<OnlineBook*>(books[i]);
        if (ob){ obs++; }
    }
    cout << "FINKI-Education" << endl << "Total number of online books: " << obs << endl <<
         "Total number of print books: " << n-obs << endl;
    cout << "The most expensive book is: " << endl << *books[idx];
}

int main() {

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2) {
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3) {
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4) {
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++) {

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            } else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i < n; i++) delete books[i];
    delete[] books;
    return 0;
}