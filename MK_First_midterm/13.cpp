#include<iostream>
#include<string.h>
using namespace std;

class Zichara{
    char *place;
    int cost;
public:
    Zichara(const char* place="", int cost=0){
        this->place = new char[strlen(place) + 1];
        strcpy(this->place, place);
        this->cost = cost;
    }
    Zichara(const Zichara& z){
        this->place = new char[strlen(z.place) + 1];
        strcpy(this->place, z.place);
        this->cost = z.cost;
    }
    Zichara& operator=(const Zichara& z){
        if (this != &z){
            delete[] this->place;
            this->place = new char[strlen(z.place) + 1];
            strcpy(this->place, z.place);
            this->cost = z.cost;
        }
        return *this;
    }

    int getCost() const {
        return cost;
    }
};

class PlaninarskiDom{
    char name[16];
    int season[2];
    char klass;
    bool cable;
    Zichara* z;
public:
    PlaninarskiDom(const char* name="", const int* season = nullptr, char klass='F'){
        strcpy(this->name, name);
        if (season != nullptr){
            this->season[0] = season[0];
            this->season[1] = season[1];
        }else{
            this->season[0] = 0;
            this->season[1] = 0;
        }
        this->klass = klass;
        z = nullptr;
        cable = false;
    }
    PlaninarskiDom(const PlaninarskiDom& pd){
        strcpy(this->name, pd.name);
        this->season[0] = pd.season[0];
        this->season[1] = pd.season[1];
        this->klass = pd.klass;
        if (pd.z != nullptr){
            z = pd.z;
        }else{
            z = nullptr;
        }
        cable = pd.cable;
    }
    PlaninarskiDom& operator=(const PlaninarskiDom& pd){
        if (this != &pd){
            strcpy(this->name, pd.name);
            this->season[0] = pd.season[0];
            this->season[1] = pd.season[1];
            this->klass = pd.klass;
            strcpy(this->name, pd.name);
            this->season[0] = pd.season[0];
            this->season[1] = pd.season[1];
            this->klass = pd.klass;
            if (pd.z != nullptr){
                z = pd.z;
            }else{
                z = nullptr;
            }
            cable = pd.cable;
        }
        return *this;
    }
    PlaninarskiDom& operator--(){
        if(klass != 'F'){
            klass++;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const PlaninarskiDom& pd){
        out << pd.name <<" klasa:" << pd.klass;
        if (pd.cable) {
            out << " so Zichara";
        }
        out << endl;
        return out;
    }
    bool operator<=(char c)const{
        return klass >= c;
    }
    int presmetajDnevenPrestoj(int day, int month, int &price){
        if (day > 31 || month > 12){
            throw -1;
        }
        price = 0;
        if (month >= 4 && month <= 8){
            price += this->season[0];
        }else if(month == 9 && day == 1){
            price += this->season[0];
        }else{
            price += this->season[1];
        }
        if (this->cable){
            price += z->getCost();
        }
        return price;
    }
    void setZichara(Zichara& z){
        this->z = &z;
        this->cable = true;
    }

};

int main(){

    PlaninarskiDom p;

    char imePlaninarskiDom[15],mestoZichara[30],klasa;
    int ceni[12];
    int dnevnakartaZichara;
    bool daliZichara;
    cin>>imePlaninarskiDom;
    for (int i=0;i<2;i++) cin>>ceni[i];
    cin>>klasa;
    cin>>daliZichara;

    if (daliZichara) {
        cin>>mestoZichara>>dnevnakartaZichara;
        PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
        Zichara r(mestoZichara,dnevnakartaZichara);
        pom.setZichara(r);
        p=pom;
    }
    else{
        PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
        p=*pok;
    }

    --p;
    --p;

    int cena;
    int den,mesec;
    cin>>den>>mesec;
    try{
        p.presmetajDnevenPrestoj(den,mesec,cena);
        cout<<"Informacii za PlaninarskiDomot:"<<endl;
        cout<<p;
        if (p<='D')
            cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

        cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena;
    }
    catch (int){
        cout<<"Mesecot ili denot e greshno vnesen!";
    }
}
