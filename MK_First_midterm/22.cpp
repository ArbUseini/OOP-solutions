#include <iostream>
#include <cstring>

using namespace std;

class Proizvod{
    char code[21];
    int cost;
    int ava;
public:
    Proizvod(const char* code="", int cost=0, int ava=0){
        strcpy(this->code, code);
        this->cost = cost;
        this->ava = ava;
    }
    Proizvod& operator=(const Proizvod& p){
        if (this != &p){
            strcpy(this->code, p.code);
            this->cost = p.cost;
            this->ava = p.ava;
        }
        return *this;
    }
    friend istream& operator>>(istream& in, Proizvod& p){
        in >> p.code >> p.cost >> p.ava;
        return in;
    }

    const char *getCode() const {
        return code;
    }

    int getCost() const {
        return cost;
    }

    int getAva() const {
        return ava;
    }
};

class Narachka{
    char name[16];
    Proizvod *pozs;
    int arr[10];
    int n;
public:
    Narachka(const char* name=""){
        strcpy(this->name, name);
        pozs = nullptr;
        n = 0;
    }
    Narachka& operator+=(const Proizvod& p){
        Proizvod* temp = new Proizvod[n+1];
        for (int i = 0; i < n; i++){
            temp[i] = pozs[i];
        }
        temp[n++] = p;
        delete[] pozs;
        pozs = temp;
        return *this;
    }

    friend void pecatiFaktura(Narachka n);
    friend istream& operator>>(istream& in, Narachka& nara){
        int m;
        in >> nara.name >> m;
        for (int i = 0; i < m; i++){
            Proizvod p;
            in >> p;
            nara += p;
        }
        for (int i = 0; i < nara.n; i++){
            in >> nara.arr[i];
        }
        return in;
    }
};

void pecatiFaktura(Narachka n) {
    cout << "Faktura za " << n.name << endl;

    for (int i = 0; i < n.n; ++i) {
        for (int j = 0; j < n.n - 1; ++j) {
            if (strcmp(n.pozs[j].getCode(), n.pozs[j + 1].getCode()) > 0) {
                Proizvod temp = n.pozs[j];
                n.pozs[j] = n.pozs[j + 1];
                n.pozs[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n.n; ++i) {
        if (n.arr[i] > n.pozs[i].getAva()) {
            cout << "Fakturata ne moze da se izgotvi";
            return;
        }
    }

    int s = 0;
    for (int i = 0; i < n.n; ++i) {
        cout << n.pozs[i].getCode() << " " << n.pozs[i].getCost() << " " << n.arr[i]
             << " " << n.arr[i] * n.pozs[i].getCost() << endl;
        s += n.arr[i] * n.pozs[i].getCost();

    }

    cout << "Vkupnata suma na fakturata e " << s << endl;
}

int main(){
    Narachka nara;
    cin >> nara;
    pecatiFaktura(nara);
}