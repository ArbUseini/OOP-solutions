#include<iostream>
#include<string.h>
using namespace std;

class Koncert{
private:
    char name[21];
    char loc[21];
    double price;
    static double dis;
public:
    Koncert(const char* name="", const char* loc="", double price=0):price(price){
        strcpy(this->name, name);
        strcpy(this->loc, loc);
    }
    Koncert(const Koncert& k):price(k.price){
        strcpy(this->name, k.name);
        strcpy(this->loc, k.loc);
    }
    virtual ~Koncert(){}
    virtual double cena()const{
        return price - price*dis;
    }

    static void setSezonskiPopust(double dis) {
        Koncert::dis = dis;
    }

    double getPrice() const {
        return price;
    }

    const char *getLoc() const {
        return loc;
    }

    static double getSezonskiPopust() {
        return dis;
    }

    const char *getNaziv() const{
        return name;
    }

    bool operator==(const Koncert &rhs) const {
        return strcmp(name, rhs.name)==0;
    }
};

class ElektronskiKoncert:public Koncert{
    char* dj;
    double hours;
    bool time; //day-true/night- false
public:
    ElektronskiKoncert(const char* name="", const char* loc="", double price=0, const char* dj="", double hours=0, bool time=true):
            Koncert(name, loc, price), hours(hours), time(time){
        this->dj = new char[strlen(dj)+1];
        strcpy(this->dj, dj);
    }
    ElektronskiKoncert(const ElektronskiKoncert& ek):
            Koncert(ek.getNaziv(), ek.getLoc(), ek.getPrice()), hours(ek.hours), time(ek.time){
        this->dj = new char[strlen(ek.dj)+1];
        strcpy(this->dj, ek.dj);
    }
    ~ElektronskiKoncert(){
        delete[] dj;
    }
    double cena()const{
        double sum = Koncert::cena();
        if (hours > 7){
            sum+=360;
        }else if (hours > 5){
            sum+=150;
        }
        sum += (time)? -50:100;
        return sum;
    }
};

void najskapKoncert(Koncert ** koncerti, int n){
    double max(0);
    int elektro(0), idx(0);
    for (int i = 0; i < n; i++){
        double rel = koncerti[i]->cena();
        ElektronskiKoncert* ek = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if (rel > max){
            max = rel;
            idx = i;
        }
        if(ek){elektro++;}
    }
    cout << "Najskap koncert: " << koncerti[idx]->getNaziv() << " " << koncerti[idx]->cena() << endl;
    cout << "Elektronski koncerti: " << elektro << " od vkupno " << n << endl;
}

bool prebarajKoncert(Koncert ** koncerti, int n, char * name, bool electronic){
    for (int i = 0; i < n; i++){
        ElektronskiKoncert* ek = dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(!ek && electronic){ continue;}
        if (*koncerti[i] == name){
            cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
            return true;
        }
    }
    return false;
}

double Koncert::dis=0.2;

int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
