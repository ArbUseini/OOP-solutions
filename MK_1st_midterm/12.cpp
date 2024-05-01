#include <iostream>
#include <cstring>
using namespace std;

class Pica{
    char name[16];
    int cost;
    char* ingredients;
    int discount;
public:
    Pica(const char* name="", int cost=0, const char* ingredients="", int discount=0){
        strcpy(this->name, name);
        this->cost = cost;
        this->ingredients = new char[strlen(ingredients)+1];
        strcpy(this->ingredients, ingredients);
        this->discount = discount;
    }
    Pica(const Pica& p){
        strcpy(this->name, p.name);
        this->cost = p.cost;
        this->ingredients = new char[strlen(p.ingredients)+1];
        strcpy(this->ingredients, p.ingredients);
        this->discount = p.discount;
    }
    ~Pica(){
        delete[] ingredients;
    }

    Pica& operator=(const Pica& p){
        if (this != &p){
            delete[] ingredients;
            strcpy(this->name, p.name);
            this->cost = p.cost;
            this->ingredients = new char[strlen(p.ingredients)+1];
            strcpy(this->ingredients, p.ingredients);
            this->discount = p.discount;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Pica& p){
        out << p.name << " - " << p.ingredients << ", " << p.cost << " " << p.cost*(100-p.discount)/100;
        return out;
    }
    bool operator==(const Pica& p){
        return strcmp(ingredients, p.ingredients)==0;
    }

    char *getIngredients() const {
        return ingredients;
    }

    int getDiscount() const {
        return discount;
    }
};

class Picerija{
    char name[16];
    Pica* pizzas;
    int n;
public:
    Picerija(const char* name=""){
        strcpy(this->name, name);
        pizzas = nullptr;
        n = 0;
    }
    Picerija (const Picerija& p){
        strcpy(this->name, p.name);
        this->n = p.n;
        this->pizzas = new Pica[n];
        for (int i = 0; i < n; i++){
            this->pizzas[i] = p.pizzas[i];
        }
    }
    ~Picerija(){
        delete[] pizzas;
    }
    Picerija& operator+=(const Pica& p){
        for (int i = 0; i < n; i++){
            if (strcmp(p.getIngredients(), pizzas[i].getIngredients())==0){
                return *this;
            }
        }
        Pica* temp = new Pica[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = pizzas[i];
        }
        temp[n++] = p;
        delete[] pizzas;
        pizzas = temp;
        return *this;
    }
    friend ostream& operator<<(ostream& out, const Picerija& p){
        for (int i = 0; i < p.n; i++){
            if (p.pizzas[i].getDiscount() != 0){
                out << p.pizzas[i] << endl;
            }
        }
        return out;
    }
    void setIme(const char* name){
        strcpy(this->name, name);
    }

    const char *getIme() const {
        return name;
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    cout << p1;

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    cout << p2;

    return 0;
}