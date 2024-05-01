#include <iostream>
#include <cstring>
using namespace std;

enum Tip{
    LINUX, UNIX, WINDOWS
};

class OperativenSistem{
    char* os_name;
    double version;
    Tip type;
    double size;
public:
    OperativenSistem(const char* os_name="", double version=0, Tip type=WINDOWS, double size=0){
        this->os_name = new char[strlen(os_name)+1];
        strcpy(this->os_name, os_name);
        this->version = version;
        this->type = type;
        this->size = size;
    }
    OperativenSistem(const OperativenSistem& ops){
        this->os_name = new char[strlen(ops.os_name)+1];
        strcpy(this->os_name, ops.os_name);
        this->version = ops.version;
        this->type = ops.type;
        this->size = ops.size;
    }
    ~OperativenSistem(){
        delete[] os_name;
    }
    OperativenSistem& operator=(const OperativenSistem& ops){
        if(this != &ops){
            delete[] this->os_name;
            this->os_name = new char[strlen(ops.os_name)+1];
            strcpy(this->os_name, ops.os_name);
            this->version = ops.version;
            this->type = ops.type;
            this->size = ops.size;
        }
        return *this;
    }
    void pecati(){
        // Name: Ubuntu Version: 17.04 Type: 1 Size: 2.25GB
        cout << "Ime: " << os_name << " Verzija: " << version << " Tip: " << type << " Golemina:" << size << "GB" << endl;
    }
    bool ednakviSe(const OperativenSistem &ops){
        if (strcmp(os_name, ops.os_name)==0){
            if (version == ops.version){
                if (type == ops.type){
                    if (size == ops.size){
                        return true;
                    }
                }
            }
        }
        return false;
    }
    int sporediVerzija(const OperativenSistem &ops){
        if (version == ops.version){
            return 0;
        }
        if (version < ops.version){
            return -1;
        }
        return 1;
    }
    bool istaFamilija(const OperativenSistem &sporedba){
        if (strcmp(os_name, sporedba.os_name)==0){
            if (type == sporedba.type){
                return true;
            }
        }
        return false;
    }
};

class Repozitorium{
    char name[21];
    OperativenSistem* oses;
    int n;
public:
    Repozitorium(const char *ime=""){
        strcpy(name, ime);
        oses = nullptr;
        n = 0;
    }
    ~Repozitorium(){
        delete[] oses;
    }
    void pecatiOperativniSistemi(){
        cout << "Repozitorium: " << name << endl;
        for (int i = 0; i < n; i++){
            oses[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &operativenSistem){
        for (int i = 0; i < n; i++){
            if (oses[i].ednakviSe(operativenSistem)){
                OperativenSistem* temp = new OperativenSistem[n-1];
                int s(0);
                for (int j = 0; j < n; j++){
                    if (j != i){
                        temp[s++] = oses[j];
                    }
                }
                delete[] oses;
                oses = temp;
                n--;
                i--;
            }
        }
    }
    void dodadi(const OperativenSistem &nov){
        for (int i = 0; i < n; i++){
            if (oses[i].istaFamilija(nov) && oses[i].sporediVerzija(nov)==-1){
                OperativenSistem* temp = new OperativenSistem[n];
                for (int j = 0; j < n; j++){
                    if (j != i){
                        temp[i] = oses[j];
                    }
                    else{
                        temp[i] = nov;
                    }
                }
                delete[] oses;
                oses = temp;
                return;
            }
        }
        OperativenSistem* temp = new OperativenSistem[n+1];
        for (int j = 0; j < n; j++){
            temp[j] = oses[j];
        }
        temp[n++] = nov;
        delete[] oses;
        oses = temp;
    }
};

int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}