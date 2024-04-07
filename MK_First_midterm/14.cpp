#include<iostream>
#include<cstring>

using namespace std;

enum Extension{
    TXT=1, PDF=0, EXE=2
};

class File{
    char* filename;
    Extension end;
    char* owner;
    int size;
public:
    File(const char* filename="", const char* owner="", int size=0, Extension end=TXT){
        this->filename = new char[strlen(filename)+1];
        strcpy(this->filename, filename);
        this->end = end;
        this->owner = new char[strlen(owner)+1];
        strcpy(this->owner, owner);
        this->size = size;
    }
    File(const File& f){
        this->filename = new char[strlen(f.filename)+1];
        strcpy(this->filename, f.filename);
        this->end = f.end;
        this->owner = new char[strlen(f.owner)+1];
        strcpy(this->owner, f.owner);
        this->size = f.size;
    }
    ~File(){
        delete[] filename;
        delete[] owner;
    }
    File& operator=(const File& f){
        if (this != &f){
            delete[] filename;
            delete[] owner;
            filename = new char[strlen(f.filename) + 1];
            owner = new char[strlen(f.owner) + 1];
            strcpy(this->filename, f.filename);
            strcpy(this->owner, f.owner);
            this->end = f.end;
            this->size = f.size;
        }
        return *this;
    }
    friend ostream& operator<<(ostream& out, const File& f){
        out << "File name: " << f.filename;
        if (f.end == TXT){
            out << ".txt" << endl;
        }else if (f.end == PDF){
            out << ".pdf" << endl;
        }else if (f.end == EXE){
            out << ".exe" << endl;
        }
        out << "File owner: " << f.owner << endl << "File size: " << f.size;
        return out;
    }
    bool operator==(const File& f)const{
        return (strcmp(filename, f.filename) == 0) && (strcmp(owner, f.owner) == 0) && (end == f.end);
    }
    bool equalsType(const File& f)const{
        return end == f.end;
    }
};

class Folder{
    char* name;
    File* files;
    int n;
public:
    Folder(const char* name=""){
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        files = nullptr;
        n = 0;
    }
    ~Folder(){
        delete[] name;
        delete[] files;
    }
    friend ostream& operator<<(ostream& out, const Folder& f){
        out << "Folder name: " << f.name << endl;
        for (int i = 0; i < f.n; i++){
            out << f.files[i] << endl;
        }
        return out;
    }
    Folder& operator-=(const File& f){
        for (int i = 0; i < n; i++){
            if (f == files[i]){
                File* temp = new File[n-1];
                int size = 0;
                for (int j = 0; j < n; j++){
                    if (i != j){
                        temp[size++] = files[j];
                    }
                }
                delete[] files;
                files = temp;
                n--;
            }
        }
        return *this;
    }
    Folder& operator+=(const File& f){
        File* temp = new File[n+1];
        for (int j = 0; j < n; j++){
            temp[j] = files[j];
        }
        temp[n++] = f;
        delete[] files;
        files = temp;
        return *this;
    }
};

int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        cout << created << endl;
        cout << endl;
        cout << "======= COPIED =======" << endl;
        cout << copied << endl;
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        cout << assigned << endl;
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        cout << first << endl;

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        cout << second << endl;

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        cout << third << endl;

        bool equals = first == second;
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first == third;
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second == third;
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        cout << folder << endl;

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder += file;
            iter--;
        }
        cout << folder << endl;
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder += file;
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder -= file;
        cout << folder << endl;
    }
    return 0;
}