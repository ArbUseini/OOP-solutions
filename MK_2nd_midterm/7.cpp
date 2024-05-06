#include<iostream>
#include<string.h>
using namespace std;

class OutOfBoundException{
    char msg[100];
public:
    OutOfBoundException(const char* msg=""){
        strcpy(this->msg, msg);
    }
    void print(){
        cout << msg << endl;
    }

};

class Karticka{
protected:
    char smetka[16];
    int pin;
    bool povekjePin;
public:
    Karticka(const char* smetka="",int pin=0){
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->povekjePin=false;
    }
    virtual int tezinaProbivanje()const{
        int sum(0), num(pin);
        while (num){
            sum++;
            num/=10;
        }
        return sum;
    }
    friend ostream& operator<<(ostream& out, const Karticka& k){
        return out << k.smetka << ": " << k.tezinaProbivanje() << endl;
    }

    const char *getSmetka() const {
        return smetka;
    }

    bool getDopolnitelenPin() const {
        return povekjePin;
    }
};

class SpecijalnaKarticka: public Karticka{
    int* codes;
    int n;
    const static int p; //4
public:
    SpecijalnaKarticka(const char* smetka="",int pin=0000): Karticka(smetka, pin), codes(nullptr), n(0){}
    int tezinaProbivanje()const{
        int sum(0), num(pin);
        while (num){
            sum++;
            num/=10;
        }
        return sum;
    }
    SpecijalnaKarticka& operator+=(int k){
        if (n >= p) {
            throw OutOfBoundException();
        }
        int* temp = new int[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = codes[i];
        }
        temp[n++] = k;
        delete[] codes;
        codes = temp;
    }

};

const int SpecijalnaKarticka::p = 4;


class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;//7
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
        strcpy(this->naziv,naziv);
        for (int i=0;i<broj;i++){
            //ako kartickata ima dopolnitelni pin kodovi
            if (karticki[i]->getDopolnitelenPin()){
                this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
            }
            else this->karticki[i]=new Karticka(*karticki[i]);
        }
        this->broj=broj;
    }
    ~Banka(){
        for (int i=0;i<broj;i++) delete karticki[i];
    }

    static void setLIMIT(int limit) {
        LIMIT = limit;
    }

    void pecatiKarticki(){
        cout << "Vo bankata "<< naziv << " moze da se probijat kartickite:" << endl;
        for (int i = 0; i < broj; i++){
            if (karticki[i]->tezinaProbivanje() <= LIMIT) {
                cout << *karticki[i];
            }
        }
    }

    void dodadiDopolnitelenPin(char* smetka, int novPin) {
        for (int i = 0; i < broj; i++) {
            if (strcmp(karticki[i]->getSmetka(), smetka) == 0 && karticki[i]->getDopolnitelenPin()) {
                try {
                    dynamic_cast<SpecijalnaKarticka*>(karticki[i])->operator+=(novPin);
                }
                catch (OutOfBoundException& obe) {
                    obe.print();
                }
                break;
            }
        }
    }
    //да се дополни класата

};

int Banka::LIMIT=7;



int main(){

    Karticka **niza;
    int n,m,pin;
    char smetka[16];
    bool daliDopolnitelniPin;
    cin>>n;
    niza=new Karticka*[n];
    for (int i=0;i<n;i++){
        cin>>smetka;
        cin>>pin;
        cin>>daliDopolnitelniPin;
        if (!daliDopolnitelniPin)
            niza[i]=new Karticka(smetka,pin);
        else
            niza[i]=new SpecijalnaKarticka(smetka,pin);
    }

    Banka komercijalna("Komercijalna",niza,n);
    for (int i=0;i<n;i++) delete niza[i];
    delete [] niza;
    cin>>m;
    for (int i=0;i<m;i++){
        cin>>smetka>>pin;
        komercijalna.dodadiDopolnitelenPin(smetka, pin);
    }

    Banka::setLIMIT(5);

    komercijalna.pecatiKarticki();

}
